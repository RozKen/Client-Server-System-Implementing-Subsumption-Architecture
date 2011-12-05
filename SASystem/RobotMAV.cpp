#include "RobotMAV.h"

RobotMAV::RobotMAV(){
	/////Sensorを追加
	///////Sensorには初期値も与える必要がある.
	//Batteryセンサを追加
	SenseBattery* sB = new SenseBattery();
	sB->setFBoard(0, 100.0f);
	this->addModule(sB);
	//位置センサを追加
	SensePos* sP = new SensePos();
	sP->setFBoard(0, START_X);
	sP->setFBoard(1, START_Y);
	this->addModule(sP);

	//距離センサを追加
	SenseRange* sR = new SenseRange();
	for(int i = 0; i < sR->getFBoardTitles()->size(); i++){
		sR->setFBoard(i, 4.0f);
	}
	this->addModule(sR);

	/////Controllerを追加
	//Alive
	ContAlive* cAl = new ContAlive();
	this->addModule(cAl);
	modColor[0][0] = 1.0f;
	modColor[0][1] = 0.0f;
	modColor[0][2] = 0.0f;
	//Avoid
	ContAvoid* cAv = new ContAvoid();
	this->addModule(cAv);
	modColor[1][0] = 0.0f;
	modColor[1][1] = 1.0f;
	modColor[1][2] = 0.0f;
	//Wander
	ContWander* cW = new ContWander();
	this->addModule(cW);
	modColor[2][0] = 0.5f;
	modColor[2][1] = 0.5f;
	modColor[2][2] = 0.5f;

	/////Actuatorを追加
	//位置Actuatorを追加
	ActPos* aP = new ActPos();
	this->addModule(aP);

	/////Arbiterを追加
	///先にWireObjects
	//Batteryセンサ->Alive
	Arbiter* sBcAl = new Arbiter(sB, 0, cAl, 0, 2.0f);
	this->addArbiter(sBcAl);
	//位置センサ->Alive
	Arbiter* sPcAl[2];
	for(int i = 0; i < 2; i++){
		sPcAl[i] = new Arbiter(sP, i , cAl, i+1, 2.0f);
		this->addArbiter(sPcAl[i]);
	}
	//距離センサ->Avoid
	Arbiter* sRcAv[RANGE_DIV];
	for(int i = 0; i < RANGE_DIV; i++){
		sRcAv[i] = new Arbiter(sR, i, cAv, i, 2.0f);
		this->addArbiter(sRcAv[i]);
	}
	//位置センサ->Wander
	Arbiter* sPcW[2];
	for(int i = 0; i < 2; i++){
		sPcW[i] = new Arbiter(sP, i, cW, i, 2.0f);
		this->addArbiter(sPcW[i]);
	}
	/////////以下の順番は重要．/////////
	/////////階層の低い者から実施するため////
	//Alive->位置Actuator	//Suppressされたデータが流れるWire
	Arbiter* cAlaP[2];
	for(int i = 0; i < 2; i++){
		cAlaP[i] = new Arbiter(cAl, i, aP, i, 2.0f);
		this->addArbiter(cAlaP[i]);
	}
	//Suppress Avoid -> 位置Actuator
	Arbiter* cAvaP[2];
	for(int i = 0; i < 2; i++){
		cAvaP[i] = new Arbiter(cAv, i, aP, i, 1.0f);
		this->addArbiter(cAvaP[i]);
	}
	//Suppress Wander -> 位置Actuator
	Arbiter* cWaP[2];
	for(int i = 0; i < 2; i++){
		cWaP[i] = new Arbiter(cW, i, aP, i, 1.0f);
		this->addArbiter(cWaP[i]);
	}

	numOfLayers = 3;
}

RobotMAV::RobotMAV(std::string directoryPath, std::string fileName)
	:Robot(directoryPath, fileName){
	/////Sensorを追加
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

	/////Controllerを追加
	//Alive
	ContAlive* cAl = new ContAlive();
	this->addModule(cAl);
	modColor[0][0] = 1.0f;
	modColor[0][1] = 0.0f;
	modColor[0][2] = 0.0f;
	//Avoid
	ContAvoid* cAv = new ContAvoid();
	this->addModule(cAv);
	modColor[1][0] = 0.0f;
	modColor[1][1] = 1.0f;
	modColor[1][2] = 0.0f;
	//Wander
	ContWander* cW = new ContWander();
	this->addModule(cW);
	modColor[2][0] = 0.5f;
	modColor[2][1] = 0.5f;
	modColor[2][2] = 0.5f;

	/////Actuatorを追加
	//位置Actuatorを追加
	ActPos* aP = new ActPos();
	this->addModule(aP);

	/////Arbiterを追加
	///先にWireObjects
	///0:Batteryセンサ->Alive
	Arbiter* sBcAl = new Arbiter(sB, 0, cAl, 0, 2.0f);
	this->addArbiter(sBcAl);
	///1,2:位置センサ->Alive
	Arbiter* sPcAl[2];
	for(int i = 0; i < 2; i++){
		sPcAl[i] = new Arbiter(sP, i , cAl, i+1, 2.0f);
		this->addArbiter(sPcAl[i]);
	}
	///3 - 14 :距離センサ->Avoid
	Arbiter* sRcAv[RANGE_DIV];
	for(int i = 0; i < RANGE_DIV; i++){
		sRcAv[i] = new Arbiter(sR, i, cAv, i, 2.0f);
		this->addArbiter(sRcAv[i]);
	}
	///15, 16:位置センサ->Wander
	Arbiter* sPcW[2];
	for(int i = 0; i < 2; i++){
		sPcW[i] = new Arbiter(sP, i, cW, i, 2.0f);
		this->addArbiter(sPcW[i]);
	}
	/////////以下の順番は重要．/////////
	/////////階層の低い者から実施するため////
	///17, 18:Alive->位置Actuator	//Suppressされたデータが流れるWire
	Arbiter* cAlaP[2];
	for(int i = 0; i < 2; i++){
		cAlaP[i] = new Arbiter(cAl, i, aP, i, 2.0f);
		this->addArbiter(cAlaP[i]);
	}
	///19, 20:Suppress Avoid -> 位置Actuator
	Arbiter* cAvaP[2];
	for(int i = 0; i < 2; i++){
		cAvaP[i] = new Arbiter(cAv, i, aP, i, 1.0f);
		this->addArbiter(cAvaP[i]);
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
	//Logを取る
	Log();
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
		case 19:	//Avoid Suppress Alive and ActPos
			ratios[0] = arbiters->at(i)->getCurrentRatio();
			break;
		case 21:	//Wander Suppress Avoid, Alive and ActPos
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

	std::cout << "colors: ";
	for(int j = 0; j < 3; j++){
		std::cout << color[j] << ",";
	}
	std::cout << std::endl;
}