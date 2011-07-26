#include "SAServer.h"
#include "SAModule.h"
#include "StochasticSelecter.hpp"

SAServer::SAServer(){
	Initialize();
}
void SAServer::Process(){
	Run();
	Inhibit();
	Suppress();
}
void SAServer::Initialize(){
	//0�ŏ�����
	for(int i = 0; i < NUM_MODULES; i++){
		inbox[i] = 0.0;
		outbox[i] = 0.0;
		for(int j = 0; j < NUM_MODULES; j++){
			probInhibition[i][j] = 0.0;
			probSuppression[i][j] = 0.0;

			timeInhibition[i][j] = 100;
			timeSuppression[i][j] = 100;
		}
		inhibited[i] = 0;
		suppressed[i] = 0;
	}

	//Inhibition�̊m����ݒ�
	probInhibition[5][4] = 0.8;	//Wander to Avoid
	probInhibition[6][5] = 0.4;	//Return to Wander

	//Suppression�̊m����ݒ�
	probSuppression[2][0] = 1.0;		//LeftMotorDriver(LMD) to LeftMotor(LM)
	probSuppression[3][1] = 1.0;		//RightMotorDriver)RMD) to RightMotor(RM)
	probSuppression[4][2] = 1.0;		//Avoid to LMD
	probSuppression[4][3] = 1.0;		//Avoid to RMD
	probSuppression[7][4] = 1.0;		//RangeSensor(RS) to Avoid
}

void SAServer::Run(){
	for(int i = 0; i < NUM_MODULES; i++){
		outbox[i] = modules[i]->Run(inbox[i]);
	}
}

void SAServer::Inhibit(){
	///Inhibit������ɍs����悤�C��w���珈�����s��
	for(int i = NUM_MODULES; i > 0; i--){
		///��{�I�ɂ�outbox�̒��g�����̂܂�connector�ɗ����
		connector[i] = outbox[i];
		for(int j = 0; j < NUM_MODULES; j++){
			///inhibit������ꍇ�́Cconnector���㏑��
			if(probInhibition[j][i] != 0.0){
				inhibited[i]--;
				if(inhibited[i] <= 0){	//�O�̃N���b�N��inhibit����Ă��Ȃ������ꍇ
					StochasticSelector ss(probInhibition[j][i]);
					if(ss()){		//���߂�ꂽ����inhibit����
						inhibited[i] = timeInhibition[j][i];
					}else{			//inhibit���Ȃ�
						inhibited[i] = 0;
					}
				}
				///���N���b�N��inhibit���邱�ƂɂȂ��Ă���ꍇ�Cconnector���㏑��
				if(inhibited[i] > 0){
					connector[i] = outbox[j];
				}
			}
		}
	}
}

void SAServer::Suppress(){
	///Suppress������ɍs����悤�C��w���珈�����s��
	for(int i = NUM_MODULES; i > 0; i --){
		///��{�I�ɁCconnector�̒��g�����̂܂�inbox�ɗ����
		inbox[i] = connector[i];
		for(int j = 0; j < NUM_MODULES; j++){
			///suppress������ꍇ�́Cinbox���㏑��
			if(probSuppression[j][i] != 0.0){
				suppressed[i]--;
				if(inhibited[i] <= 0){	//�O�̃N���b�N��suppress����Ă��Ȃ������ꍇ
					StochasticSelector ss(probSuppression[j][i]);
					if(ss()){			//���߂�ꂽ����suppress����
						suppressed[i] = timeSuppression[j][i];
					}else{				//suppress���Ȃ�
						suppressed[i] = 0;
					}
				}
				///���N���b�N��suppress���邱�ƂɂȂ��Ă���ꍇ�Cinbox���㏑��
				if(suppressed[i] > 0){
					inbox[i] = connector[j];
				}
			}
		}
	}
}