#include "SAModule.h"

SAModule::SAModule():numOfInputPorts(0), numOfOutputPorts(0){
}

SAModule::SAModule(int numberOfInputPorts, int numberOfOutputPorts)
	:numOfInputPorts(numberOfInputPorts), numOfOutputPorts(numberOfOutputPorts){
	//信号Bufferを初期化
	//メモリの初期化
	inputs = new float[numberOfInputPorts];
	outputs = new float[numberOfOutputPorts];
	//値の初期化
	for(int i = 0; i < numberOfInputPorts; i++){
		inputs[i] = NO_SIGNAL;
	}
	for(int i = 0; i < numberOfOutputPorts; i++){
		outputs[i] = NO_SIGNAL;
	}
}

void SAModule::createInputPort(int numberOfPorts){
	//入力信号Bufferを初期化
	//メモリの初期化
	inputs = new float[numberOfPorts];
	numOfInputPorts = numberOfPorts;
	//値の初期化
	for(int i = 0; i < numOfInputPorts; i++){
		inputs[i] = NO_SIGNAL;
	}
}

void SAModule::createOutputPort(int numberOfPorts){
	//入力信号Bufferを初期化
	//メモリの初期化
	outputs = new float[numberOfPorts];
	numOfOutputPorts = numberOfPorts;
	//値の初期化
	for(int i = 0; i < numOfOutputPorts; i++){
		outputs[i] = NO_SIGNAL;
	}
}

float* SAModule::getInputsPtr(){
	return inputs;
}

float* SAModule::getOutputsPtr(){
	return outputs;
}

void SAModule::setInput(float inputSignal, int index){
	inputs[index] = inputSignal;
}

float SAModule::getInput(int index){
	return inputs[index];
}

void SAModule::setOutput(float outputSignal, int index){
	outputs[index] = outputSignal;
}

float SAModule::getOutput(int index){
	return outputs[index];
}

int SAModule::getNumOfInputPorts(){
	return numOfInputPorts;
}

int SAModule::getNumOfOutputPorts(){
	return numOfOutputPorts;
}