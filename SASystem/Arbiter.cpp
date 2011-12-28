#include "Arbiter.h"
#include <math.h>

Arbiter::Arbiter()
	:_rand(0, 1), timeToModify(0), timeLeftModified(0)
	, factor(NO_SIGNAL){
}

Arbiter::Arbiter(SAModule* src, int srcPort, SAModule* dest, int destPort)
	:_rand(0, 1), source(src), srcPort(srcPort), destination(dest), destPort(destPort),
	timeToModify(0), timeLeftModified(0), factor(NO_SIGNAL){
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
	_rand(factor_min, factor_max), timeToModify(0), timeLeftModified(0), factor(NO_SIGNAL){
		addInput(src->getOutputTitles()->at(srcPort));
		addInputIndex(src->getOutputIndex(srcPort));
		addOutput(dest->getInputTitles()->at(destPort));
		addOutputIndex(dest->getInputIndex(destPort));
}

Arbiter::~Arbiter(){
	delete source;
	delete destination;
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
		///Arbiterへの入力はmemoryの入力から入手※Moduleと異なる
	int result = memory->getInput(this->inputIndex->at(0));
	return result;
}
float Arbiter::getInput(int index) const{
	return getInput();
}

void Arbiter::setInput(float signal){
	memory->setInput(this->inputIndex->at(0), signal);
}
void Arbiter::setInput(int index, float signal){
	return setInput(signal);
}

float Arbiter::getOutput() const{
	int result = memory->getOutput(this->outputIndex->at(0));
	return result;
}
float Arbiter::getOutput(int index) const{
	return getOutput();
}

void Arbiter::setOutput(float signal){
	///Arbiterからの出力は，memoryの出力へ送信※Moduleと異なる
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
	///現Stepにおける，Arbiterの挙動を決める因子
	double currentFactor;
	///factorが指定されていなければ，
	if(factor == NO_SIGNAL){
#ifdef	IMPORTANCE_BASED
		///importanceを入手
		float impSrc = source->getImportance();
		float impDst = destination->getImportance();
		//sourceかdestinationのどちらかがNO_SIGNALの時
		if(impSrc == NO_SIGNAL || impDst == NO_SIGNAL){
#endif	//IMPORTANCE_BASED
			if(impSrc != NO_SIGNAL){
				currentFactor = 0.0f;
			}else if(impDst != NO_SIGNAL){
				currentFactor = 1.0f;
			}else{
				///乱数で生成
				currentFactor = _rand();
			}
#ifdef	IMPORTANCE_BASED
		}else{	//そうでないときは，計算できる
			currentFactor = impSrc / (impSrc + impDst);
		}
#endif	//IMPORTANCE_BASED
	}else{
		///factorが指定されていれば，その値を利用
		currentFactor = (double)factor;
	}

	double destRatio;	///接続先(下層)の信号の影響率
	double sourceRatio;	///接続元(上層)の信号の影響率

	double magnitude;	///信号全体の強さの係数

	if(currentFactor >= 0.0 && currentFactor <= 1.0){
		//Act like Suppressor, Selecter or Superposer
		magnitude = 1.0;

#ifdef INVERSE_SUPPRESSOR
		if(getDest() != NO_SIGNAL){
			destRatio = 0.5 * ( cos ( 0.5 * PI * ( cos ( (double) currentFactor * PI ) + 1.0 ) ) + 1.0 );
			sourceRatio = 1.0 - destRatio;
#else	// if NORMAL_SUPRESSOR
		if(getSrc() != NO_SIGNAL){
			sourceRatio = 0.5 * ( cos ( 0.5 * PI * ( cos ( (double) currentFactor * PI ) + 1.0 ) ) + 1.0 );
			destRatio = 1.0 - sourceRatio;
#endif	//INVERSE_SUPPRESSOR
		}else{
#ifdef INVERSE_SUPPRESSOR
			//getDest() == NO_SIGNAL
			destRatio = 0.0;
			sourceRatio = 1.0;
#else	// if NORMAL_SUPRESSOR
			//getSrc() == NO_SIGNAL
			destRatio = 1.0;
			sourceRatio = 0.0;
#endif	//INVERSE_SUPPRESSOR
		}
	}else if(currentFactor < 0.0 && currentFactor >= -1.0){
		//Act like Inhibitor
		sourceRatio = 0.0;
		destRatio = 1.0;
		magnitude = 0.5 * ( cos( 0.5 * PI * ( cos( (double)(currentFactor + 1.0) * PI ) + 1.0 ) ) + 1.0 );
	}else{	//Act as Wire
		sourceRatio = 1.0;
		destRatio = 0.0;
		magnitude = 1.0;
	}
	this->currentRatio = sourceRatio;
	double signal = magnitude * (destRatio * (double)getDest() + sourceRatio * (double)getSrc());
#ifdef _DEBUG
	
	//std::cout << "magnitude: " << magnitude << std::endl;
	//std::cout << "dest: " << this->outputTitles->at(0) << ":" << getDest() << std::endl;
	//std::cout << "src: " << this->inputTitles->at(0) << ":" << getSrc() << std::endl;
	//std::cout << "signal: " << signal << std::endl;
	
#endif
	return signal;
}
