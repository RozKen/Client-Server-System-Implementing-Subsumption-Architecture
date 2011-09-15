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
	SAModule(int numberOfInputPorts, int numberOfOutputPorts);
	/**
		@brief モジュールを動作させる
		純粋仮想関数．継承した子クラスでの定義が必須
		@param	signal 入力信号
		@return 信号出力
	*/
	virtual float Run(float signal) = 0;
	//現在の所，一応残しておく

	/**
		@brief モジュールを動作させる．
		純粋仮想関数．継承した子クラスでの定義が必須
	 */
	virtual void Run() = 0;

	/**
		@brief モジュールに入力ポートを作成する
		@param numberOfPorts 作成する入力ポートの数
	 */
	void createInputPort(int numberOfPorts);

	/**
		@brief モジュールに出力ポートを作成する.指定した個数を一回だけ作成する
		@param numberOfPorts 作成する出力ポートの数
	 */
	void createOutputPort(int numberOfPorts);
	/**
		@brief inputsへのポインタを与える.SAConnectorの接続へ利用する.
		@return *inputs
		@sa SAConnector
	 */
	float* getInputsPtr();
	/**
		@brief outputsへのポインタを与える.SAConnectorの接続へ利用する.
		@return *outputs
		@sa SAConnector
	 */
	float* getOutputsPtr();
	/**
		@brief input信号を設定する．
		@param input 入力信号の配列要素へ代入する値
		@param index 設定する配列要素のindex
	 */
	void setInput(float inputSignal, int index);
	/**
		@brief input信号を渡す．
		@param index 得る配列要素のindex
		@return input 入力信号の配列要素の値
	 */
	float getInput(int index);
	/**
		@brief outputを信号設定する
		@param output 出力信号の配列要素へ代入する値
		@param index 設定する配列要素のindex
	 */
	void setOutput(float outputSignal, int index);
	/**
		@brief output信号を渡す
		@param index 得る配列要素のindex
		@return outputs
	 */
	float getOutput(int index);

	
protected:
	///入力信号Buffer
	float* inputs;
	///出力信号Nuffer
	float* outputs;
};

inline SAModule::SAModule(){
}

inline SAModule::SAModule(int numberOfInputPorts, int numberOfOutputPorts){
	//信号Bufferを初期化
	inputs = new float[numberOfInputPorts];
	outputs = new float[numberOfOutputPorts];
}

inline void SAModule::createInputPort(int numberOfPorts){
	//入力信号Bufferを初期化
	inputs = new float[numberOfPorts];
}

inline void SAModule::createOutputPort(int numberOfPorts){
	//入力信号Bufferを初期化
	outputs = new float[numberOfPorts];
}

inline float* SAModule::getInputsPtr(){
	return inputs;
}

inline float* SAModule::getOutputsPtr(){
	return outputs;
}

inline void SAModule::setInput(float inputSignal, int index){
	inputs[index] = inputSignal;
}

inline float SAModule::getInput(int index){
	return inputs[index];
}

inline void SAModule::setOutput(float outputSignal, int index){
	outputs[index] = outputSignal;
}

inline float SAModule::getOutput(int index){
	return outputs[index];
}
#endif //_SAModule_H_