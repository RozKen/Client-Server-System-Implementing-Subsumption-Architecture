#include "ContArbitrateDestination.hpp"

#include "RobotMAV.h"
#include "ContExplore.hpp"

ContArbitrateDestination::ContArbitrateDestination(){
	//InputにはPositonを用いる
	this->addInput("posXCAd");
	this->addInput("posYCAd");
}

ContArbitrateDestination::ContArbitrateDestination(SAModule* parent){
	this->setParent(parent);
	//InputにはPositonを用いる
	this->addInput("posXCAd");
	this->addInput("posYCAd");

	Initialize();
}

void ContArbitrateDestination::Initialize(){
	//ContExploreのIBoardを用いる．
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
		//自分が進もうとしている方向が，Robotの中心方向かを調べるため内積を取る
		//Vector A : 自分の進もうとしている方向
		float vecAx = (float)destXself - posXself;
		float vecAy = (float)destYself - posYself;
		float vecAnorm = norm(vecAx, vecAy);
		//Vector B : 自分の位置から，Robotの中へ向かう方向
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
		//中心方向じゃない場合
		if(innerProduct < 0.5){
			//自分の進もうとしている方向が，他のRobotの進もうとしている方向と大幅にずれていないか
			//調べるため，内積を取る
			
			//Vector A : 自分の進もうとしている方向
			//以前と同じだからComment out
			//vecAx = (float)destXself - posXself;
			//vecAy = (float)destYself - posYself;
			//vecAnorm = norm(vecAx, vecAy);

			//Vector B : ほかの4つが，進もうとしている方向の平均
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
			//方角が全然ちがったら，
			if(innerProduct2 < - DEST_STRONG_WRONG){
				//Destinationを再計算させるようにする
				this->setIBoard(0, (int)NO_SIGNAL);
				this->setIBoard(1, (int)NO_SIGNAL);
			}
		}
	}
}