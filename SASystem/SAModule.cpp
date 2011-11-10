#include "SAModule.h"

SAModule::SAModule():numOfInputPorts(0), numOfOutputPorts(0){
}

SAModule::SAModule(int numberOfInputPorts, int numberOfOutputPorts)
	:numOfInputPorts(numberOfInputPorts), numOfOutputPorts(numberOfOutputPorts){
	//�M��Buffer��������
	//�������̏�����
	inputs = new float[numberOfInputPorts];
	outputs = new float[numberOfOutputPorts];
	//�l�̏�����
	for(int i = 0; i < numberOfInputPorts; i++){
		inputs[i] = NO_SIGNAL;
	}
	for(int i = 0; i < numberOfOutputPorts; i++){
		outputs[i] = NO_SIGNAL;
	}
}

void SAModule::createInputPort(int numberOfPorts){
	//���͐M��Buffer��������
	//�������̏�����
	inputs = new float[numberOfPorts];
	numOfInputPorts = numberOfPorts;
	//�l�̏�����
	for(int i = 0; i < numOfInputPorts; i++){
		inputs[i] = NO_SIGNAL;
	}
}

void SAModule::createOutputPort(int numberOfPorts){
	//���͐M��Buffer��������
	//�������̏�����
	outputs = new float[numberOfPorts];
	numOfOutputPorts = numberOfPorts;
	//�l�̏�����
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