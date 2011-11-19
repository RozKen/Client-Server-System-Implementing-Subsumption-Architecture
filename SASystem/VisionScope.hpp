#ifndef VisionScope_HPP_
#define VisionScope_HPP_

#include "SAModule.h"
#include "EnvUpdater.h"
#include "Constants.h"

/**
	@class VisionScope
	@brief 現在位置とその前後5つのマスに，GoalやBatteryがあるかを調べる
	@sa SAModule
 */

class VisionScope : public SAModule{
public:
	/**
		@brief Constructor
		<ul>
		<li>outputs[0] : -5</li>
		<li>outputs[1] : -4</li>
		<li>outputs[2] : -3</li>
		<li>outputs[3] : -2</li>
		<li>outputs[4] : -1</li>
		<li>outputs[5] :  0</li>
		<li>outputs[6] :  1</li>
		<li>outputs[7] :  2</li>
		<li>outputs[8] :  3</li>
		<li>outputs[9] :  4</li>
		<li>outputs[10] :  5</li>
		</ul>
		@param environment 外部環境へのポインタ
	 */
	VisionScope(EnvUpdater* environment);
	
	/**
		@brief 近傍11マスの状態をoutputsに出力
	 */
	void Run();
protected:
	EnvUpdater* env;
};
inline VisionScope::VisionScope(EnvUpdater* environment) : env(environment){
}
inline void VisionScope::Run(){
	const int* field = env->getField();
	int pos = env->getPosition();
	//Vision探索ポイント
	int point;
	for(int i = 0; i < 11; i++){
		point = pos - 5 + i;
		//Area外の時
		if(point < 0 || point > LENGTH - 1){
			//outputs[i] = OUTOFAREA;
		}else{	//Area内の時
			//outputs[i] = field[point];
		//	std::cout << outputs[i] << std::endl;
		}
	}
}
#endif //VisionScope_HPP_