#ifndef _Arbiter_H_
#define _Arbiter_H_

#include "Random.hpp"
#include "SAModule.h"

/**
	@class Arbiter
	@brief Wire, Inhibitor, Suppressなどの記録
	Arbiterとしての統一表現を試みる
	@date 9th November 2011
	@author Kenichi Yorozu
 */
class Arbiter : public SAModule {
public:
	/**
		@brief Default Constructor
		とりあえずArbiterを作りたいときに利用.
	 */
	Arbiter();
	/**
		@brief factor = 0.0 - 1.0のランダムのArbiter
	 */
	Arbiter(SAModule* src, int srcPort, SAModule* dest, int destPort);
	/**
		@brief factor固定のArbiter
	 */
	Arbiter(SAModule* src, int srcPort, SAModule* dest, int destPort, float factor);
	/**
		@brief 指定範囲内factor固定のArbiter
	 */
	Arbiter(SAModule* src, int srcPort, SAModule* dest, int destPort, 
		float factor_min, float factor_max);
	/**
		@brief Transfer/Modify/Arbit Signal
		@sa generateSignal
	 */
	void Run();

	/**
		@brief set Source. addInputの代わりに利用
		@param src 接続元Module
		@param srcPort 接続元Module上の出力ポート番号
	 */
	void setSource(SAModule* src, int srcPort);
	/**
		@brief set Destination. addOutputの代わりに利用
		@param src 接続先Module
		@param srcPort 接続先Module上の入力ポート番号
	 */
	void setDestination(SAModule* dest, int destPort);
	
	/**
		@brief 接続先が元々持っている信号を得る
		@return 接続先が保持する信号
	 */
	float getDest() const;
	/**
		@brief 接続元が持っている信号を得る
		@return 接続元が保持する信号
	 */
	float getSrc() const;

	/**
		@brief 入力信号を得る．
		@return input 入力信号の配列要素の値
		@override SAModule::getInput
		@sa SAModule::getInput
	 */
	float getInput() const;
	/**
		@brief 入力信号を得る．
		@param index [disabled]得る配列要素のモジュール上の入力ポート番号
		@return input 入力信号の配列要素の値
		@override SAModule::getInput
		@sa SAModule::getInput
	 */
	float getInput(int index) const;
	/**
		@brief 出力信号を設定する
		@param output 出力信号の配列要素へ代入する値
		@override SAModule::setOutput
		@sa SAModule::setOutput
	 */
	void setOutput(float signal);
	/**
		@brief 出力信号を設定する
		@param output 出力信号の配列要素へ代入する値
		@param index [disabled]設定する配列要素のモジュール上の出力ポート番号
		@override SAModule::setOutput
		@sa SAModule::setOutput
	 */
	void setOutput(int index, float signal);

	/**
		@brief Getter of factor
		@sa factor
		@return factor
	 */
	float getFactor() const;
protected:
	/**
		@brief Generate Signal
		@return signal
	 */
	double generateSignal();

	///接続元のModuleへのポインタ
	SAModule* source;
	///接続先のModuleへのポインタ
	SAModule* destination;
	///接続元のModuleの出力ポート番号
	int srcPort;
	///接続先のModuleの入力ポート番号
	int destPort;
	///一回のModifyが有効な時間．単位はclock. nullの場合もある
	int timeToModify;
	///Modifyするかしないかを決めたりする確率
	float factor;
	///残りModify時間.
	int timeLeftModified;
	///ランダム一様分布生成器
	Random<boost::uniform_real<> > _rand;
};

inline float Arbiter::getFactor() const {
	return factor;
}

#endif	//_Arbiter_H_