#ifndef _Connector_H_
#define _Connector_H_

#include "Random.hpp"
#include "SAModule.h"

/**
	@class Connector
	@brief Wire, Inhibitor, Suppressなどの記録
	Arbiterとしての統一表現を試みる
	@date 9th November 2011
	@author Kenichi Yorozu
 */
class Connector : public SAModule {
public:
	/**
		@brief Default Constructor
	 */
	Connector();
	/**
		@brief
	 */
	Connector(float* source, float* destination, int type);

	void setSource(float* source);
	void setDestination(float* destination);
	/**
		@brief Transfer/Modify/Arbit Signal
	 */
	void Run();

	/**
		@brief getter of type
		@sa type
	 */
	int getType() const;
protected:
	///接続元の要素へのポインタ
	float* source;
	///接続先の要素へのポインタ
	float* destination;
	/**
		@brief 接続の方法.
		<ul>
			<li>Wire = 0</li>
			<li>Inhibit = 1</li>
			<li>Suppress = 2</li>
			<li>...Modified Suppress...</li>
		</ul>
	 */
	int type;
	///一回のModifyが有効な時間．単位はclock. nullの場合もある
	int timeToModify;
	///Modifyするかしないかを決めたりする確率．nullの場合もある
	float probModify;
	///残りModify時間.
	int timeLeftModified;
	///ランダム一様分布生成器
	Random<boost::uniform_real<> > _rand;
};

inline int Connector::getType() const {
	return type;
}

#endif	//_Connector_H_