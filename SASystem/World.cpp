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

			////////Range////////
			updateRange(robot);
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

void World::updateRange(RobotMAV* robot){
	//robotの座標
	float x = robot->getInput(1);
	float y = robot->getInput(2);
	/**
		@brief value[x][y] 
		x,yは左上が0
		(0,0),(1,0)
		(0,1),(1,1)
	 */
	float value[RANGE * 2 + 1][RANGE * 2 + 1];

	for(int i = 0; i < RANGE * 2 + 1; i++){
		for(int j = 0; j < RANGE * 2 + 1; j++){
			value[i][j] = NORMAL;
		}
	}

	//Field外の検出
	int boundary[4];
	//north
	boundary[0] = FIELD_SIZE - 1 - round(y);
	//east
	boundary[1] = FIELD_SIZE - 1 - round(x);
	//south
	boundary[2] = y;
	//west
	boundary[3] = x;
	for(int i = 0; i < 4; i++){
		if(boundary[i] > RANGE_DANGER){
			boundary[i] = RANGE_DANGER;
		}else{
			for(int j = boundary[i]; j < RANGE; j++){
				switch(i){
				case 0:		//North Boundary
					for(int x = 0; x < RANGE * 2; x++){
						value[x][j - boundary[i]] = OUTOFAREA;
					}
					break;
				case 1:		//East Boundary
					for(int y = 0; y < RANGE * 2; y++){
						value[j][y] = OUTOFAREA;
					}
					break;
				case 2:		//South Boundary
					for(int x = 0; x < RANGE * 2; x++){
						value[x][j] = OUTOFAREA;
					}
					break;
				case 3:		//West Boundary
					for(int y = 0; y < RANGE * 2; y++){
						value[j - boundary[i]][y] = OUTOFAREA;
					}
					break;
				default:	//想定外
					break;
				}
			}
		}
	}

	//近隣の障害物情報

	//近隣のrobotを探す

	//RANGEへinput
}