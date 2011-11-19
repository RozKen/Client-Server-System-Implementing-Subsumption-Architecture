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
	Arbiter(SAModule* src, int srcPort, SAModule* dest, int destPort);
	/**
		@brief factor�Œ��Arbiter
	 */
	Arbiter(SAModule* src, int srcPort, SAModule* dest, int destPort, float factor);
	/**
		@brief �w��͈͓�factor�Œ��Arbiter
	 */
	Arbiter(SAModule* src, int srcPort, SAModule* dest, int destPort, 
		float factor_min, float factor_max);
	/**
		@brief Transfer/Modify/Arbit Signal
		@sa generateSignal
	 */
	void Run();

	/**
		@brief set Source. addInput�̑���ɗ��p
		@param src �ڑ���Module
		@param srcPort �ڑ���Module��̏o�̓|�[�g�ԍ�
	 */
	void setSource(SAModule* src, int srcPort);
	/**
		@brief set Destination. addOutput�̑���ɗ��p
		@param src �ڑ���Module
		@param srcPort �ڑ���Module��̓��̓|�[�g�ԍ�
	 */
	void setDestination(SAModule* dest, int destPort);
	
	/**
		@brief �ڑ��悪���X�����Ă���M���𓾂�
		@return �ڑ��悪�ێ�����M��
	 */
	float getDest() const;
	/**
		@brief �ڑ����������Ă���M���𓾂�
		@return �ڑ������ێ�����M��
	 */
	float getSrc() const;

	/**
		@brief ���͐M���𓾂�D
		@return input ���͐M���̔z��v�f�̒l
		@override SAModule::getInput
		@sa SAModule::getInput
	 */
	float getInput() const;
	/**
		@brief ���͐M���𓾂�D
		@param index [disabled]����z��v�f�̃��W���[����̓��̓|�[�g�ԍ�
		@return input ���͐M���̔z��v�f�̒l
		@override SAModule::getInput
		@sa SAModule::getInput
	 */
	float getInput(int index) const;
	/**
		@brief �o�͐M����ݒ肷��
		@param output �o�͐M���̔z��v�f�֑������l
		@override SAModule::setOutput
		@sa SAModule::setOutput
	 */
	void setOutput(float signal);
	/**
		@brief �o�͐M����ݒ肷��
		@param output �o�͐M���̔z��v�f�֑������l
		@param index [disabled]�ݒ肷��z��v�f�̃��W���[����̏o�̓|�[�g�ԍ�
		@override SAModule::setOutput
		@sa SAModule::setOutput
	 */
	void setOutput(int index, float signal);

	/**
		@brief Getter of factor
		@sa factor
		@return factor
	 */
	float getFactor() const;
protected:
	/**
		@brief Generate Signal
		@return signal
	 */
	double generateSignal();

	///�ڑ�����Module�ւ̃|�C���^
	SAModule* source;
	///�ڑ����Module�ւ̃|�C���^
	SAModule* destination;
	///�ڑ�����Module�̏o�̓|�[�g�ԍ�
	int srcPort;
	///�ڑ����Module�̓��̓|�[�g�ԍ�
	int destPort;
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