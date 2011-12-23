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
	//hop, relativeRootを更新
	if(hop == NO_SIGNAL){
		//見つからなかったら．
		if(!findHQ()){
			//Start地点へ戻る
			float dX = ((float)START_X - posX);
			float dY = ((float)START_Y - posY);
			float d = norm(dX, dY);
			signalX = (float)MAX_DRIVE * dX / d;
			signalY = (float)MAX_DRIVE * dY / d;
		}
	}else{	//既にhopがある時
		if(hop == 0){	//hop数が0の時はrelativeRootがない
			float dX = ((float)START_X - posX);
			float dY = ((float)START_Y - posY);
			float d = norm(dX, dY);
			if(d >= START_R){
				hop = NO_SIGNAL;
			}
		}else{
			int pHop = ((RobotMAV*)parent)->getRelativeRoot()->getHop();
			//relativeRootのHopが，自分のHopよりも大きかったら，NO_SIGNALとする
			if( pHop >= ((RobotMAV*)this->parent)->getHop()){
				hop = NO_SIGNAL;
			}else{
				//そうじゃないときは，自分のHopを計算し直す．
				hop = pHop + 1;;
			}
		}
	}
	this->setIBoard(0, hop);

	//ときおり，relativeRootを書き換える機会を与える
	if(P_RECONNECT > rand()){
		findHQ();
	}


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
	}else{	//そうでないとき，
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