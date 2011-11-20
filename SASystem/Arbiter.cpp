#include "Arbiter.h"
#include <math.h>

Arbiter::Arbiter()
	:_rand(0, 1), timeToModify(0), timeLeftModified(0)
	, factor(-100.0f){
}

Arbiter::Arbiter(SAModule* src, int srcPort, SAModule* dest, int destPort)
	:_rand(0, 1), source(src), srcPort(srcPort), destination(dest), destPort(destPort),
	timeToModify(0), timeLeftModified(0), factor(-100.0f){
		addInput(src->getOutputTitles()->at(srcPort));
		addInputIndex(src->getOutputIndex(srcPort));
		addOutput(dest->getInputTitles()->at(destPort));
		addOutputIndex(dest->getInputIndex(destPort));
}

Arbiter::Arbiter(SAModule* src, int srcPort, SAModule* dest, int destPort, float factor)
	:_rand(0, 1),  source(src), srcPort(srcPort), destination(dest), destPort(destPort),
	timeToModify(0), timeLeftModified(0), factor(factor){
		addInput(src->getOutputTitles()->at(srcPort));
		addInputIndex(src->getOutputIndex(srcPort));
		addOutput(dest->getInputTitles()->at(destPort));
		addOutputIndex(dest->getInputIndex(destPort));
}

Arbiter::Arbiter(SAModule* src, int srcPort, SAModule* dest, int destPort, 
		float factor_min, float factor_max)
	: source(src), srcPort(srcPort), destination(dest), destPort(destPort), 
	_rand(factor_min, factor_max), timeToModify(0), timeLeftModified(0), factor(-100.0f){
		addInput(src->getOutputTitles()->at(srcPort));
		addInputIndex(src->getOutputIndex(srcPort));
		addOutput(dest->getInputTitles()->at(destPort));
		addOutputIndex(dest->getInputIndex(destPort));
}

void Arbiter::Run(){
	this->setOutput((float)generateSignal());
}

void Arbiter::setSource(SAModule* src, int srcPort){
	this->source = src;
	this->srcPort = srcPort;
	addInput(src->getOutputTitles()->at(srcPort));
	addInputIndex(src->getOutputIndex(srcPort));
}

void Arbiter::setDestination(SAModule* dest, int destPort){
	this->destination = dest;
	this->destPort = destPort;
	addOutput(dest->getInputTitles()->at(destPort));
	addOutputIndex(dest->getInputIndex(destPort));
}

float Arbiter::getInput() const{
		///Arbiter�ւ̓��͂�memory�̓��͂�����聦Module�ƈقȂ�
	int result = memory->getInput(this->inputIndex->at(0));
	return result;
}
float Arbiter::getInput(int index) const{
	return getInput();
}

void Arbiter::setOutput(float signal){
	///Arbiter����̏o�͂́Cmemory�̏o�֑͂��M��Module�ƈقȂ�
	memory->setOutput(this->outputIndex->at(0), signal);
}
void Arbiter::setOutput(int index, float signal){
	setOutput(signal);
}

float Arbiter::getDest() const{
	return memory->getOutput(this->outputIndex->at(0));
}

float Arbiter::getSrc() const{
	return memory->getInput(this->inputIndex->at(0));
}

double Arbiter::generateSignal(){
	///��Step�ɂ�����CArbiter�̋��������߂���q
	double currentFactor;
	///factor���w�肳��Ă��Ȃ���΁C�����Ő���
	if(factor == -100.0f){
		currentFactor = _rand();
	}else{
		///factor���w�肳��Ă���΁C���̒l�𗘗p
		currentFactor = (double)factor;
	}

	double destRatio;	///�ڑ���(���w)�̐M���̉e����
	double sourceRatio;	///�ڑ���(��w)�̐M���̉e����

	double magnitude;	///�M���S�̂̋����̌W��

	if(factor >= 0){
		sourceRatio = 0.5 * ( cos ( 0.5 * PI * ( cos ( (double) factor * PI ) + 1.0 ) ) + 1.0 );
		destRatio = 1.0 - sourceRatio;
		magnitude = 1.0;
	}else{
		destRatio = 1.0;
		sourceRatio = 0.0;
		magnitude = 0.5 * ( cos( 0.5 * PI * ( cos( (double)(currentFactor + 1.0) * PI ) + 1.0 ) ) + 1.0 );
	}

	double signal = magnitude * (destRatio * (double)getDest() + sourceRatio * (double)getSrc());
#ifdef _DEBUG
	std::cout << "magnitude: " << magnitude << std::endl;
	std::cout << "dest: " << getDest() << std::endl;
	std::cout << "src: " << getSrc() << std::endl;
	std::cout << "signal: " << signal << std::endl;
#endif
	return signal;
}
