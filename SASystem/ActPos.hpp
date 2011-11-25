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
	this->addIBoard("deltaX");
	this->addIBoard("deltaY");
}

inline void ActPos::Run(){
	//M†‚ð“üŽè
	int dX = this->round(this->getInput(0));
	int dY = this->round(this->getInput(1));
	//Robot‚Ì“à•”‚Éo—ÍM†‚ðŠi”[
	this->setIBoard(0, dX);
	this->setIBoard(1, dY);
}

#endif	//_Act_Pos_HPP_