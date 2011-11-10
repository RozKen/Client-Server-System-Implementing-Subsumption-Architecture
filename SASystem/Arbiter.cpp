#include "Arbiter.h"

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

void Arbiter::Run(){
	float currentFactor;
	if(factor == -100.0f){
		currentFactor = _rand();
	}else{
		currentFactor = factor;
	}

	/************** TODO ****************/
}