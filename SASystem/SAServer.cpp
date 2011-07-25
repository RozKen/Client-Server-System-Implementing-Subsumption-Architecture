#include "SAServer.h"
#include "SAModule.h"

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
		}
		inhibited[i] = 0;
		suppressed[i] = 0;
	}
	//Inhibition�̊m����ݒ�
	probInhibition[2][0] = 1.0;		//LeftMotorDriver(LMD) to LeftMotor(LM)
	probInhibition[3][1] = 1.0;		//RightMotorDriver)RMD) to RightMotor(RM)
	probInhibition[4][2] = 1.0;		//Avoid to LMD
	probInhibition[4][3] = 1.0;		//Avoid to RMD
	probInhibition[7][4] = 1.0;		//RangeSensor(RS) to Avoid

	//Suppression�̊m����ݒ�
	probSuppression[5][4] = 0.8;	//Wander to Avoid
	probSuppression[6][5] = 0.4;	//Return to Wander
	
}

void SAServer::Run(){
	for(int i = 0; i < NUM_MODULES; i++){
		outbox[i] = modules[i]->Run(inbox[i]);
	}
}

void SAServer::Inhibit(){
	//TODO
	//probInhibition�̊m���ɉ����āCoutbox��
	//���g��I�����Cinbox�𐶐�
	for(int i = 0; i < NUM_MODULES; i++){
		//inbox[i] = outbox[i];

	}
}

void SAServer::Suppress(){
	//TODO ���܂͂Ȃɂ����Ȃ���I
}