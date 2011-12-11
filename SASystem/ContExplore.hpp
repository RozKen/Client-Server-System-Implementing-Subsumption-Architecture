#ifndef _Cont_Explore_HPP_
#define _Cont_Explore_HPP_

#include "SAModule.h"
/**
	@class ContExplore
	@brief <h1>Mission</h1>: �T�����Ă��Ȃ��ꏊ�֍s��
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
			<ul>
				<li>
					radMap��geoMap�̃f�[�^���Ȃ�(NO_DATA)�Ƃ����
					innerMap����T���C������ڎw���ē���
				</li>
				<li>
					NO_DATA���Ȃ��ꍇ��CNO_DATA�������̈ʒu�̎���
					�o�͂�NO_SIGNAL�Ƃ���
				</li>
			</ul>
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