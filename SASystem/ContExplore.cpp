#include "ContExplore.hpp"

#include "RobotMAV.h"

void ContExplore::Run(){
	//Current Position
	float x = ((RobotMAV*)(this->parent))->getPosX();
	float y = ((RobotMAV*)(this->parent))->getPosY();
	
	if(destination[0] != NO_DATA_ON_FIELD && destination[1] != NO_DATA_ON_FIELD){
		if(//geoMap
			((RobotMAV*)(this->parent))->geoMap[destination[0]][destination[1]] != NO_DATA_ON_FIELD
			&&
			//radMap
			((RobotMAV*)(this->parent))->radMap[destination[0]][destination[1]] != NO_DATA_ON_FIELD
			){
				DecideDestination();
		}
	}else{
		DecideDestination();
	}

	//Generate Signals
	float signalX = NO_SIGNAL;
	float signalY = NO_SIGNAL;
	if(destination[0] != -1 && destination[1] != -1){
		float norm = sqrt(pow((double)destination[0] - x, 2) + pow((double)destination[1] - y, 2));
		if(norm != 0.0f){
			signalX = (destination[0] - x) / norm;
			signalY = (destination[1] - y) / norm;
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
	int destX = (int)NO_DATA_ON_FIELD;
	int destY = (int)NO_DATA_ON_FIELD;
	//Distance
	float distance = (float)(FIELD_SIZE * FIELD_SIZE);
	//Decide Destination
	for(int i = 0; i < FIELD_SIZE; i++){
		for(int j = 0; j < FIELD_SIZE; j++){
			if(	//geoMap
				((RobotMAV*)(this->parent))->geoMap[i][j] == NO_DATA_ON_FIELD
				||
				//radMap
				((RobotMAV*)(this->parent))->radMap[i][j] == NO_DATA_ON_FIELD
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
	destination[0] = destX;
	destination[1] = destY;
}