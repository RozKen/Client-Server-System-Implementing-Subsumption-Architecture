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
	//Avoid
	ContAvoid* cAv = new ContAvoid();
	this->addModule(cAv);
	//Wander
	ContWander* cW = new ContWander();

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
	//Avoid
	ContAvoid* cAv = new ContAvoid();
	this->addModule(cAv);
	//Wander
	ContWander* cW = new ContWander();
	this->addModule(cW);

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
