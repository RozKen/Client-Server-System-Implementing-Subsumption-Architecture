#include "RobotMAV.h"

RobotMAV::RobotMAV(){
	/////Sensor��ǉ�
	///////Sensor�ɂ͏����l���^����K�v������.
	//Battery�Z���T��ǉ�
	SenseBattery* sB = new SenseBattery();
	sB->setFBoard(0, 100.0f);
	this->addModule(sB);
	//�ʒu�Z���T��ǉ�
	SensePos* sP = new SensePos();
	sP->setFBoard(0, START_X);
	sP->setFBoard(1, START_Y);
	this->addModule(sP);

	//�����Z���T��ǉ�
	SenseRange* sR = new SenseRange();
	for(int i = 0; i < sR->getFBoardTitles()->size(); i++){
		sR->setFBoard(i, 4.0f);
	}
	this->addModule(sR);

	/////Controller��ǉ�
	//Alive
	ContAlive* cAl = new ContAlive();
	this->addModule(cAl);
	//Avoid
	ContAvoid* cAv = new ContAvoid();
	this->addModule(cAv);
	//Wander
	ContWander* cW = new ContWander();

	/////Actuator��ǉ�
	//�ʒuActuator��ǉ�
	ActPos* aP = new ActPos();
	this->addModule(aP);

	/////Arbiter��ǉ�
	///���WireObjects
	//Battery�Z���T->Alive
	Arbiter* sBcAl = new Arbiter(sB, 0, cAl, 0, 2.0f);
	this->addArbiter(sBcAl);
	//�ʒu�Z���T->Alive
	Arbiter* sPcAl[2];
	for(int i = 0; i < 2; i++){
		sPcAl[i] = new Arbiter(sP, i , cAl, i+1, 2.0f);
	}
	//�����Z���T->Avoid
	Arbiter* sRcAv[RANGE_DIV];
	for(int i = 0; i < RANGE_DIV; i++){
		sRcAv[i] = new Arbiter(sR, i, cAv, i, 2.0f);
		this->addArbiter(sRcAv[i]);
	}
	//�ʒu�Z���T->Wander
	Arbiter* sPcW[2];
	for(int i = 0; i < 2; i++){
		sPcW[i] = new Arbiter(sP, i, cW, i, 2.0f);
		this->addArbiter(sPcW[i]);
	}
	/////////�ȉ��̏��Ԃ͏d�v�D/////////
	/////////�K�w�̒Ⴂ�҂�����{���邽��////
	//Alive->�ʒuActuator	//Suppress���ꂽ�f�[�^�������Wire
	Arbiter* cAlaP[2];
	for(int i = 0; i < 2; i++){
		cAlaP[i] = new Arbiter(cAl, i, aP, i, 2.0f);
		this->addArbiter(cAlaP[i]);
	}
	//Suppress Avoid -> �ʒuActuator
	Arbiter* cAvaP[2];
	for(int i = 0; i < 2; i++){
		cAvaP[i] = new Arbiter(cAv, i, aP, i, 1.0f);
		this->addArbiter(cAvaP[i]);
	}
	//Suppress Wander -> �ʒuActuator
	Arbiter* cWaP[2];
	for(int i = 0; i < 2; i++){
		cWaP[i] = new Arbiter(cW, i, aP, i, 1.0f);
		this->addArbiter(cWaP[i]);
	}
}

RobotMAV::RobotMAV(std::string directoryPath, std::string fileName)
	:Robot(directoryPath, fileName){
	/////Sensor��ǉ�
	///////Sensor�ɂ͏����l���^����K�v������.
	//Battery�Z���T��ǉ�
	SenseBattery* sB = new SenseBattery();
	this->addModule(sB);
	//sB->setFBoard(0, 100.0f);
	//�ʒu�Z���T��ǉ�
	SensePos* sP = new SensePos();
	this->addModule(sP);
	//sP->setFBoard(0, START_X);
	//sP->setFBoard(1, START_Y);

	//�����Z���T��ǉ�
	SenseRange* sR = new SenseRange();
	this->addModule(sR);
	//for(int i = 0; i < sR->getFBoardTitles()->size(); i++){
	//	sR->setFBoard(i, 4.0f);
	//}

	/////Controller��ǉ�
	//Alive
	ContAlive* cAl = new ContAlive();
	this->addModule(cAl);
	//Avoid
	ContAvoid* cAv = new ContAvoid();
	this->addModule(cAv);
	//Wander
	ContWander* cW = new ContWander();
	this->addModule(cW);

	/////Actuator��ǉ�
	//�ʒuActuator��ǉ�
	ActPos* aP = new ActPos();
	this->addModule(aP);

	/////Arbiter��ǉ�
	///���WireObjects
	//Battery�Z���T->Alive
	Arbiter* sBcAl = new Arbiter(sB, 0, cAl, 0, 2.0f);
	this->addArbiter(sBcAl);
	//�ʒu�Z���T->Alive
	Arbiter* sPcAl[2];
	for(int i = 0; i < 2; i++){
		sPcAl[i] = new Arbiter(sP, i , cAl, i+1, 2.0f);
		this->addArbiter(sPcAl[i]);
	}
	//�����Z���T->Avoid
	Arbiter* sRcAv[RANGE_DIV];
	for(int i = 0; i < RANGE_DIV; i++){
		sRcAv[i] = new Arbiter(sR, i, cAv, i, 2.0f);
		this->addArbiter(sRcAv[i]);
	}
	//�ʒu�Z���T->Wander
	Arbiter* sPcW[2];
	for(int i = 0; i < 2; i++){
		sPcW[i] = new Arbiter(sP, i, cW, i, 2.0f);
		this->addArbiter(sPcW[i]);
	}
	/////////�ȉ��̏��Ԃ͏d�v�D/////////
	/////////�K�w�̒Ⴂ�҂�����{���邽��////
	//Alive->�ʒuActuator	//Suppress���ꂽ�f�[�^�������Wire
	Arbiter* cAlaP[2];
	for(int i = 0; i < 2; i++){
		cAlaP[i] = new Arbiter(cAl, i, aP, i, 2.0f);
		this->addArbiter(cAlaP[i]);
	}
	//Suppress Avoid -> �ʒuActuator
	Arbiter* cAvaP[2];
	for(int i = 0; i < 2; i++){
		cAvaP[i] = new Arbiter(cAv, i, aP, i, 1.0f);
		this->addArbiter(cAvaP[i]);
	}
	//Suppress Wander -> �ʒuActuator
	Arbiter* cWaP[2];
	for(int i = 0; i < 2; i++){
		cWaP[i] = new Arbiter(cW, i, aP, i, 1.0f);
		this->addArbiter(cWaP[i]);
	}
}

void RobotMAV::Run(){
	//Robot�ւ�Input����������
	ProcessInputs();
	//Robot�̊eModule�𓮂���
	RunModules();
	//Arbiter���쓮������
	ProcessArbiters();
	//Robot�����Output����������
	ProcessOutputs();
	//Log�����
	Log();
}
