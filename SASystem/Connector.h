#ifndef _Connector_H_
#define _Connector_H_

#include "Random.hpp"
#include "SAModule.h"

/**
	@class Connector
	@brief Wire, Inhibitor, Suppress�Ȃǂ̋L�^
	Arbiter�Ƃ��Ă̓���\�������݂�
	@date 9th November 2011
	@author Kenichi Yorozu
 */
class Connector : public SAModule {
public:
	/**
		@brief Default Constructor
	 */
	Connector();
	/**
		@brief
	 */
	Connector(float* source, float* destination, int type);

	void setSource(float* source);
	void setDestination(float* destination);
	/**
		@brief Transfer/Modify/Arbit Signal
	 */
	void Run();

	/**
		@brief getter of type
		@sa type
	 */
	int getType() const;
protected:
	///�ڑ����̗v�f�ւ̃|�C���^
	float* source;
	///�ڑ���̗v�f�ւ̃|�C���^
	float* destination;
	/**
		@brief �ڑ��̕��@.
		<ul>
			<li>Wire = 0</li>
			<li>Inhibit = 1</li>
			<li>Suppress = 2</li>
			<li>...Modified Suppress...</li>
		</ul>
	 */
	int type;
	///����Modify���L���Ȏ��ԁD�P�ʂ�clock. null�̏ꍇ������
	int timeToModify;
	///Modify���邩���Ȃ��������߂��肷��m���Dnull�̏ꍇ������
	float probModify;
	///�c��Modify����.
	int timeLeftModified;
	///�����_����l���z������
	Random<boost::uniform_real<> > _rand;
};

inline int Connector::getType() const {
	return type;
}

#endif	//_Connector_H_