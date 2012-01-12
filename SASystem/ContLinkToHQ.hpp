#ifndef _Cont_Link_To_HQ_HPP_
#define	_Cont_Link_To_HQ_HPP_

#include "SAModule.h"
#include "Random.hpp"

/**
	@class ContLinkToHQ
	@brief Mission: �i�ߕ��Ƃ̘A���o�H���m�ۂ��鐧��� Link to Headquaters
	<h1>Inputs</h1>
	<ul>
		<li>Input0 : posXCLTHQ : ���݈ʒu(X���W)</li>
		<li>Input1 : posYCLTHQ : ���݈ʒu(Y���W)</li>
	</ul>
	<h1>Outputs</h1>
	<ul>
		<li>Output0 : dXCLTHQ : �����̎w��(X���W)</li>
		<li>Output1 : dYCLTHQ : �����̎w��(Y���W)</li>
	</ul>
	<h1>iBoards</h1>
	<ul>
		<li>iBoard0 : iHop : �i�ߕ��֓��B����܂łɌo�R����Robot�̐�</li>
	</ul>
	<h1>Others</h1>
	<ul>
		<li>Using (RobotUGV *)relative_root which data is stored on RobotUGV : setRelativeRoot, getRelativeRoot</li>
	</ul>
 */
class ContLinkToHQ : public SAModule{
public:
	/**
		@brief Default Constructor
		Input, Output�Ȃǂ�ǉ����Ă����D
	 */
	ContLinkToHQ();

	/**
		@brief ���s���̓���
			<ul>
				<li>hop = NO_SIGNAL�̎�</li>
				<ul>
					<li>�߂���hop >= 0 ��������C�����relative_root�Ƃ���</li>
					<li>���Ȃ���΁C�i�ߕ��֌�����(START_X, START_Y)</li>
				</ul>
				<li>hop != NO_SIGNAL�̎�</li>
				<ul>
					<li> hop == 0�̂Ƃ��C�i�ߕ��Ƃ̋������m�F���āC�q�����Ă��邩�C�m�F</li>
					<li>�����łȂ��Ƃ�</li>
					<ul>
						<li>relative_root��hop > this->hop �Ȃ�Chop = NO_SIGNAL�Ƃ��C�V����relative_root��T��</li>
						<li>�����łȂ��Ƃ�this->hop = relative_root->hop + 1�Ƃ���</li>
						<li>���X�Crelative_root�̑�ֈĂ�����΁C�������ɏ�芷�����������</li>
					</ul>
				</ul>
			</ul>
		@sa SAModule::Run
	 */
	virtual void Run();
protected:
	/**
		@brief Headquarter�ւ�Route��T��
	 */
	bool findHQ();
	/**
		@brief hop��relativeRoot���X�V����
		@return true : �����ƂȂ����Ă���, false : START�n�_�֖߂�
	 */
	bool update();
	/**
		@brief Random Generator. relative_root�̑�ֈĂ�T�����ǂ��������߂�ۂɗ��p����
	 */
	Random<boost::uniform_real<> > rand;
};

#endif	//_Cont_Link_To_HQ_HPP_