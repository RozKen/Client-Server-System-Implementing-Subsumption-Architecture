#include "SAServer.h"
#include "SAModule.h"

SAServer::SAServer(){
	Initialize();
	while(true){
		Run();
		Inhibit();
		Suppress();
	}
}

void SAServer::Initialize(){
	//0で初期化
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
	//Inhibitionの確率を設定
	probInhibition[2][4] = 1.0;		//RangeSensor	-> avoid
	probInhibition[4][0] = 1.0;		//avoid			-> LeftMotor
	probInhibition[4][1] = 1.0;		//avoid			-> RightMotor
	probInhibition[5][4] = 0.7;		//wander		-> avoid
	probInhibition[6][5] = 0.2;		//return		-> wander
	//Suppressionの確率を設定
	//TODO いまはなにも設定しないよ！
	
}

void SAServer::Run(){
	for(int i = 0; i < NUM_MODULES; i++){
		outbox[i] = modules[i]->Run(inbox[i]);
	}
}

void SAServer::Inhibit(){
	//
	for(int i = 0; i < NUM_MODULES; i++){
		//inbox[i] = outbox[i];
	}
}

void SAServer::Suppress(){
	//TODO いまはなにもしないよ！
}