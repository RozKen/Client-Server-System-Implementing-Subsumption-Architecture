#ifndef _World_H_
#define _World_H_

#include <vector>

#ifndef _Blackboard_H_
class Blackboard;
#endif
#ifndef _Robot_H_
class Robot;
#endif

/**
	@class World
	@brief
 */
class World{
public:
	/**
		@brief Constructor
	 */
	World();
	/**
		@brief ���E��1 [clock] �i�߂�
		<ol>
			<li>RunRobots()</li>
			<li>UpdateWorld()</li>
			<li>Log()</li>
			<li>clockCount++</li>
		</ol>
		@sa RunRobots()
		@sa UpdateWorld()
		@sa Log()
		@sa clockCount
	 */
	void Run();
protected:
	/**
		@brief World���̃��{�b�g�𓮂���
	 */
	void RunRobots();
	/**
		@brief �e���{�b�g����̏o�͂����ɁCWorld���č\��.
		�e���{�b�g����̏o�͂�Conflict����(Arbit)��C
		���{�b�g�̏Փ˂Ȃǂ������D
	 */
	void UpdateWorld();
	/**
		@brief Log Blackboard Data
		@sa environment
	 */
	void Log();
	/**
		@brief World��Blackboard. �^�X�N���Ɋւ���ϐ����������܂��
	 */
	Blackboard* environment;
	/**
		@brief World�ɑ��݂���Robot.
	 */
	std::vector<Robot *> robots;
	/**
		@brief Simulation�̌o��Clock
	 */
	int clockCount;
};

#endif	//_World_H_