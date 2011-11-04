#include <string>

#include "Constants.h"
#include "Random.hpp"
#include "FieldTester.hpp"
#include <time.h>
#include <iostream>

//for wait
#include <Windows.h>
//for _mkdir
#include <direct.h>

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

void main(){
	int* field = new int[LENGTH];
	int numberOfFields = 1;
	for(int i = 0; i < numberOfFields; i++){
		//Fieldの作成
		fieldGenerator(field);
		
		//特定のFieldの作成
		/*
		int field2[] = {1,0,0,0,0,0,3,0,0,0,0,0,0,0,0,
					0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,
					3,0,0,0,0,0,0,0,0,3,0,0,0,3,3,
					0,0,0,3,0,0,0,0,3,0,3,0,3,0,0,
					3,3,0,3,0,3,0,0,0,0,0,0,3,0,0,
					0,0,0,0,0,3,0,3,0,0,3,3,0,0,0,
					3,0,0,0,0,0,0,3,0,2};
		field = field2;
		*/

		//FieldTesterの作成
		FieldTester ft = FieldTester((const int *)field);
		//FieldTestの実行
		ft.Test();
	}
	delete(field);

	std::cout << "Enter any character and Press 'Enter Key'" << std::endl;
	
	std::string input;
	std::cin >> input;
	return;
}