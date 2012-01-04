#include "ContAlive.hpp"
#include "RobotMAV.h"

void ContAlive::Run(){
	float batLevel = this->getInput(0);
	float signalX = NO_SIGNAL;
	float signalY = NO_SIGNAL;
#ifdef	IMPORTANCE_BASED
	this->importance = NO_SIGNAL;
#endif	//IMPORTANCE_BASED
	if(batLevel != NO_SIGNAL){
#ifdef	IMPORTANCE_BASED
		float posX = this->getInput(1);
		float posY = this->getInput(2);
		float deltaX = START_X - posX;
		float deltaY = START_Y - posY;
		float norm = this->norm(deltaX, deltaY);
		if(norm > START_R - 1.0f){	//充電地まで進む
			signalX = MAX_DRIVE * deltaX / norm;
			signalY = MAX_DRIVE * deltaY / norm;
		}else{	//充電中は停止する
			signalX = 0.0f;
			signalY = 0.0f;
		}
		//重要度を設定
		this->importance = this->calcImportance(1.0f - batLevel / ((float)MAX_BAT));
	}else{
		this->importance = NO_SIGNAL;
	}
#else
		if(batLevel / ((float)MAX_BAT) < threshold){
			float posX = this->getInput(1);
			float posY = this->getInput(2);
			float deltaX = START_X - posX;
			float deltaY = START_Y - posY;
			float norm = this->norm(deltaX, deltaY);
			if(norm > START_R - 1.0f){	//充電地まで進む
				signalX = MAX_DRIVE * deltaX / norm;
				signalY = MAX_DRIVE * deltaY / norm;
			}else{	//充電中は停止する
				signalX = 0.0f;
				signalY = 0.0f;
			}
		}else{
			signalX = NO_SIGNAL;
			signalY = NO_SIGNAL;
		}
	}
#endif	//IMPORTANCE_BASED

	this->setOutput(0, signalX);
	this->setOutput(1, signalY);
}