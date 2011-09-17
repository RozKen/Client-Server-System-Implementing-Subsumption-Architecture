#include <time.h>
#include <iostream>

//#include "StochasticSelecter.hpp"
//#include "Modules.h"
#include "SAServer.h"
#include "EnvUpdater.h"
#include "SensePosition.hpp"
#include "SenseOrientation.hpp"
#include "SAConnector.h"

SAServer::SAServer(): clock(0){
	Initialize();
}
void SAServer::Process(){
	RunModules();
	ProcessConnectors();
	Log();
	clock++;
}

void SAServer::Initialize(){

	///�����\�z
	env = new EnvUpdater();

	//���ݎ���
	time_t now;
	//���ݎ������擾
	time(&now);
	///Log��ݒ�
	logFileName = "log_";
	logFileName.append(ctime(&now));
	logFileName.erase(logFileName.size() - 12, 1);
	logFileName.erase(logFileName.size() - 9, 1);
	logFileName.erase(logFileName.size() - 1, 1);
	//logFileName.append(now);
	logFileName.append(".csv");
	std::cout << logFileName.c_str() << std::endl;
	ofs.open(logFileName.c_str());

	///Module��o�^
	/*modules[0] = new ActMotor();
	modules[1] = new ActMotor();
	modules[2] = new MotorDriver(true);
	modules[3] = new MotorDriver(false);
	modules[4] = new Avoid();
	modules[5] = new Wander();
	modules[6] = new Return();
	modules[7] = new SenseRange(env);
	modules[8] = new SensePosition(env);
	modules[9] = new SenseOrientation(env);
	*/

	///Module�ȊO�̂��ׂĂ̒l��0�ŏ�����
	/*for(int i = 0; i < NUM_MODULES; i++){
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
	*/
	///Inhibition�̊m����ݒ�
	//probInhibition[5][4] = 0.8f;	//Wander to Avoid
	//probInhibition[6][5] = 0.4f;	//Return to Wander

	///Suppression�̊m����ݒ�
	/*
	probSuppression[2][0] = 1.0f;		//LeftMotorDriver(LMD) to LeftMotor(LM)
	probSuppression[3][1] = 1.0f;		//RightMotorDriver)RMD) to RightMotor(RM)
	probSuppression[4][2] = 1.0f;		//Avoid to LMD
	probSuppression[4][3] = 1.0f;		//Avoid to RMD
	probSuppression[7][4] = 1.0f;		//RangeSensor(RS) to Avoid
	*/
}

void SAServer::addModule(SAModule *module){
	modules.push_back(module);
}

void SAServer::addConnector(SAConnector *connector){
	connectors.push_back(connector);
}

void SAServer::RunModules(){
	for(int i = 0; i < modules.size(); i++){
		modules[i]->Run();
	}
	//env->update(((ActMotor*)modules[0])->getSpeed(), ((ActMotor*)modules[1])->getSpeed());
}

void SAServer::ProcessConnectors(){
	//outputs��������
	outputs = std::vector<float>();
	//Module����output���擾
	for(int i = 0; i < modules.size(); i++){
		for(int j = 0; j < modules[i]->getNumOfOutputPorts(); j++){
			outputs.push_back(modules[i]->getOutput(j));
		}
	}
	//Inhibit�����s
	for(int i = 0; i < connectors.size(); i++){
		//type == Inhibit�̂Ƃ�Process�����s
		if(connectors[i]->getType() == 1){
			connectors[i]->Process();
		}
	}

	//inhibited��������
	inhibited = std::vector<float>();
	//Module����output���擾
	for(int i = 0; i < modules.size(); i++){
		for(int j = 0; j < modules[i]->getNumOfOutputPorts(); j++){
			inhibited.push_back(modules[i]->getOutput(j));
		}
	}
	//Wire�����s
	for(int i = 0; i < connectors.size(); i++){
		//type == Wire�̂Ƃ�Process�����s
		if(connectors[i]->getType() == 0){
			connectors[i]->Process();
		}
	}

	//preSuppress��������
	preSuppress = std::vector<float>();
	//Module����input���擾
	for(int i = 0; i < modules.size(); i++){
		for(int j = 0; j < modules[i]->getNumOfInputPorts(); j++){
			preSuppress.push_back(modules[i]->getInput(j));
		}
	}
	//Suppress�����s
	for(int i = 0; i < connectors.size(); i++){
		//type == Suppress�̂Ƃ�Process�����s
		if(connectors[i]->getType() == 2){
			connectors[i]->Process();
		}
	}

	//inputs��������
	inputs = std::vector<float>();
	//Module����input���擾
	for(int i = 0; i < modules.size(); i++){
		for(int j = 0; j < modules[i]->getNumOfInputPorts(); j++){
			inputs.push_back(modules[i]->getInput(j));
		}
	}
}

void SAServer::Log(){
	if(clock == 0){
		//��s�ځF�^�C�g������������
		ofs << "clock,posX,posY,Orient,Range,DiffX,DiffY,DiffOrient";
		
		for(int i = 0; i < outputs.size(); i++){
			ofs << ",out[" << i << "]";
		}
		for(int i = 0; i < inhibited.size(); i++){
			ofs << ",inhbt[" << i << "]";
		}
		for(int i = 0; i < preSuppress.size(); i++){
			ofs << ",preSprs[" << i << "]";
		}
		for(int i = 0; i < inputs.size(); i++){
			ofs << ",inputs[" << i << "]";
		}
		/*for(int i = 0; i < NUM_MODULES; i++){
			ofs << ",inhbt[" << i << "]";
		}
		for(int i = 0; i < NUM_MODULES; i++){
			ofs << ",suprs[" << i << "]";
		}
		*/
		ofs << std::endl;
	}

	ofs << clock;
	ofs << "," << env->getPositionX();
	ofs << "," << env->getPositionY();
	ofs << "," << env->getOrientation();
	ofs << "," << env->getRange();
	ofs << "," << env->getDiffPosX();
	ofs << "," << env->getDiffPosY();
	ofs << "," << env->getDiffOrient();

	for(int i = 0; i < outputs.size(); i++){
		ofs << "," << outputs[i];
	}
	for(int i = 0; i < inhibited.size(); i++){
		ofs << "," << inhibited[i];
	}
	for(int i = 0; i < preSuppress.size(); i++){
		ofs << "," << preSuppress[i];
	}
	for(int i = 0; i < inputs.size(); i++){
		ofs << "," << inputs[i];
	}
	/*for(int i = 0; i < NUM_MODULES; i++){
		ofs << "," << inhibited[i];
	}
	for(int i = 0; i < NUM_MODULES; i++){
		ofs << "," << suppressed[i];
	}
	*/
	ofs << std::endl;
}