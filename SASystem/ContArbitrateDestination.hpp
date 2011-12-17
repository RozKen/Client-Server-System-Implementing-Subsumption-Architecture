#ifndef _Cont_Arbitrate_Destination_HPP_
#define _Cont_Arbitrate_Destination_HPP_

#include "SAModule.h"

/**
	@class ContArbitrateDestination
	@brief Mission : �T���ꏊ�̕������C���̃��{�b�g�Ɠ����ɂȂ�悤�ɂ���
	<h1>Inputs</h1>
	<ul>
		<li>Input0 : posXCAd</li>
		<li>Input1 : posYCAd</li>
	</ul>
	<h1>Outputs</h1>
	No Outputs
	@author Kenichi Yorozu
	@date 16th December 2011
	@sa SAModule
	@sa ContExplore
 */
class ContArbitrateDestination : public SAModule {
public:
	/**
		@brief Default Constructor
		Input��Output�Ȃǂ�ǉ����Ă����D
		ContExplore��IBoard��p���邽�߁CiBoardIndex��ݒ�
		@sa ContExplore
	 */
	ContArbitrateDestination();
	/**
		@brief ���s���̓���
			<ul>
				<li>
					���g��Explore��Destination������Robot��
					�قȂ�����ɂ���Ƃ��CDestination��NO_SIGNAL�Ƃ���
				</li>
				<li>
					�����łȂ��Ƃ��͏o�͂�NO_SIGNAL�Ƃ���
				</li>
			</ul>
	 */
	virtual void Run();
};
#endif	//_Cont_Arbitrate_Destination_HPP_