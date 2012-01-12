#include "ContSpread.hpp"

ContSpread::ContSpread(){
	std::string head = "pos";
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

	float signalX = NO_SIGNAL;
	float signalY = NO_SIGNAL;
	if(robots == 0){
		signalX = NO_SIGNAL;
		signalY = NO_SIGNAL;
#ifdef	IMPORTANCE_BASED
		this->importance = NO_SIGNAL;
#endif	//IMPORTANCE_BASED
	}else{
#ifndef IMPORTANCE_BASED
		signalX = 0.0f;
		signalY = 0.0f;
#endif	//IMPORTANCE_BASED
		float maxImp = NO_SIGNAL;
		for(int i = 0; i < robots; i++){
			//i”Ô–Ú‚É‹ß‚¢Robot‚Æ‚ÌˆÊ’u‚Ì·
			float dX = this->getInput(i * 2 + 2);
			float dY = this->getInput(i * 2 + 2 + 1);
			//i”Ô–Ú‚É‹ß‚¢Robot‚Æ‚Ì‹——£
			float d = this->norm(dX, dY);
#ifdef	IMPORTANCE_BASED
			float impD = computeImportance(d, i);
			if(maxImp < impD){
				maxImp = impD;
				float signalStrength = calcStrength(d);
				if(signalStrength != NO_SIGNAL){
					/*signalX = (float)MAX_DRIVE * signalStrength * dX / d;
					signalY = (float)MAX_DRIVE * signalStrength * dY / d;
					*/
					if(d != 0.0f){
						signalX = signalStrength * dX / d;
						signalY = signalStrength * dY / d;
					}else{
						signalX = signalStrength * dX;
						signalY = signalStrength * dY;
					}
					float signal = this->norm(signalX, signalY);
					if(signal != 0.0f){
						signalX *= impD * (float)MAX_DRIVE / signal;
						signalY *= impD * (float)MAX_DRIVE / signal;
					}

					this->importance = maxImp;
					if(signalStrength == 0.0f){
						signalX = NO_SIGNAL;
						signalY = NO_SIGNAL;
						this->importance = NO_SIGNAL;
					}
				}
			}
		}
#else	//IMPORTANCE_BASED
			float signalStrength = calcStrength(d);
			if(signalStrength != NO_SIGNAL){
				if(d != 0.0f){
					signalX += signalStrength * dX / d;
					signalY += signalStrength * dY / d;
				}else{
					signalX += signalStrength * dX;
					signalY += signalStrength * dY;
				}
			}
			float signal = this->norm(signalX, signalY);
			if(signal != 0.0f){
				signalX *= (float)MAX_DRIVE / signal;
				signalY *= (float)MAX_DRIVE / signal;
			}
		}
#endif	//IMPORTANCE_BASED	
	}
	////For Now
	//signalX = NO_SIGNAL;
	//signalY = NO_SIGNAL;
#ifdef	IMPORTANCE_BASED
	this->importance = NO_SIGNAL;
#endif	//IMPORTANCE_BASED
	this->setOutput(0, signalX);
	this->setOutput(1, signalY);
}

int ContSpread::countNumberOfRobots(){
	int result = 0;

	for(int i = 0; i < WIFI_CONNECT; i++){
		if(this->getInput(i * 2) != NO_SIGNAL){
			result = i;
		}else{
			break;
		}
	}

	return result;
}

float ContSpread::calcStrength(float distance){
	float strength = NO_SIGNAL;
	if(distance < WIFI_REACH * WIFI_NEUTRAL){
		strength = -1.0f;
	}else{
		strength = 1.0f;
	}

	float ratio = distance / (WIFI_REACH * WIFI_NEUTRAL);
	if(ratio > 0.8f && ratio < 1.2f){
		strength = 0.0f;
	}

	return strength;
}

#ifdef	IMPORTANCE_BASED
float ContSpread::computeImportance(float distance, int i){
	float importance = NO_SIGNAL;
	if(distance < 1.0f || distance > WIFI_REACH * WIFI_WEAK){
		importance = 1.0f;
	}else if(distance < WIFI_REACH * WIFI_NEUTRAL){
		float k = 1.0f / (WIFI_REACH * WIFI_NEUTRAL - 1.0f);
		importance = this->calcImportance(1.0f - k * (distance - 1.0f) );
	}else{
		float k = 1.0f / (WIFI_REACH * (WIFI_WEAK - WIFI_NEUTRAL));
		importance = this->calcImportance(k * (distance - WIFI_REACH * WIFI_NEUTRAL));
	}

	if(WIFI_CONNECT != 0){
		importance *= this->calcImportance((WIFI_CONNECT - i) / WIFI_CONNECT);
	}

	return importance;
}
#endif	//IMPORTANCE_BASED