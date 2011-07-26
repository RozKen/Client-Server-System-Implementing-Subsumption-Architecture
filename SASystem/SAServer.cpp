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
	//0で初期化
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
	///Inhibitが正常に行われるよう，上層から処理を行う
	for(int i = NUM_MODULES; i > 0; i--){
		///基本的にはoutboxの中身がそのままconnectorに流れる
		connector[i] = outbox[i];
		for(int j = 0; j < NUM_MODULES; j++){
			///inhibitがある場合は，connectorを上書き
			if(probInhibition[j][i] != 0.0){
				inhibited[i]--;
				if(inhibited[i] <= 0){	//前のクロックでinhibitされていなかった場合
					StochasticSelector ss(probInhibition[j][i]);
					if(ss()){		//決められた時間inhibitする
						inhibited[i] = timeInhibition[j][i];
					}else{			//inhibitしない
						inhibited[i] = 0;
					}
				}
				///現クロックでinhibitすることになっている場合，connectorを上書き
				if(inhibited[i] > 0){
					connector[i] = outbox[j];
				}
			}
		}
	}
}

void SAServer::Suppress(){
	///Suppressが正常に行われるよう，上層から処理を行う
	for(int i = NUM_MODULES; i > 0; i --){
		///基本的に，connectorの中身がそのままinboxに流れる
		inbox[i] = connector[i];
		for(int j = 0; j < NUM_MODULES; j++){
			///suppressがある場合は，inboxを上書き
			if(probSuppression[j][i] != 0.0){
				suppressed[i]--;
				if(inhibited[i] <= 0){	//前のクロックでsuppressされていなかった場合
					StochasticSelector ss(probSuppression[j][i]);
					if(ss()){			//決められた時間suppressする
						suppressed[i] = timeSuppression[j][i];
					}else{				//suppressしない
						suppressed[i] = 0;
					}
				}
				///現クロックでsuppressすることになっている場合，inboxを上書き
				if(suppressed[i] > 0){
					inbox[i] = connector[j];
				}
			}
		}
	}
}