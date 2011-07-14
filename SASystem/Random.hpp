#ifndef _Random_HPP_
#define _Random_HPP_

#include <boost/random.hpp>

/**
	Random生成クラス.
	オブジェクトを生成したら，"オブジェクト名()"でランダムな値をはき出す
	ランダムの生成はboost::mt19937によるメルセンヌツイスタ．一様分布
	@author n_shuyo
	@sa http://d.hatena.ne.jp/n_shuyo/20100407
 */

template<class D, class G = boost::mt19937>
class Rand{
public:
	///Default Constructor
	Rand() : _gen(static_cast<unsigned long>(time (0))),
		_rand(_gen, _dst){}
	///よく分からないけど，たぶん範囲を指定したコンストラクタ
	template<typename T1>
	Rand(T1 a1) : _gen(static_cast<unsigned long>(time(0))),
		_dst(a1), _rand(_gen, _dst){}
	///範囲を指定したコンストラクタ
	template<typename T1, typename T2>
	Rand(T1 a1, T2 a2): _gen(static_cast<unsigned long>(time(0))),
		_dst(a1, a2), _rand(_gen, _dst){}

	///RandObjectに"()"を付けると，ランダムな数値が戻ってくる
	typename D::result_type operator()(){
		return _rand();
	}
protected:
	///Random Generator
	G _gen;
	///Distribution Range
	D _dst;
	///Random Generator
	boost::variate_generator<G, D> _rand;
};

#endif //_Random_HPP_