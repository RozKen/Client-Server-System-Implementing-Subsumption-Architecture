#include "ContSpread.hpp"

ContSpread::ContSpread(){
	std::string head = "posX";
	std::string foot = "CSp";
	//Add Inputs
	////Add Position Input
	for(int i = 0; i < 2; i++){
		std::string name = head;
		if(i % 2 == 0){
			name.append("X");
		}else{
			name.append("Y");
		}
		name.append(foot);
		this->addInput(name);
	}

	////Add Network Input
	head = "Robot";
	for(int i = 0; i < WIFI_CONNECT * 2; i++){
		std::string name = head;
		name.append(intToString( i / 2 ) );
		if( i % 2 == 0){
			name.append("X");
		}else{
			name.append("Y");
		}
		name.append(foot);
		this->addInput(name);
	}

	//Add Outputs
	head = "d";
	for(int i = 0; i < 2; i++){
		std::string name = head;
		if( i % 2 == 0){
			name.append("X");
		}else{
			name.append("Y");
		}
		name.append(foot);
		this->addOutput(name);
	}
}

void ContSpread::Run(){
	int robots = countNumberOfRobots();

	float signalX = 0.0f;
	float signalY = 0.0f;
	if(robots == 0){
		signalX = NO_SIGNAL;
		signalY = NO_SIGNAL;
#ifdef	IMPORTANCE_BASED
		this->importance = NO_SIGNAL;
#endif	//IMPORTANCE_BASED
	}else{
		float maxD = NO_SIGNAL;
		for(int i = 0; i < robots; i++){
			//i”Ô–Ú‚É‹ß‚¢Robot‚Æ‚ÌˆÊ’u‚Ì·
			float dX = this->getInput(i * 2 + 2) - this->getInput(0);
			float dY = this->getInput(i * 2 + 2 + 1) - this->getInput(1);
			//i”Ô–Ú‚É‹ß‚¢Robot‚Æ‚Ì‹——£
			float d = this->norm(dX, dY);
			float impD = calcImportance(d);
			if(maxD < impD){
				maxD = impD;
			}
			float signalStrength = calcStrength(d);
			signalX = (float)MAX_DRIVE * signalStrength * dX / d;
			signalY = (float)MAX_DRIVE * signalStrength * dY / d;
		}
		#ifdef	IMPORTANCE_BASED
			this->importance = calcImportance(maxD);
#endif	//IMPORTANCE_BASED
	}

	this->setOutput(0, signalX);
	this->setOutput(1, signalY);
}

int ContSpread::countNumberOfRobots(){
	int result = 0;

	for(int i = 0; i < WIFI_CONNECT; i++){
		if(this->getInput(i * 2) != NO_SIGNAL){
			result = i;
		}
	}

	return result;
}

float ContSpread::calcStrength(float distance){
	float strength = NO_SIGNAL;
	if(distance < WIFI_REACH * WIFI_NEUTRAL){
		strength = 1.0f;
	}else{
		strength = -1.0f;
	}
	return strength;
}

#ifdef	IMPORTANCE_BASED
float ContSpread::calcImportance(float distance){
	float importance = NO_SIGNAL;
	if(distance < 1.0f || distance > WIFI_REACH * WIFI_WEAK){
		importance = 1.0f;
	}else if(distance < WIFI_REACH * WIFI_NEUTRAL){
		float k = 1.0f / (WIFI_REACH * WIFI_NEUTRAL - 1.0f);
		importance = this->calcImportance(1.0f - k * (distance - 1.0f) );
	}else{
		float k = 1.0f / (WIFI_REACH * (WIFI_WEAK - WIFI_NEUTRAL));
		importance = this->calcImportance(distance - WIFI_REACH * WIFI_NEUTRAL);
	}

	return importance;
}
#endif	//IMPORTANCE_BASED