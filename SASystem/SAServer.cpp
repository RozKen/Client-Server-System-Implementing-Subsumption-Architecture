#include "StochasticSelecter.hpp"
#include "Modules.h"
#include "SAServer.h"
#include "EnvUpdater.h"
#include "SensePosition.hpp"
#include "SenseOrientation.hpp"

SAServer::SAServer(): clock(0){
	Initialize();
}
void SAServer::Process(){
	Run();
	Inhibit();
	Suppress();
	Log();
	clock++;
}
void SAServer::Initialize(){

	///環境を構築
	env = new EnvUpdater();

	///Logを設定
	logFileName = "log.csv";
	ofs.open(logFileName);
	//一行目：タイトルを書き込む
	ofs << "clock";
	for(int i = 0; i < NUM_MODULES; i++){
		ofs << ",outbox[" << i << "]";
	}
	for(int i = 0; i < NUM_MODULES; i++){
		ofs << ",connector[" << i << "]";
	}
	for(int i = 0; i < NUM_MODULES; i++){
		ofs << ",inbox[" << i << "]";
	}
	for(int i = 0; i < NUM_MODULES; i++){
		ofs << ",inhibited[" << i << "]";
	}
	for(int i = 0; i < NUM_MODULES; i++){
		ofs << ",suppressed[" << i << "]";
	}
	ofs << std::endl;

	///Moduleを登録
	modules[0] = new ActMotor();
	modules[1] = new ActMotor();
	modules[2] = new MotorDriver(true);
	modules[3] = new MotorDriver(false);
	modules[4] = new Avoid();
	modules[5] = new Wander();
	modules[6] = new Return();
	modules[7] = new SenseRange(env);
	modules[8] = new SensePosition(env);
	modules[9] = new SenseOrientation(env);

	///Module以外のすべての値を0で初期化
	for(int i = 0; i < NUM_MODULES; i++){
		inbox[i] = 0.0;
		outbox[i] = 0.0;
		for(int j = 0; j < NUM_MODULES; j++){
			probInhibition[i][j] = 0.0f;
			probSuppression[i][j] = 0.0f;

			timeInhibition[i][j] = 100;
			timeSuppression[i][j] = 100;
		}
		inhibited[i] = 0;
		suppressed[i] = 0;
	}

	///Inhibitionの確率を設定
	probInhibition[5][4] = 0.8f;	//Wander to Avoid
	probInhibition[6][5] = 0.4f;	//Return to Wander

	///Suppressionの確率を設定
	probSuppression[2][0] = 1.0f;		//LeftMotorDriver(LMD) to LeftMotor(LM)
	probSuppression[3][1] = 1.0f;		//RightMotorDriver)RMD) to RightMotor(RM)
	probSuppression[4][2] = 1.0f;		//Avoid to LMD
	probSuppression[4][3] = 1.0f;		//Avoid to RMD
	probSuppression[7][4] = 1.0f;		//RangeSensor(RS) to Avoid

}

void SAServer::Run(){
	for(int i = 0; i < NUM_MODULES; i++){
#ifdef _DEBUG
		std::cout << "inbox[" << i << "] : " << inbox[i] << std::endl;
#endif //_DEBUG
		outbox[i] = modules[i]->Run(inbox[i]);
	}
	env->update(((ActMotor*)modules[0])->getSpeed(), ((ActMotor*)modules[1])->getSpeed());
}

void SAServer::Inhibit(){
	///Inhibitが正常に行われるよう，上層から処理を行う
	for(int i = NUM_MODULES-1; i >= 0; i--){
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
	for(int i = NUM_MODULES - 1; i >= 0; i --){
		///基本的に，connectorの中身がそのままinboxに流れる
		inbox[i] = connector[i];
		
		for(int j = 0; j < NUM_MODULES; j++){
			///suppressがある場合は，inboxを上書き
			if(probSuppression[j][i] != 0.0){
				suppressed[i]--;
				if(suppressed[i] <= 0){	//前のクロックでsuppressされていなかった場合
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

void SAServer::Log(){
	ofs << clock;
	for(int i = 0; i < NUM_MODULES; i++){
		ofs << "," << outbox[i];
	}
	for(int i = 0; i < NUM_MODULES; i++){
		ofs << "," << connector[i];
	}
	for(int i = 0; i < NUM_MODULES; i++){
		ofs << "," << inbox[i];
	}
	for(int i = 0; i < NUM_MODULES; i++){
		ofs << "," << inhibited[i];
	}
	for(int i = 0; i < NUM_MODULES; i++){
		ofs << "," << suppressed[i];
	}
	ofs << std::endl;
}