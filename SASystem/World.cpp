#include "World.h"
#include "RobotMAV.h"
World::World(){
	//robotPos = new std::vector<position>();
	int tmp[2][HASH_MAX] = {
		{0,0,1,0,-1,0,1,2,1,0,-1,-2,-1,0,1,2,3,2,1,0,-1,-2,-3,-2,-1},
		{0,1,0,-1,0,2,1,0,-1,-2,-1,0,1,3,2,1,0,-1,-2,-3,-2,-1,0,1,2}
	};
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < HASH_MAX; j++){
			hash[i][j] = tmp[i][j];
		}
	}
}

World::World(std::string directoryPath, std::string fileName)
	:Robot(directoryPath, fileName){
	int tmp[2][HASH_MAX] = {
		{0,0,1,0,-1,0,1,2,1,0,-1,-2,-1,0,1,2,3,2,1,0,-1,-2,-3,-2,-1},
		{0,1,0,-1,0,2,1,0,-1,-2,-1,0,1,3,2,1,0,-1,-2,-3,-2,-1,0,1,2}
	};
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < HASH_MAX; j++){
			hash[i][j] = tmp[i][j];
		}
	}
	this->Initialize();
}

void World::Initialize(){
	generateGeoField();
	generateSemField();
}

int World::getHash(int which, int index) const{
	return hash[which][index];
}

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
		robot = this->getRobot(i);
		////////Battery////////
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
			float newX = posX + dX;
			if(newX < 0.0f){
				newX = 0.0f;
			}else if(newX > FIELD_SIZE){
				newX = FIELD_SIZE;
			}
			robot->setInput(1, newX);
			//fPosY = fPosY + fDeltaY
			float posY = robot->getInput(2);
			float dY = robot->getOutput(1);
			float newY = posY + dY;
			if(newY < 0.0f){
				newY = 0.0f;
			}else if(newY > FIELD_SIZE){
				newY = FIELD_SIZE;
			}
			robot->setInput(2, newY);
			//Positionに応じてBatteryを減らす
			if(sqrt(dX) > 0 || sqrt(dY) > 0){
				battery -= (float)BAT_LOSS;
			}

			////////Range////////
			updateRange(robot);
			////////Network////////
			updateNetWork(robot);
#ifdef _DEBUG
		//	std::cout << "Robot[" << i << "] : " << posX + dX << ", " << posY + dY << std::endl;
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
		
		//For Debug//////////////////////////////////////////////////////////////////////////////////
		//robot->setInput(0, (float)MAX_BAT);
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
	////File Output
	std::string fileName = this->getLogDirectoryPath();
	fileName.append("/geoField.csv");
	std::ofstream ofsGeoField(fileName);
	for(int i = FIELD_SIZE - 1; i >= 0; i--){
		for(int j = 0; j < FIELD_SIZE; j++){
			ofsGeoField << geoField[j][i] << ",";
		}
		ofsGeoField << std::endl;
	}
	ofsGeoField.close();
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

	////File Output
	std::ofstream ofsSemField;
	std::string fileName = this->getLogDirectoryPath();
	fileName.append("/semField.csv");
	ofsSemField.open(fileName);
	for(int i = FIELD_SIZE - 1; i >= 0; i--){
		for(int j = 0; j < FIELD_SIZE; j++){
			ofsSemField << semField[j][i] << ",";
		}
		ofsSemField << std::endl;
	}
	ofsSemField.close();
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
	//robotの座標 (int)
	int x = round(robot->getInput(1));
	int y = round(robot->getInput(2));
	/**
		@brief value[x][y] 
		x,yは左下が原点
	 */
	int value[RANGE * 2 + 1][RANGE * 2 + 1];
	//int value[7][7];

	for(int i = 0; i < RANGE * 2 + 1; i++){
		for(int j = 0; j < RANGE * 2 + 1; j++){
			value[i][j] = NORMAL;
		}
	}

	////////Field外の検出////////
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
		if(boundary[i] > RANGE){
			boundary[i] = RANGE;
		}else{
			for(int j = boundary[i]; j < RANGE; j++){
				switch(i){
				case 0:		//North Boundary
					for(int x = 0; x < RANGE * 2 + 1; x++){
						value[x][RANGE + 1 + j] = OUTOFAREA;
					}
					break;
				case 1:		//East Boundary
					for(int y = 0; y < RANGE * 2 + 1; y++){
						value[RANGE + 1 + j][y] = OUTOFAREA;
					}
					break;
				case 2:		//South Boundary
					for(int x = 0; x < RANGE * 2 + 1; x++){
						value[x][RANGE - 1 - j] = OUTOFAREA;
					}
					break;
				case 3:		//West Boundary
					for(int y = 0; y < RANGE * 2 + 1; y++){
						value[RANGE - 1 - j][y] = OUTOFAREA;
					}
					break;
				default:	//想定外
					break;
				}
			}
		}
	}

	////////近隣の障害物情報////////
	int searchX;	//現在Searchしている位置X
	int searchY;	//現在Searchしている位置Y
	for(int i = -RANGE; i <= RANGE; i++){
		for(int j = -RANGE; j <= RANGE; j++){
			searchX = x + i;
			searchY = y + j;
			//Robotの近傍がField内の時
			if( searchX >= 0 && searchX < FIELD_SIZE
				&& searchY >= 0 && searchY < FIELD_SIZE){
					//地形情報が普通じゃないとき
					if(geoField[searchX][searchY] != NORMAL){
						value[i + RANGE][j + RANGE] = geoField[searchX][searchY];
					}
			}
		}
	}
	////////近隣のrobotを探す////////
	float robotX, robotY;
	for(int i = 0; i < this->numOfModules; i++){
		robotX = this->getRobot(i)->getInput(1);
		robotY = this->getRobot(i)->getInput(2);
		if(robotX != robot->getPosX() && robotY != robot->getPosY()){
			if( robotX < x + RANGE && robotX > x - RANGE
				&& robotY < y + RANGE && robotY > y - RANGE){
					value[(int)robotX - x + RANGE][(int)robotY - y + RANGE] = ROBOTEXIST;
			}
		}
	}
	////////RANGEへinput////////
	////どのRangeへ出力するかを決定する
	/**
		@brief そのindexにあるvalueがどのRANGEに送られるかを保持する
		<ul>
			<li>Range0: 345 <= theta < 360 || 0 <= theta < 15 </li>
			<li>Range1: 15 <= theta < 45</li>
			<li>Range2: 45 <= theta < 75</li>
			<li>Range3: 75 <= theta < 105</li>
			<li>Range4: 105 <= theta < 135</li>
			<li>Range5: 135 <= theta < 165</li>
			<li>Range6: 165 <= theta < 195</li>
			<li>Range7: 195 <= theta < 225</li>
			<li>Range8: 225 <= theta < 255</li>
			<li>Range9: 255 <= theta < 285</li>
			<li>Range10: 285 <= theta < 315</li>
			<li>Range11: 315 <= theta < 345</li>
		</ul>
		@sa value
	 */
	int orientation[RANGE * 2 + 1][RANGE * 2 + 1];
	for(int i = 0; i < RANGE * 2 + 1; i++){
		for(int j = 0; j < RANGE * 2 + 1; j++){
			//単位pi : [-PI/2, PI/2]
			double phi = atan( ((double)j - (double)RANGE) / ((double)i - (double)RANGE) );
			double theta = phi * 180.0 / PI;
			
			//象限ごとに追加の処理を行なう
			if(i - RANGE < 0){
				theta += 180.0;
			}else if(j - RANGE < 0){	//第四象限
				theta += 360.0f;
			}

			if( (theta >= 345 && theta < 360) || ( theta >= 0 && theta < 15) ){
				orientation[i][j] = 0;
			}else if ( theta >= 15 && theta < 45){
				orientation[i][j] = 1;
			}else if ( theta >= 45 && theta < 75){
				orientation[i][j] = 2;
			}else if ( theta >= 75 && theta < 105){
				orientation[i][j] = 3;
			}else if ( theta >= 105 && theta < 135){
				orientation[i][j] = 4;
			}else if ( theta >= 135 && theta < 165){
				orientation[i][j] = 5;
			}else if ( theta >= 165 && theta < 195){
				orientation[i][j] = 6;
			}else if ( theta >= 195 && theta < 225){
				orientation[i][j] = 7;
			}else if ( theta >= 225 && theta < 255){
				orientation[i][j] = 8;
			}else if ( theta >= 255 && theta < 285){
				orientation[i][j] = 9;
			}else if ( theta >= 285 && theta < 315){
				orientation[i][j] = 10;
			}else if ( theta >= 315 && theta < 345){
				orientation[i][j] = 11;
			}else{
				//orientation[RANGE][RANGE]のみ
				orientation[i][j] = 0;
			}
		}
	}
	////最も近いSensorValueを決める．
	/**
		@brief 各方向のRangeSensorへ送る信号
	 */
	float signal[RANGE_DIV];
	for(int i = 0; i < RANGE_DIV; i++){
		//信号の初期化.余裕を持って大きめにしてある．
		signal[i] = RANGE_DANGER * 2.0f;
	}
	//一番近い障害物の距離で上書きしていく
	for(int i = 0; i < RANGE * 2 + 1; i++){
		for(int j = 0; j < RANGE * 2 + 1; j++){
			if(value[i][j] != NORMAL){
				float distance = norm(((double)(i - RANGE)), ((double)(RANGE - j)));

				if( distance < signal[orientation[i][j]] ){
					signal[orientation[i][j]] = distance;
				}
			}
		}
	}

	////Rangeへ出力する
	for(int i = 0; i < RANGE_DIV; i++){
		robot->setInput(3 + i, signal[i]);
	}
}

void World::updateNetWork(RobotMAV* robot){
	//現在位置
	float x = robot->getPosX();
	float y = robot->getPosY();
	//現在位置に近いロボットをPickUp
	std::vector<RobotMAV*>* neighbors = new std::vector<RobotMAV*>();
	for(int i = 0; i < this->numOfModules; i++){
		float xi = (this->getRobot(i))->getPosX();
		float yi = (this->getRobot(i))->getPosY();
		if(this->norm(xi - x, yi - y) < WIFI_REACH){
			neighbors->push_back(this->getRobot(i));
		}

	}
	//昇順にソート
	std::sort(neighbors->begin(), neighbors->end());
	robot->clearNearest();
	for(int i = 0; i < 5 && i < neighbors->size(); i++){
		//nearestを設定
		robot->pushNearest(neighbors->at(i));
		//fBoardを設定
		robot->getSenseNet()->setFBoard(i * 2, neighbors->at(i)->getPosX() - x);
		robot->getSenseNet()->setFBoard(i * 2 + 1, neighbors->at(i)->getPosY() - y);
	}
}