#include "World.h"
#include "RobotMAV.hpp"

void World::Run(){
	this->RunModules();
	for(int i = 0; i < this->modules->size(); i++){
		//TODO setPos‚Ìˆø”‘‚«Š·‚¦
		//Robot‚ÌŒ»ÝˆÊ’u‚ðXV‚·‚é
		//((RobotMAV *)(this->modules->at(i)))->setPos(0,0);
	}
}