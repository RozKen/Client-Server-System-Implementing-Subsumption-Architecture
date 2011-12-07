#ifndef _Sense_Net_HPP_
#define _Sense_Net_HPP_

#include "SAModule.h"

#ifndef _RobotMAV_H_
class RobotMAV;
#endif	//_RobotMAV_H_

/**
	@class SenseNet
	@brief ネットワーク接続を検知し，近傍五つのロボットの位置を出力
	また，近傍のロボットとの情報の交流を行なうため，
	内部にそれらのRobotへのポインタを保持する
	<h1>FBoard</h1>
	<ul>
		<li>fRobot0X : Robot[0]->posX</li>
		<li>fRobot0Y : Robot[0]->posY</li>
		<li>fRobot1X : Robot[1]->posX</li>
		<li>fRobot1Y : Robot[1]->posY</li>
		<li>fRobot2X : Robot[2]->posX</li>
		<li>fRobot2Y : Robot[2]->posY</li>
		<li>fRobot3X : Robot[3]->posX</li>
		<li>fRobot3Y : Robot[3]->posY</li>
		<li>fRobot4X : Robot[4]->posX</li>
		<li>fRobot4Y : Robot[4]->posY</li>
	</ul>
	<h1>Outputs</h1>
	<ul>
		<li>Robot0X : Robot[0]->posX</li>
		<li>Robot0Y : Robot[0]->posY</li>
		<li>Robot1X : Robot[1]->posX</li>
		<li>Robot1Y : Robot[1]->posY</li>
		<li>Robot2X : Robot[2]->posX</li>
		<li>Robot2Y : Robot[2]->posY</li>
		<li>Robot3X : Robot[3]->posX</li>
		<li>Robot3Y : Robot[3]->posY</li>
		<li>Robot4X : Robot[4]->posX</li>
		<li>Robot4Y : Robot[4]->posY</li>
	</ul>
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
	/**
		@brief 実行時の動作.
		近くの繋がっているRobotを5体まで検知し，そこまでの位置(方向と距離)を出力
		@sa SAModule::Run()
	 */
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
		/*std::cout << "Robot[" << i << "]";
		if(i % 2 == 0){
			std::cout << " - x : ";
		}else{
			std::cout << " - y : ";
		}
		std::cout << temp << std::endl;
		*/
#endif //_DEBUG
		this->setOutput(i, temp);
	}
}

#endif	//_Sense_Net_HPP_