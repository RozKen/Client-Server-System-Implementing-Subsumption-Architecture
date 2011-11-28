#ifndef _Cont_Move_HPP_
#define _Cont_Move_HPP_

#include "SAModule.h"

class ContMove : public SAModule{
public:
	ContMove();
	virtual void Run();
};

inline ContMove::ContMove(){
	this->addOutput("cX");
	this->addOutput("cY");
}

inline void ContMove::Run(){
	this->setOutput(0, 2.0);
	this->setOutput(1, 2.0);
	//Log();
}

#endif	//_Cont_Move_HPP_