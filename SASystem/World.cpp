#include "World.h"
#include "RobotMAV.hpp"

void World::Run(){
	this->RunModules();
	for(int i = 0; i < this->modules->size(); i++){
		//TODO setPosの引数書き換え
		//Robotの現在位置を更新する
		//((RobotMAV *)(this->modules->at(i)))->setPos(0,0);
	}
}