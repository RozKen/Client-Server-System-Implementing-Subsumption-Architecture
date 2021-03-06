#include "ContSmartAlive.hpp"
#include "RobotUGV.h"

ContSmartAlive::ContSmartAlive() : distance(NO_SIGNAL){

	for(int i = 0; i < 2; i++){
		nearestCharger[i] = NO_SIGNAL;
	}

	this->addInput("posXCS");
	this->addInput("posYCS");
	this->addInput("batCS");
	this->addInput("onBatChCS");

	this->addOutput("dXCS");
	this->addOutput("dYCS");

	this->addIBoard("iChargeF");
}

void ContSmartAlive::Run(){
	//基本的にNO_SIGNALを出力
	float signalX = NO_SIGNAL;
	float signalY = NO_SIGNAL;
#ifdef	IMPORTANCE_BASED
	this->importance = NO_SIGNAL;
#endif	//IMPORTANCE_BASED
	//Charge中の時
	if(this->getIBoard(0) == 1){
		signalX = 0.0f;
		signalY = 0.0f;
#ifdef	IMPORTANCE_BASED
	this->importance = VERY_IMPORTANT;
#endif	//IMPORTANCE_BASED
		if(this->getInput(2) >= MAX_BAT){
			//Charge済みとする
			this->setIBoard(0, 0);
			this->distance = NO_SIGNAL;
		}
	}else{	//Charge中じゃないとき
		//Batteryが少なくて，充電器の上にいるとき
		if(this->getInput(2) < MAX_BAT * 0.5 && this->getInput(3) == 1.0f){
			//Charge中とする
			this->setIBoard(0, 1);
			//停止する=充電する
			signalX = 0.0f;
			signalY = 0.0f;
#ifdef	IMPORTANCE_BASED
			this->importance = VERY_IMPORTANT;
#endif	//IMPORTANCE_BASED
		}else{	//充電器の上にはいない時
			if(findNearestCharger()){
				//Batteryが足りなくなりそうだったら
				if(SURPLUS * (distance * 1.0f) > this->getInput(2) / BAT_LOSS){
					//最も近い充電エリアへ向かう
					signalX = (float)MAX_DRIVE * (nearestCharger[0] - this->getInput(0)) / distance;
					signalY = (float)MAX_DRIVE * (nearestCharger[1] - this->getInput(1)) / distance;
#ifdef	IMPORTANCE_BASED
					//this->importance = 20.0f;
					this->importance = 20.0f * this->calcImportance(1.0f - this->getInput(2) / ((float)MAX_BAT));
#endif	//IMPORTANCE_BASED
				}
			}//else 見つからなかったら，諦める．
		}
	}
	//Set Outputs
	this->setOutput(0, signalX);
	this->setOutput(1, signalY);
}

bool ContSmartAlive::findNearestCharger(){
	bool result = false;
	float posX = this->getInput(0);
	float posY = this->getInput(1);
	//どうしようもなく司令部から遠いときは，諦める．
	if(norm(posX - START_X, posY - START_Y) - 5.0f > this->getInput(2) / BAT_LOSS){
		result = false;
	}else{
		int x, y;
		float distance = 1000.0f;
		for(int i = 0; i < FIELD_SIZE; i++){
			for(int j = 0; j < FIELD_SIZE; j++){
				if(((RobotUGV*)(this->parent))->semMap[i][j] == ONCHARGER
					|| ((RobotUGV*)(this->parent))->semMap[i][j] == ONSTART){
					float tmp = norm(posX - i, posY - j);
					if(distance > tmp){
						distance = tmp;
						x = i;
						y = j;
						//目標をひとつ内側にする．
						if(x < START_X){
							x += 1;
						}else{
							x -= 1;
						}
						if(y < START_Y){
							y += 1;
						}else{
							y -= 1;
						}
						result = true;
					}
				}
			}
		}
		if(result){
			nearestCharger[0] = x;
			nearestCharger[1] = y;
			//マンハッタン距離にしてみる
			//this->distance = (posX - x) + (posY - y);

			this->distance = this->norm(posX - x, posY - y);
		}else{
			nearestCharger[0] = NO_SIGNAL;
			nearestCharger[1] = NO_SIGNAL;
			distance = NO_SIGNAL;
		}
	}

	return result;
}