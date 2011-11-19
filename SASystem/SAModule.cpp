#include "SAModule.h"

SAModule::SAModule():numOfInputPorts(0), numOfOutputPorts(0){
	this->inputIndex = new std::vector<int>();
	this->outputIndex = new std::vector<int>();
	this->inputTitles = new std::vector<std::string>();
	this->outputTitles = new std::vector<std::string>();
	this->memory = new Blackboard();
}

SAModule::~SAModule(){
	delete(inputIndex);
	delete(outputIndex);
	delete(inputTitles);
	delete(outputTitles);
	delete(memory);
}

void SAModule::addInput(std::string title){
	this->inputTitles->push_back(title);
	this->numOfInputPorts = this->inputTitles->size();
}

void SAModule::addOutput(std::string title){
	this->outputTitles->push_back(title);
	this->numOfOutputPorts = this->outputTitles->size();
}

void SAModule::addInputIndex(int index){
	this->inputIndex->push_back(index);
}

void SAModule::addOutputIndex(int index){
	this->outputIndex->push_back(index);
}

void SAModule::setParent(SAModule* parent){
	this->parent = parent;
	this->memory = parent->getMemory();
}

std::vector<std::string>* SAModule::getInputTitles() const{
	return inputTitles;
}

std::vector<std::string>* SAModule::getOutputTitles() const{
	return outputTitles;
}

float SAModule::getInput(int index) const{
	//moduleへの入力はmemoryの出力から入手
	int result = memory->getOutput(this->inputIndex->at(index));
	return result;
}

void SAModule::setOutput(int index, float signal){
	//moduleからの出力は、memoryの入力へ送信
	memory->setInput(this->outputIndex->at(index), signal);
}


int SAModule::getNumOfInputPorts() const{
	return this->numOfInputPorts;
}

int SAModule::getNumOfOutputPorts() const{
	return this->numOfOutputPorts;
}

Blackboard* SAModule::getMemory() const{
	return this->memory;
}