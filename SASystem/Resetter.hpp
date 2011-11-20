#ifndef _Resetter_HPP_
#define _Resetter_HPP_

#include "SAModule.h"

class Resetter : public SAModule{
public:
	Resetter(float signal);
	void Run();
protected:
	float resetSignal;
};

Resetter::Resetter(float signal): resetSignal(signal){
	this->addOutput("signal");
}

void Resetter::Run(){
	setOutput(0, resetSignal);
}

#endif	//_Resetter_HPP_