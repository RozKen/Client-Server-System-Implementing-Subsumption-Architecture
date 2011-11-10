#include "Blackboard.h"

void Blackboard::Update(){
}

void Blackboard::Log(){
}

void Blackboard::createInputPort(int numberOfPorts){
	//入力信号Bufferを初期化
	//メモリの初期化
	this->numOfInputPorts = numberOfPorts;
	this->inputs = new float[this->numOfInputPorts];
	//値の初期化
	for(int i = 0; i < this->numOfInputPorts; i++){
		this->inputs[i] = NO_SIGNAL;
	}
}

void Blackboard::createOutputPort(int numberOfPorts){
	//入力信号Bufferを初期化
	//メモリの初期化
	this->numOfOutputPorts = numberOfPorts;
	this->outputs = new float[this->numOfOutputPorts];
	//値の初期化
	for(int i = 0; i < this->numOfOutputPorts; i++){
		this->outputs[i] = NO_SIGNAL;
	}
}