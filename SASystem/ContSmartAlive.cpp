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
	//Charge���̎�
	if(this->getIBoard(0) == 1){
		signalX = 0.0f;
		signalY = 0.0f;
		if(this->getInput(2) >= MAX_BAT){
			//Charge�ς݂Ƃ���
			this->setIBoard(0, 0);
		}
	}else{	//Charge������Ȃ��Ƃ�
		//Battery�����Ȃ��āC�[�d��̏�ɂ���Ƃ�
		if(this->getInput(2) < MAX_BAT * 0.5 && this->getInput(3) == 1.0f){
			//Charge���Ƃ���
			this->setIBoard(0, 1);
			//��~����=�[�d����
			signalX = 0.0f;
			signalY = 0.0f;
		}else{
			if(findNearestCharger()){
				//Battery������Ȃ��Ȃ肻����������
				if(distance > SURPLUS * this->getInput(2) / BAT_LOSS){
					//�����֌�����
					signalX = (float)MAX_DRIVE * (nearestCharger[0] - this->getInput(0)) / distance;
					signalY = (float)MAX_DRIVE * (nearestCharger[1] - this->getInput(1)) / distance;
				}
			}//else ������Ȃ�������C���߂�D
		}
	}

	this->setOutput(0, signalX);
	this->setOutput(1, signalY);
}

bool ContSmartAlive::findNearestCharger(){
	bool result = false;
	float posX = this->getInput(0);
	float posY = this->getInput(1);
	//�ǂ����悤���Ȃ��i�ߕ����牓���Ƃ��́C���߂�D
	if(norm(posX - START_X, posY - START_Y) > (float)MAX_DRIVE * MAX_BAT / BAT_LOSS){
		result = false;
	}else{
		int x, y;
		float distance = 1000.0;
		for(int i = 0; i < FIELD_SIZE; i++){
			for(int j = 0; j < FIELD_SIZE; j++){
				if(((RobotMAV*)(this->parent))->semMap[i][j] == ONCHARGER
					|| ((RobotMAV*)(this->parent))->semMap[i][j] == ONSTART){
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
			//�}���n�b�^�������ɂ��Ă݂�
			this->distance = (posX - x) + (posY - y);
		}
	}

	return result;
}