#ifndef _Cont_Explore_HPP_
#define _Cont_Explore_HPP_

#include "SAModule.h"
/**
	@class ContExplore
	@brief Mission : �T�����Ă��Ȃ��ꏊ�֍s�����Ƃ��鐧���
	<h1>Inputs</h1>
		Input�͂Ȃ��DRobot������Map�𗘗p����
	<h1>Outputs</h1>
	<ul>
		<li>Output0 : dXCExp</li>
		<li>Output1 : dYCExp</li>
	</ul>
	<h1>iBoard</h1>
	<ul>
		<li>iBoard0 : iDestinationX</li>
		<li>iBoard1 : iDestinationY</li>
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
					radMap��geoMap�̃f�[�^���Ȃ�(NO_DATA_ON_FIELD)�Ƃ����
					innerMap����T���C������ڎw���ē���
				</li>
				<li>
					���łɖړI�n���ݒ肳��Ă���ꍇ�́C�V�K�ɒT�����C
					������ڎw���ē���
				</li>
				<li>
					NO_DATA_ON_FIELD���Ȃ��ꍇ��CNO_DATA_ON_FIELD�������̈ʒu�̎���
					�o�͂�NO_SIGNAL�Ƃ���
				</li>
			</ul>
		@sa geoMap
		@sa radMap
	 */
	virtual void Run();
	/**
		@brief �V���ɖړI�n���߂�
	 */
	void DecideDestination();
	/**
		@brief ���݂̖ړI�n��X���W�𓾂�
		@return ���݂̖ړI�n��X���W
		@sa destination
	 */
	int getDestinationX() const;
	/**
		@brief ���݂̖ړI�n��Y���W�𓾂�
		@return ���݂̖ړI�n��Y���W
		@sa destination
	 */
	int getDestinationY() const;
protected:
};

inline ContExplore::ContExplore(){
	this->addOutput("dXCExp");
	this->addOutput("dYCExp");

	this->addIBoard("iDestinationX");
	this->addIBoard("iDestinationY");
}

inline int ContExplore::getDestinationX() const{
	return this->getIBoard(0);
}

inline int ContExplore::getDestinationY() const{
	return this->getIBoard(1);
}

#endif	//_Cont_Explore_HPP_