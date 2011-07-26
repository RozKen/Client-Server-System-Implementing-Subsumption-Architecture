#ifndef _StochasticSelector_HPP_
#define _StochasticSelector_HPP_

#include <ctime>
#include "Random.hpp"

/**
	@class StochasticSelector
	@brief �m���I��2�̂����̂ǂ��炩��I������I�u�W�F�N�g.
	get()���\�b�h��true/false�̒l��
	�ŏ��Ɏw�肵��probability�̊m���ŕԂ�
	@author Kenichi Yorozu
	@date 14th July 2011
	@sa Random
 */
class StochasticSelector{
public:
	/**
		@brief �f�t�H���g�R���X�g���N�^.
		�m��0.5��true��Ԃ��悤�ȃI�u�W�F�N�g�𐶐�
	 */
	StochasticSelector();
	/**
		@brief �R���X�g���N�^
		�m��probability��true��Ԃ��悤�ȃI�u�W�F�N�g�𐶐�
	 */
	StochasticSelector(float probability);
	/**
		@brief �m���I�Ɍ��ʂ�Ԃ�.
		<ul>
			<li>true: �I�����ꂽ�ꍇ�F�^����ꂽ�m���Ɋ�Â��ďo������̂͂�����</li>
			<li>false: �I������Ȃ������ꍇ</li>
		</ul>
	 */
	bool get();
	/**
		@brief get�֐��Ɠ��l�C�m���I�ɑI�����ꂽ���ʂ�Ԃ�
		<ul>
			<li>true: �I�����ꂽ�ꍇ�F�^����ꂽ�m���Ɋ�Â��ďo������̂͂�����</li>
			<li>false: �I������Ȃ������ꍇ</li>
		</ul>
		@sa get()
	 */
	bool operator()();
private:
	///true�ł���m��
	float prob;
	//Random�֐�
	Random<boost::uniform_real<> > _rand;
};

StochasticSelector::StochasticSelector()
	:prob(0.5f), _rand(0, 1)
{}

StochasticSelector::StochasticSelector(float probability)
	:prob(probability), _rand(0, 1)
{
}

bool StochasticSelector::get(){
	if(_rand() <= prob){
		return true;
	}else{
		return false;
	}
}

bool StochasticSelector::operator()(){
	return get();
}
#endif //_StochasticSelector_HPP_