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
	Arbiter(float* source, float* destination);
	/**
		@brief factor固定のArbiter
	 */
	Arbiter(float* source, float* destination, float factor);
	/**
		@brief 指定範囲内factor固定のArbiter
	 */
	Arbiter(float* source, float* destination, 
		float factor_min, float factor_max);
	/**
		@brief set Source
	 */
	void setSource(float* source);
	/**
		@brief set Destination
	 */
	void setDestination(float* destination);
	/**
		@brief Transfer/Modify/Arbit Signal
		@sa generateSignal
	 */
	void Run();

	/**
		@brief Getter of factor
		@sa factor
		@return factor
	 */
	float getFactor() const;
protected:
	/**
		@brief Gnerate Signal
		@return signal
	 */
	double generateSignal();

	///接続元の要素へのポインタ
	float* source;
	///接続先の要素へのポインタ
	float* destination;
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