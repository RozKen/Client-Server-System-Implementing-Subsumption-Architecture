#ifndef _SAModule_H_
#define _SAModule_H_

//無信号状態	NO_SIGNALをinclude
#include "Constants.h"
#include "Blackboard.h"

/**
	@class SAModule
	@brief ModuleのInterfaceクラス
	ModuleはState Machine，Actuator, Sensorの3種類を想定
	基本，inboxの信号を受け取って，Runすると，outboxに入れる信号を出力する
*/
class SAModule {
public:
	/**
		@brief Constructor. Initialize std::vector
	*/
	SAModule();
	/**
		@brief Destructor. Delete std::vector
	 */
	~SAModule();
	/**
		@brief モジュールを動作させる．
		純粋仮想関数．継承した子クラスでの定義が必須
	 */
	virtual void Run() = 0;

	/**
		@brief 入力ポートを追加する
		@param title 入力ポートの名前
	 */
	void addInput(std::string title);
	/**
		@brief 出力ポートを追加する
		@param title 出力ポートの名前
	 */
	void addOutput(std::string title);
	/**
		@brief memoryにおけるポート番号を追加する
		@param index 入力ポート番号
	 */
	void addInputIndex(int index);
	/**
		@brief memoryにおけるポート番号を追加する
		@param index 出力ポート番号
	 */
	void addOutputIndex(int index);

	///////////////Setters and Getters///////////////
	/**
		@brief 制御上，このModuleの親となるModuleを指定する
		基本的に，Blackboardは，親のものを利用する
		@sa Blackboard
	 */
	virtual void setParent(SAModule* parent);

	std::vector<std::string>* getInputTitles() const;
	std::vector<std::string>* getOutputTitles() const;

	/**
		@brief input信号を渡す．
		@param index 得る配列要素のindex
		@return input 入力信号の配列要素の値
	 */
	float getInput(int index) const;
	/**
		@brief outputを信号設定する
		@param output 出力信号の配列要素へ代入する値
		@param index 設定する配列要素のindex
	 */
	void setOutput(int index, float signal);
	/**
		@brief 入力信号ポート数を返す
		@return 入力信号ポート数
	 */
	int getNumOfInputPorts() const;
	/**
		@brief 出力信号ポート数を返す
		@return 出力信号ポート数
	 */
	int getNumOfOutputPorts() const;
	/**
		@brief 内部に持つ記憶領域へのポインタを返す
		@return 内部に持つ記憶領域
		@sa Blackboard
	 */
	Blackboard* getMemory() const;
	
protected:
	///SAModuleの入力値が格納されているmemory上のIndex
	std::vector<int> *inputIndex;
	///SAModuleの出力値が格納されているmemory上のIndex
	std::vector<int> *outputIndex;
	///Logにあたり，入力値を説明する名前
	std::vector<std::string> *inputTitles;
	///Logにあたり，出力値を説明する名前
	std::vector<std::string> *outputTitles;
	///入力信号ポート数
	int numOfInputPorts;
	///出力信号ポート数
	int numOfOutputPorts;
	///制御上，親に当たるモジュール
	SAModule* parent;
	///値の入出力に当たり，利用する記憶領域
	Blackboard* memory;
};

#endif //_SAModule_H_