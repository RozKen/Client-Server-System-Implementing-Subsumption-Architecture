#ifndef StepCounter_HPP_
#define StepCounter_HPP_

#include "SAModule.h"
#include "Constants.h"

/**
	@class StepCounter
	@brief ���݂܂łɉ��X�e�b�v�o�߂�������Ԃ�
	@sa SAModule
 */

class StepCounter : public SAModule{
public:
	/**
		@brief outputs[0] : ���݂�step��
	 */
	StepCounter();

	/**
		@brief outputs�Ɍ��݂�step�����o�͌�Cstep++
	 */
	void Run();

	/**
		@brief getter of step
		@sa step
	 */
	int getStep();
protected:
	///�o�߃X�e�b�v��
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