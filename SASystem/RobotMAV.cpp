#include "RobotMAV.h"
#include "World.h"

RobotMAV::RobotMAV(){
	Initialize();
}

RobotMAV::RobotMAV(std::string directoryPath, std::string fileName)
	:Robot(directoryPath, fileName){
	Initialize();
}

void RobotMAV::Initialize(){
	///Memberの配列を初期化
	for(int i = 0; i < FIELD_SIZE; i++){
		for(int j = 0; j < FIELD_SIZE; j++){
			geoMap[i][j] = NO_DATA;
			radMap[i][j] = NO_DATA;
		}
	}

	numOfLayers = 0;
	
	for(int i = 0; i < 3; i++){
		color[i] = 1.0f;
		for(int j = 0; j < 3; j++){
			modColor[i][j] = 1.0f;
		}
	}

	this->nearest = new std::vector<RobotMAV *>();

	///Sensorを追加
	///////Sensorには初期値も与える必要がある.
	//Batteryセンサを追加
	SenseBattery* sB = new SenseBattery();
	this->addModule(sB);
	//sB->setFBoard(0, 100.0f);
	//位置センサを追加
	SensePos* sP = new SensePos();
	this->addModule(sP);
	//sP->setFBoard(0, START_X);
	//sP->setFBoard(1, START_Y);

	//距離センサを追加
	SenseRange* sR = new SenseRange();
	this->addModule(sR);
	//for(int i = 0; i < sR->getFBoardTitles()->size(); i++){
	//	sR->setFBoard(i, 4.0f);
	//}

	//放射線量センサを追加
	SenseRadiation* sRad = new SenseRadiation();
	this->addModule(sRad);

	//Network接続センサを追加
	SenseNet* sN = new SenseNet();
	this->addModule(sN);

	///Controllerを追加
	///Avoid : Red
	ContAvoid* cAv = new ContAvoid();
	this->addModule(cAv);
	modColor[0][0] = 1.0f;
	modColor[0][1] = 0.0f;
	modColor[0][2] = 0.0f;
	///Alive : Green
	ContAlive* cAl = new ContAlive();
	this->addModule(cAl);	
	modColor[1][0] = 0.0f;
	modColor[1][1] = 1.0f;
	modColor[1][2] = 0.0f;
	///Wander : Gray
	ContWander* cW = new ContWander();
	this->addModule(cW);
	modColor[2][0] = 0.5f;
	modColor[2][1] = 0.5f;
	modColor[2][2] = 0.5f;
	

	/////Actuatorを追加
	//位置Actuatorを追加
	ActPos* aP = new ActPos();
	this->addModule(aP);

	///Arbiterを追加
	///先にWireObjects
	///0 - 11 :距離センサ->Avoid
	Arbiter* sRcAv[RANGE_DIV];
	for(int i = 0; i < RANGE_DIV; i++){
		sRcAv[i] = new Arbiter(sR, i, cAv, i, 2.0f);
		this->addArbiter(sRcAv[i]);
	}
	///12:Batteryセンサ->Alive
	Arbiter* sBcAl = new Arbiter(sB, 0, cAl, 0, 2.0f);
	this->addArbiter(sBcAl);
	///13, 14:位置センサ->Alive
	Arbiter* sPcAl[2];
	for(int i = 0; i < 2; i++){
		sPcAl[i] = new Arbiter(sP, i , cAl, i + 1, 2.0f);
		this->addArbiter(sPcAl[i]);
	}
	///15, 16:位置センサ->Wander
	Arbiter* sPcW[2];
	for(int i = 0; i < 2; i++){
		sPcW[i] = new Arbiter(sP, i, cW, i, 2.0f);
		this->addArbiter(sPcW[i]);
	}
	/////////以下の順番は重要．/////////
	/////////階層の低い者から実施するため////
	///17, 18:Avoid->位置Actuator	//Suppressされたデータが流れるWire
	Arbiter* cAvaP[2];
	for(int i = 0; i < 2; i++){
		cAvaP[i] = new Arbiter(cAv, i, aP, i, 2.0f);
		this->addArbiter(cAvaP[i]);
	}
	///19, 20:Suppress Alive -> 位置Actuator
	Arbiter* cAlaP[2];
	for(int i = 0; i < 2; i++){
		cAlaP[i] = new Arbiter(cAl, i, aP, i, 1.0f);
		this->addArbiter(cAlaP[i]);
	}
	///21, 22:Suppress Wander -> 位置Actuator
	Arbiter* cWaP[2];
	for(int i = 0; i < 2; i++){
		cWaP[i] = new Arbiter(cW, i, aP, i, 1.0f);
		this->addArbiter(cWaP[i]);
	}
	std::cout << "Number of Arbiters" << this->getNumOfArbiters() << std::endl;
	this->numOfLayers = 3;
}

void RobotMAV::Run(){
	//RobotへのInputを処理する
	ProcessInputs();
	//Robotの各Moduleを動かす
	RunModules();
	//Arbiterを作動させる
	ProcessArbiters();
	//RobotからのOutputを処理する
	ProcessOutputs();
	//内部の情報を更新する
	Update();
	//Logを取る
	Log();
}

void RobotMAV::Update(){
	updateInnerGeoMap();
	//updateInnerRadMap();
}

float RobotMAV::getBattery() const{
	return this->getInput(0);
}
void RobotMAV::setBattery(float value){
	this->setInput(0, value);
}
float RobotMAV::getPosX() const{
	return this->getInput(1);
}
void  RobotMAV::setPosX(float value){
	this->setInput(1, value);
}
float RobotMAV::getPosY() const{
	return this->getInput(2);
}
void RobotMAV::setPosY(float value){
	this->setInput(2, value);
}

float RobotMAV::getRange(int index) const{
	return this->getInput(3 + index);
}

float RobotMAV::getRad(int index) const{
	return this->getInput(3 + RANGE_DIV + index);
}

void RobotMAV::setRad(int index, float value){
	this->setInput(3 + RANGE_DIV + index, value);
}

float RobotMAV::getColorR() const{
	return this->color[0];
}

float RobotMAV::getColorG() const{
	return this->color[1];
}
float RobotMAV::getColorB() const{
	return this->color[2];
}

void RobotMAV::ProcessArbiters(){
	float ratios[2];
	for(int i = 0; i < arbiters->size(); i++){
		arbiters->at(i)->Run();
		switch(i){
		case 19:	//Alive Suppress Avoid and ActPos
			ratios[0] = arbiters->at(i)->getCurrentRatio();
			break;
		case 21:	//Wander Suppress Alive, Avoid and ActPos
			ratios[1] = arbiters->at(i)->getCurrentRatio();
			break;
		default:
			break;
		}
	}

	///Set RobotColor According to Suppress
	for(int j = 0; j < 3; j++){
		color[j] = modColor[numOfLayers - 1][j] * ratios[numOfLayers - 2] 
		+ modColor[numOfLayers - 2][j] * (1.0f - ratios[numOfLayers - 2]);
	}
	for(int i = numOfLayers - 3; i >= 0; i--){
		for(int j= 0; j < 3; j++){
			color[j] = color[j] * ratios[i] + modColor[i][j] * (1.0f - ratios[i]);
		}
	}
	/*
	std::cout << "colors: ";
	for(int j = 0; j < 3; j++){
		std::cout << color[j] << ",";
	}
	std::cout << std::endl;
	*/
}

void RobotMAV::updateInnerGeoMap(){
	for(int i = 0; i < RANGE_DIV; i++){
		float range = this->getRange(i);
		if(range < RANGE_DANGER){
			float dx = range * cos( (double)i * PI * RANGE_DEG / 180.0);
			float dy = range * sin( (double)i * PI * RANGE_DEG / 180.0);
			int x = round(this->getPosX() + dx);
			int y = round(this->getPosY() + dy);
			geoMap[x][y] = OUTOFAREA;
		}
	}
}

void RobotMAV::updateInnerRadMap(){
	for(int i = 0; i < MAX_AREA; i++){
		int x = round(this->getPosX()) + ((World *)(this->parent))->getHash(0, i);
		int y = round(this->getPosY()) + ((World *)(this->parent))->getHash(1, i);
		radMap[x][y] = this->getRad(i);
	}
}

SenseNet* RobotMAV::getSenseNet(){
	///現在はSenseNetのModuleはindex == 3のところで登録されている．
	///もし，Moduleを登録する順番に変更があれば，ここも変更する必要がある．
	return (SenseNet*)(this->modules->at(3));
}

void RobotMAV::pushNearest(RobotMAV * robot){
	this->nearest->push_back(robot);
	numOfNearestRobots = nearest->size();
}

RobotMAV* RobotMAV::getNearestAt(int index){
	return this->nearest->at(index);
}

std::vector<RobotMAV *>* RobotMAV::getNearest(){
	return this->nearest;
}

void RobotMAV::clearNearest(){
	this->nearest->clear();
	numOfNearestRobots = 0;
}

int RobotMAV::getNumOfNearestRobots() const{
	return numOfNearestRobots;
}