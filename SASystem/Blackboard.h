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

	/* Accessしやすいようにpublicにしちゃった */
	///入力信号Buffer
	float* inputs;
	///出力信号Buffer
	float* outputs;
	///入力信号ポート数
	int numOfInputPorts;
	///出力信号ポート数
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
	//入力信号Bufferを初期化
	//メモリの初期化
	inputs = new float[numberOfPorts];
	numOfInputPorts = numberOfPorts;
	//値の初期化
	for(int i = 0; i < numOfInputPorts; i++){
		inputs[i] = NO_SIGNAL;
	}
}

inline Blackboard::Blackboard(){
}

inline void Blackboard::createOutputPort(int numberOfPorts){
	//入力信号Bufferを初期化
	//メモリの初期化
	outputs = new float[numberOfPorts];
	numOfOutputPorts = numberOfPorts;
	//値の初期化
	for(int i = 0; i < numOfOutputPorts; i++){
		outputs[i] = NO_SIGNAL;
	}
}

#endif //_Blackboard_H_