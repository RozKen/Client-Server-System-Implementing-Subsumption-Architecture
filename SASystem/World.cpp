#include "World.h"
#include "RobotMAV.hpp"

void World::Run(){
	this->RunModules();
	for(int i = 0; i < this->modules->size(); i++){
		//TODO setPos�̈�����������
		//Robot�̌��݈ʒu���X�V����
		//((RobotMAV *)(this->modules->at(i)))->setPos(0,0);
	}
}