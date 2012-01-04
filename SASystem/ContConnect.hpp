#ifndef _Cont_Connect_HPP_
#define _Cont_Connect_HPP_

#include "SAModule.h"
#include <string.h>
#include "Random.hpp"

/**
	@class ContConnect
	@brief Mission : 近くにいる仲間と繋がろうとする制御器
	<h1>Inputs</h1>
	<ul>
		<li>Input0: Robot0XCC : Robot[0]->posX</li>
		<li>Input1: Robot0YCC : Robot[0]->posY</li>
		<li>Input2: Robot1XCC : Robot[1]->posX</li>
		<li>Input3: Robot1YCC : Robot[1]->posY</li>
		<li>Input4: Robot2XCC : Robot[2]->posX</li>
		<li>Input5: Robot2YCC : Robot[2]->posY</li>
		<li>Input6: Robot3XCC : Robot[3]->posX</li>
		<li>Input7: Robot3YCC : Robot[3]->posY</li>
		<li>Input8: Robot4XCC : Robot[4]->posX</li>
		<li>Input9: Robot4YCC : Robot[4]->posY</li>
	</ul>
	<h1>Outputs</h1>
	<ul>
		<li>Output0: dXCC: delta X - differential of Motion X</li>
		<li>Output1: dYCC: delta Y - differential of Motion Y</li>
	</ul>
	@sa SenseNet
	@author Kenichi Yorozu
	@date 9th December 2011
 */
class ContConnect : public SAModule{
public:
	/**
		@brief Default Constructor
		InputやOutputなどを追加していく
	 */
	ContConnect();
	/**
		@brief 実行時の動作
		<ul>
			<li>Networkが切れそうなRobotがあれば，そちらへ向かう</li>
			<li>そうでない場合，時々近傍のロボットの真ん中に陣取る</li>
			<li>それ以外はNO_SIGNAL</li>
		</ul>
		Networkが切れそう := WIFI_REACH * WIFI_WEAKの距離
		時々 := WIFI_BALANCE
		@sa SAModule::Run()
		@sa WIFI_REACH
		@sa WIFI_WEAK
		@sa WIFI_BALANCE
	 */
	virtual void Run();
protected:
	/**
		@brief Random Generator.WIFI_BALANCE関連で利用
	 */
	Random<boost::uniform_real<> > rand;
};

inline ContConnect::ContConnect() : rand(0.0, 1.0){
	std::string head = "Robot";
	std::string foot = "CC";
	//Add Inputs
	for(int i = 0; i < WIFI_CONNECT * 2; i++){
		std::string name = head;
		name.append(intToString( i / 2 ) );
		if( i % 2 == 0){
			name.append("X");
		}else{
			name.append("Y");
		}
		name.append(foot);
		this->addInput(name);
	}

	head = "d";
	//Add Outputs
	for(int i = 0; i < 2; i++){
		std::string name = head;
		if( i % 2 == 0){
			name.append("X");
		}else{
			name.append("Y");
		}
		name.append(foot);
		this->addOutput(name);
	}
}
	
#endif	_Cont_Connect_HPP_