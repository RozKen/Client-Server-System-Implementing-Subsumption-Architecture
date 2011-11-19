#include "FieldConnectorTester.h"

#include "EnvUpdater.h"
#include "SAServer.h"
#include "Modules.h"
#include "SAConnector.h"
#include "DataInDirectoryInvestigator.h"

#include <time.h>
#include <iostream>
#include <Windows.h>	//for wait
#include <direct.h>		//for _mkdir
#include <sstream>

FieldConnectorTester::FieldConnectorTester(const int* field, int mode, double prob) 
	: mode(mode), prob(prob), count(0), numOfSuccess(0), numOfBatteryFail(0), aveSuccessClock(0.0), aveDistance(0.0)
{
	this->field = field;
	numOfBattery = countNumOfBatteries();
	maxBatD = maxBatteryDistance();
	minBatD = minBatteryDistance();
	aveBatD = averageBatteryDistance();

	//現在時刻
	time_t now;
	///現在時刻を取得
	time(&now);
	///LogDirectoryPathを設定
	testLogDirectoryPath = "../../../../analysis/";
	testLogDirectoryPath.append(ctime(&now));
	testLogDirectoryPath.erase(testLogDirectoryPath.size() - 12, 1);
	testLogDirectoryPath.erase(testLogDirectoryPath.size() - 9, 1);
	testLogDirectoryPath.erase(testLogDirectoryPath.size() - 1, 1);
	std::ostringstream oss;
	oss << this->prob;
	switch(mode){
	case 1:
		testLogDirectoryPath.append("_Inhibit");
		break;
	case 2:
		testLogDirectoryPath.append("_Suppress");
		break;
	case 3:
		testLogDirectoryPath.append("_probSelect_").append(oss.str());
		break;
	case 4:
		testLogDirectoryPath.append("_probSuperpose_");
		break;
	default:
		testLogDirectoryPath.append("_Wire");
	}
	_mkdir(testLogDirectoryPath.c_str());	//ディレクトリを作成(Windows)
}
/*
FieldConnectorTester::FieldConnectorTester(const int* field, int mode) : mode(mode), prob(0.6), count(0), numOfSuccess(0), aveSuccessClock(0.0),
	aveDistance(0.0)
{
	FieldConnectorTester(field, mode, 0.6);
	this->field = field;
	numOfBattery = countNumOfBatteries();
	maxBatD = maxBatteryDistance();
	minBatD = minBatteryDistance();
	aveBatD = averageBatteryDistance();
}*/

int FieldConnectorTester::maxBatteryDistance(){
	///現在の最大距離
	int maxD = 0;
	///一つ前のバッテリーの位置
	int prevBattery = 0;
	///現在探索中の位置
	int current = 0;
	//探索と最大距離の更新
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

int FieldConnectorTester::minBatteryDistance(){
	///現在の最小距離
	int minD = 100;
	///一つ前のバッテリーの位置
	int prevBattery = 0;
	///現在探索中の位置
	int current = 0;
	//探索と最大距離の更新
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

double FieldConnectorTester::averageBatteryDistance(){
	double average = (double)countNumOfBatteries() / (double)LENGTH;
	return average;
}

int FieldConnectorTester::countNumOfBatteries(){
	int batteryCount = 0;
	for(int i = 0; i < LENGTH; i++){
		if(field[i] == ONCHARGER){
			batteryCount++;
		}
	}
	return batteryCount;
}

void FieldConnectorTester::Test(){
	Test(100, 70 * 3);
}

void FieldConnectorTester::Test(int maxTime, int maxCount){
	
	
	testLogFileName = testLogDirectoryPath;
	testLogFileName.append("_testLog_");
	testLogFileName.append(".csv");
	std::cout << "testLogFileLocation : " << testLogFileName.c_str() << std::endl;

	std::ofstream ofs;
	ofs.open(testLogFileName.c_str());

	ofs << "battery,progress,step,numOfBat,maxBatD,minBatD,aveBatD,stepFor,stepStop,stepBack,dirChange,logFileName";
	for(int i = 0; i < LENGTH; i++){
		ofs << ",field[" << i << "]";
	}
	ofs << std::endl;

	for(int time = 0; time < maxTime; time++){
		/*SAServer server(this->field, testLogDirectoryPath, time);
	
		//std::cout << "Created Server" << std::endl;

		std::vector<SAModule *> modules;

		///Moduleの定義
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

		///Moduleの登録
		for(int i = 0; i < modules.size(); i++){
			server.addModule(modules[i]);
		}

		std::vector<SAConnector *> connectors;
		///Wireの定義
		connectors.push_back( new SAConnector(&(modules[1]->getOutputsPtr()[0]), &(modules[0]->getInputsPtr()[1]), 0) );
		connectors.push_back( new SAConnector(&(modules[1]->getOutputsPtr()[0]), &(modules[5]->getInputsPtr()[RANGEVISION]), 0) );
		connectors.push_back( new SAConnector(&(modules[5]->getOutputsPtr()[0]), &(modules[0]->getInputsPtr()[0]), 0) );
		for(int i = 0; i < RANGEVISION; i++){
			connectors.push_back( new SAConnector(&(modules[2]->getOutputsPtr()[i]), &(modules[5]->getInputsPtr()[i]), 0) );
			connectors.push_back( new SAConnector(&(modules[2]->getOutputsPtr()[i]), &(modules[6]->getInputsPtr()[i]), 0) );
		}
		connectors.push_back( new SAConnector(&(modules[4]->getOutputsPtr()[0]), &(modules[6]->getInputsPtr()[RANGEVISION]), 0) );
		connectors.push_back( new SAConnector(&(modules[3]->getOutputsPtr()[0]), &(modules[6]->getInputsPtr()[RANGEVISION+1]), 0) );
		///Inhibitorの定義

		///Suppressorの定義
		switch(mode){
		case 1:
			//Inhibitor
			connectors.push_back( new SAConnector(&(modules[6]->getOutputsPtr()[0]), &(modules[0]->getInputsPtr()[0]), 1) );
			break;
		case 2:
			//Suppressor
			connectors.push_back( new SAConnector(&(modules[6]->getOutputsPtr()[0]), &(modules[0]->getInputsPtr()[0]), 2) );
			break;
		case 3:
			//Probability-based Selector
			connectors.push_back( new SAConnector(&(modules[6]->getOutputsPtr()[0]), &(modules[0]->getInputsPtr()[0]), 3, (float)prob) );
			break;
		case 4:
			//Probability-based Superposer
			connectors.push_back( new SAConnector(&(modules[6]->getOutputsPtr()[0]), &(modules[0]->getInputsPtr()[0]), 4) );
			break;
		default:
			//Wire
			connectors.push_back( new SAConnector(&(modules[6]->getOutputsPtr()[0]), &(modules[0]->getInputsPtr()[0]), 0) );
		}
		///Serverへ登録
		for(int i = 0; i < connectors.size(); i++){
			server.addConnector(connectors[i]);
		}

		count = 0;
		while(true){
			if(count >= maxCount){
				break;
			}
			if(((BatteryStatus *)modules[1])->getStatus() < BATTLOSS || server.getEnv()->getPosition() == LENGTH - 1){
				break;
			}
			server.Process();
			count++;
		}

		int battery = ((BatteryStatus *)modules[1])->getStatus();
		int progress = ((ProgressCounter *)modules[3])->getPosition();
		int step = ((StepCounter *)modules[4])->getStep();
		///前進している回数
		int stepForward = server.getStepForward();
		///停止している回数
		int stepStop = server.getStepStop();
		///後進している回数
		int stepBackward = server.getStepBackward();
		///前後進が切り替わった回数
		int stepSwitchDirection = server.getStepSwitchDirection();

		std::string logFileName = server.getLogFileName();
	
		//std::cout << "Battery: " << battery << std::endl;
		//std::cout << "Progress: " << progress << std::endl;
		//std::cout << "Step: " << step << std::endl;
		//std::cout << "numOfBatteries: " << numberOfBatteries << std::endl;
		//std::cout << "logFileName: " << logFileName << std::endl;
		

		if(progress == LENGTH - 1){
			numOfSuccess ++;
			aveSuccessClock += (double)step;
		}
		if(battery < BATTLOSS){
			numOfBatteryFail++;
		}
		aveDistance += (double)progress;

		ofs << battery << "," << progress << "," << step << "," << numOfBattery << ",";
		ofs << maxBatD << "," << minBatD << "," << aveBatD << "," ;
		ofs << stepForward << "," << stepStop << "," << stepBackward << "," << stepSwitchDirection << ",";
		ofs << logFileName;
		for(int i = 0; i < LENGTH; i++){
			ofs << "," << field[i];
		}
		ofs << std::endl;

		//std::cout << "End" <<std::endl;
		//0.5秒Sleep
		//Sleep(1000);
		*/
	}

	if(numOfSuccess == 0){
		aveSuccessClock = 0.0;
	}else{
		aveSuccessClock /= (double)numOfSuccess;
	}
	aveDistance /= (double)maxTime;

	ofs << std::endl;
	ofs << "numOfSuccess," << numOfSuccess << std::endl;
	ofs << "aveSuccessClock," << aveSuccessClock << std::endl;
	ofs << "aveDistance," << aveDistance << std::endl;
	ofs << "numOfBatteryFile," << numOfBatteryFail << std::endl;

	//For Analysis CSV Data Output
	std::string investigationFileName = testLogDirectoryPath;
	investigationFileName.append("\\");
	DataInDirectoryInvestigator dind = DataInDirectoryInvestigator(investigationFileName);
	dind.Run();

	ofs.close();
}