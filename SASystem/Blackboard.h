#ifndef _Blackboard_H_
#define _Blackboard_H_

#include "Constants.h"

/**
	@class Blackboard
	@brief Base of Blackboard System. Hold Data and provide getter and setter.
	To provide semantic data to sensors, this class builds internal world
	from some data

	@sa H. Penny Nii, Blackboard Application Systems
		and a Knowledge Engineering Perspective (1986 AI Magazine vol. 7)

	@date 9th November 2011
	@author Kenichi Yorozu
 */
class Blackboard {
public:
	/**
		@brief Constructor
	*/
	Blackboard();

	/**
		@brief Update Internal World from inputs and set outputs according to the World
	*/
	void Update();

	/**
		@brief Log Datas on Blackboard.
	 */
	void Log();

	/* Access���₷���悤��public�ɂ�������� */
	///���͐M��Buffer
	float* inputs;
	///�o�͐M��Buffer
	float* outputs;
	///���͐M���|�[�g��
	int numOfInputPorts;
	///�o�͐M���|�[�g��
	int numOfOutputPorts;
protected:

	void createInputPort(int numberOfPorts);

	void createOutputPort(int numberOfPorts);
};

inline Blackboard::Blackboard(): numOfInputPorts(0), numOfOutputPorts(0){
	createInputPort(numOfInputPorts);
	createOutputPort(numOfOutputPorts);
}

inline void Blackboard::createInputPort(int numberOfPorts){
	//���͐M��Buffer��������
	//�������̏�����
	inputs = new float[numberOfPorts];
	numOfInputPorts = numberOfPorts;
	//�l�̏�����
	for(int i = 0; i < numOfInputPorts; i++){
		inputs[i] = NO_SIGNAL;
	}
}

inline Blackboard::Blackboard(){
}

inline void Blackboard::createOutputPort(int numberOfPorts){
	//���͐M��Buffer��������
	//�������̏�����
	outputs = new float[numberOfPorts];
	numOfOutputPorts = numberOfPorts;
	//�l�̏�����
	for(int i = 0; i < numOfOutputPorts; i++){
		outputs[i] = NO_SIGNAL;
	}
}

#endif //_Blackboard_H_