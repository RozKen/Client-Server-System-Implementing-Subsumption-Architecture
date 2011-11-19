#ifndef StepCounter_HPP_
#define StepCounter_HPP_

#include "SAModule.h"
#include "Constants.h"

/**
	@class StepCounter
	@brief 現在までに何ステップ経過したかを返す
	@sa SAModule
 */

class StepCounter : public SAModule{
public:
	/**
		@brief outputs[0] : 現在のstep数
	 */
	StepCounter();

	/**
		@brief outputsに現在のstep数を出力後，step++
	 */
	void Run();

	/**
		@brief getter of step
		@sa step
	 */
	int getStep();
protected:
	///経過ステップ数
	int step;
};

inline StepCounter::StepCounter() : step(0){
}

inline void StepCounter::Run(){
	//outputs[0] = step;
	step++;
}

inline int StepCounter::getStep(){
	return step;
}

#endif //StepCounter_HPP_