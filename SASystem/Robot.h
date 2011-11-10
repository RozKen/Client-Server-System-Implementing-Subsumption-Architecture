#ifndef _Robot_H_
#define _Robot_H_

#include <vector>
#include "SAModule.h"
#include "Blackboard.h"

class Arbiter;

/**
	@class Robot
	@brief ロボット一体の動きを制御するモジュール.
	以前のSAServerに近い役割をするが，Blackboard Systemを実装してある

	inputs: sensorへの入力
	outputs: actuatorによる出力
	@sa SAModule
 */
class Robot : public SAModule{
public:
	/**
		@brief Constructor
	 */
	Robot();

	/**
		@brief Constructor
		@param inputPorts センサへの入力の数
		@param outputPorts アクチュエータによる出力の数
	 */
	Robot(int inputPorts, int outputPorts);

	/**
		@brief Mission: Operate a Robot
		<ol>
			<li>RunModules</li>
			<li>ProcessArbiters</li>
			<li>Log</li>
		</ol>
	 */
	void Run();

	/**
		@brief モジュールに入力ポートを作成する. 指定した個数を一回だけ作成する
		SAModuleのものを上書き
		@param numberOfPorts 作成する入力ポートの数
	 */
	virtual void createInputPort(int numberOfPorts);
	/**
		@brief モジュールに出力ポートを作成する.指定した個数を一回だけ作成する
		SAModuleのものを上書き
		@param numberOfPorts 作成する出力ポートの数
	 */
	virtual void createOutputPort(int numberOfPorts);
protected:
	/**
		@brief このRobot個体が持つ記憶領域 Internal Blackboard
	 */
	Blackboard* memory;
	/**
		@brief ロボット内のModuleをすべて実行する
	 */
	void RunModules();
	/**
		@brief すべてのArbiterを実行する
	 */
	void ProcessArbiters();
	/**
		@brief ログをとる
	 */
	void Log();
	/**
		@brief Initialize States
		環境の構築,ログの初期化
		@sa Blackboard
		@sa Log();
	*/
	void Initialize();
	/**
		@brief モジュールを登録する
		@sa SAModule
	 */
	void addModule(SAModule *module);
	/**
		@brief コネクターを登録する
		@sa Arbiter
	 */
	void addArbiter(Arbiter *arbiter);

	/**
		@brief 管理されているModule
		Moduleの登録された順に格納されている.
	*/
	std::vector<SAModule*> modules;

	/**
		@brief 登録されているArbiter
		Modifierの登録された順に格納されている.
	 */
	std::vector<Arbiter*> arbiters;

};

#endif _Robot_H_