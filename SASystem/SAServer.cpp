#include <time.h>
#include <iostream>

//#include "StochasticSelecter.hpp"
#include "Modules.h"
#include "SAServer.h"
#include "EnvUpdater.h"
#include "SAConnector.h"

SAServer::SAServer(int* field): clock(0), field(field){
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
	env = new EnvUpdater(field);

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
	env->update(((PositionUpdater*)modules[0])->getProgress());
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
		ofs << "clock,pos,battery,progress";
		
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
	ofs << "," << env->getPosition();
	ofs << "," << env->getBattery();
	ofs << "," << env->getProgress();

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