#include "SAModule.h"
#include <math.h>

void SAModule::SignalDecoder(float input, float &output1, float &output2){
	///ŠeˆÊ‚Ì’l‚ðŠi”[‚·‚é
	int digits1[4], digits2[4];
	for(int i = 0; i < 4; i++){
		digits1[i] = 0;
		digits2[i] = 0;
	}
	for(int i = 0; i < 4; i++){
		float power = pow(100.0f, i);
		digits1[i] = (int)(input * 10.0f * power) % 10;
		digits2[i] = (int)(input * 100.0f * power) % 10;
	}
	//digits‚©‚çoutput‚Ö“ü—Í‚µ‚Ä‚¢‚­
	output1 = 0.0f;
	output2 = 0.0f;
	for(int i = 0; i < 4; i++){
		float power = pow(0.1f, i + 1);
		output1 += (float)digits1[0] * power;
		output2 += (float)digits2[0] * power;
	}
	output1 = (float)digits1[0] * 0.1f + (float)digits1[1] * 0.01f + (float)digits1[2] * 0.001f + (float)digits1[3] * 0.0001f;
	output2 = (float)digits2[0] * 0.1f + (float)digits2[1] * 0.01f + (float)digits2[2] * 0.001f + (float)digits2[3] * 0.0001f;
}

float SAModule::SignalEncoder(float input1, float input2){
	float output = 0.0f;
	int digits1[4], digits2[4];
	for(int i = 0; i < 4; i++){
		float power = pow(10.0f, i+1);
		digits1[i] = (int)(input1 * power) % 10;
		digits2[i] = (int)(input2 * power) % 10;
	}
	for(int i = 0; i < 4; i++){
		float power = pow(0.01f, i);
		output += ((float)digits1[i] * 0.1f + (float)digits2[i] * 0.01f) * power;
	}
	return output;
}