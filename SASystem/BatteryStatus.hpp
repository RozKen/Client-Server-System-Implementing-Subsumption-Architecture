#ifndef BatteryStatus_HPP_
#define BatteryStatus_HPP_

#include "SAModule.h"
#include "Constants.h"
#include "EnvUpdater.h"

/**
	@class BatteryStatus
	@brief バッテリーの状態を取得して出力するセンサ
 */
class BatteryStatus : public SAModule{
public:
	/**
		@brief Constructor
		outputs[0] : バッテリー状態
	 */
	BatteryStatus(EnvUpdater* environment);

	/**
		@brief バッテリー状態を取得して出力する
	 */
	void Run();

protected:
	EnvUpdater* env;
};

inline BatteryStatus::BatteryStatus(EnvUpdater* environment)
	: SAModule(0, 1), env(environment){
}

inline void BatteryStatus::Run(){
	outputs[0] = env->getBattery();
	return;
}
#endif //BatteryStatus_HPP_