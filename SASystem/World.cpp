#include "World.h"
#include "RobotMAV.h"

void World::Run(){
	this->RunRobots();
	//���݈ʒu�̍X�V: Update�֐��ő�ւ�������
	for(int i = 0; i < this->modules->size(); i++){
		//TODO setPos�̈�����������
		//Robot�̌��݈ʒu���X�V����
		//((RobotMAV *)(this->modules->at(i)))->setPos(0,0);
		RobotMAV* module = (RobotMAV*)(modules->at(i));
		//iPosX = iPosX + iDeltaX
		int tmp1 = module->getInput(0) + module->getOutput(0);
		module->setInput(0, (float)tmp1);
		//iPosY = iPosY + iDeltaY
		int tmp2 = module->getInput(1) + module->getOutput(1);
		module->setInput(1, (float)tmp2);
		//std::cout << "Robot[" << i << "] : " << tmp1 << ", " << tmp2 << std::endl;
	}
	//this->innerMemory->setIBoard(0, this->innerMemory->getIBoard(0) + this->innerMemory->getIBoard(2));
	//this->innerMemory->setIBoard(1, this->innerMemory->getIBoard(1) + this->innerMemory->getIBoard(3));
	//this->innerMemory->setIBoard(4, this->innerMemory->getIBoard(4) + this->innerMemory->getIBoard(6));
	//this->innerMemory->setIBoard(5, this->innerMemory->getIBoard(5) + this->innerMemory->getIBoard(7));
	//���݂̏�Ԃ��L�^
	Log();
}

void World::RunRobots(){
	for(int i = 0; i < this->modules->size(); i++){
		((RobotMAV*)(this->modules->at(i)))->Run();
	}
}