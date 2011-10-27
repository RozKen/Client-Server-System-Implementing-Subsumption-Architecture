#include <time.h>
#include <iostream>
#include <sstream>

//#include "StochasticSelecter.hpp"
#include "Modules.h"
#include "SAServer.h"
#include "EnvUpdater.h"
#include "SAConnector.h"

SAServer::SAServer(const int* field, std::string logDirectoryPath): clock(0), field(field), index(0), stepForward(0),
	stepStop(0), stepBackward(0), stepSwitchDirection(0), prevPos(-1), prevDirection(true), logDirectoryPath(logDirectoryPath)
{
	Initialize();
}
SAServer::SAServer(const int* field, std::string logDirectoryPath, int index): clock(0), field(field), index(index), stepForward(0),
	stepStop(0), stepBackward(0), stepSwitchDirection(0), prevPos(-1), prevDirection(true), logDirectoryPath(logDirectoryPath)
{
	Initialize();
}
void SAServer::Process(){
	RunModules();
	ProcessConnectors();
	Log();
	clock++;
}
std::string SAServer::intToString(int number){
	std::string str = "";
	std::stringstream ss;
	ss << number;
	if(number / 1000 > 0){
		str = ss.str();
	}else if(number / 100 > 0){
		str = "0";
		str.append(ss.str());
	}else if(number / 10 > 0){
		str = "00";
		str.append(ss.str());
	}else{
		str = "000";
		str.append(ss.str());
	}
	return str;
}
void SAServer::Initialize(){

	///環境を構築
	env = new EnvUpdater(field);

	//現在時刻
	time_t now;
	//現在時刻を取得
	time(&now);
	///Logを設定
	logFileName = logDirectoryPath;
	logFileName.append("/");
	logFileName.append(intToString(index));
	logFileName.append("_log");
	
	logFileName.append(".csv");
	std::cout << "logFileLocation" << logFileName.c_str() << std::endl;
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
	//outputsを初期化
	outputs = std::vector<float>();
	//Moduleからoutputを取得
	for(int i = 0; i < modules.size(); i++){
		for(int j = 0; j < modules[i]->getNumOfOutputPorts(); j++){
			outputs.push_back(modules[i]->getOutput(j));
		}
	}
	//Inhibitを実行
	for(int i = 0; i < connectors.size(); i++){
		//type == InhibitのときProcessを実行
		if(connectors[i]->getType() == 1){
			connectors[i]->Process();
		}
	}

	//inhibitedを初期化
	inhibited = std::vector<float>();
	//Moduleからoutputを取得
	for(int i = 0; i < modules.size(); i++){
		for(int j = 0; j < modules[i]->getNumOfOutputPorts(); j++){
			inhibited.push_back(modules[i]->getOutput(j));
		}
	}
	//Wireを実行
	for(int i = 0; i < connectors.size(); i++){
		//type == WireのときProcessを実行
		if(connectors[i]->getType() == 0){
			connectors[i]->Process();
		}
	}

	//preSuppressを初期化
	preSuppress = std::vector<float>();
	//Moduleからinputを取得
	for(int i = 0; i < modules.size(); i++){
		for(int j = 0; j < modules[i]->getNumOfInputPorts(); j++){
			preSuppress.push_back(modules[i]->getInput(j));
		}
	}
	//Suppressを実行
	for(int i = 0; i < connectors.size(); i++){
		//type == SuppressのときProcessを実行
		if(connectors[i]->getType() >= 2){
			connectors[i]->Process();
		}
	}

	//inputsを初期化
	inputs = std::vector<float>();
	//Moduleからinputを取得
	for(int i = 0; i < modules.size(); i++){
		for(int j = 0; j < modules[i]->getNumOfInputPorts(); j++){
			inputs.push_back(modules[i]->getInput(j));
		}
	}
}

void SAServer::Log(){
	if(clock == 0){
		//一行目：タイトルを書き込む
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

		prevPos = 0;
	}else{
		if(clock % 3 == 0){
			int currentPos = env->getPosition();
			bool currentDirection;
			if((currentPos - prevPos) > 0){
				stepForward++;
				prevPos = currentPos;
				currentDirection = true;
				if(currentDirection != prevDirection){
					stepSwitchDirection++;
					prevDirection = currentDirection;
				}
			}else if((currentPos - prevPos) == 0){
				stepStop ++;
			}else if((currentPos - prevPos) < 0){
				stepBackward ++;
				prevPos = currentPos;
				currentDirection = false;
				if(currentDirection != prevDirection){
					stepSwitchDirection++;
					prevDirection = currentDirection;
				}
			}
		}
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

	ofs << std::endl;
}