#ifndef ProgressCounter_HPP_
#define ProgressCounter_HPP_

#include "SAModule.h"
#include "Constants.h"
#include "EnvUpdater.h"

/**
	@class ProgressCounter
	@brief ���݂̈ʒu�𒲂ׂĕԂ�
	@sa SAModule
 */
class ProgressCounter : public SAModule{
public:
	/**
		@brief Constructor
		outputs[0] : ���݈ʒu
	 */
	ProgressCounter(EnvUpdater* environment);
	/**
		@brief ���݂̈ʒu�𒲂ׂ�outputs�ɏo��
	 */
	void Run();
	/**
		@brief ���݂̈ʒu�𒲂ׂĕԂ�
	 */
	int getPosition();
protected:
	EnvUpdater* env;
};

inline ProgressCounter::ProgressCounter(EnvUpdater* environment)
	: env(environment){
}

inline void ProgressCounter::Run(){
	int pos = env->getPosition();
	//outputs[0] = pos;
	return;
}

inline int ProgressCounter::getPosition(){
	return env->getPosition();
}

#endif //ProgressCounter_HPP_