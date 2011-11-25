#ifndef _Sense_Pos_HPP_
#define _Sense_Pos_HPP_

#include "SAModule.h"

class SensePos : public SAModule{
public:
	/**
		@brief Default Constructor
		Outputなどを追加していく.
		Sensorなので，Inputはない．
	 */
	SensePos();
	/**
		@brief 実行時の動作
		@sa SAModule::Run()
	 */
	virtual void Run();
};

inline SensePos::SensePos(){
	this->addIBoard("posX");
	this->addIBoard("posY");
	this->addOutput("posX");
	this->addOutput("posY");
}

inline void SensePos::Run(){
	//Sensor情報を入手
	int posX = this->getIBoard(0);
	int posY = this->getIBoard(1);
	//Sensor情報を出力
	this->setOutput(0, (float) posX);
	this->setOutput(1, (float) posY);
}

#endif	//_Sense_Pos_HPP_