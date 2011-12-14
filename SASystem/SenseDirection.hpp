#ifndef _Sense_Direction_HPP_
#define _Sense_Direction_HPP_

#include "SAModule.h"

/**
	@class SenseDirection
	@brief ���݂̕��������m���C�o�͂���(�n���C���m)�Z���T
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
		Output, fBoard��ǉ�����
		Sensor�Ȃ̂ŁCInput�͂Ȃ�
	 */
	SenseDirection();

	/**
		@brief ���s���̓���
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