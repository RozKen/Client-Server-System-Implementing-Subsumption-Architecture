#include <iostream>
#include <string>

#include "Constants.h"

#include "EnvUpdater.h"
#include "SAServer.h"
#include "Modules.h"
#include "SAConnector.h"
#include "Random.hpp"
#include <time.h>
#include <iostream>

//for wait
#include <Windows.h>

Random<boost::uniform_int<> > _numBatGen(5, 25);
int numberOfBatteries;
Random<boost::uniform_int<> > _batPos(1, LENGTH);
std::string testLogFileName;
std::ofstream ofs;

void fieldGenerator(int* field){
	numberOfBatteries = _numBatGen();
	for(int i = 0; i < LENGTH; i++){
		field[i] = NORMAL;
		/**
		if(i % 10 == 3){
			field[i] = ONCHARGER;
		}else{
			field[i] = NORMAL;
		}
		*/
	}
	field[0] = ONSTART;
	field[LENGTH - 1] = ONGOAL;
	for(int i = 0; i < numberOfBatteries; ){
		int index = _batPos();
		if(field[index] != ONCHARGER){
			field[index] = ONCHARGER;
			i++;
		}
	}
	/*
	for(int i = 0; i < LENGTH; i++){
		std::cout << field[i] << "\t";
	}
	std::cout << std::endl;
	*/
}

void main(){
	//Œ»ÝŽž
	time_t now;
	//Œ»ÝŽž‚ðŽæ“¾
	time(&now);
	///Log‚ðÝ’è
	testLogFileName = "testLog_";
	testLogFileName.append(ctime(&now));
	testLogFileName.erase(testLogFileName.size() - 12, 1);
	testLogFileName.erase(testLogFileName.size() - 9, 1);
	testLogFileName.erase(testLogFileName.size() - 1, 1);
	testLogFileName.append(".csv");
	std::cout << testLogFileName.c_str() << std::endl;
	ofs.open(testLogFileName.c_str());

	ofs << "battery,progress,step,logFileName";
	for(int i = 0; i < LENGTH; i++){
		ofs << ",field[" << i << "]";
	}
	ofs << std::endl;

	for(int time = 0; time < 100; time++){
		int field[LENGTH];
		fieldGenerator(field);
		
		SAServer server(field);
	
		std::cout << "Created Server" << std::endl;

		std::vector<SAModule *> modules;

		///Module‚Ì’è‹`
		//Actuators
		modules.push_back(new PositionUpdater());						//0
		//Sensors
		modules.push_back(new BatteryStatus(server.getEnv()));			//1
		modules.push_back(new VisionScope(server.getEnv()));			//2
		modules.push_back(new ProgressCounter(server.getEnv()));		//3
		modules.push_back(new StepCounter());							//4
		//Controllers
		modules.push_back(new Alive());									//5
		modules.push_back(new Progress());								//6

		///Module‚Ì“o˜^
		for(int i = 0; i < modules.size(); i++){
			server.addModule(modules[i]);
		}

		std::vector<SAConnector *> connectors;
		///Wire‚Ì’è‹`
		connectors.push_back( new SAConnector(&(modules[1]->getOutputsPtr()[0]), &(modules[0]->getInputsPtr()[1]), 0) );
		connectors.push_back( new SAConnector(&(modules[1]->getOutputsPtr()[0]), &(modules[5]->getInputsPtr()[RANGEVISION]), 0) );
		connectors.push_back( new SAConnector(&(modules[5]->getOutputsPtr()[0]), &(modules[0]->getInputsPtr()[0]), 0) );
		for(int i = 0; i < RANGEVISION; i++){
			connectors.push_back( new SAConnector(&(modules[2]->getOutputsPtr()[i]), &(modules[5]->getInputsPtr()[i]), 0) );
			connectors.push_back( new SAConnector(&(modules[2]->getOutputsPtr()[i]), &(modules[6]->getInputsPtr()[i]), 0) );
		}
		connectors.push_back( new SAConnector(&(modules[4]->getOutputsPtr()[0]), &(modules[6]->getInputsPtr()[RANGEVISION]), 0) );
		connectors.push_back( new SAConnector(&(modules[3]->getOutputsPtr()[0]), &(modules[6]->getInputsPtr()[RANGEVISION+1]), 0) );
		///Inhibitor‚Ì’è‹`

		///Suppressor‚Ì’è‹`
		connectors.push_back( new SAConnector(&(modules[6]->getOutputsPtr()[0]), &(modules[0]->getInputsPtr()[0]), 2) );

		///Server‚Ö“o˜^
		for(int i = 0; i < connectors.size(); i++){
			server.addConnector(connectors[i]);
		}

		int count = 0;
		while(true){
			/*
			std::string tmp;
			std::cin >> tmp;
			if(tmp.compare("q") == 0){
				break;
			}else{
				if(tmp.compare("4") == 0){
				}else if(tmp.compare("8") == 0){
				}else if(tmp.compare("6") == 0){
				}else if(tmp.compare("2") == 0){
				}else{
				}
			}
			*/
			if(count > 1000){
				break;
			}
			if(server.getEnv()->getBattery() == 0 || server.getEnv()->getPosition() == LENGTH - 1){
				break;
			}
			server.Process();
			count++;
		}

		int battery = ((BatteryStatus *)modules[1])->getStatus();
		int progress = ((ProgressCounter *)modules[3])->getPosition();
		int step = ((StepCounter *)modules[4])->getStep();
		std::string logFileName = server.getLogFileName();
	
		std::cout << "Battery: " << battery << std::endl;
		std::cout << "Progress: " << progress << std::endl;
		std::cout << "Step: " << step << std::endl;
		std::cout << "logFileName: " << step << std::endl;

		ofs << battery << "," << progress << "," << step << "," << logFileName;
		for(int i = 0; i < LENGTH; i++){
			ofs << "," << field[i];
		}
		ofs << std::endl;
		
		std::cout << "End" <<std::endl;
		//0.5•bSleep
		Sleep(1000);
	}

	ofs.close();

	std::cout << "Enter any character and Press 'Enter Key'" << std::endl;
	
	std::string input;
	std::cin >> input;
	return;
}