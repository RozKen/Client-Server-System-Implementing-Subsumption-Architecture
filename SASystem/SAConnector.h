#ifndef SAConnector_H_
#define SAConnector_H_

#include "Random.hpp"

///���M�����
#ifndef NO_SIGNAL	//���SAModule.h�Œ�`����Ă��邩���m��Ȃ�
#define NO_SIGNAL	0.0f
#endif //NO_SIGNAL

#ifndef _StochasticSelector_HPP_
	class StochasticSelector;
#endif
/**
	@brief Wire, Inhibitor, Suppressor�Ȃǂ̔z���D
 */
class SAConnector
{
public:
	
	/**
		@brief Default Constructor
	 */
	SAConnector(float* source, float* destination, int type);
	/**
		@brief Default Constructor for Modifiers
	 */
	SAConnector(float* source, float* destination, int type, int timeToModify);
	/**
		@brief Constructor for Original Modifiers
	 */
	SAConnector(float* source, float* destination, int type, int timeToModify, float probModify);
	/**
		@brief Constructor for Original Modifiers 2
	 */
	SAConnector(float* source, float* destination, int type, float probModify);

	/**
		@brief Transfer/Modify Signal
	 */
	void Process();

	/**
		@brief getter of type
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
	///
	StochasticSelector* ss;
	///
	Random<boost::uniform_real<> > _rand;
};

inline int SAConnector::getType() const{
	return type;
}

#endif //SAConnector_H_