#ifndef _Cont_Smart_Alive_HPP_
#define _Cont_Smart_Alive_HPP_

#include "SAModule.h"

/**
	@class ContSmartAlive
	@brief Mission : �[�d�Ɋւ��āA���X�}�[�g�ȓ����𔭌�������.
	<h1>Inputs</h1>
	<ul>
		<li>Input0 : posXCS</li>
		<li>Input1 : posYCS</li>
		<li>Input2 : batCS</li>
		<li>Input3 : onBatChCS</li>
	</ul>
	<h1>Outputs</h1>
	<ul>
		<li>Output0 : dXCS</li>
		<li>Output1 : dYCS</li>
	</ul>
	<h1>iBoard</h1>
	<ul>
		<li>iBoard0 : iChargeF ; Charge Flag : 1 = Stop and Charge, 0 = Other</li>
	</ul>
	@author Kenichi Yorozu
	@date 18th December 2011
	@sa SAModule
 */

class ContSmartAlive : public SAModule{
public:
	/**
		@brief Default Constructor
		Input��Output�Ȃǂ�ǉ����Ă����D
	 */
	ContSmartAlive();
	/**
		@brief ���s���̓���
			<ul>
				<li>Battery Level < 50% ���� ON_BATTERY�̎��́A100%�ɂȂ�܂ŏ[�d����</li>
				<li>�����Ƃ��߂�Battery Charger�܂ňړ��ł��邬�肬���Battery Level�ɂȂ�����C�߂�</li>
				<li>�����łȂ��Ƃ��͏o�͂�NO_SIGNAL�Ƃ���</li>
			</ul>
		@sa SAModule::Run
	 */
	virtual void Run();

protected:
	/**
		@brief �������C�ߖT�̃o�b�e���[�ꏊ
	 */
	float nearestCharger[2];
	/**
		@brief �������ꏊ�Ƃ̋���
	 */
	float distance;
	/**
		@brief �[�d�ꏊ�̂����C�����Ƃ��߂��ꏊ�����邩�ǂ����C�T���D
		����΁C���̍��W�Ƌ��������ꂼ��
		nearestCharger��distance�Ɋi�[����
		@sa nearestCharger
	 */
	bool findNearestCharger();
};
#endif	//_Cont_Smart_Alive_HPP_
