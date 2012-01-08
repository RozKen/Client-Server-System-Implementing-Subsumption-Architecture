#include "ContExplore.hpp"

#include "RobotMAV.h"

void ContExplore::Run(){
	int destX = this->getIBoard(0);
	int destY = this->getIBoard(1);
	
	if(destX != NO_SIGNAL && destY != NO_SIGNAL){
		if(//geoMap
			((RobotMAV*)(this->parent))->geoMap[destX][destY] != NO_SIGNAL
			&&
			//radMap
			((RobotMAV*)(this->parent))->radMap[destX][destY] != NO_SIGNAL
			){
				DecideDestination();
				destX = this->getIBoard(0);
				destY = this->getIBoard(1);
		}
	}else{
		DecideDestination();
		destX = this->getIBoard(0);
		destY = this->getIBoard(1);
	}

	//Generate Signals
	float signalX = NO_SIGNAL;
	float signalY = NO_SIGNAL;
#ifdef	IMPORTANCE_BASED
	this->importance = NO_SIGNAL;
#endif	//IMPORTANCE_BASED
	if(destX != (int)NO_SIGNAL && destY != (int)NO_SIGNAL){
		//Current Position
		float x = ((RobotMAV*)(this->parent))->getPosX();
		float y = ((RobotMAV*)(this->parent))->getPosY();
		
		float norm = sqrt(pow((double)destX - x, 2) + pow((double)destY - y, 2));
		if(norm != 0.0f){
			signalX = (float)MAX_DRIVE * (destX - x) / norm;
			signalY = (float)MAX_DRIVE * (destY - y) / norm;
#ifdef	IMPORTANCE_BASED
			///ここでは直接値を指定している(イレギュラー)
			this->importance = this->calcImportance(0.5f);
#endif	//IMPORTANCE_BASED
		}
	}
	//Set Outputs

	this->setOutput(0, signalX);
	this->setOutput(1, signalY);
}

void ContExplore::DecideDestination(){
	//Current Position
	float x = ((RobotMAV*)(this->parent))->getPosX();
	float y = ((RobotMAV*)(this->parent))->getPosY();
	//Destination
	int destX = (int)NO_SIGNAL;
	int destY = (int)NO_SIGNAL;
	//Distance
	float distance = (float)(FIELD_SIZE * FIELD_SIZE);
	//Decide Destination
	for(int i = 0; i < FIELD_SIZE; i++){
		for(int j = 0; j < FIELD_SIZE; j++){
			if(	//geoMap
				((RobotMAV*)(this->parent))->geoMap[i][j] == NO_SIGNAL
				||
				//radMap
				((RobotMAV*)(this->parent))->radMap[i][j] == NO_SIGNAL
				){
					float tmp = sqrt(pow((double)i - x, 2) + pow((double)j - y, 2));
					if(distance > tmp){
						destX = i;
						destY = j;
						distance = tmp;
					}
			}
		}
	}

	//未探索の場所が見あたらなかったら，START地点へ戻る
	if(distance == (float)(FIELD_SIZE * FIELD_SIZE)){
		distance = sqrt(pow((double)START_X - x, 2) + pow((double)START_Y - y, 2));
		if(distance > START_R){
			destX = START_X;
			destY = START_Y;
		}
	}

	this->setIBoard(0, destX);
	this->setIBoard(1, destY);
}