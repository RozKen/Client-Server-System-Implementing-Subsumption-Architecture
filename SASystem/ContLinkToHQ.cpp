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
#ifdef	IMPORTANCE_BASED
	this->importance = NO_SIGNAL;
#endif	//IMPORTANCE_BASED

	bool toStart = !update();
	//start地点へ向かう場合
	if(toStart){
		float dX = ((float)START_X) - posX;
		float dY = ((float)START_Y) - posY;
		float d = norm(dX, dY);
		signalX = ((float)MAX_DRIVE) * dX / d;
		signalY = ((float)MAX_DRIVE) * dY / d;
#ifdef	IMPORTANCE_BASED
		float value = d * 2 / FIELD_SIZE;
		if(value > 1.0f){
			value = 1.0f;
		}
		this->importance = this->calcImportance(value);
#endif	//IMPORTANCE_BASED
		//std::cout << "Headquarter 0: " << signalX << ", " << signalY << std::endl;
	}else{	//start地点へ向かう必要はない場合．
		float dXP;
		float dYP;
		//hop = 0の時はrelativeRootがいない：Start地点へ向かう
		if(hop == 0 || hop == NO_SIGNAL){
			dXP = (float)START_X - posX;
			dYP = (float)START_Y - posY;
		}else{	//hop != 0のときは，relativeRootへ向かう．
			float pPosX = ((RobotMAV*)this->parent)->getRelativeRoot()->getPosX();
			float pPosY = ((RobotMAV*)this->parent)->getRelativeRoot()->getPosY();
			dXP = pPosX - posX;
			dYP = pPosY - posY;
		}
		float dP = norm(dXP, dYP);
		//relativeRoot / START が少し遠いとき
		if(dP >= WIFI_CONNECT * WIFI_WEAK){
			//目的地に向かう
			signalX = (float)MAX_DRIVE * dXP / dP;
			signalY = (float)MAX_DRIVE * dYP / dP;
#ifdef	IMPORTANCE_BASED
			float value = dP / (WIFI_CONNECT * WIFI_WEAK);
			this->importance = this->calcImportance(value);
#endif	//IMPORTANCE_BASED
			//std::cout << "Headquarter 1: " << signalX << ", " << signalY << std::endl;
		}else{
			//Wifiを接続するのに充分近いとき，信号は出さない
			signalX = NO_SIGNAL;
			signalY = NO_SIGNAL;
#ifdef	IMPORTANCE_BASED
			this->importance = NO_SIGNAL;
#endif	//IMPORTANCE_BASED
		}
	}
	//set Outputs
	////For Now
	//signalX = NO_SIGNAL;
	//signalY = NO_SIGNAL;
#ifdef	IMPORTANCE_BASED
	//this->importance = NO_SIGNAL;
#endif	//IMPORTANCE_BASED
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
	
	//findHQするかどうかを決めつつ，hopを再計算

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

	//とにかく探索してみる
	find = true;

	//新たに探索する場合
	if(find){
		//見つからなかったら
		if(!findHQ()){
			//START地点へ戻るよう伝える
			result = false;
		}else{
			//見つかったときは，
			result = true;
		}
	}else{
		//新たに探索する必要がない場合
		result = true;
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
				result = true;
				//なるべく遠くのものと繋がるようにしてみた．
				//これにより，長く繋がる気がする
			}
		}
		//nearestのhop = NO_SIGNALの時
		if(!flag){
			//hop = NO_SIGNALとして，result = false
			parent->setHop(NO_SIGNAL);
			result = false;
		}
	}
	//この時点で，hop = NO_SIGNALで
	//司令部から近ければ
	if(d < START_R && parent->getHop() == NO_SIGNAL){	//司令部から近いとき
		//hop = 0とする
		parent->setHop(0);
		result = true;
	}

	return result;
}