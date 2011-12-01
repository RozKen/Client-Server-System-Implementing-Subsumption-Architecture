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

//#include "Robot.h"
//#include "Arbiter.h"

#include "World.h"
#include "RobotMAV.h"

//#define TEST_ROBOT

#ifdef TEST_ROBOT
#include "ModMultiple.hpp"
#include "Resetter.hpp"

void RobotTest();
#endif	//TEST_ROBOT

//#define TEST_LOGGER

#ifdef TEST_LOGGER
#include "Logger.h"
#include <math.h>

void LoggerTest();

#endif	//TEST_LOGGER

void fieldGenerator(int* field);
std::string logPathGenerator();

void main(){	

#ifdef TEST_ROBOT
	RobotTest();
#endif	//TEST_ROBOT

#ifdef TEST_LOGGER
	LoggerTest();
#endif	//TEST_LOGGER

	World* world = new World();
	std::string directory = logPathGenerator();

	world->setLogDirectoryPath(directory, "world.csv");
	std::cout << "world:Directory: " << world->getLogFilePath() << std::endl;
	RobotMAV* mav1 = new RobotMAV(directory, "mav1.csv");
	RobotMAV* mav2 = new RobotMAV(directory, "mav2.csv");
	world->addRobot(mav1);
	world->addRobot(mav2);
	//èâä˙ílÇê›íË
	mav1->setInput(0, 100.0f);
	mav1->setInput(1, START_X + 1.0f);
	mav1->setInput(2, START_Y + 1.0f);
	mav2->setInput(0, 100.0f);
	mav2->setInput(1, START_X - 1.0f);
	mav2->setInput(2, START_Y + 1.0f);
	for(int i = 0; i < 100; i++){
		world->Run();
	}
	/*int* field = new int[LENGTH];
	int numberOfFields = 1;
	for(int i = 0; i < numberOfFields; i++){
		//FieldÇÃçÏê¨
		fieldGenerator(field);
		
		//ì¡íËÇÃFieldÇÃçÏê¨
		
		//int field2[] = {1,0,0,0,0,0,3,0,0,0,0,0,0,0,0,
		//			0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,
		//			3,0,0,0,0,0,0,0,0,3,0,0,0,3,3,
		//			0,0,0,3,0,0,0,0,3,0,3,0,3,0,0,
		//			3,3,0,3,0,3,0,0,0,0,0,0,3,0,0,
		//			0,0,0,0,0,3,0,3,0,0,3,3,0,0,0,
		//			3,0,0,0,0,0,0,3,0,2};
		//field = field2;
		

		//FieldTesterÇÃçÏê¨
		FieldTester ft = FieldTester((const int *)field);
		//FieldTestÇÃé¿çs
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
	///åªç›éûçèÇéÊìæ
	time(&now);
	///LogDirectoryPathÇê›íË
	std::string testLogDirectoryPath = "../../../../analysis/";
	testLogDirectoryPath.append(ctime(&now));
	testLogDirectoryPath.erase(testLogDirectoryPath.size() - 12, 1);
	testLogDirectoryPath.erase(testLogDirectoryPath.size() - 9, 1);
	testLogDirectoryPath.erase(testLogDirectoryPath.size() - 1, 1);
	std::string logPath = testLogDirectoryPath;
	return logPath;
}

#ifdef TEST_ROBOT
void RobotTest(){
	std::string logPath;
	std::string option = "test.csv";
	logPath = logPathGenerator();

	Robot* robo;
	robo = new Robot();
	std::cout << logPath << "," << option << std::endl;
	robo->setLogDirectoryPath(logPath, option);

	std::vector<SAModule* > mod;
	std::vector<Arbiter* > arb;
	Resetter* reset = new Resetter(2.0f);
	ModMultiple* a = new ModMultiple();
	ModMultiple* b = new ModMultiple();
	ModMultiple* c = new ModMultiple();
	ModMultiple* d = new ModMultiple();
	ModMultiple* e = new ModMultiple();
	ModMultiple* f = new ModMultiple();
	ModMultiple* g = new ModMultiple();

	mod.push_back(reset);
	mod.push_back(a);
	mod.push_back(b);
	mod.push_back(c);
	mod.push_back(d);
	mod.push_back(e);
	mod.push_back(f);
	mod.push_back(g);

	for(int i = 0; i < mod.size(); i++){
		robo->addModule(mod.at(i));

	}
	for(int i = 0; i < mod.size(); i++){
		for(int j = 0; j < mod.at(i)->getNumOfInputPorts(); j++){
			robo->addArbiter(new Arbiter(reset, 0, mod.at(i), j, -2.0));
		}
	}
	//Wire
	Arbiter* ae = new Arbiter(a, 0, e, 0, -2.0);
	//Inhibitor
	Arbiter* be = new Arbiter(b, 0, e, 1, -1.0);
	//Suppressor
	Arbiter* cf = new Arbiter(c, 0, f, 0, 1.0);
	//factor = -0.5
	Arbiter* df = new Arbiter(d, 0, f, 1, -0.5);
	//factor = 0.6
	Arbiter* eg = new Arbiter(e, 0, g, 0, 0.6);
	//factor = 0.8
	Arbiter* fg = new Arbiter(f, 0, g, 1, 0.85);

	arb.push_back(ae);
	arb.push_back(be);
	arb.push_back(cf);
	arb.push_back(df);
	arb.push_back(eg);
	arb.push_back(fg);

	for(int i = 0; i < arb.size(); i++){
		robo->addArbiter(arb.at(i));
	}

	for(int i = 0; i < 100; i++){
		robo->Run();
	}
}
#endif

#ifdef TEST_LOGGER
void LoggerTest(){
	std::cout << "Logger Test Started" << std::endl;
	//åªç›éûçè
	time_t now;
	///åªç›éûçèÇéÊìæ
	time(&now);
	///LogDirectoryPathÇê›íË
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
