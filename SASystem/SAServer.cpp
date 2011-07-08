#include "SAServer.h"

SAServer::SAServer(){
	Initialize();
	while(true){
		Run();
		Inhibit();
		Suppress();
	}
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
	probInhibition[4][0] = 1.0;
	probInhibition[4][1] = 1.0;
	probInhibition[5][4] = 0.7;
	probInhibition[6][5] = 0.2;
	//Suppression�̊m����ݒ�
	//TODO ���܂͂Ȃɂ��ݒ肵�Ȃ���I
	
}

void SAServer::Run(){
	
}

void SAServer::Inhibit(){
	
}

void SAServer::Suppress(){
	//TODO ���܂͂Ȃɂ����Ȃ���I
}