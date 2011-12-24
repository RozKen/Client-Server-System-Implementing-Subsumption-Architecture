#include "ContLinkToHQ.hpp"
#include "RobotMAV.h"

ContLinkToHQ::ContLinkToHQ() : rand(0.0, 1.0){
	this->addInput("posXCLTHQ");
	this->addInput("posYCLTHQ");

	this->addOutput("dXCLTHQ");
	this->addOutput("dXCLTHQ");

	this->addIBoard("iHop");
}

void ContLinkToHQ::Run(){
	int hop = this->getIBoard(0);

	float posX = this->getInput(0);
	float posY = this->getInput(1);

	float signalX = NO_SIGNAL;
	float signalY = NO_SIGNAL;

	bool toStart = !update();
	
	if(toStart){
		float dX = ((float)START_X) - posX;
		float dY = ((float)START_Y) - posY;
		float d = norm(dX, dY);
		signalX = ((float)MAX_DRIVE) * dX / d;
		signalY = ((float)MAX_DRIVE) * dY / d;
	}else{
		float dXP;
		float dYP;
		//hop = 0の時はrelativeRootがいない
		if(hop == 0 || hop == NO_SIGNAL){
			dXP = (float)START_X - posX;
			dYP = (float)START_Y - posY;
		}else{
			float pPosX = ((RobotMAV*)this->parent)->getRelativeRoot()->getPosX();
			float pPosY = ((RobotMAV*)this->parent)->getRelativeRoot()->getPosY();
			dXP = pPosX - posX;
			dYP = pPosY - posY;
		}
		float dP = norm(dXP, dYP);
		//relativeRoot / START が少し遠いとき
		if(dP < WIFI_CONNECT * WIFI_WEAK){
			signalX = (float)MAX_DRIVE * dXP / dP;
			signalY = (float)MAX_DRIVE * dYP / dP;
		}else{
			signalX = NO_SIGNAL;
			signalY = NO_SIGNAL;
		}
	}

	this->setOutput(0, signalX);
	this->setOutput(1, signalY);
}

bool ContLinkToHQ::update(){
	bool result = false;
	bool find = false;

	int hop = this->getIBoard(0);
	float posX = this->getInput(0);
	float posY = this->getInput(1);
	float dX = ((float)START_X) - posX;
	float dY = ((float)START_Y) - posY;
	float d = norm(dX, dY);
	float signalX = NO_SIGNAL;
	float signalY = NO_SIGNAL;
	//hop, relativeRootを更新

	//ときおり，relativeRootを書き換える機会を与える
	if(P_RECONNECT > rand()){
		find = true;
	}else{	//確率的には書き換えない場合
		if(hop == 0){
			//現在もまだ接続が確立されていなければ，新たに探すよう指示
			if(d >= START_R){
				find = true;
				hop = NO_SIGNAL;
			}else{
				find = false;
			}
		}else if(hop != NO_SIGNAL){
			int pHop = ((RobotMAV*)parent)->getRelativeRoot()->getHop();
			//relativeRootのHopが，自分のHopよりも大きかったら，NO_SIGNALとする
			if( pHop >= ((RobotMAV*)this->parent)->getHop()){
				hop = NO_SIGNAL;
			}else{
				//そうじゃないときは，自分のHopを計算し直す．
				hop = pHop + 1;
			}
		}
	}
	//hopを更新
	this->setIBoard(0, hop);
	//この時点でhop == NO_SIGNALなら，検索するようセットする
	if(hop == NO_SIGNAL){
		find = true;
	}

	//新たに探索する場合
	if(find){
		//見つからなかったら
		if(!findHQ()){
			//START地点へ戻るよう伝える
			result = false;
			return result;
		}else{
			result = true;
			return result;
		}
	}

	return result;
}

bool ContLinkToHQ::findHQ(){
	bool result = false;
	float posX = this->getInput(0);
	float posY = this->getInput(1);
	float dX = START_X - posX;
	float dY = START_Y - posY;
	float d = norm(dX, dY);
	RobotMAV* parent = ((RobotMAV*)this->parent);
	if(d < START_R){	//司令部から近いとき
		parent->setHop(0);
		return true;
	}else
	{	//そうでないとき，
		//nearest->size() = 0の時
		if(parent->getNearest()->size() == 0){
			//hop = NO_SIGNALとして，result = false
			parent->setHop(NO_SIGNAL);
			return false;
		}else{
			bool flag = false;
			for(int i = 0; i < parent->getNearest()->size(); i++){
				int pHop = parent->getNearestAt(i)->getHop();
				if(pHop != NO_SIGNAL){
					//nearestの中で，繋がっているものがある場合
					//relativeRobotを更新
					parent->setRelativeRoot(parent->getNearestAt(i));
					//Hopを更新
					parent->setHop(pHop + 1);
					flag = true;
					return true;
				}
			}
			//nearestのhop = NO_SIGNALの時
			if(!flag){
				//hop = NO_SIGNALとして，result = false
				parent->setHop(NO_SIGNAL);
				return false;
			}
		}
	}
	return result;
}