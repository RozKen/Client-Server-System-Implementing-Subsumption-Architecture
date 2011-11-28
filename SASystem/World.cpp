#include "World.h"
#include "RobotMAV.h"

void World::Run(){
	this->RunRobots();
	for(int i = 0; i < this->modules->size(); i++){
		//TODO setPos�̈�����������
		//Robot�̌��݈ʒu���X�V����
		//((RobotMAV *)(this->modules->at(i)))->setPos(0,0);
	}
	Log();
}

void World::RunRobots(){
	for(int i = 0; i < this->modules->size(); i++){
		((RobotMAV*)(this->modules->at(i)))->Run();
	}
	//���݈ʒu�̍X�V: Update�֐��ő�ւ�������
	for(int i = 0; i < modules->size(); i++){
		RobotMAV* module = (RobotMAV*)(modules->at(i));
		module->setIBoard(0, module->getIBoard(0) + module->getIBoard(2));
		module->setIBoard(1, module->getIBoard(1) + module->getIBoard(3));
	}
}