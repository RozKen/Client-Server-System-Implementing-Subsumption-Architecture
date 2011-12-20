#include "ContArbitrateDestination.hpp"

#include "RobotMAV.h"
#include "ContExplore.hpp"

ContArbitrateDestination::ContArbitrateDestination(){
	//Input�ɂ�Positon��p����
	this->addInput("posXCAd");
	this->addInput("posYCAd");
}

ContArbitrateDestination::ContArbitrateDestination(SAModule* parent){
	this->setParent(parent);
	//Input�ɂ�Positon��p����
	this->addInput("posXCAd");
	this->addInput("posYCAd");

	Initialize();
}

void ContArbitrateDestination::Initialize(){
	//ContExplore��IBoard��p����D
#ifdef SWAP_CCCE
	int modNum = 11;
#else
	int modNum = 12;
#endif
	ContExplore* cE = (ContExplore*)(((RobotMAV*)(this->parent))->getModule(modNum));
	this->addIBoardIndex(cE->getIBoardIndex(0));
	this->addIBoardIndex(cE->getIBoardIndex(1));
}

void ContArbitrateDestination::Run(){
	RobotMAV* parent = (RobotMAV*)(this->getParent());
	float posXself = this->getInput(0);
	float posYself = this->getInput(1);
	int destXself = this->getIBoard(0);
	int destYself = this->getIBoard(1);

	if(DEST_FAR < this->norm(posXself - (float)destXself, posYself - (float)destYself)){

		int connect = parent->getNumOfNearestRobots();
		std::vector<float>	posX;
		std::vector<float>	posY;
		std::vector<int>	destX;
		std::vector<int>	destY;
		float centerX = 0.0f;
		float centerY = 0.0f;
		float destCenterX = 0.0f;
		float destCenterY = 0.0f;

		for(int robot = 0; robot < connect; robot++){
			RobotMAV* mav = parent->getNearestAt(robot);
			float tmpPosX = mav->getPosX();
			float tmpPosY = mav->getPosY();
			int tmpDestX = mav->getObjectiveX();
			int tmpDestY = mav->getObjectiveY();
			posX.push_back(tmpPosX);
			centerX += tmpPosX;
			posY.push_back(tmpPosY);
			centerY += tmpPosY;
			destX.push_back(tmpDestX);
			destCenterX += (float)tmpDestX;
			destY.push_back(tmpDestY);
			destCenterY += (float)tmpDestY;
		}
		centerX /= connect;
		centerY /= connect;
		//�������i�����Ƃ��Ă���������CRobot�̒��S�������𒲂ׂ邽�ߓ��ς����
		//Vector A : �����̐i�����Ƃ��Ă������
		float vecAx = (float)destXself - posXself;
		float vecAy = (float)destYself - posYself;
		float vecAnorm = norm(vecAx, vecAy);
		//Vector B : �����̈ʒu����CRobot�̒��֌���������
		float vecBx = (float)destXself - centerX;
		float vecBy = (float)destYself - centerY;
		float vecBnorm = norm(vecBx, vecBy);

		float innerProduct = vecAx * vecBx + vecAy * vecBy;
		if(vecAnorm != 0.0f){
			innerProduct /= vecAnorm;
		}
		if(vecBnorm != 0.0f){
			innerProduct /= vecBnorm;
		}
		//std::cout << "innerProduct : " << innerProduct << std::endl;
		//���S��������Ȃ��ꍇ
		if(innerProduct < 0.5){
			//�����̐i�����Ƃ��Ă���������C����Robot�̐i�����Ƃ��Ă�������Ƒ啝�ɂ���Ă��Ȃ���
			//���ׂ邽�߁C���ς����
			
			//Vector A : �����̐i�����Ƃ��Ă������
			//�ȑO�Ɠ���������Comment out
			//vecAx = (float)destXself - posXself;
			//vecAy = (float)destYself - posYself;
			//vecAnorm = norm(vecAx, vecAy);

			//Vector B : �ق���4���C�i�����Ƃ��Ă�������̕���
			vecBx = destCenterX - centerX;
			vecBy = destCenterY - centerY;
			vecBnorm = norm(vecBx, vecBy);

			float innerProduct2 = vecAx * vecBx + vecAy * vecBy;
			if(vecAnorm != 0.0f){
				innerProduct2 /= vecAnorm;
			}
			/**
			if(vecBnorm != 0.0f){
				innerProduct2 /= vecBnorm;
			}
			**/
			//std::cout << "innerProduct2 : " << innerProduct2 << std::endl;
			//���p���S�R����������C
			if(innerProduct2 < - DEST_STRONG_WRONG){
				//Destination���Čv�Z������悤�ɂ���
				this->setIBoard(0, (int)NO_SIGNAL);
				this->setIBoard(1, (int)NO_SIGNAL);
			}
		}
	}
}