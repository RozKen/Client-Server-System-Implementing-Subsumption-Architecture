#include "Logger.h"
#include "Blackboard.h"

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
	return index;
}

