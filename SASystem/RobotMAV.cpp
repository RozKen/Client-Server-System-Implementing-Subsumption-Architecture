#include "RobotMAV.h"
#include "World.h"

RobotMAV::RobotMAV(){
	Initialize();
}

RobotMAV::RobotMAV(std::string directoryPath, std::string fileName)
	:Robot(directoryPath, fileName){
	Initialize();
}

RobotMAV::~RobotMAV(){
	geoLog.close();
	radLog.close();

	nearest->clear();

	delete nearest;
}

void RobotMAV::Initialize(){
	///Memberの配列を初期化
	for(int i = 0; i < FIELD_SIZE; i++){
		for(int j = 0; j < FIELD_SIZE; j++){
			geoMap[i][j] = NO_DATA_ON_FIELD;
			radMap[i][j] = (float)NO_DATA_ON_FIELD;
			semMap[i][j] = NO_DATA_ON_FIELD;
		}
	}
	
	for(int i = 0; i < 3; i++){
		color[i] = 1.0f;
		for(int j = 0; j < 3; j++){
			modColor[i][j] = 1.0f;
		}
	}

	this->nearest = new std::vector<RobotMAV *>();

	///Sensorを追加
	///////Sensorにはどこかで初期値も与える必要がある.
	///Module 00 : Batteryセンサを追加
	sB = new SenseBattery();
	this->addModule(sB);
	
	///Module 01 : 位置センサを追加
	sP = new SensePos();
	this->addModule(sP);
	
	///Module 02 : 方向センサを追加
	sD = new SenseDirection();
	this->addModule(sD);

	///Module 03 : 距離センサを追加
	sR = new SenseRange();
	this->addModule(sR);
	

	///Module 04 : 放射線量センサを追加
	sRad = new SenseRadiation();
	this->addModule(sRad);

	///Module 05 : 充電器センサを追加
	sBc = new SenseBatteryCharger();
	this->addModule(sBc);

	///Module 06 : Network接続センサを追加
	sN = new SenseNet();
	this->addModule(sN);

	///Controllerを追加
	///////Controllerは発現したときの表現色を定義する必要がある
	///Module 07 : Avoid : Red
	cAv = new ContAvoid();
	this->addModule(cAv);
	modColor[0][0] = 1.0f;
	modColor[0][1] = 0.0f;
	modColor[0][2] = 0.0f;
	///Module 08 : Alive : Yellow
	cAl = new ContAlive();
	this->addModule(cAl);	
	modColor[1][0] = 1.0f;
	modColor[1][1] = 1.0f;
	modColor[1][2] = 0.0f;
	///Module 09 : Wander : Gray
	cW = new ContWander();
	this->addModule(cW);
	modColor[2][0] = 0.5f;
	modColor[2][1] = 0.5f;
	modColor[2][2] = 0.5f;

	///Module 10 : Smart Alive : Orange
	cSa = new ContSmartAlive();
	this->addModule(cSa);
	modColor[3][0] = 1.0f;
	modColor[3][1] = 0.5f;
	modColor[3][2] = 0.0f;
	
#ifdef SWAP_CCCE
	///Module 11 : ContExplore : Sky Blue
	cE = new ContExplore();
	this->addModule(cE);
	modColor[4][0] = 0.0f;
	modColor[4][1] = 1.0f;
	modColor[4][2] = 1.0f;

	///Module 12 : ContConnect : White
	cC = new ContConnect();
	this->addModule(cC);
	modColor[5][0] = 1.0f;
	modColor[5][1] = 1.0f;
	modColor[5][2] = 1.0f;

#else

	///Module 11 : ContConnect : White
	cC = new ContConnect();
	this->addModule(cC);
	modColor[4][0] = 1.0f;
	modColor[4][1] = 1.0f;
	modColor[4][2] = 1.0f;

	///Module 12 : ContExplore : Sky Blue
	cE = new ContExplore();
	this->addModule(cE);
	modColor[5][0] = 0.0f;
	modColor[5][1] = 1.0f;
	modColor[5][2] = 1.0f;

#endif	//SWAP_CCCE

	///Module 13 : ContArbitrateDestination : Purple?
	cAd = new ContArbitrateDestination(this);
	this->addModule(cAd);
	modColor[6][0] = 1.0f;
	modColor[6][1] = 0.0f;
	modColor[6][2] = 1.0f;

	/////Actuatorを追加
	///Module 14 : 位置Actuatorを追加
	aP = new ActPos();
	this->addModule(aP);

	std::cout << "Number of Modules" << this->getNumOfModules() << std::endl;

	///////////////////Arbiter/////////////////////////////
	///Arbiterを追加
	///先にWireObjects
	
	///0 - 11 :距離センサ->Avoid
	Arbiter* sRcAv[RANGE_DIV];
	for(int i = 0; i < RANGE_DIV; i++){
		sRcAv[i] = new Arbiter(sR, i, cAv, i, 2.0f);
		this->addArbiter(sRcAv[i]);
	}

	///12 : 方向センサ->Avoid
	Arbiter* sDcAv;
	sDcAv = new Arbiter(sD, 0, cAv, RANGE_DIV, 2.0f);
	this->addArbiter(sDcAv);
	
	///13 : Batteryセンサ->Alive
	Arbiter* sBcAl = new Arbiter(sB, 0, cAl, 0, 2.0f);
	this->addArbiter(sBcAl);
	
	///14, 15:位置センサ->Alive
	Arbiter* sPcAl[2];
	for(int i = 0; i < 2; i++){
		sPcAl[i] = new Arbiter(sP, i , cAl, i + 1, 2.0f);
		this->addArbiter(sPcAl[i]);
	}
	
	///16, 17:位置センサ->Wander
	Arbiter* sPcW[2];
	for(int i = 0; i < 2; i++){
		sPcW[i] = new Arbiter(sP, i, cW, i, 2.0f);
		this->addArbiter(sPcW[i]);
	}
	
	///18 - 27: Networkセンサ->Connect
	Arbiter* sNcC[WIFI_CONNECT * 2];
	for(int i = 0; i < WIFI_CONNECT * 2; i++){
		sNcC[i] = new Arbiter(sN, i, cC, i, 2.0f);
		this->addArbiter(sNcC[i]);
	}

	///28, 29 : 位置センサ -> SmartAlive
	Arbiter* sPcSa[2];
	for(int i = 0; i < 2; i++){
		sPcSa[i] = new Arbiter(sP, i, cSa, i, 2.0f);
		this->addArbiter(sPcSa[i]);
	}

	///30 : Batteryセンサ -> SmartAlive
	Arbiter* sBcSa = new Arbiter(sB, 0, cSa, 2, 2.0f);
	this->addArbiter(sBcSa);

	///31 : BatteryChargerセンサ -> SmartAlive
	Arbiter* sBccSa = new Arbiter(sBc, 0, cSa, 3, 2.0f);
	this->addArbiter(sBccSa);

	/////////以下の順番は重要．/////////
	/////////階層の低い者から実施するため////
	///32, 33:Avoid->位置Actuator	//Suppressされたデータが流れるWire
	Arbiter* cAvaP[2];
	for(int i = 0; i < 2; i++){
		cAvaP[i] = new Arbiter(cAv, i, aP, i, 2.0f);
		this->addArbiter(cAvaP[i]);
	}
	
	///34, 35:Suppress Alive -> 位置Actuator
	Arbiter* cAlaP[2];
	for(int i = 0; i < 2; i++){
		cAlaP[i] = new Arbiter(cAl, i, aP, i, 1.0f);
		this->addArbiter(cAlaP[i]);
	}
	
	///36, 37:Suppress Wander -> 位置Actuator
	Arbiter* cWaP[2];
	for(int i = 0; i < 2; i++){
		cWaP[i] = new Arbiter(cW, i, aP, i, 1.0f);
		this->addArbiter(cWaP[i]);
	}

	///38, 39:Suppress SmartAlive -> 位置Actuator
	Arbiter* cSaaP[2];
	for(int i = 0; i < 2; i++){
		cSaaP[i] = new Arbiter(cSa, i, aP, i, 1.0f);
		this->addArbiter(cSaaP[i]);
	}

#ifdef SWAP_CCCE
	///40, 41:Suppress Explore -> 位置Actuator
	Arbiter* cEaP[2];
	for(int i = 0; i < 2; i++){
		cEaP[i] = new Arbiter(cE, i, aP, i, 1.0f);
		this->addArbiter(cEaP[i]);
	}

	///42, 43:Suppress Connect -> 位置Actuator
	Arbiter* cCaP[2];
	for(int i = 0; i < 2; i++){
		cCaP[i] = new Arbiter(cC, i, aP, i, 1.0f);
		this->addArbiter(cCaP[i]);
	}

#else
	///40, 41:Suppress Connect -> 位置Actuator
	Arbiter* cCaP[2];
	for(int i = 0; i < 2; i++){
		cCaP[i] = new Arbiter(cC, i, aP, i, 1.0f);
		this->addArbiter(cCaP[i]);
	}

	///42, 43:Suppress Explore -> 位置Actuator
	Arbiter* cEaP[2];
	for(int i = 0; i < 2; i++){
		cEaP[i] = new Arbiter(cE, i, aP, i, 1.0f);
		this->addArbiter(cEaP[i]);
	}
#endif	//SWAP_CCCE

	///44, 45: Wire 位置Sensor -> ArbitrateDestination
	Arbiter* sPcAd[2];
	for(int i = 0; i < 2; i++){
		sPcAd[i] = new Arbiter(sP, i, cAd, i, 2.0f);
		this->addArbiter(sPcAd[i]);
	}
	
	std::cout << "Number of Arbiters" << this->getNumOfArbiters() << std::endl;
	std::cout << "Number of Inputs" << this->getNumOfInputPorts() << std::endl;
	std::cout << "Number of Outputs" << this->getNumOfOutputPorts() << std::endl;
	std::cout << "Number of fBoards" << this->innerMemory->getNumOfFBoards() << std::endl;
	std::cout << "Number of iBoards" << this->innerMemory->getNumOfIBoards() << std::endl;

	///////Initialize Map Log Files///////
	std::string filename = this->getLogFilePath();
	filename.append(".geoLog.csv");
	geoLog.open(filename);

	filename = this->getLogFilePath();
	filename.append(".radLog.csv");
	radLog.open(filename);

	filename = this->getLogFilePath();
	filename.append(".semLog.csv");
	semLog.open(filename);
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
	//地図を記録する
	//logMaps();
}

void RobotMAV::logMaps(){
	for(int i = 0; i < FIELD_SIZE; i++){
		for(int j = 0; j < FIELD_SIZE; j++){
			geoLog << geoMap[i][j] << ",";
			radLog << radMap[i][j] << ",";
			semLog << semMap[i][j] << ",";
		}
	}
	geoLog << std::endl;
	radLog << std::endl;
	semLog << std::endl;
}

void RobotMAV::Update(){
	updateInnerGeoMap();
	updateInnerRadMap();
	updateInnerSemMap();
}

float RobotMAV::getDX() const {
	return this->getOutput(0);
}

float RobotMAV::getDY() const {
	return this->getOutput(1);
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

float RobotMAV::getDirection() const{
	return this->getInput(3);
}
void RobotMAV::setDirection(float value){
	this->setInput(3, value);
}

float RobotMAV::getRange(int index) const{
	return this->getInput(4 + index);
}

void RobotMAV::setRange(int index, float value){
	this->setInput(4 + index, value);
}

float RobotMAV::getRad(int index) const{
	return this->getInput(4 + RANGE_DIV + index);
}

void RobotMAV::setRad(int index, float value){
	this->setInput(4 + RANGE_DIV + index, value);
}

int RobotMAV::getBatteryCharger() const{
	return this->getInput(4 + RANGE_DIV + MAX_AREA);
}

float RobotMAV::getRobot(int index, bool x){
	int odd = 1;
	if(x){
		odd = 0;
	}
	return this->getInput(4 + RANGE_DIV + MAX_AREA + 1 + index * 2 + odd);
}

void RobotMAV::setRobot(int index, float value, bool x){
	int odd = 1;
	if(x){
		odd = 0;
	}
	this->setInput(4 + RANGE_DIV + MAX_AREA + 1 + index * 2 + odd, value);
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
	float ratios[NUM_OF_LAYERS - 1];
	for(int i = 0; i < arbiters->size(); i++){
		arbiters->at(i)->Run();
		switch(i){
		case 34:	//Alive Suppress Avoid and ActPos
			ratios[0] = arbiters->at(i)->getCurrentRatio();
			break;
		case 36:	//Wander Suppress Alive, Avoid and ActPos
			ratios[1] = arbiters->at(i)->getCurrentRatio();
			break;
		case 38:	//Explore Suppress Wander, Alive, Avoid and ActPos
			ratios[2] = arbiters->at(i)->getCurrentRatio();
			break;
		case 40:	//Connect Suppress Explore, Wander, Alive, Avoid and ActPos
			ratios[3] = arbiters->at(i)->getCurrentRatio();
			break;
		case 42:
			ratios[4] = arbiters->at(i)->getCurrentRatio();
			break;
		default:
			break;
		}
	}

	//ratios[5] doesn't used. ContArbitrateDestination
	ratios[5] = 0.0f;

	///Set RobotColor According to Suppress
	for(int j = 0; j < 3; j++){
		color[j] = modColor[NUM_OF_LAYERS - 1][j] * ratios[NUM_OF_LAYERS - 2] 
		+ modColor[NUM_OF_LAYERS - 2][j] * (1.0f - ratios[NUM_OF_LAYERS - 2]);
	}

	for(int i = NUM_OF_LAYERS - 3; i >= 0; i--){
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
	//Self Acquired Data
	//まず，検知できる範囲をNORMALとする
	for(int i = -RANGE; i <= RANGE; i++){
		for(int j = -RANGE; j <= RANGE; j++){
			int x = i + round(this->getPosX());
			int y = j + round(this->getPosY());
			if( x >= 0 && x < FIELD_SIZE 
				&& y >= 0 && y < FIELD_SIZE){
				geoMap[x][y] = NORMAL;
			}
		}
	}
	//障害物があるところをOUTOFAREAとする
	for(int i = 0; i < RANGE_DIV; i++){
		float range = this->getRange(i);
		if(range < RANGE_DANGER){
			float dx = range * cos( (double)i * PI * RANGE_DEG / 180.0);
			float dy = range * sin( (double)i * PI * RANGE_DEG / 180.0);
			int x = round(this->getPosX() + dx);
			int y = round(this->getPosY() + dy);
			if( x >= 0 && x < FIELD_SIZE 
				&& y >= 0 && y < FIELD_SIZE){
				geoMap[x][y] = OUTOFAREA;
			}
		}
	}

	//Collect Data from Other Robots
	for(int i = 0; i < WIFI_CONNECT && i < nearest->size(); i++){
		RobotMAV* robot = nearest->at(i);
		int value;
		for(int j = 0; j < FIELD_SIZE; j++){
			for(int k = 0; k < FIELD_SIZE; k++){
				value = robot->geoMap[j][k];
				if(value != NO_DATA_ON_FIELD){
					this->geoMap[j][k] = value;
				}
			}
		}
	}
}

void RobotMAV::updateInnerRadMap(){
	//Self Acquired Data
	for(int i = 0; i < MAX_AREA; i++){
		int x = round(this->getPosX()) + ((World *)(this->parent))->getHash(0, i);
		int y = round(this->getPosY()) + ((World *)(this->parent))->getHash(1, i);
		if( x >= 0 && x < FIELD_SIZE 
				&& y >= 0 && y < FIELD_SIZE){
			radMap[x][y] = this->getRad(i);
		}
	}

	//Collect Data from Other Robots
	for(int i = 0; i < WIFI_CONNECT && i < nearest->size(); i++){
		RobotMAV* robot = nearest->at(i);
		float value;
		for(int j = 0; j < FIELD_SIZE; j++){
			for(int k = 0; k < FIELD_SIZE; k++){
				value = robot->radMap[j][k];
				if(value != NO_DATA_ON_FIELD){
					this->radMap[j][k] = value;
				}
			}
		}
	}
}

void RobotMAV::updateInnerSemMap(){
	//Self Acquired Data
	int x = this->getPosX();
	int y = this->getPosY();
	int onBattery = this->getBatteryCharger();
	this->semMap[x][y] = onBattery;

	//Collect Data from Other Robots
	for(int i = 0; i < WIFI_CONNECT && i < nearest->size(); i++){
		RobotMAV* robot = nearest->at(i);
		int value;
		for(int j = 0; j < FIELD_SIZE; j++){
			for(int k = 0; k < FIELD_SIZE; k++){
				value = robot->semMap[j][k];
				if(value != (int)NO_DATA_ON_FIELD){
					this->semMap[j][k] = value;
				}
			}
		}
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

float RobotMAV::getObjectiveX() const{
	return this->cE->getDestinationX();
}

float RobotMAV::getObjectiveY() const{
	return this->cE->getDestinationY();
}