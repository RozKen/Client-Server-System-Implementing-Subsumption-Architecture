#ifndef ProgressController_HPP_
#define ProgressController_HPP_

#include "SAModule.h"
#include "Constants.h"
#include <iostream>
/**
	@brief Mission : ゴールの方向へ進む
	<ol>
		<li>視界内にゴールがある時，そこへ移動</li>
		<li>position / step < thresholdの時，5マス進む</li>
		<li>その他の時，出力0</li>
	</ol>
	*/
class Progress : public SAModule {
public:
	/**
		@brief Constructor
		<ul>
			<li>outputs[0] : 移動先の相対位置</li>
			<li>inputs[0] - inputs[RANGEVISION - 1] : 見えているもの</li>
			<li>inputs[RANGEVISION] ; step数</li>
			<li>inputs[RANGEVISION + 1] : progress量</li>
		</ul>
	 */
	Progress();
	/**
		@brief Mission : ゴールの方向へ進む
		<ol>
			<li>視界内にゴールがある時，そこへ移動</li>
			<li>position / step < thresholdの時，5マス進む</li>
			<li>その他の時，出力0</li>
		</ol>
	 */
	void Run();

protected:
	/**
		@brief 視界内にGoalがあるかどうか調べる
		@return 視界内にGoalがあるかどうか
	 */
	bool isSeeGoal();
	/**
		@brief ゴールの相対位置を返す
		@return ゴールの相対位置
	 */
	int stepToGoal();

	///step数
	int stepCount;
	///進度
	int progressCount;
	///視界
	int vision[RANGEVISION];
	///進みたがる性質の強さ[0.0 - 1.0]
	float threshold;
	///発火制御Counter
	int count;
};

inline Progress::Progress() 
	: SAModule(RANGEVISION + 2, 1), stepCount(0), progressCount(0), threshold(0.7), count(0){
	for(int i = 0; i < RANGEVISION; i++){
		vision[i] = 0;
		inputs[i] = 0;
	}
	inputs[RANGEVISION] = 0;
	inputs[RANGEVISION + 1] = 0;
}

inline void Progress::Run(){
	if(count % 3 == 0){
		//Update Local Variables
		for(int i = 0; i < RANGEVISION; i++){
			vision[i] = inputs[i];
		}
		stepCount = inputs[RANGEVISION];
		progressCount = inputs[RANGEVISION + 1];

		if(isSeeGoal()){
			outputs[0] = stepToGoal();
		}else if(stepCount < 10){
			outputs[0] = 0;
		}else if((double)progressCount / (double)stepCount < threshold){
	//		std::cout << "progressCount: " << progressCount << std::endl;
	//		std::cout << "stepCount: " << stepCount << std::endl;
	//		std::cout << "ratio: " << (double)progressCount / (double)stepCount << std::endl;
	//		std::cout << "threshold: " << threshold << std::endl;
			//TODO 本当は[1-10]のランダムにする予定
			outputs[0] = 5;
		}else{
			outputs[0] = 0;
		}
	}else{
		outputs[0] = 0;
	}
	count++;
}

inline bool Progress::isSeeGoal(){
	for(int i = 0; i < RANGEVISION; i++){
		if(vision[i] == ONGOAL){
			return true;
		}
	}
	return false;
}

inline int Progress::stepToGoal(){
	int index = -100;
	for(int i = 0; i < RANGEVISION; i++){
		if(vision[i] == ONGOAL){
			index = i - ((RANGEVISION - 1) / 2);
			break;
		}
	}
	return index;
}

#endif //Progress_HPP_