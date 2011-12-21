#ifndef _Cont_Wander_HPP_
#define _Cont_Wander_HPP_

#include <math.h>
#include "Random.hpp"
#include "SAModule.h"
#include "Constants.h"

/**
	@class ContWander
	@brief Mission : うろつき行動をしようとする制御器
	<h1>Inputs</h1>
	<ul>
		<li>Input0: posXCW : current Position - X</li>
		<li>Input1: posYCW : current Position - Y</li>
	</ul>
	<h1>Outputs</h1>
	<ul>
		<li>Output0: dXCW: delta X - differential of Motion X</li>
		<li>Output1: dYCW: delta Y - differential of Motion Y</li>
	</ul>
	<h1>Inner FBoard</h1>
	<ul>
		<li>innerFBoard0: fPosX0 : current Position[t] - X</li>
		<li>innerFBoard1: fPosY0 : current Position[t] - Y</li>
		<li>innerFBoard2: fPosX1 : Position[t-1] - X</li>
		<li>innerFBoard3: fPosY1 : Position[t-1] - Y</li>
		<li>innerFBoard4: fPosX2 : Position[t-2] - X</li>
		<li>innerFBoard5: fPosY2 : Position[t-2] - Y</li>
		<li>innerFBoard6: fPosX3 : Position[t-3] - X</li>
		<li>innerFBoard7: fPosY3 : Position[t-3] - Y</li>
		<li>innerFBoard8: fPosX4 : Position[t-4] - X</li>
		<li>innerFBoard9: fPosY4 : Position[t-4] - Y</li>
	</ul>
	@author Kenichi Yorozu
	@date 30th November 2011
 */

class ContWander : public SAModule{
public:
	/**
		@brief Default Constructor
		Input, Outputなどを追加していく.
	 */
	ContWander();
	/**
		@brief 実行時の動作.
		<ul>
			<li>確率0.1でランダムな方向へ1進む</li>
			<li>その他の時，NO_SIGNAL</li>
		</ul>
		@sa SAModule::Run()
	 */
	virtual void Run();
protected:
	///Random Generator
	Random<boost::uniform_real<> > _rand;
};

inline ContWander::ContWander(): _rand(0, 1){
	this->addInput("posXCW");
	this->addInput("posYCW");

	this->addOutput("dXCW");
	this->addOutput("dYCW");

	std::string temp;
	for(int i = 0; i < 10; i++){
		temp = "fPos";
		if( i % 2 == 0 ){
			temp.append("X");
		}else{
			temp.append("Y");
		}
		temp.append(this->intToString(i/2));
		this->innerMemory->addFloatPort(temp);
	}
}

inline void ContWander::Run(){
	//履歴を移動
	for(int i = 9; i > 1; i--){
		this->innerMemory->setFBoard(i, this->innerMemory->getFBoard(i - 2));
	}
	//最新状態を更新
	this->innerMemory->setFBoard(0, this->getInput(0));
	this->innerMemory->setFBoard(1, this->getInput(1));
	//とりあえず，履歴とかは考えずに，ランダムに動く．
	float signalX = NO_SIGNAL;
	float signalY = NO_SIGNAL;
	if(_rand() < P_WANDER){
		float theta = 2.0 * PI * _rand();
		signalX = (float)MAX_DRIVE * cos(theta);
		signalY = (float)MAX_DRIVE * sin(theta);
	}else{
		signalX = NO_SIGNAL;
		signalY = NO_SIGNAL;
	}
	//出力
	this->setOutput(0, signalX);
	this->setOutput(1, signalY);
}

#endif	//_Cont_Wander_HPP_