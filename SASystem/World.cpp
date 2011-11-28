#include "World.h"
#include "RobotMAV.h"

void World::Run(){
	this->RunRobots();
	for(int i = 0; i < this->modules->size(); i++){
		//TODO setPosの引数書き換え
		//Robotの現在位置を更新する
		//((RobotMAV *)(this->modules->at(i)))->setPos(0,0);
	}
	Log();
}

void World::RunRobots(){
	for(int i = 0; i < this->modules->size(); i++){
		((RobotMAV*)(this->modules->at(i)))->Run();
	}
	//現在位置の更新: Update関数で代替したいね
	for(int i = 0; i < modules->size(); i++){
		RobotMAV* module = (RobotMAV*)(modules->at(i));
		module->setIBoard(0, module->getIBoard(0) + module->getIBoard(2));
		module->setIBoard(1, module->getIBoard(1) + module->getIBoard(3));
	}
}