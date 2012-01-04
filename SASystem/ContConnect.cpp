#include "ContConnect.hpp"
#include "RobotMAV.h"

void ContConnect::Run(){
	//出力信号：基本NO_SIGNAL
	float signalX = NO_SIGNAL;
	float signalY = NO_SIGNAL;
#ifdef	IMPORTANCE_BASED
	this->importance = NO_SIGNAL;
#endif	//IMPORTANCE_BASED

	//切れそうなのがあったら，そっちの方へ．
	//切れそうなもののうち，一番近いRobotの方へ向かう	//for Loopを逆にしてある.
	for(int i = WIFI_CONNECT - 1; i >= 0 ; i--){
		float dx = this->getInput(i * 2);
		float dy = this->getInput(i * 2 + 1);
		float distance = this->norm(dx, dy);
		if(distance > WIFI_REACH * WIFI_WEAK && dx != NO_SIGNAL && dy != NO_SIGNAL){
			signalX = (float)MAX_DRIVE * dx / distance;
			signalY = (float)MAX_DRIVE * dy / distance;
#ifdef	IMPORTANCE_BASED
			//重要度は，接続しているRobotの数に依存する
			this->importance = this->calcImportance(WIFI_CONNECT - 1 - i);
#endif	//IMPORTANCE_BASED
		}
	}

	//切れそうなものがなかったら，時々バランスをとる	//実際は使ってない.(WIFI_BALANCE = 0.0f)
	if(signalX == NO_SIGNAL && signalY == NO_SIGNAL){
		float random = rand();
		if(random < WIFI_BALANCE){
			signalX = 0.0f;
			signalY = 0.0f;
			for(int i = 0; i < WIFI_CONNECT; i++){
				signalX += this->getInput( i * 2 );
				signalY += this->getInput( i * 2 + 1 );
			}
			float distance = this->norm(signalX, signalY);
			if(distance != 0.0f){
				signalX /= distance;
				signalY /= distance;
			}
			signalX *= (float)MAX_DRIVE;
			signalY *= (float)MAX_DRIVE;
#ifdef	IMPORTANCE_BASED
			this->importance = this->calcImportance(1.0f - random / WIFI_BALANCE);
#endif	//IMPORTANCE_BASED
		}
	}

	//出力
	this->setOutput(0, signalX);
	this->setOutput(1, signalY);
}