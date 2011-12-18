#include "ContSmartAlive.hpp"
#include "RobotMAV.h"

ContSmartAlive::ContSmartAlive(){

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
	float signalX = NO_SIGNAL;
	float signalY = NO_SIGNAL;
	//Charge’†‚ÌŽž
	if(this->getIBoard(0) == 1){
		signalX = 0.0f;
		signalY = 0.0f;
		if(this->getInput(2) >= MAX_BAT){
			//ChargeÏ‚Ý‚Æ‚·‚é
			this->setIBoard(0, 0);
		}
	}else{	//Charge’†‚¶‚á‚È‚¢‚Æ‚«
		//Battery‚ª­‚È‚­‚ÄC[“dŠí‚Ìã‚É‚¢‚é‚Æ‚«
		if(this->getInput(2) < MAX_BAT * 0.5 && this->getInput(3) == 1.0f){
			//Charge’†‚Æ‚·‚é
			this->setIBoard(0, 1);
			//’âŽ~‚·‚é=[“d‚·‚é
			signalX = 0.0f;
			signalY = 0.0f;
		}else{
			if(findNearestCharger()){
				//Battery‚ª‘«‚è‚È‚­‚È‚è‚»‚¤‚¾‚Á‚½‚ç
				if(distance > SURPLUS * this->getInput(2) / BAT_LOSS){
					//‚»‚±‚ÖŒü‚©‚¤
					signalX = nearestCharger[0] / distance;
					signalY = nearestCharger[1] / distance;
				}
			}//else Œ©‚Â‚©‚ç‚È‚©‚Á‚½‚çC’ú‚ß‚éD
		}
	}

	this->setOutput(0, signalX);
	this->setOutput(1, signalY);
}

bool ContSmartAlive::findNearestCharger(){
	bool result = false;
	float posX = this->getInput(0);
	float posY = this->getInput(1);
	//‚Ç‚¤‚µ‚æ‚¤‚à‚È‚­Ži—ß•”‚©‚ç‰“‚¢‚Æ‚«‚ÍC’ú‚ß‚éD
	if(norm(posX - START_X, posY - START_Y) > MAX_BAT / BAT_LOSS){
		result = false;
	}else{
		int x, y;
		float distance = 1000.0;
		for(int i = 0; i < FIELD_SIZE; i++){
			for(int j = 0; j < FIELD_SIZE; j++){
				if(((RobotMAV*)(this->parent))->semMap[i][j] == ONCHARGER){
					float tmp = norm(posX - i, posY - j);
					if(distance > tmp){
						distance = tmp;
						x = i;
						y = j;
						result = true;
					}
				}
			}
		}
		if(result){
			nearestCharger[0] = x;
			nearestCharger[1] = y;
			this->distance = distance;
		}
	}

	return result;
}