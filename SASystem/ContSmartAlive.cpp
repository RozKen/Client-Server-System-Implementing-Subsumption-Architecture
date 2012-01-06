#include "ContSmartAlive.hpp"
#include "RobotMAV.h"

ContSmartAlive::ContSmartAlive() : distance(NO_SIGNAL){

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
	//��{�I��NO_SIGNAL���o��
	float signalX = NO_SIGNAL;
	float signalY = NO_SIGNAL;
#ifdef	IMPORTANCE_BASED
	this->importance = NO_SIGNAL;
#endif	//IMPORTANCE_BASED
	//Charge���̎�
	if(this->getIBoard(0) == 1){
		signalX = 0.0f;
		signalY = 0.0f;
#ifdef	IMPORTANCE_BASED
	this->importance = VERY_IMPORTANT;
#endif	//IMPORTANCE_BASED
		if(this->getInput(2) >= MAX_BAT){
			//Charge�ς݂Ƃ���
			this->setIBoard(0, 0);
			this->distance = NO_SIGNAL;
		}
	}else{	//Charge������Ȃ��Ƃ�
		//Battery�����Ȃ��āC�[�d��̏�ɂ���Ƃ�
		if(this->getInput(2) < MAX_BAT * 0.5 && this->getInput(3) == 1.0f){
			//Charge���Ƃ���
			this->setIBoard(0, 1);
			//��~����=�[�d����
			signalX = 0.0f;
			signalY = 0.0f;
#ifdef	IMPORTANCE_BASED
			this->importance = VERY_IMPORTANT;
#endif	//IMPORTANCE_BASED
		}else{	//�[�d��̏�ɂ͂��Ȃ���
			if(findNearestCharger()){
				//Battery������Ȃ��Ȃ肻����������
				if(distance > SURPLUS * this->getInput(2) / BAT_LOSS){
					//�ł��߂��[�d�G���A�֌�����
					signalX = (float)MAX_DRIVE * (nearestCharger[0] - this->getInput(0)) / distance;
					signalY = (float)MAX_DRIVE * (nearestCharger[1] - this->getInput(1)) / distance;
#ifdef	IMPORTANCE_BASED
					this->importance = 1.0f;
#endif	//IMPORTANCE_BASED
				}
			}//else ������Ȃ�������C���߂�D
		}
	}
	//Set Outputs
	this->setOutput(0, signalX);
	this->setOutput(1, signalY);
}

bool ContSmartAlive::findNearestCharger(){
	bool result = false;
	float posX = this->getInput(0);
	float posY = this->getInput(1);
	//�ǂ����悤���Ȃ��i�ߕ����牓���Ƃ��́C���߂�D
	if(norm(posX - START_X, posY - START_Y) - 5.0f > this->getInput(2) / BAT_LOSS){
		result = false;
	}else{
		int x, y;
		float distance = 1000.0f;
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
		}else{
			nearestCharger[0] = NO_SIGNAL;
			nearestCharger[1] = NO_SIGNAL;
			distance = NO_SIGNAL;
		}
	}

	return result;
}