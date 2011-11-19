#include <string>

#include "Constants.h"
#include "Random.hpp"
//#include "FieldTester.hpp"
#include <time.h>
#include <iostream>

//for wait
#include <Windows.h>
//for _mkdir
#include <direct.h>

#include "Robot.h"

//#define TEST_LOGGER

#ifdef TEST_LOGGER
#include "Logger.h"
#include <math.h>

void LoggerTest();

#endif	//TEST_LOGGER

void fieldGenerator(int* field);
std::string logPathGenerator();

void main(){
	std::string logPath;
	std::string option = "test";
	logPath = logPathGenerator();

	Robot* robo;
	robo = new Robot();
	std::cout << logPath << "," << option << std::endl;
	robo->setLogDirectoryPath(logPath, option);

#ifdef TEST_LOGGER
	LoggerTest();
#endif	//TEST_LOGGER

	/*int* field = new int[LENGTH];
	int numberOfFields = 1;
	for(int i = 0; i < numberOfFields; i++){
		//Fieldの作成
		fieldGenerator(field);
		
		//特定のFieldの作成
		
		//int field2[] = {1,0,0,0,0,0,3,0,0,0,0,0,0,0,0,
		//			0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,
		//			3,0,0,0,0,0,0,0,0,3,0,0,0,3,3,
		//			0,0,0,3,0,0,0,0,3,0,3,0,3,0,0,
		//			3,3,0,3,0,3,0,0,0,0,0,0,3,0,0,
		//			0,0,0,0,0,3,0,3,0,0,3,3,0,0,0,
		//			3,0,0,0,0,0,0,3,0,2};
		//field = field2;
		

		//FieldTesterの作成
		FieldTester ft = FieldTester((const int *)field);
		//FieldTestの実行
		ft.Test();
	}
	delete(field);
	*/
	std::cout << "Enter any character and Press 'Enter Key'" << std::endl;
	
	std::string input;
	std::cin >> input;
	return;
}

std::string logPathGenerator(){
	time_t now;
	///現在時刻を取得
	time(&now);
	///LogDirectoryPathを設定
	std::string testLogDirectoryPath = "../../../../analysis/";
	testLogDirectoryPath.append(ctime(&now));
	testLogDirectoryPath.erase(testLogDirectoryPath.size() - 12, 1);
	testLogDirectoryPath.erase(testLogDirectoryPath.size() - 9, 1);
	testLogDirectoryPath.erase(testLogDirectoryPath.size() - 1, 1);
	std::string logPath = testLogDirectoryPath;
	return logPath;
}

#ifdef TEST_LOGGER
void LoggerTest(){
	std::cout << "Logger Test Started" << std::endl;
	//現在時刻
	time_t now;
	///現在時刻を取得
	time(&now);
	///LogDirectoryPathを設定
	std::string testLogDirectoryPath = "../../../../analysis/";
	testLogDirectoryPath.append(ctime(&now));
	testLogDirectoryPath.erase(testLogDirectoryPath.size() - 12, 1);
	testLogDirectoryPath.erase(testLogDirectoryPath.size() - 9, 1);
	testLogDirectoryPath.erase(testLogDirectoryPath.size() - 1, 1);
	std::string testLogFileName = "_logTest.csv";
	std::cout << "Log File Path: " << testLogDirectoryPath << testLogFileName << std::endl;

	Logger logger(testLogDirectoryPath, testLogFileName);
	int step = 0;
	float factor = 0.0f;
	float magnitude = 1.0f;
	float signal = 0.0f;
	logger.add("step", &step);
	logger.add("factor", &factor);
	logger.add("magnitude", &magnitude);
	logger.add("signal", &signal);
	std::vector<float>* data = new std::vector<float>();
	
	for(int i = 0; i < 10; i++){
		data->push_back(0.0f);
		std::string title = "data";
		logger.add(title, data, i);
	}

	std::cout << "Logger has set up." << std::endl;

	int MAX_STEP = 100;
	double delta = 1.0 / (double)MAX_STEP;
	for(int i = 0; i < MAX_STEP; i++){
		step = i;
		factor = delta * (double)i;
		signal = (float)0.5 * ( cos(0.5 * PI * (cos((double)factor * PI) + 1.0)) + 1.0 );
		for(int j = 0; j < 10; j++){
			data->at(j) = (float)pow(signal, j);
		}
		logger.Log();
	}

	std::cout << "Logger test has done!" << std::endl;
}
#endif	//TEST_LOGGER

Random<boost::uniform_int<> > _numBatGen(15, 25);
int numberOfBatteries;
Random<boost::uniform_int<> > _batPos(1, LENGTH);
//std::string testLogFileName;
//std::ofstream ofs;
//int count = 0;
//int numOfSuccess = 0;
//double aveSuccessClock = 0;
//double aveDistance = 0;

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
		if(field[index] != ONCHARGER && field[index] != ONSTART
			&& field[index] != ONGOAL){
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
