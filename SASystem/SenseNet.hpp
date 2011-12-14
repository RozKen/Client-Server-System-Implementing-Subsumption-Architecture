#ifndef _Sense_Net_HPP_
#define _Sense_Net_HPP_

#include "SAModule.h"

#ifndef _RobotMAV_H_
class RobotMAV;
#endif	//_RobotMAV_H_

/**
	@class SenseNet
	@brief ネットワーク接続を検知し，近傍五つのロボットの相対位置を出力するセンサ
	情報の交流などは，RobotMAVやWorldにて，Moduleを用いない方法で実装されている.
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
	for(int i = 0; i < WIFI_CONNECT * 2; i++){
		std::string name = "Robot";
		name.append(intToString( i / 2 ));
		if( i % 2 == 0){
			name.append("X");
		}else{
			name.append("Y");
		}
		this->addOutput(name);
		std::string fname = "f";
		fname.append(name);
		this->addFBoard(fname);
	}
}

inline void SenseNet::Run(){
	float temp;
	for(int i = 0; i < WIFI_CONNECT * 2; i++){
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