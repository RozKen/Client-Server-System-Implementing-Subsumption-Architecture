#ifndef Alive_HPP_
#define Alive_HPP_

#include "SAModule.h"
#include "Constants.h"

/**
	@brief Mission: バッテリーをゼロにしない
	<ol>
		<li>現在バッテリー上で，Battery Status < 100%のとき，出力=0</li>
		<li>視界内にBattery Chargerがあるとき，そこまで進むよう出力</li>
		<li>その他の時，出力=0</li>
	</ol>
 */
class Alive : public SAModule {
public:
	/**
		@brief Constructor
		<ul>
			<li>outputs[0] : 移動先の相対位置</li>
			<li>inputs[0] - inputs[10] : Vision Scope</li>
			<li>inputs[11] : Battery Status</li>
		</ul>
	 */
	Alive();
	/**
		@brief Mission: バッテリーをゼロにしない
		<ol>
			<li>現在バッテリー上で，Battery Status < 100%のとき，出力=0</li>
			<li>視界内にBattery Chargerがあるとき，そこまで進むよう出力</li>
			<li>その他の時，出力=0</li>
		</ol>
	 */
	void Run();
protected:
	/**
		@brief 見えている範囲(RANGEVISION内)にBattery Chargerがあるか
		確認する
		@return Battery Chargerの有無
	 */
	bool isChargerExist();
	/**
		@brief 最近傍のBatteryChargerを探し，相対位置を返す
		現在Charger上であることは想定していない．
		@return 最近傍のBatteryChargerの相対位置
	 */
	int findNearestCharger();
	///バッテリー残量
	int battery;
	///見えているもの
	int vision[RANGEVISION];
	///現在位置のvision配列上のindex
	int CURRENT;
	///発火制御Counter
	int count;
};

inline Alive::Alive()
	: SAModule(RANGEVISION + 1, 1), battery(0), CURRENT((RANGEVISION - 1) / 2), count(0){
	for(int i = 0; i < RANGEVISION; i++){
		vision[i] = 0;
		inputs[i] = 0;
	}
	vision[CURRENT] = ONSTART;
	inputs[CURRENT] = ONSTART;
	inputs[RANGEVISION] = 100;
}
inline void Alive::Run(){
	if(count % 3 == 0){
		//Inputeからの情報で内部変数を更新
		for(int i = 0; i < RANGEVISION; i++){
			vision[i] = inputs[i];
		}
		battery = inputs[RANGEVISION];

		if(vision[CURRENT] == ONCHARGER && battery < 100){
			outputs[0] = 0;
		}else if(isChargerExist()){
			outputs[0] = findNearestCharger();
		}else{
			outputs[0] = 0;
		}
	}else{
		outputs[0] = 0;
	}
	count++;
}

inline bool Alive::isChargerExist(){
	for(int i = 0; i < RANGEVISION; i++){
		if(i != CURRENT){
			if(vision[i] == ONCHARGER){
				return true;
			}
		}
	}
	return false;
}

inline int Alive::findNearestCharger(){
	for(int i = 1; i < (RANGEVISION + 1) / 2; i++){
		if(vision[CURRENT + i] == ONCHARGER){
			return i;
		}else if(vision[CURRENT - i] == ONCHARGER){
			return -i;
		}
	}
	//見つからない場面でのこの関数の利用は想定外.
	return -100;
}

#endif //Alive_HPP_