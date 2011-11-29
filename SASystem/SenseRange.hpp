#ifndef _Sense_Range_HPP_
#define _Sense_Range_HPP_

#include "SAModule.h"
#include "RobotMAV.h"

/**
	@class SenseRange
	@brief Survey Obstacles for each 30 degree
	0�x�͏��x�������D
	<h1>FBoard</h1>
	<ul>
		<li>fRange0 : 0</li>
		<li>fRange1 : 30</li>
		<li>fRange2 : 60</li>
		<li>fRange3 : 90</li>
		<li>fRange4 : 120</li>
		<li>fRange5 : 150</li>
		<li>fRange6 : 180</li>
		<li>fRange7 : 210</li>
		<li>fRange8 : 240</li>
		<li>fRange9 : 270</li>
		<li>fRange10 : 300</li>
		<li>fRange11 : 330</li>
	</ul>
	<h1>Outputs</h1>
	<ul>
		<li>Range0 : 0</li>
		<li>Range1 : 30</li>
		<li>Range2 : 60</li>
		<li>Range3 : 90</li>
		<li>Range4 : 120</li>
		<li>Range5 : 150</li>
		<li>Range6 : 180</li>
		<li>Range7 : 210</li>
		<li>Range8 : 240</li>
		<li>Range9 : 270</li>
		<li>Range10 : 300</li>
		<li>Range11 : 330</li>
	</ul>
	@author Kenichi Yorozu
	@date 29th November 2011
 */

class SenseRange : public SAModule{
public:
	/**
		@brief Default Constructor
		Output�Ȃǂ�ǉ����Ă���.
		Sensor�Ȃ̂ŁCInput�͂Ȃ��D
		0�x����30�x���C�������̕����ɂ����ԋ߂���Q���ւ̋�����ێ�
	 */
	SenseRange();
	/**
		@brief ���s���̓���.
		�e�����̍ł��߂����̂̋��������m���C�o��
		@sa SAModule::Run()
	 */
	virtual void Run();
};

inline SenseRange::SenseRange(){
	std::string temp;
	for(int i = 0; i < RANGE_DIV; i++){
		temp = "fRange";
		temp.append(this->intToString(i));
		this->addFBoard(temp);
	}
	for(int i = 0; i < RANGE_DIV; i++){
		temp = "Range";
		temp.append(this->intToString(i));
		this->addOutput(temp);
	}
}

inline void SenseRange::Run(){
	float temp;
	for(int i = 0; i < RANGE_DIV; i++){
		temp = this->getFBoard(i);
#ifdef _DEBUG
		std::cout << "Range[" << i << "] : " << temp << std::endl;
#endif	//_DEBUG
		this->setOutput(i, temp);
	}
}

#endif	//_Sense_Range_HPP_