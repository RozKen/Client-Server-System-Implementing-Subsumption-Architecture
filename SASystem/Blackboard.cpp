#include "Logger.h"
#include "Blackboard.h"
#include <iostream>

void Blackboard::Update(){
}

void Blackboard::Log(){
	///記録
	logger->Log();
}

int Blackboard::addInputPort(std::string title){
	///変数領域をinputs上に確保，登録
	inputs->push_back(NO_SIGNAL);
	///inputs内のindexを取得
	int index = inputs->size() - 1;
	///Blackboardの入力ポート数を更新
	numOfInputPorts = inputs->size();
	///Loggerに記録するよう設定
	logger->add(title, inputs, index);
	if(index < 0){
		std::cout << "Index has wrong value : " << index << ", Blackboard::input: " << title << std::endl;
	}
	return index;
}
int Blackboard::addOutputPort(std::string title){
	///変数領域をoutputs上に確保，登録
	outputs->push_back(NO_SIGNAL);
	///outputs内のindexを取得
	int index = outputs->size() - 1;
	///Blackboardの出力ポート数を更新
	numOfOutputPorts = outputs->size();
	///Loggerに記録するよう設定
	logger->add(title, outputs, index);
	if(index < 0){
		std::cout << "Index has wrong value : " << index << ", Blackboard::output: " << title << std::endl;
	}
	return index;
}

int Blackboard::addIntPort(std::string title){
	iBoard->push_back(NO_SIGNAL);
	int index = iBoard->size() - 1;
	logger->add(title, iBoard, index);
	return index;
}

int Blackboard::addFloatPort(std::string title){
	fBoard->push_back(NO_SIGNAL);
	int index = fBoard->size() - 1;
	logger->add(title, fBoard, index);
	return index;
}
