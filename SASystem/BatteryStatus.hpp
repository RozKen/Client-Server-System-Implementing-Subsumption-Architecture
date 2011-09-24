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
	/**
		@brief getter of status
		@sa status
		@return status
	 */
	int getStatus();
protected:
	///���ւ̃|�C���^
	EnvUpdater* env;
	///Battery Status (�c�� [%])
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