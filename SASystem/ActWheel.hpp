#ifndef _ActWheel_HPP_
#define _ActWheel_HPP_

#include "SAModule.h"
#include <iostream>

class ActWheel :public SAModule{
public:
	float Run(float signal);
	int getPos();
protected:
	//Œ»İ‚Ì‰ñ“]”
	int position;
};
inline ActWheel(): position(0){
}
inline float ActWheel::Run(float signal){
	//Position‚ğXV
	position += 6.0 * (signal - 0.5);
	return signal;
}

inline int ActWheel::getPos(){
	return position;
}

#endif //_ActWheel_HPP_