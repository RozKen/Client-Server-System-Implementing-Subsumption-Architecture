#include "Blackboard.h"

void Blackboard::Update(){
}

void Blackboard::Log(){
}

void Blackboard::createInputPort(int numberOfPorts){
	//���͐M��Buffer��������
	//�������̏�����
	this->numOfInputPorts = numberOfPorts;
	this->inputs = new float[this->numOfInputPorts];
	//�l�̏�����
	for(int i = 0; i < this->numOfInputPorts; i++){
		this->inputs[i] = NO_SIGNAL;
	}
}

void Blackboard::createOutputPort(int numberOfPorts){
	//���͐M��Buffer��������
	//�������̏�����
	this->numOfOutputPorts = numberOfPorts;
	this->outputs = new float[this->numOfOutputPorts];
	//�l�̏�����
	for(int i = 0; i < this->numOfOutputPorts; i++){
		this->outputs[i] = NO_SIGNAL;
	}
}