#ifndef _Act_Pos_HPP_
#define _Act_Pos_HPP_

#include "SAModule.h"
/**
	@class ActPos
	@brief

	@author Kenichi Yorozu
	@date 25th November 2011
 */
class ActPos : public SAModule{
public:
	ActPos();

	virtual void Run();
};

inline ActPos::ActPos(){
	this->addInput("controlX");
	this->addInput("controlY");
	this->addIBoard("iDeltaX");
	this->addIBoard("iDeltaY");
}

inline void ActPos::Run(){
	//信号を入手
	int dX = this->round(this->getInput(0));
	int dY = this->round(this->getInput(1));
	//Robotの内部に出力信号を格納
	this->setIBoard(0, dX);
	this->setIBoard(1, dY);
	//Log();
}

#endif	//_Act_Pos_HPP_