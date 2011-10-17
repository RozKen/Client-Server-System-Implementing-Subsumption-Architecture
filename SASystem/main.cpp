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
int count = 0;
int numOfSuccess = 0;
double aveSuccessClock = 0;
double aveDistance = 0;

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
/**
	@brief Battery�Ԃ̍ő�̋������v��
	@param field �t�B�[���h
	@return Battery�Ԃ̍ő�̋���
 */
int maxBatteryDistance(const int* field){
	///���݂̍ő勗��
	int maxD = 0;
	///��O�̃o�b�e���[�̈ʒu
	int prevBattery = 0;
	///���ݒT�����̈ʒu
	int current = 0;
	//�T���ƍő勗���̍X�V
	for(current = 0; current < LENGTH; current++){
		if(field[current] == ONCHARGER){
			if((current - prevBattery) > maxD){
				maxD = current - prevBattery;
			}
			prevBattery = current;
		}
	}
	return maxD;
}
/**
	@brief Battery�Ԃ̍ŏ��̋������v��
	@param field �t�B�[���h
	@return Battery�Ԃ̍ŏ��̋���
 */
int minBatteryDistance(const int* field){
	///���݂̍ŏ�����
	int minD = 100;
	///��O�̃o�b�e���[�̈ʒu
	int prevBattery = 0;
	///���ݒT�����̈ʒu
	int current = 0;
	//�T���ƍő勗���̍X�V
	for(current = 0; current < LENGTH; current++){
		if(field[current] == ONCHARGER){
			if((current - prevBattery) < minD){
				minD = current - prevBattery;
			}
			prevBattery = current;
		}
	}
	return minD;
}

/**
	@brief Battery�Ԃ̕��ς̋������v��
	@param field �t�B�[���h
	@return Battery�Ԃ̕��ϋ���
 */
double averageBatteryDistance(const int* field){
	int batteryCount = 0;
	for(int i = 0; i < LENGTH; i++){
		if(field[i] == ONCHARGER){
			batteryCount++;
		}
	}
	double average = (double)batteryCount / (double)LENGTH;
	return average;
}

void main(){
	//���ݎ���
	time_t now;
	//���ݎ������擾
	time(&now);
	///Log��ݒ�
	testLogFileName = "testLog_";
	testLogFileName.append(ctime(&now));
	testLogFileName.erase(testLogFileName.size() - 12, 1);
	testLogFileName.erase(testLogFileName.size() - 9, 1);
	testLogFileName.erase(testLogFileName.size() - 1, 1);
	testLogFileName.append(".csv");
	std::cout << testLogFileName.c_str() << std::endl;
	ofs.open(testLogFileName.c_str());

	ofs << "battery,progress,step,numOfBat,maxBatD,minBatD,aveBatD,stepFor,stepStop,stepBack,dirChange,logFileName";
	for(int i = 0; i < LENGTH; i++){
		ofs << ",field[" << i << "]";
	}
	ofs << std::endl;

	for(int time = 0; time < 100; time++){
		int field[LENGTH];
		///�t�B�[���h�������_���ɐ���
		fieldGenerator(field);
		int maxBatD = maxBatteryDistance(field);
		int minBatD = minBatteryDistance(field);
		double aveBatD = averageBatteryDistance(field);

		SAServer server(field);
	
		std::cout << "Created Server" << std::endl;

		std::vector<SAModule *> modules;

		///Module�̒�`
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

		///Module�̓o�^
		for(int i = 0; i < modules.size(); i++){
			server.addModule(modules[i]);
		}

		std::vector<SAConnector *> connectors;
		///Wire�̒�`
		connectors.push_back( new SAConnector(&(modules[1]->getOutputsPtr()[0]), &(modules[0]->getInputsPtr()[1]), 0) );
		connectors.push_back( new SAConnector(&(modules[1]->getOutputsPtr()[0]), &(modules[5]->getInputsPtr()[RANGEVISION]), 0) );
		connectors.push_back( new SAConnector(&(modules[5]->getOutputsPtr()[0]), &(modules[0]->getInputsPtr()[0]), 0) );
		for(int i = 0; i < RANGEVISION; i++){
			connectors.push_back( new SAConnector(&(modules[2]->getOutputsPtr()[i]), &(modules[5]->getInputsPtr()[i]), 0) );
			connectors.push_back( new SAConnector(&(modules[2]->getOutputsPtr()[i]), &(modules[6]->getInputsPtr()[i]), 0) );
		}
		connectors.push_back( new SAConnector(&(modules[4]->getOutputsPtr()[0]), &(modules[6]->getInputsPtr()[RANGEVISION]), 0) );
		connectors.push_back( new SAConnector(&(modules[3]->getOutputsPtr()[0]), &(modules[6]->getInputsPtr()[RANGEVISION+1]), 0) );
		///Inhibitor�̒�`

		///Suppressor�̒�`
		//Suppressor
		//connectors.push_back( new SAConnector(&(modules[6]->getOutputsPtr()[0]), &(modules[0]->getInputsPtr()[0]), 2) );
		//Probability-based Selector
		connectors.push_back( new SAConnector(&(modules[6]->getOutputsPtr()[0]), &(modules[0]->getInputsPtr()[0]), 3, 0.6f) );
		//Probability-based Superposer
		//connectors.push_back( new SAConnector(&(modules[6]->getOutputsPtr()[0]), &(modules[0]->getInputsPtr()[0]), 4) );

		///Server�֓o�^
		for(int i = 0; i < connectors.size(); i++){
			server.addConnector(connectors[i]);
		}

		count = 0;
		while(true){
			if(count >= 70 * 3){
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
		///�O�i���Ă����
		int stepForward = server.getStepForward();
		///��~���Ă����
		int stepStop = server.getStepStop();
		///��i���Ă����
		int stepBackward = server.getStepBackward();
		///�O��i���؂�ւ������
		int stepSwitchDirection = server.getStepSwitchDirection();

		std::string logFileName = server.getLogFileName();
	
		/*std::cout << "Battery: " << battery << std::endl;
		std::cout << "Progress: " << progress << std::endl;
		std::cout << "Step: " << step << std::endl;
		std::cout << "numOfBatteries: " << numberOfBatteries << std::endl;
		std::cout << "logFileName: " << logFileName << std::endl;
		*/

		if(progress == LENGTH - 1){
			numOfSuccess ++;
			aveSuccessClock += (double)step;
		}
		aveDistance += (double)progress;

		ofs << battery << "," << progress << "," << step << "," << numberOfBatteries << ",";
		ofs << maxBatD << "," << minBatD << "," << aveBatD << "," ;
		ofs << stepForward << "," << stepStop << "," << stepBackward << "," << stepSwitchDirection << ",";
		ofs << logFileName;
		for(int i = 0; i < LENGTH; i++){
			ofs << "," << field[i];
		}
		ofs << std::endl;
		
		std::cout << "End" <<std::endl;
		//0.5�bSleep
		Sleep(1000);
	}

	aveSuccessClock /= (double)numOfSuccess;
	aveDistance /= (double)count;

	ofs << std::endl;
	ofs << "numOfSuccess," << numOfSuccess << std::endl;
	ofs << "aveSuccessClock," << aveSuccessClock << std::endl;
	ofs << "aveDistance," << aveDistance << std::endl;

	ofs.close();

	std::cout << "Enter any character and Press 'Enter Key'" << std::endl;
	
	std::string input;
	std::cin >> input;
	return;
}