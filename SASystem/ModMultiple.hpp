#ifndef ModMultiple_HPP_
#define ModMultiple_HPP_

#include "SAModule.h"
#include <iostream>

class ModMultiple : public SAModule{
public:
	ModMultiple();
	void Run();
};

inline ModMultiple::ModMultiple(){
	addInput(std::string("mult_left"));
	addInput(std::string("mult_right"));
	addOutput(std::string("mult_result"));
}

inline void ModMultiple::Run(){
	//Acquire Data
	float a = getInput(0);
	float b = getInput(1);
	//Process
	float c = a * b;
	std::cout << std::fixed << "a: " << a << ", b: " << b << ", c: " << c << std::endl;
	//Deliver Data
	setOutput(0, c);
}

#endif	//ModMultiple_HPP_