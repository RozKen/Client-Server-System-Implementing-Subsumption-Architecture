#ifndef _SAServer_H_
#define _SAServer_H_

#define	NUM_MODULES	7		//Moduleの数

class SAModule;	//header内で変数を宣言するために，classを宣言
/**
	すべてのModuleの接続関係，Inhibition, Suppression関係を保持し，
	それに応じた信号の決定を管理するクラス
	1ClockごとにすべてのModuleを動かし，それぞれの出力を基に，
	次の入力を決めている
	@sa SAModule
 */
class SAServer{
public:
	/**
		Construct and Run SAServer
		<ol>
			<li>Initialize()</li>
		</ol>
	*/
	SAServer();
	/**
		一クロック分制御を進める
		<ol>
			<li>Run();</li>
			<li>Inhibit();</li>
			<li>Suppress();</li>
		</ol>
	 */
	void Process();
protected:
	/**
		Initialize States
	*/
	void Initialize();
	/**
		Serverに登録されているすべてのModuleをRunする
	*/
	void Run();
	/**
		下層のModuleを抑制する.
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
		下層のModuleを抑圧する.
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
		次にModuleに送られる信号
	*/
	float inbox[NUM_MODULES];
	/**
		Moduleから送られてきた信号
	*/
	float outbox[NUM_MODULES];

	/**
		Inhibitionの確率行列
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
		普通のSubsumption Architectureなら，行列である必要はない．
		一つ下の階層をInhibitする確率を知ればよいから，配列で良いはず
		けれど，同じ階層のものを作ったりするときに，行列が必要
	*/
	float probInhibition[NUM_MODULES][NUM_MODULES];
	/**
		Suppressionの確率行列
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
		普通のSubsumption Architectureなら，行列である必要はない．
		一つ下の階層をSuppressionする確率を知ればよいから，配列で良いはず
		けれど，同じ階層のものを作ったりするときに，行列が必要
	*/
	float probSuppression[NUM_MODULES][NUM_MODULES];

	/**
		Inhibitされたままでいる残時間
	*/
	int inhibited[NUM_MODULES];
	/**
		Suppressされたままでいる残時間
	*/
	int suppressed[NUM_MODULES];

	/**
		管理されているModule
	*/
	SAModule* modules[NUM_MODULES];
};

#endif //_SAServer_H_