#include "RobotMAV.h"

RobotMAV::RobotMAV(){
	/////Sensorを追加
	//位置センサを追加
	SensePos* sP = new SensePos();
	this->addModule(sP);

	/////Controllerを追加
	//移動コントローラを追加
	ContMove* cM = new ContMove();
	this->addModule(cM);
	
	/////Actuatorを追加
	//位置Actuatorを追加
	ActPos* aP = new ActPos();
	this->addModule(aP);

	/////Arbiterを追加
	//移動コントローラ->位置Actuator
	Arbiter* cMaPX = new Arbiter(cM, 0, aP, 0);
	this->addArbiter(cMaPX);
	Arbiter* cMaPY = new Arbiter(cM, 1, aP, 1);
	this->addArbiter(cMaPY);
}

RobotMAV::RobotMAV(std::string directoryPath, std::string fileName)
	:Robot(directoryPath, fileName){
		/////Sensorを追加
	//位置センサを追加
	SensePos* sP = new SensePos();
	this->addModule(sP);

	/////Controllerを追加
	//移動コントローラを追加
	ContMove* cM = new ContMove();
	this->addModule(cM);
	
	/////Actuatorを追加
	//位置Actuatorを追加
	ActPos* aP = new ActPos();
	this->addModule(aP);

	/////Arbiterを追加
	//移動コントローラ->位置Actuator
	Arbiter* cMaPX = new Arbiter(cM, 0, aP, 0);
	this->addArbiter(cMaPX);
	Arbiter* cMaPY = new Arbiter(cM, 1, aP, 1);
	this->addArbiter(cMaPY);
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
	//this->memory->Log();
	Log();
}
