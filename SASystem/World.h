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
		@brief 世界を1 [clock] 進める
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
		@brief World中のロボットを動かす
	 */
	void RunRobots();
	/**
		@brief 各ロボットからの出力を元に，Worldを再構成.
		各ロボットからの出力のConflict解消(Arbit)や，
		ロボットの衝突などを扱う．
	 */
	void UpdateWorld();
	/**
		@brief Log Blackboard Data
		@sa environment
	 */
	void Log();
	/**
		@brief WorldのBlackboard. タスク環境に関する変数が書き込まれる
	 */
	Blackboard* environment;
	/**
		@brief Worldに存在するRobot.
	 */
	std::vector<Robot *> robots;
	/**
		@brief Simulationの経過Clock
	 */
	int clockCount;
};

#endif	//_World_H_