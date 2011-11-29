#ifndef _Sense_Net_HPP_
#define _Sense_Net_HPP_

#include "SAModule.h"

/**
	@class SenseNet
	@brief ネットワーク接続を検知し，近傍五つのロボットの位置を出力
	@author Kenichi Yorozu
	@date 29th November 2011
 */
class SenseNet : public SAModule{
public:
	/**
		@brief Default Constructor
		Outputなどを追加していく.
		Sensorなので，Inputはない．
	 */
	SenseNet();
	virtual void Run();
};

inline SenseNet::SenseNet(){
	this->addFBoard("fRobot0X");
	this->addFBoard("fRobot0Y");
	this->addFBoard("fRobot1X");
	this->addFBoard("fRobot1Y");
	this->addFBoard("fRobot2X");
	this->addFBoard("fRobot2Y");
	this->addFBoard("fRobot3X");
	this->addFBoard("fRobot3Y");
	this->addFBoard("fRobot4X");
	this->addFBoard("fRobot4Y");
	this->addOutput("Robot0X");
	this->addOutput("Robot0Y");
	this->addOutput("Robot1X");
	this->addOutput("Robot1Y");
	this->addOutput("Robot2X");
	this->addOutput("Robot2Y");
	this->addOutput("Robot3X");
	this->addOutput("Robot3Y");
	this->addOutput("Robot4X");
	this->addOutput("Robot4Y");
}

inline void SenseNet::Run(){
	float temp;
	for(int i = 0; i < 10; i++){
		temp = this->getFBoard(i);
#ifdef _DEBUG
		std::cout << "Robot[" << i << "]";
		if(i % 2 == 0){
			std::cout << " - x : ";
		}else{
			std::cout << " - y : ";
		}
		std::cout << temp << std::endl;
#endif //_DEBUG
		this->setOutput(i, temp);
	}
}

#endif	//_Sense_Net_HPP_