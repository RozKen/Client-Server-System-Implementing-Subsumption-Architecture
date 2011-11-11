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

	Blackboard::Blackboard(int inputPortNum, int outputPortNum);

	/**
		@brief Update Internal World from inputs and set outputs according to the World
	*/
	void Update();

	/**
		@brief Log Blackboard Data into a File.
	 */
	void Log();
	/**
		@brief 入力Portを作成
		@param numberOfPorts 入力ポート数
	 */
	void createInputPort(int numberOfPorts);
	/**
		@brief 出力Portを作成
		@param bumberOfPorts 出力ポート数
	 */
	void createOutputPort(int numberOfPorts);

	/**** Accessしやすいようにpublicにしちゃった ****/
	///入力信号Buffer
	float* inputs;
	///出力信号Buffer
	float* outputs;
	///入力信号ポート数
	int numOfInputPorts;
	///出力信号ポート数
	int numOfOutputPorts;
protected:
};

inline Blackboard::Blackboard(): numOfInputPorts(0), numOfOutputPorts(0){
	createInputPort(numOfInputPorts);
	createOutputPort(numOfOutputPorts);
}

inline Blackboard::Blackboard(int inputPortNum, int outputPortNum)
	:numOfInputPorts(inputPortNum), numOfOutputPorts(outputPortNum){
	createInputPort(numOfInputPorts);
	createOutputPort(numOfOutputPorts);
}

#endif //_Blackboard_H_