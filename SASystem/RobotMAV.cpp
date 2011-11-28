#include "RobotMAV.h"

RobotMAV::RobotMAV(){
	/////Sensor��ǉ�
	//�ʒu�Z���T��ǉ�
	SensePos* sP = new SensePos();
	this->addModule(sP);

	/////Controller��ǉ�
	//�ړ��R���g���[����ǉ�
	ContMove* cM = new ContMove();
	this->addModule(cM);
	
	/////Actuator��ǉ�
	//�ʒuActuator��ǉ�
	ActPos* aP = new ActPos();
	this->addModule(aP);

	/////Arbiter��ǉ�
	//�ړ��R���g���[��->�ʒuActuator
	Arbiter* cMaPX = new Arbiter(cM, 0, aP, 0);
	this->addArbiter(cMaPX);
	Arbiter* cMaPY = new Arbiter(cM, 1, aP, 1);
	this->addArbiter(cMaPY);
}

RobotMAV::RobotMAV(std::string directoryPath, std::string fileName)
	:Robot(directoryPath, fileName){
		/////Sensor��ǉ�
	//�ʒu�Z���T��ǉ�
	SensePos* sP = new SensePos();
	this->addModule(sP);

	/////Controller��ǉ�
	//�ړ��R���g���[����ǉ�
	ContMove* cM = new ContMove();
	this->addModule(cM);
	
	/////Actuator��ǉ�
	//�ʒuActuator��ǉ�
	ActPos* aP = new ActPos();
	this->addModule(aP);

	/////Arbiter��ǉ�
	//�ړ��R���g���[��->�ʒuActuator
	Arbiter* cMaPX = new Arbiter(cM, 0, aP, 0);
	this->addArbiter(cMaPX);
	Arbiter* cMaPY = new Arbiter(cM, 1, aP, 1);
	this->addArbiter(cMaPY);
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
	//this->memory->Log();
	Log();
}
