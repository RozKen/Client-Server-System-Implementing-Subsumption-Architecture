#include "ContWander.hpp"
#include "RobotMAV.h"

void ContWander::Run(){
	//履歴を移動
	for(int i = 9; i > 1; i--){
		this->innerMemory->setFBoard(i, this->innerMemory->getFBoard(i - 2));
	}
	//最新状態を更新
	this->innerMemory->setFBoard(0, this->getInput(0));
	this->innerMemory->setFBoard(1, this->getInput(1));
	//とりあえず，履歴とかは考えずに，ランダムに動く．
	float signalX = NO_SIGNAL;
	float signalY = NO_SIGNAL;
#ifdef	IMPORTANCE_BASED
	this->importance = NO_SIGNAL;
#endif	//IMPORTANCE_BASED
	
	float random = _rand();
	if(random < P_WANDER){
		float theta = 2.0 * PI * _rand();
		signalX = (float)MAX_DRIVE * cos(theta);
		signalY = (float)MAX_DRIVE * sin(theta);
#ifdef	IMPORTANCE_BASED
		this->importance = this->calcImportance(1.0f - random / P_WANDER);
#endif	//IMPORTANCE_BASED
	}else{
		signalX = NO_SIGNAL;
		signalY = NO_SIGNAL;
#ifdef	IMPORTANCE_BASED
	this->importance = NO_SIGNAL;
#endif	//IMPORTANCE_BASED
	}
	//出力
	////////テスト中//////
	float direc = ((RobotMAV*)(this->parent))->getDirection();
	signalX = MAX_DRIVE * cosf(direc * PI / 180.0f);
	signalY = MAX_DRIVE * sinf(direc * PI / 180.0f);
#ifdef IMPORTANCE_BASED
	this->importance = this->calcImportance(0.9f);
#endif	//IMPORTANCE_BASED
	this->setOutput(0, signalX);
	this->setOutput(1, signalY);
}