#include "Robot.h"
#include "Arbiter.h"

Robot::Robot(){
	memory = new Blackboard();
}

Robot::Robot(int inputPorts, int outputPorts){
	memory = new Blackboard();

}

void Robot::Initialize(){
}

void Robot::Run(){
	RunModules();
	ProcessArbiters();
	Log();
}

void Robot::RunModules(){
	for(int i = 0; i < modules.size(); i++){
		modules[i]->Run();
	}
}

void Robot::ProcessArbiters(){
	for(int i = 0; i < arbiters.size(); i++){
		arbiters[i]->Run();
	}
}

void Robot::Log(){
}

void Robot::addModule(SAModule *module){
	modules.push_back(module);
}

void Robot::addArbiter(Arbiter *arbiter){
	arbiters.push_back(arbiter);
}

void Robot::createInputPort(int numberOfPorts){
	SAModule::createInputPort(numberOfPorts);

	memory->createInputPort(numberOfPorts);
}

void Robot::createOutputPort(int numberOfPorts){
	SAModule::createOutputPort(numberOfPorts);

	memory->createOutputPort(numberOfPorts);
}