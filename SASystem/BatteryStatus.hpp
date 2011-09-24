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
	/**
		@brief getter of status
		@sa status
		@return status
	 */
	int getStatus();
protected:
	///環境へのポインタ
	EnvUpdater* env;
	///Battery Status (残量 [%])
	int status;
};

inline BatteryStatus::BatteryStatus(EnvUpdater* environment)
	: SAModule(0, 1), env(environment), status(100){
}

inline void BatteryStatus::Run(){
	status = env->getBattery();
	outputs[0] = status;
	return;
}

inline int BatteryStatus::getStatus(){
	return status;
}
#endif //BatteryStatus_HPP_