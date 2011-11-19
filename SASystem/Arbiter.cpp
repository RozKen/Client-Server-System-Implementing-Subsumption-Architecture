#include "Arbiter.h"
#include <math.h>

Arbiter::Arbiter()
	:_rand(0, 1), timeToModify(0), timeLeftModified(0)
	, factor(-100.0f){
}

Arbiter::Arbiter(SAModule* src, int srcPort, SAModule* dest, int destPort)
	:_rand(0, 1), source(src), srcPort(srcPort), destination(dest), destPort(destPort),
	timeToModify(0), timeLeftModified(0), factor(-100.0f){
}

Arbiter::Arbiter(SAModule* src, int srcPort, SAModule* dest, int destPort, float factor)
	:_rand(0, 1),  source(src), srcPort(srcPort), destination(dest), destPort(destPort),
	timeToModify(0), timeLeftModified(0), factor(factor){
}

Arbiter::Arbiter(SAModule* src, int srcPort, SAModule* dest, int destPort, 
		float factor_min, float factor_max)
	: source(src), srcPort(srcPort), destination(dest), destPort(destPort), 
	_rand(factor_min, factor_max), timeToModify(0), timeLeftModified(0), factor(-100.0f){
}

void Arbiter::Run(){
	*destination = (float)generateSignal();
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

float Arbiter::getInput(int index) const{
	///Arbiter‚Ö‚Ì“ü—Í‚Ímemory‚Ì“ü—Í‚©‚ç“üŽè¦Module‚ÆˆÙ‚È‚é
	int result = memory->getInput(this->inputIndex->at(index));
	return result;
}

void Arbiter::setOutput(int index, float signal){
	///Arbiter‚©‚ç‚Ìo—Í‚ÍCmemory‚Ìo—Í‚Ö‘—M¦Module‚ÆˆÙ‚È‚é
	memory->setOutput(this->outputIndex->at(index), signal);
}

double Arbiter::generateSignal(){
	///Œ»Step‚É‚¨‚¯‚éCArbiter‚Ì‹““®‚ðŒˆ‚ß‚éˆöŽq
	double currentFactor;
	if(factor == -100.0f){
		currentFactor = _rand();
	}else{
		currentFactor = (double)factor;
	}

	double destRatio;	///Ú‘±æ(‰º‘w)‚ÌM†‚Ì‰e‹¿—¦
	double sourceRatio;	///Ú‘±Œ³(ã‘w)‚ÌM†‚Ì‰e‹¿—¦

	double magnitude;	///M†‘S‘Ì‚Ì‹­‚³‚ÌŒW”

	if(factor >= 0){
		destRatio = (float)0.5 * ( cos ( 0.5 * PI * ( cos ( (double) factor * PI ) + 1.0 ) ) + 1.0 );
		sourceRatio = 1.0 - destRatio;
		magnitude = 0.0;
	}else{
		destRatio = 1.0;
		sourceRatio = 0.0;
		magnitude = 0.5 * ( cos( 0.5 * PI * ( cos( (double)(currentFactor + 1.0) * PI ) + 1.0 ) ) + 1.0 );
	}

	double signal = magnitude * (destRatio * (double)(*destination) + sourceRatio * (double)(*source));
	return signal;
}
