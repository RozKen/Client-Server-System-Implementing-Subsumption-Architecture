#ifndef SAConnector_H_
#define SAConnector_H_

#include "Random.hpp"

///無信号状態
#ifndef NO_SIGNAL	//先にSAModule.hで定義されているかも知れない
#define NO_SIGNAL	0.0f
#endif //NO_SIGNAL

#ifndef _StochasticSelector_HPP_
	class StochasticSelector;
#endif
/**
	@brief Wire, Inhibitor, Suppressorなどの配線．
 */
class SAConnector
{
public:
	
	/**
		@brief Default Constructor
	 */
	SAConnector(float* source, float* destination, int type);
	/**
		@brief Default Constructor for Modifiers
	 */
	SAConnector(float* source, float* destination, int type, int timeToModify);
	/**
		@brief Constructor for Original Modifiers
	 */
	SAConnector(float* source, float* destination, int type, int timeToModify, float probModify);
	/**
		@brief Constructor for Original Modifiers 2
	 */
	SAConnector(float* source, float* destination, int type, float probModify);

	/**
		@brief Transfer/Modify Signal
	 */
	void Process();

	/**
		@brief getter of type
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
	///
	StochasticSelector* ss;
	///
	Random<boost::uniform_real<> > _rand;
};

inline int SAConnector::getType() const{
	return type;
}

#endif //SAConnector_H_