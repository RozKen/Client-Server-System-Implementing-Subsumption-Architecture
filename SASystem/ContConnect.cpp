#include "ContConnect.hpp"
#include "RobotMAV.h"

void ContConnect::Run(){
	//�o�͐M���F��{NO_SIGNAL
	float signalX = NO_SIGNAL;
	float signalY = NO_SIGNAL;
#ifdef	IMPORTANCE_BASED
	this->importance = NO_SIGNAL;
#endif	//IMPORTANCE_BASED

	//�؂ꂻ���Ȃ̂���������C�������̕��ցD
	//�؂ꂻ���Ȃ��̂̂����C��ԋ߂�Robot�̕��֌�����	//for Loop���t�ɂ��Ă���.
	for(int i = WIFI_CONNECT - 1; i >= 0 ; i--){
		float dx = this->getInput(i * 2);
		float dy = this->getInput(i * 2 + 1);
		float distance = this->norm(dx, dy);
		if(distance > WIFI_REACH * WIFI_WEAK && dx != NO_SIGNAL && dy != NO_SIGNAL){
			signalX = (float)MAX_DRIVE * dx / distance;
			signalY = (float)MAX_DRIVE * dy / distance;
#ifdef	IMPORTANCE_BASED
			//�d�v�x�́C�ڑ����Ă���Robot�̐��Ɉˑ�����
			this->importance = this->calcImportance(WIFI_CONNECT - 1 - i);
#endif	//IMPORTANCE_BASED
		}
	}

	//�؂ꂻ���Ȃ��̂��Ȃ�������C���X�o�����X���Ƃ�	//���ۂ͎g���ĂȂ�.(WIFI_BALANCE = 0.0f)
	if(signalX == NO_SIGNAL && signalY == NO_SIGNAL){
		float random = rand();
		if(random < WIFI_BALANCE){
			signalX = 0.0f;
			signalY = 0.0f;
			for(int i = 0; i < WIFI_CONNECT; i++){
				signalX += this->getInput( i * 2 );
				signalY += this->getInput( i * 2 + 1 );
			}
			float distance = this->norm(signalX, signalY);
			if(distance != 0.0f){
				signalX /= distance;
				signalY /= distance;
			}
			signalX *= (float)MAX_DRIVE;
			signalY *= (float)MAX_DRIVE;
#ifdef	IMPORTANCE_BASED
			this->importance = this->calcImportance(1.0f - random / WIFI_BALANCE);
#endif	//IMPORTANCE_BASED
		}
	}

	//�o��
	this->setOutput(0, signalX);
	this->setOutput(1, signalY);
}