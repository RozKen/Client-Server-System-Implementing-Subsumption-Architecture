#ifndef PositionUpdater_HPP_
#define PositionUpdater_HPP_

#include "SAModule.h"
#include "EnvUpdater.h"
#include "Constants.h"

/**
	@class PositionUpdater
	@brief Controller�̐M�������ƂɌ��݈ʒu���Z�o���郂�W���[��
	inputs[0] : progress
 */
class PositionUpdater : public SAModule{
public:
	/**
		@brief Constructor
		inputs[0] : progress
	 */
	PositionUpdater();
	/**
		@brief ���͂�progress�����ɁC���݈ʒu���Z�o
	 */
	void Run();
	/**
		@brief getter of position
		@sa position
	 */
	int getPosition();
protected:
	/**
		@brief ���݈ʒu
	 */
	int position;
};

inline PositionUpdater::PositionUpdater() : SAModule(1, 0), position(0){
}

inline void PositionUpdater::Run(){
	position += inputs[0];
}

#endif //PositionUpdater_HPP_