#include "World.h"
#include "RobotMAV.h"

void World::Run(){
	this->RunRobots();
	this->Update();
	//���݂̏�Ԃ��L�^
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
		//Battery�ȊO�́C�����Ă���Ƃ������C�쓮����
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
			//Position�ɉ�����Battery�����炷
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
	//robot�̍��W
	float x = robot->getInput(1);
	float y = robot->getInput(2);
	/**
		@brief value[x][y] 
		x,y�͍��オ0
		(0,0),(1,0)
		(0,1),(1,1)
	 */
	int value[RANGE * 2 + 1][RANGE * 2 + 1];

	for(int i = 0; i < RANGE * 2 + 1; i++){
		for(int j = 0; j < RANGE * 2 + 1; j++){
			value[i][j] = NORMAL;
		}
	}

	////////Field�O�̌��o////////
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
				default:	//�z��O
					break;
				}
			}
		}
	}

	////////�ߗׂ̏�Q�����////////

	////////�ߗׂ�robot��T��////////

	////////RANGE��input////////
	////�ǂ�Range�֏o�͂��邩�����肷��
	/**
		@brief ����index�ɂ���value���ǂ�RANGE�ɑ����邩��ێ�����
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
			double theta = atan( ((double)i - (double)RANGE) / ((double)RANGE - (double)j) );
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
				//Error�������N����
				orientation[i][j] = -1;
			}
		}
	}
	////�ł��߂�SensorValue�����߂�D
	/**
		@brief �e������RangeSensor�֑���M��
	 */
	float signal[RANGE_DIV];
	for(int i = 0; i < RANGE_DIV; i++){
		//�M���̏�����.�]�T�������đ傫�߂ɂ��Ă���D
		signal[i] = RANGE_DANGER * 2.0f;
	}
	//��ԋ߂���Q���̋����ŏ㏑�����Ă���
	for(int i = 0; i < RANGE * 2 + 1; i++){
		for(int j = 0; j < RANGE * 2 + 1; j++){
			if(value[i][j] != NORMAL){
				float distance = norm((i - RANGE), (RANGE - j));

				if( distance < signal[orientation[i][j]] ){
					signal[orientation[i][j]] = distance;
				}
			}
		}
	}

	////Range�֏o�͂���
	for(int i = 0; i < RANGE_DIV; i++){
		robot->setInput(3 + i, signal[i]);
	}
}