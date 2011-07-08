#ifndef _SAModule_H_
#define _SAModule_H_
/**
	ModuleのInterfaceクラス
	ModuleはState Machine，Actuator, Sensorの3種類を想定
	基本，inboxの信号を受け取って，Runすると，outboxに入れる信号を出力する
*/
class SAModule {
public:
	/**
		コンストラクタ
	*/
	SAModule();
	/**
		モジュールを動作させる
		@param	signal 入力信号
		@return 信号出力
	*/
	virtual float Run(float signal);
protected:
};

#endif //_SAModule_H_