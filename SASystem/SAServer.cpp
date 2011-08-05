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

	///�����\�z
	env = new EnvUpdater();

	///Log��ݒ�
	logFileName = "log.csv";
	ofs.open(logFileName);
	//��s�ځF�^�C�g������������
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

	///Module��o�^
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

	///Module�ȊO�̂��ׂĂ̒l��0�ŏ�����
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

	///Inhibition�̊m����ݒ�
	probInhibition[5][4] = 0.8f;	//Wander to Avoid
	probInhibition[6][5] = 0.4f;	//Return to Wander

	///Suppression�̊m����ݒ�
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
	///Inhibit������ɍs����悤�C��w���珈�����s��
	for(int i = NUM_MODULES-1; i >= 0; i--){
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
	for(int i = NUM_MODULES - 1; i >= 0; i --){
		///��{�I�ɁCconnector�̒��g�����̂܂�inbox�ɗ����
		inbox[i] = connector[i];
		
		for(int j = 0; j < NUM_MODULES; j++){
			///suppress������ꍇ�́Cinbox���㏑��
			if(probSuppression[j][i] != 0.0){
				suppressed[i]--;
				if(suppressed[i] <= 0){	//�O�̃N���b�N��suppress����Ă��Ȃ������ꍇ
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