#include "ContExplore.hpp"

#include "RobotMAV.h"

void ContExplore::Run(){
	//Current Position
	float x = ((RobotMAV*)(this->parent))->getPosX();
	float y = ((RobotMAV*)(this->parent))->getPosY();
	//Destination
	int destX = -1;
	int destY = -1;
	//Distance
	float distance = (float)(FIELD_SIZE * FIELD_SIZE);
	//Decide Destination
	for(int i = 0; i < FIELD_SIZE; i++){
		for(int j = 0; j < FIELD_SIZE; j++){
			if(	//geoMap
				((RobotMAV*)(this->parent))->geoMap[i][j] == NO_DATA
				||
				//radMap
				((RobotMAV*)(this->parent))->radMap[i][j] == NO_DATA
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

	//Generate Signals
	float signalX = NO_SIGNAL;
	float signalY = NO_SIGNAL;
	if(destX != -1 && destY != -1){
		float norm = sqrt(pow((double)destX - x, 2) + pow((double)destY - y, 2));
		if(norm != 0.0f){
			signalX = (destX - x) / norm;
			signalY = (destY - y) / norm;
		}
	}
	//Set Outputs
	this->setOutput(0, signalX);
	this->setOutput(1, signalY);
}