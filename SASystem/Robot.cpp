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
	//moduleをrobotに登録
	modules->push_back(module);
	//moduleの親として，robot自身を登録
	module->setParent(this);
	int index;
	//moduleの入力を，このロボットのmemoryの出力と接続
	for(int i = 0; i < module->getNumOfInputPorts(); i++){
		index = this->memory->addOutputPort(module->getInputTitles()->at(i));
		module->addInputIndex(index);
	}
	//moduleの出力を，このロボットのmemoryの入力と接続
	for(int i = 0; i < module->getNumOfOutputPorts(); i++){
		index = this->memory->addInputPort(module->getOutputTitles()->at(i));
		module->addOutputIndex(index);
	}
}

void Robot::addArbiter(Arbiter *arbiter){
	//arbiterをrobotに登録
	arbiters->push_back(arbiter);
	//arbiterの親として，robot自身を登録
	arbiter->setParent(this);
	int index;
	///Arbiterにはmemoryの割り当て不要
	/**
		Arbiterには，setSource, setDestinationの時点で，
		inputIndex, outputIndexが構築されている
		*/
}

void Robot::setLogDirectoryPath(std::string directoryPath, std::string fileName){
	this->memory->setLogFilePath(directoryPath, fileName);
}