#ifndef BatteryStatus_HPP_
#define BatteryStatus_HPP_

#include "SAModule.h"
#include "Constants.h"
#include "EnvUpdater.h"

/**
	@class BatteryStatus
	@brief �o�b�e���[�̏�Ԃ��擾���ďo�͂���Z���T
 */
class BatteryStatus : public SAModule{
public:
	/**
		@brief Constructor
		outputs[0] : �o�b�e���[���
	 */
	BatteryStatus(EnvUpdater* environment);

	/**
		@brief �o�b�e���[��Ԃ��擾���ďo�͂���
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