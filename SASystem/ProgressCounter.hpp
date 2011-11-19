#ifndef ProgressCounter_HPP_
#define ProgressCounter_HPP_

#include "SAModule.h"
#include "Constants.h"
#include "EnvUpdater.h"

/**
	@class ProgressCounter
	@brief 現在の位置を調べて返す
	@sa SAModule
 */
class ProgressCounter : public SAModule{
public:
	/**
		@brief Constructor
		outputs[0] : 現在位置
	 */
	ProgressCounter(EnvUpdater* environment);
	/**
		@brief 現在の位置を調べてoutputsに出力
	 */
	void Run();
	/**
		@brief 現在の位置を調べて返す
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