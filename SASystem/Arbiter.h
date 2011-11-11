#ifndef _Arbiter_H_
#define _Arbiter_H_

#include "Random.hpp"
#include "SAModule.h"

/**
	@class Arbiter
	@brief Wire, Inhibitor, Suppress�Ȃǂ̋L�^
	Arbiter�Ƃ��Ă̓���\�������݂�
	@date 9th November 2011
	@author Kenichi Yorozu
 */
class Arbiter : public SAModule {
public:
	/**
		@brief Default Constructor
		�Ƃ肠����Arbiter����肽���Ƃ��ɗ��p.
	 */
	Arbiter();
	/**
		@brief factor = 0.0 - 1.0�̃����_����Arbiter
	 */
	Arbiter(float* source, float* destination);
	/**
		@brief factor�Œ��Arbiter
	 */
	Arbiter(float* source, float* destination, float factor);
	/**
		@brief �w��͈͓�factor�Œ��Arbiter
	 */
	Arbiter(float* source, float* destination, 
		float factor_min, float factor_max);
	/**
		@brief set Source
	 */
	void setSource(float* source);
	/**
		@brief set Destination
	 */
	void setDestination(float* destination);
	/**
		@brief Transfer/Modify/Arbit Signal
		@sa generateSignal
	 */
	void Run();

	/**
		@brief Getter of factor
		@sa factor
		@return factor
	 */
	float getFactor() const;
protected:
	/**
		@brief Gnerate Signal
		@return signal
	 */
	double generateSignal();

	///�ڑ����̗v�f�ւ̃|�C���^
	float* source;
	///�ڑ���̗v�f�ւ̃|�C���^
	float* destination;
	///����Modify���L���Ȏ��ԁD�P�ʂ�clock. null�̏ꍇ������
	int timeToModify;
	///Modify���邩���Ȃ��������߂��肷��m��
	float factor;
	///�c��Modify����.
	int timeLeftModified;
	///�����_����l���z������
	Random<boost::uniform_real<> > _rand;
};

inline float Arbiter::getFactor() const {
	return factor;
}

#endif	//_Arbiter_H_