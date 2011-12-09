#ifndef _Cont_Avoid_HPP_
#define _Cont_Avoid_HPP_

#include "Random.hpp"
#include "SAModule.h"
#include "Constants.h"

/**
	@class ContAvoid
	@brief 他のものにぶつからないようにしようとする制御器
	<h1>Inputs</h1>
	<ul>
		<li>Input0: RangeCAv0 : 0</li>
		<li>Input1: RangeCAv1 : 30</li>
		<li>Input2: RangeCAv2 : 60</li>
		<li>Input3: RangeCAv3 : 90</li>
		<li>Input4: RangeCAv4 : 120</li>
		<li>Input5: RangeCAv5 : 150</li>
		<li>Input6: RangeCAv6 : 180</li>
		<li>Input7: RangeCAv7 : 210</li>
		<li>Input8: RangeCAv8 : 240</li>
		<li>Input9: RangeCAv9 : 270</li>
		<li>Input10: RangeCAv10 : 300</li>
		<li>Input11: RangeCAv11 : 330</li>
	</ul>
	<h1>Outputs</h1>
	<ul>
		<li>Output0: dXCAv: delta X - differential of Motion X</li>
		<li>Output1: dXCAv: delta Y - differential of Motion Y</li>
	</ul>
	@author Kenichi Yorozu
	@date 29th November 2011
 */
class ContAvoid : public SAModule{
public:
	/**
		@brief Default Constructor
		Input, Outputなどを追加していく.
	 */
	ContAvoid();
	/**
		@brief 実行時の動作.
		<ul>
			<li>近くに危険な物体があるとき</li>
			<ul>
				<li>安全な方向があればそちらへ</li>
				<li>なければ停止する</li>
			</ul>
			<li>周りがすべて安全なとき，NO_SIGNAL</li>
		</ul>
		@sa SAModule::Run()
	 */
	virtual void Run();
protected:
	///Random Generator
	Random<boost::uniform_real<> > _rand;
};

inline ContAvoid::ContAvoid() : _rand(0, 1){
	std::string temp;
	for(int i = 0; i < RANGE_DIV; i++){
		temp = "RangeCAv";
		temp.append(this->intToString(i));
		this->addInput(temp);
	}
	this->addOutput("dXCAv");
	this->addOutput("dXCAv");
}

inline void ContAvoid::Run(){
	//危険な方角があるかどうか
	bool danger = false;
	//安全な方向のリスト
	std::vector<int> safeIndex;
	//出力信号
	float signalX, signalY;

	for(int i = 0; i < RANGE_DIV; i++){
		if(this->getInput(i) < RANGE_DANGER){
			danger = true;
		}else{
			safeIndex.push_back(i);
		}
	}

	if(danger){
		if(safeIndex.empty()){
			//その場に停止する
			signalX = 0.0f;
			signalY = 0.0f;
		}else{
			int index = this->round((safeIndex.size() - 1) * _rand());
			double theta = (RANGE_DEG * PI / 180.0) * (double)(safeIndex.at(index));
			signalX = (float)MAX_DRIVE * cos(theta);
			signalY = (float)MAX_DRIVE * sin(theta);
		}
	}else{
		signalX = NO_SIGNAL;
		signalY = NO_SIGNAL;
	}

	this->setOutput(0, signalX);
	this->setOutput(1, signalY);
}


#endif	//_Cont_Avoid_HPP_