#ifndef _Sense_Radiation_HPP_
#define _Sense_Radiation_HPP_

#include "SAModule.h"

class SenseRadiation : public SAModule{
public:
	SenseRadiation();

	virtual void Run();
};

inline SenseRadiation::SenseRadiation(){
	for(int i = 0; i < MAX_AREA; i++){
		addFBoard("fRad[" + intToString(i) + "]");
		addOutput("radiation[" + intToString(i) + "]");
	}
}

inline void SenseRadiation::Run(){
	for(int i = 0; i < MAX_AREA; i++){
		//fBoard‚Ì’l‚ðOutput
		setOutput(i, this->getFBoard(i));
	}
}

#endif	//_Sense_Radiation_HPP_