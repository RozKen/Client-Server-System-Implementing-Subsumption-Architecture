#include "Arbiter.h"
#include <math.h>

Arbiter::Arbiter()
	:_rand(0, 1), timeToModify(0), timeLeftModified(0)
	, factor(-100.0f){
}

Arbiter::Arbiter(float* source, float* destination)
	:source(source), destination(destination), _rand(0, 1), 
	timeToModify(0), timeLeftModified(0), factor(-100.0f){
}

Arbiter::Arbiter(float* source, float* destination, float factor)
	:source(source), destination(destination), _rand(0, 1), 
	timeToModify(0), timeLeftModified(0), factor(-100.0f){
		this->factor = factor;
}

Arbiter::Arbiter(float* source, float* destination, 
		float factor_min, float factor_max)
	:source(source), destination(destination), _rand(factor_min, factor_max), 
	timeToModify(0), timeLeftModified(0), factor(-100.0f){
}

void Arbiter::setSource(float* source){
	this->source = source;
}

void Arbiter::setDestination(float* destination){
	this->destination = destination;
}

double Arbiter::generateSignal(){
	///現Stepにおける，Arbiterの挙動を決める因子
	double currentFactor;
	if(factor == -100.0f){
		currentFactor = _rand();
	}else{
		currentFactor = (double)factor;
	}

	double destRatio;	///接続先(下層)の信号の影響率
	double sourceRatio;	///接続元(上層)の信号の影響率

	double magnitude;	///信号全体の強さの係数

	if(factor >= 0){
		destRatio = 0.5 * ( cos(0.5 * PI * cos(currentFactor * PI) + 1.0) + 1.0 );
		sourceRatio = 1.0 - destRatio;
		magnitude = 0.0;
	}else{
		destRatio = 1.0;
		sourceRatio = 0.0;
		magnitude = 0.5 * ( cos( 0.5 * PI * ( cos( (currentFactor + 1) * PI ) + 1.0 ) ) + 1.0 );
	}

	double signal = magnitude * (destRatio * (double)(*destination) + sourceRatio * (double)(*source));
	return signal;
}

void Arbiter::Run(){
	*destination = (float)generateSignal();
}