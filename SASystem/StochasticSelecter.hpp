#ifndef _StochasticSelector_HPP_
#define _StochasticSelector_HPP_

#include <ctime>
#include <boost/random.hpp>
#include "Random.hpp"

/**
	@class StochasticSelector
	@brief	�m���I��2�̂����̂ǂ��炩��I������I�u�W�F�N�g.
	get()���\�b�h��true/false�̒l��
	�ŏ��Ɏw�肵��probability�̊m���ŕԂ�
	@author Kenichi Yorozu
	@date 14th July 2011
	@sa Random
 */
class StochasticSelector{
public:
	/**
		�f�t�H���g�R���X�g���N�^.
		�m��0.5��true��Ԃ��悤�ȃI�u�W�F�N�g�𐶐�
	 */
	StochasticSelector();
	/**
		�R���X�g���N�^
		�m��probability��true��Ԃ��悤�ȃI�u�W�F�N�g�𐶐�
	 */
	StochasticSelector(float probability);
	/**
		�m���I�ɑI�����ꂽ���ʂ�Ԃ�
	 */
	bool get();
	/**
		get�֐��Ɠ��l�C�m���I�ɑI�����ꂽ���ʂ�Ԃ�
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