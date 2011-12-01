#include "World.h"
#include "RobotMAV.h"

void World::Run(){
	this->RunRobots();
	this->Update();
	//現在の状態を記録
	Log();
}

void World::RunRobots(){
	for(int i = 0; i < this->modules->size(); i++){
		((RobotMAV*)(this->modules->at(i)))->Run();
	}
}

void World::Update(){
	RobotMAV* robot;
	for(int i = 0; i < this->modules->size(); i++){
		robot = (RobotMAV*)(modules->at(i));
		////////Battery//////// - Need to be Updated ///////////////////////////
		float battery = robot->getInput(0);
		if(onBatteryCharger(robot)){
			battery += (float)BAT_GAIN;
		}
		//Battery以外は，生きているときだけ，作動する
		if(isAlive(robot)){
			////////Position////////
			//fPosX = fPosX + fDeltaX
			float posX = robot->getInput(1);
			float dX = robot->getOutput(0);
			robot->setInput(1, posX + dX);
			//fPosY = fPosY + fDeltaY
			float posY = robot->getInput(2);
			float dY = robot->getOutput(1);
			robot->setInput(2, posY + dY);
			//Positionに応じてBatteryを減らす
			if(sqrt(dX) > 0 || sqrt(dY) > 0){
				battery -= (float)BAT_LOSS;
			}

#ifdef _DEBUG
			std::cout << "Robot[" << i << "] : " << posX + dX << ", " << posY + dY << std::endl;
#endif	//_DEBUG
		}

		////////MAX_BAT Condition////////
		if(battery > MAX_BAT){
			robot->setInput(0, (float)MAX_BAT);
		}else if(battery < 0){
			robot->setInput(0, 0.0f);
		}else{
			robot->setInput(0, battery);
		}
	}
}

	//geoField
void World::generateGeoField(){
	Random<boost::uniform_real<> > rand;
	for(int i = 0; i < FIELD_SIZE; i++){
		for(int j = 0; j < FIELD_SIZE; j++){
			if(rand() < P_BARRIER){
				geoField[i][j] = OUTOFAREA;
			}else{
				geoField[i][j] = NORMAL;
			}
		}
	}
}

void World::generateSemField(){
	//semField
	int startX = this->round((float)START_X);
	int startY = this->round((float)START_Y);
	double startR = START_R;
	for(int i = 0; i < FIELD_SIZE; i++){
		for(int j = 0; j < FIELD_SIZE; j++){
			if(startR > norm((float)(startX - i),(float)(startY - j))){
				if(i == startX && j == startY){
					semField[i][j] = ONSTART;
				}else{
					semField[i][j] = ONCHARGER;
				}
			}else{
				semField[i][j] = OUTOFAREA;
			}
		}
	}
}

bool World::onBatteryCharger(const RobotMAV* robot){
	bool result = false;
	int i = robot->getInput(1);
	int j = robot->getInput(2);
	if(this->semField[i][j] == ONCHARGER){
		result = true;
	}
	return result;
}

bool World::isAlive(const RobotMAV* robot){
	bool result = true;
	if(robot->getInput(0) < 1.0){
		result = false;
	}
	return result;
}