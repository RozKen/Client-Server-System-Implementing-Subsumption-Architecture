#ifndef _ActWheel_HPP_
#define _ActWheel_HPP_

#include "SAModule.h"
#include <iostream>

class ActWheel extends SAModule{
public:
	float Run(float signal);
	int getPos();
protected:
	//Œ»İ‚Ì‰ñ“]”
	int position;
};

inline float ActWheel::Run(float signal){
	//Position‚ğXV
	position += 6.0 * (signal - 0.5);
	return signal;
}

inline int ActWheel::printPos(){
	return position;
}

#endif //_ActWheel_HPP_