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
	probInhibition[5][4] = 0.8;	//Wander to Avoid
	probInhibition[6][5] = 0.4;	//Return to Wander

	//Suppressionの確率を設定
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
	//TODO
	//probInhibitionの確率に応じて，outboxの
	//中身を選択し，inboxを生成
	for(int i = 0; i < NUM_MODULES; i++){
		//inbox[i] = outbox[i];

	}
}

void SAServer::Suppress(){
	//TODO いまはなにもしないよ！
}