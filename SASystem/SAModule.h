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
		@brief ログをとる
	 */
	virtual void Log();
	/**
		@brief 入力ポートを追加する
		@param title 入力ポートの名前
	 */
	virtual void addInput(std::string title);
	/**
		@brief 出力ポートを追加する
		@param title 出力ポートの名前
	 */
	virtual void addOutput(std::string title);
	virtual void addIBoard(std::string title);
	virtual void addFBoard(std::string title);
	/**
		@brief memoryにおけるポート番号を追加する
		@param index 入力ポート番号
	 */
	virtual void addInputIndex(int index);
	/**
		@brief memoryにおけるポート番号を追加する
		@param index 出力ポート番号
	 */
	virtual void addOutputIndex(int index);

	virtual void addIBoardIndex(int index);
	virtual void addFBoardIndex(int index);

	///////////////Setters and Getters///////////////
	/**
		@brief 制御上，このModuleの親となるModuleを指定する
		基本的に，Blackboardは，親のものを利用する
		@param parent 親モジュール
		@sa Blackboard
	 */
	virtual void setParent(SAModule* parent);
	/**
		@brief 親モジュールを得る
		@return 親モジュール
	 */
	virtual SAModule* getParent() const;
	/**
		@brief このモジュールの入力ポート名の配列を返す
		@return 入力ポート名の配列へのポインタ
	 */
	virtual std::vector<std::string>* getInputTitles() const;
	/**
		@brief このモジュールの出力ポート名の配列を返す
		@return 出力ポート名の配列へのポインタ
	 */
	virtual std::vector<std::string>* getOutputTitles() const;
	/**
		@brief このモジュールのindexOnModule番目の入力ポートが，
		memory上のどの出力ポートと繋がっているか？を返す
		@param indexOnModule モジュールの入力ポート番号
		@return memory上の出力ポート番号
	 */
	virtual std::vector<std::string>* getIBoardTitles() const;
	virtual std::vector<std::string>* getFBoardTitles() const;

	virtual int	getInputIndex(int indexOnModule) const;
	/**
		@brief このモジュールのindexOnModule番目の出力ポートが，
		memory上のどの入力ポートと繋がっているか？を返す
		@param indexOnModule モジュールの出力ポート番号
		@return memory上の入力ポート番号
	 */
	virtual int getOutputIndex(int indexOnModule) const;
	virtual int getIBoardIndex(int indexOnModule) const;
	virtual int getFBoardIndex(int indexOnModule) const;
	/**
		@brief 入力信号を渡す．
		@param index 得る配列要素のモジュール上の入力ポート番号
		@return input 入力信号の配列要素の値
	 */
	virtual float getInput(int index) const;
	/**
		@brief 出力信号を設定する
		@param index 設定する配列要素のモジュール上の出力ポート番号
		@param output 出力信号の配列要素へ代入する値
	 */
	virtual void setOutput(int index, float signal);
	///iBoardとfBoardは，innerMemoryのものにアクセスする
	virtual int getIBoard(int index) const;
	virtual float getFBoard(int index) const;
	virtual void setIBoard(int index, int signal);
	virtual void setFBoard(int index, float signal);

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
		@brief 親の持つ記憶領域へのポインタを返す
		@return 親の持つ記憶領域へのポインタ
		@sa Blackbaord
	 */
	Blackboard* getMemory() const;
	/**
		@brief 内部に持つ記憶領域へのポインタを返す
		@return 内部に持つ記憶領域
		@sa Blackboard
	 */
	Blackboard* getInnerMemory() const;
	
protected:
	///SAModuleの入力値が格納されているmemory上のIndex
	std::vector<int> *inputIndex;
	///SAModuleの出力値が格納されているmemory上のIndex
	std::vector<int> *outputIndex;
	std::vector<int> *iBoardIndex;
	std::vector<int> *fBoardIndex;
	///Logにあたり，入力値を説明する名前
	std::vector<std::string> *inputTitles;
	///Logにあたり，出力値を説明する名前
	std::vector<std::string> *outputTitles;
	std::vector<std::string> *iBoardTitles;
	std::vector<std::string> *fBoardTitles;
	///入力信号ポート数
	int numOfInputPorts;
	///出力信号ポート数
	int numOfOutputPorts;
	///制御上，親に当たるモジュール
	SAModule* parent;
	///自分の保持する値を格納するための，親の記憶領域
	Blackboard* memory;
	///値の入出力に当たり，利用する記憶領域
	Blackboard* innerMemory;
	/**
		@brief int型の変数をstring型に変換して変えす関数
		@param num 変換したい数値
		@return string型になった数値
	 */
	std::string intToString(int num);
	/**
		@brief float型の値を四捨五入してint型にする
		@param value 四捨五入したい値
		@return 四捨五入された値
	 */
	int round(float value);
};

#endif //_SAModule_H_