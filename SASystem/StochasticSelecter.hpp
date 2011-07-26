#ifndef _StochasticSelector_HPP_
#define _StochasticSelector_HPP_

#include <ctime>
#include "Random.hpp"

/**
	@class StochasticSelector
	@brief 確率的に2つのうちのどちらかを選択するオブジェクト.
	get()メソッドはtrue/falseの値を
	最初に指定したprobabilityの確率で返す
	@author Kenichi Yorozu
	@date 14th July 2011
	@sa Random
 */
class StochasticSelector{
public:
	/**
		@brief デフォルトコンストラクタ.
		確率0.5でtrueを返すようなオブジェクトを生成
	 */
	StochasticSelector();
	/**
		@brief コンストラクタ
		確率probabilityでtrueを返すようなオブジェクトを生成
	 */
	StochasticSelector(float probability);
	/**
		@brief 確率的に結果を返す.
		<ul>
			<li>true: 選択された場合：与えられた確率に基づいて出現するのはこちら</li>
			<li>false: 選択されなかった場合</li>
		</ul>
	 */
	bool get();
	/**
		@brief get関数と同様，確率的に選択された結果を返す
		<ul>
			<li>true: 選択された場合：与えられた確率に基づいて出現するのはこちら</li>
			<li>false: 選択されなかった場合</li>
		</ul>
		@sa get()
	 */
	bool operator()();
private:
	///trueである確率
	float prob;
	//Random関数
	Random<boost::uniform_real<> > _rand;
};

StochasticSelector::StochasticSelector()
	:prob(0.5f), _rand(0, 1)
{}

StochasticSelector::StochasticSelector(float probability)
	:prob(probability), _rand(0, 1)
{
}

bool StochasticSelector::get(){
	if(_rand() <= prob){
		return true;
	}else{
		return false;
	}
}

bool StochasticSelector::operator()(){
	return get();
}
#endif //_StochasticSelector_HPP_