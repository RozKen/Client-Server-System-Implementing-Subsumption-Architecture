#ifndef _Sense_Direction_HPP_
#define _Sense_Direction_HPP_

#include "SAModule.h"

/**
	@class SenseDirection
	@brief 現在の方向を検知し，出力する(地磁気検知)センサ
	<h1>Outputs</h1>
	<ul>
		<li>Output0 : direc - Direction [degree]</li>
	</ul>
	<h1>FBoard</h1>
	<ul>
		<li>fBoard0 : fDirec - Direction [degree]</li>
	</ul>
	@author Kenichi Yorozu
	@date 10th December 2011
 */
class SenseDirection : public SAModule{
public:
	/**
		@brief Default Constructor
		Output, fBoardを追加する
		Sensorなので，Inputはない
	 */
	SenseDirection();

	/**
		@brief 実行時の動作
		@sa SAModule::Run()
	 */
	virtual void Run();
};

inline SenseDirection::SenseDirection(){
	this->addFBoard("fDirec");
	this->addOutput("direc");
}

inline void SenseDirection::Run(){
	this->setOutput(0, this->getFBoard(0));
}

#endif	//_Sense_Direction_HPP_