#ifndef _FieldConnectorTester_H_
#define _FieldConnectorTester_H_

#include <string>

/**
	@class FieldConnectorTester
	@brief 与えられたfieldを用いてテストをするクラス
	Testを呼ぶ際に，試行回数，一回の試行のclock数などを指定する
	@date 18th October 2011
	@author Kenichi Yorozu
 */
class FieldConnectorTester{
public:
	/**
		@brief Constructor
		@param field フィールド
		@param mode TestするConnectorのMode
		<ol>
			<li>Inhibitor</li>
			<li>Suppressor</li>
			<li>Probability-based Selector</li>
			<li>Probability-based Superposer</li>
		</ol>
		default: Wire
	 */
	FieldConnectorTester(const int* field, int mode);
	/**
		@brief Battery間の最大の距離を計測
		@param field フィールド
		@return Battery間の最大の距離
	 */
	int maxBatteryDistance();
	/**
		@brief Battery間の最小の距離を計測
		@param field フィールド
		@return Battery間の最小の距離
	 */
	int minBatteryDistance();
	/**
		@brief Battery間の平均の距離を計測
		@param field フィールド
		@return Battery間の平均距離
	 */
	double averageBatteryDistance();
	/**
		@brief Field内のBatteryを数え上げる
		@return Field中に含まれるBatteryの数
	 */
	int countNumOfBatteries();
	/**
		@brief Execute Test
		maxTime = 100
		maxCount = 70 * 3  = 210
		としたデフォルトのテスト
	 */
	void Test();
	/**
		@brief Execute Test
		@param maxTime 試行回数
		@param maxCount 一回の試行のclock数
	 */
	void Test(int maxTime, int maxCount);
protected:
	///タスクフィールド
	const int* field;
	///TestするConnectorのMode
	int mode;
	///Batteryの数
	int numOfBattery;
	///ログファイル名
	std::string testLogFileName;
	///ログ記録フォルダpath
	std::string testLogDirectoryPath;
	///現在のclock数
	int count;
	///ゴールにたどり着いた試行の数
	int numOfSuccess;
	///ゴール到達までの平均clock数
	double aveSuccessClock;
	///平均の進んだ距離
	double aveDistance;
	///最大バッテリー間距離
	int maxBatD;
	///最小バッテリー間距離
	int minBatD;
	///平均バッテリー間距離
	double aveBatD;
};

#endif	//_FieldConnectorTester_H_