#ifndef _SAServer_H_
#define _SAServer_H_

#include <fstream>

#define	NUM_MODULES	10		//Moduleの数

class SAModule;	//header内で変数を宣言するために，classを宣言
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
			<li>Run();</li>
			<li>Inhibit();</li>
			<li>Suppress();</li>
			<li>Log();</li>
		</ol>
		@sa Run()
		@sa Inhibit()
		@sa Suppress()
		@sa Log()
	 */
	void Process();

	/**
		@brief Initialize States
	*/
	void Initialize();

	protected:
	/**
		@brief Serverに登録されているすべてのModuleをRunする
		その他に，現在は両輪(LM, RM)のspeedを基に，位置と向きを算出し，
		それらをセンサーに送る．
	*/
	void Run();
	/**
		@brief 下層のModuleからの出力を抑制する.
		<ol>
			<li>inhibited[]の各要素から1を引く</li>
			<li>inhibited[]の値が-1であるものは，0に直し，</li>
			<li>probInhibition[][]に基づいてinhibited[]を更新する</li>
			<li>inhibited[]の値が正である要素をinhibitする</li>
		</ol>
		@sa inhibited[]
		@sa probInhibition[][]
	*/
	void Inhibit();
	/**
		@brief 下層のModuleへの入力を抑圧する.
		<ol>
			<li>suppressed[]の各要素から1を引く</li>
			<li>suppressed[]の値が-1であるものは，0に直し，</li>
			<li>probSuppression[][]に基づいてsuppressed[]を更新する</li>
			<li>suppressed[]の値が正である要素をsuppressする</li>
		</ol>
		@sa suppressed[]
		@sa probSuppression[][]
	*/
	void Suppress();

	/**
		@brief Log Datas
	*/
	void Log();

	/**
		@brief 次にModuleに送られる信号
		outbox ---[inhibit]-->connector---[suppress]--><b>inbox</b>-->Modules
		@sa outbox
		@sa connector
	*/
	float inbox[NUM_MODULES];
	/**
		@brief Moduleから送られてきた信号
		<b>outbox</b> ---[inhibit]-->connector---[suppress]-->inbox-->Modules
		@sa inbox
		@sa connector
	*/
	float outbox[NUM_MODULES];
	/**
		@brief Connectorを流れる信号.
		outbox ---[inhibit]--><b>connector</b>---[suppress]-->inbox-->Modules
		@sa outbox
		@sa inbox
	*/
	float connector[NUM_MODULES];

	/**
		@brief Inhibitionの確率行列
		<table width="200" border="1">
		  <tr>
			<td>&nbsp;</td>
			<td colspan="6">Inferior Layer</td>
		  </tr>
		  <tr>
			<td rowspan="6">Superior Layer</td>
		<td>0.0</td><td>0.0</td><td>0.0</td><td>0.0</td><td>0.0</td><td>0.0</td>
		  </tr>
		  <tr>
			<td>0.2</td><td>0.0</td><td>0.0</td><td>0.0</td><td>0.0</td><td>0.0</td>
		  </tr>
		  <tr>
			<td>0.0</td><td>0.3</td><td>0.0</td><td>0.0</td><td>0.0</td><td>0.0</td>
		  </tr>
		  <tr>
			<td>0.0</td><td>0.0</td><td>0.5</td><td>0.0</td><td>0.0</td><td>0.0</td>
		  </tr>
		  <tr>
			<td>0.0</td><td>0.0</td><td>0.0</td><td>0.7</td><td>0.0</td><td>0.0</td>
		  </tr>
		  <tr>
			<td>0.0</td><td>0.0</td><td>0.0</td><td>0.0</td><td>0.2</td><td>0.0</td>
		  </tr>
		</table>
		probInhibition[A][B] -> A inhibits B

		普通のSubsumption Architectureなら，行列である必要はない．
		一つ下の階層をInhibitする確率を知ればよいから，配列で良いはず
		けれど，同じ階層のものを作ったりするときに，行列が必要
	*/
	float probInhibition[NUM_MODULES][NUM_MODULES];
	/**
		@brief Suppressionの確率行列
		<table width="200" border="1">
		  <tr>
			<td>&nbsp;</td>
			<td colspan="6">Inferior Layer</td>
		  </tr>
		  <tr>
			<td rowspan="6">Superior Layer</td>
		<td>0.0</td><td>0.0</td><td>0.0</td><td>0.0</td><td>0.0</td><td>0.0</td>
		  </tr>
		  <tr>
			<td>0.2</td><td>0.0</td><td>0.0</td><td>0.0</td><td>0.0</td><td>0.0</td>
		  </tr>
		  <tr>
			<td>0.0</td><td>0.3</td><td>0.0</td><td>0.0</td><td>0.0</td><td>0.0</td>
		  </tr>
		  <tr>
			<td>0.0</td><td>0.0</td><td>0.5</td><td>0.0</td><td>0.0</td><td>0.0</td>
		  </tr>
		  <tr>
			<td>0.0</td><td>0.0</td><td>0.0</td><td>0.7</td><td>0.0</td><td>0.0</td>
		  </tr>
		  <tr>
			<td>0.0</td><td>0.0</td><td>0.0</td><td>0.0</td><td>0.2</td><td>0.0</td>
		  </tr>
		</table>
		probSuppression[A][B] -> A suppresses B

		普通のSubsumption Architectureなら，行列である必要はない．
		一つ下の階層をSuppressionする確率を知ればよいから，配列で良いはず
		けれど，同じ階層のものを作ったりするときに，行列が必要
	*/
	float probSuppression[NUM_MODULES][NUM_MODULES];

	/**
		@brief Inhibitする時間を指定する行列．単位はクロック
	*/
	int	timeInhibition[NUM_MODULES][NUM_MODULES];
	/**
		@brief Suppressする時間を指定する行列．単位はクロック
	*/
	int timeSuppression[NUM_MODULES][NUM_MODULES];

	/**
		@brief Inhibitされたままでいる残時間
	*/
	int inhibited[NUM_MODULES];
	/**
		@brief Suppressされたままでいる残時間
	*/
	int suppressed[NUM_MODULES];

	/**
		@brief 管理されているModule
	*/
	SAModule* modules[NUM_MODULES];

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