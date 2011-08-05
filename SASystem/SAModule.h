#ifndef _SAModule_H_
#define _SAModule_H_
/**
	@class SAModule
	@brief ModuleのInterfaceクラス
	ModuleはState Machine，Actuator, Sensorの3種類を想定
	基本，inboxの信号を受け取って，Runすると，outboxに入れる信号を出力する
*/
class SAModule {
public:
	/**
		@brief コンストラクタ.何もしないよ
	*/
	SAModule();
	/**
		@brief モジュールを動作させる
		純粋仮想関数．継承した子クラスでの定義が必須
		@param	signal 入力信号
		@return 信号出力
	*/
	virtual float Run(float signal) = 0;

	/**
	 * @fn SignalDecoder
	 * @brief 一つのfloat型の値から二つの信号を抽出する.
	 * @param input 入力値
	 * @param output1 出力値1
	 * @param output2 出力値2
	 */

	void SignalDecoder(float input, float &output1, float &output2);
	/**
	 * @fn SignalEncoder
	 * @brief 2つのfloat型の値から1つの信号を生成する.
	 * @param input1 入力値1
	 * @param input2 入力値2
	 * @return output 出力値
	 */
	float SignalEncoder(float input1, float input2);
protected:
};

#endif //_SAModule_H_