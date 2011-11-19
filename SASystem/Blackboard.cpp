#include "Logger.h"
#include "Blackboard.h"

void Blackboard::Update(){
}

void Blackboard::Log(){
	///�L�^
	logger->Log();
}

int Blackboard::addInputPort(std::string title){
	///�ϐ��̈��inputs��Ɋm�ہC�o�^
	inputs->push_back(NO_SIGNAL);
	///inputs����index���擾
	int index = inputs->size() - 1;
	///Blackboard�̓��̓|�[�g�����X�V
	numOfInputPorts = inputs->size();
	///Logger�ɋL�^����悤�ݒ�
	logger->add(title, inputs, index);
	return index;
}
int Blackboard::addOutputPort(std::string title){
	///�ϐ��̈��outputs��Ɋm�ہC�o�^
	outputs->push_back(NO_SIGNAL);
	///outputs����index���擾
	int index = outputs->size() - 1;
	///Blackboard�̏o�̓|�[�g�����X�V
	numOfOutputPorts = outputs->size();
	///Logger�ɋL�^����悤�ݒ�
	logger->add(title, outputs, index);
	return index;
}

