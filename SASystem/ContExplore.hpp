#ifndef _Cont_Explore_HPP_
#define _Cont_Explore_HPP_

#include "SAModule.h"
/**
	@class ContExplorer
	@brief 
	<h1>Inputs</h1>
		Input�͂Ȃ��DRobot������Map�𗘗p����
	<h1>Outputs</h1>
	<ul>
		<li>dXCExp</li>
		<li>dYCExp</li>
	</ul>
	@author Kencihi Yorozu
	@date 8th December 2011
 */

class ContExplore : public SAModule{
public:
	/**
		@brief Default Constructor
		Input��Output�Ȃǂ�ǉ����Ă����D
	 */
	ContExplore();
	/**
		@brief ���s���̓���
		radMap��geoMap�̃f�[�^���Ȃ��Ƃ����ڎw���ē���
		@sa geoMap
		@sa radMap
	 */
	virtual void Run();
};

inline ContExplore::ContExplore(){
	this->addOutput("dXCExp");
	this->addOutput("dYCExp");
}

#endif	//_Cont_Explore_HPP_