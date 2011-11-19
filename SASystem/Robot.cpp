#include "Robot.h"
#include "Arbiter.h"

Robot::Robot(){
	this->modules = new std::vector<SAModule*>();
	this->arbiters = new std::vector<Arbiter*>();
}

Robot::Robot(std::string directoryPath, std::string fileName){
	this->modules = new std::vector<SAModule*>();
	this->arbiters = new std::vector<Arbiter*>();
	this->memory->setLogFilePath(directoryPath, fileName);
}

Robot::~Robot(){
	delete(modules);
	delete(arbiters);
}

void Robot::Initialize(){
}

void Robot::Run(){
	RunModules();
	ProcessArbiters();
	Log();
}

void Robot::RunModules(){
	for(int i = 0; i < modules->size(); i++){
		modules->at(i)->Run();
	}
}

void Robot::ProcessArbiters(){
	for(int i = 0; i < arbiters->size(); i++){
		arbiters->at(i)->Run();
	}
}

void Robot::Log(){
	memory->Log();
}

void Robot::addModule(SAModule *module){
	//module��robot�ɓo�^
	modules->push_back(module);
	//module�̐e�Ƃ��āCrobot���g��o�^
	module->setParent(this);
	int index;
	//module�̓��͂��C���̃��{�b�g��memory�̏o�͂Ɛڑ�
	for(int i = 0; i < module->getNumOfInputPorts(); i++){
		index = this->memory->addOutputPort(module->getInputTitles()->at(i));
		module->addInputIndex(index);
	}
	//module�̏o�͂��C���̃��{�b�g��memory�̓��͂Ɛڑ�
	for(int i = 0; i < module->getNumOfOutputPorts(); i++){
		index = this->memory->addInputPort(module->getOutputTitles()->at(i));
		module->addOutputIndex(index);
	}
}

void Robot::addArbiter(Arbiter *arbiter){
	//arbiter��robot�ɓo�^
	arbiters->push_back(arbiter);
	//arbiter�̐e�Ƃ��āCrobot���g��o�^
	arbiter->setParent(this);
	int index;
	///Arbiter�ɂ�memory�̊��蓖�ĕs�v
	/**
		Arbiter�ɂ́CsetSource, setDestination�̎��_�ŁC
		inputIndex, outputIndex���\�z����Ă���
		*/
}

void Robot::setLogDirectoryPath(std::string directoryPath, std::string fileName){
	this->memory->setLogFilePath(directoryPath, fileName);
}