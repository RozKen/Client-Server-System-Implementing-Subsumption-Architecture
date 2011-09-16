#ifndef _SAServer_H_
#define _SAServer_H_

#include <fstream>
#include <vector>

//#define	NUM_MODULES	10		//Moduleの数

class SAModule;	//header内で変数を宣言するために，classを宣言
class SAConnector;
class EnvUpdater;
/**
	@class SAServer
	@brief すべてのModuleの接続関係，Inhibition, Suppression関係を保持し，
	それに応じた信号の決定を管理するクラス
	1ClockごとにすべてのModuleを動かし，それぞれの出力を基に，
	次の入力を決めている
	@sa SAModule
 */
class SAServer{
public:

	/**
		@brief Construct SAServer. Initialize <b>clock</b> as 0
		<ol>
			<li>Initialize()</li>
		</ol>
		@sa clock
	*/
	SAServer();
	/**
		@brief 一クロック分制御を進める
		<ol>
			<li>RunModules();</li>
			<li>ProcessConnections();</li>
			<li>Log();</li>
			<li>clock++</li>
		</ol>
		@sa RunModules()
		@sa ProcessConnections()
		@sa Log()
	 */
	void Process();

	/**
		@brief Initialize States
		環境の構築,ログの初期化
		@sa EnvUpdater
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
		@sa SAConnector
	 */
	void addConnector(SAConnector *connector);

	/**
		@brief EnvUpdaterのGetter
	 */
	EnvUpdater* getEnv();

	protected:
	/**
		@brief Serverに登録されているすべてのModuleをRunする
		その他に，現在は両輪(LM, RM)のspeedを基に，位置と向きを算出し，
		それらをセンサーに送る．
		@sa SAModules
	*/
	void RunModules();

	/**
		@brief Serverに設定されている全てのWire, Inhibitor, Suppressorを処理する
		@sa SAConnector
	 */
	void ProcessConnectors();

	
	/**
		@brief Log Datas
	*/
	void Log();

	/**
		@brief 管理されているModule
		Moduleの登録された順に格納されている.
	*/
	std::vector<SAModule*> modules;

	/**
		@brief 登録されているModifiers
		Modifierの登録された順に格納されている.
	 */
	std::vector<SAConnector*> connectors;

	/**
		@brief Moduleが出力した信号＝Inhibit前の出力信号
	 */
	std::vector<float> outputs;
	/**
		@brief Inhibit後の出力信号
	 */
	std::vector<float> inhibited;
	/**
		@brief Suppress前の入力信号
	 */
	std::vector<float> preSuppress;
	/**
		@brief Moduleに入力される信号＝Suppress後の入力信号
	 */
	std::vector<float> inputs;
	/**
		@brief 暫定的に利用している環境
	*/
	EnvUpdater* env;

	/**
		@brief Logファイルの名前
	*/
	std::string logFileName;
	/**
		@brief Logファイル用，書き出しストリーム
	*/
	std::ofstream ofs;

	/**
		@brief 開始してからのclock数
	*/
	long int clock;
};

#endif //_SAServer_H_