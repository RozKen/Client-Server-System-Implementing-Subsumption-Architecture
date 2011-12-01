#include "World.h"
#include "RobotMAV.h"

void World::Run(){
	this->RunRobots();
	//現在位置の更新: Update関数で代替したいね
	for(int i = 0; i < this->modules->size(); i++){
		//TODO setPosの引数書き換え
		//Robotの現在位置を更新する
		//((RobotMAV *)(this->modules->at(i)))->setPos(0,0);
		RobotMAV* module = (RobotMAV*)(modules->at(i));
		//Battery - Need to be Updated ///////////////////////////
		module->setInput(0, 100.0f);
		//fPosX = fPosX + fDeltaX
		float tmp1 = module->getInput(1) + module->getOutput(0);
		module->setInput(1, tmp1);
		//fPosY = fPosY + fDeltaY
		float tmp2 = module->getInput(2) + module->getOutput(1);
		module->setInput(2, tmp2);
		//std::cout << "Robot[" << i << "] : " << tmp1 << ", " << tmp2 << std::endl;
	}
	//this->innerMemory->setIBoard(0, this->innerMemory->getIBoard(0) + this->innerMemory->getIBoard(2));
	//this->innerMemory->setIBoard(1, this->innerMemory->getIBoard(1) + this->innerMemory->getIBoard(3));
	//this->innerMemory->setIBoard(4, this->innerMemory->getIBoard(4) + this->innerMemory->getIBoard(6));
	//this->innerMemory->setIBoard(5, this->innerMemory->getIBoard(5) + this->innerMemory->getIBoard(7));
	//現在の状態を記録
	Log();
}

void World::RunRobots(){
	for(int i = 0; i < this->modules->size(); i++){
		((RobotMAV*)(this->modules->at(i)))->Run();
	}
}