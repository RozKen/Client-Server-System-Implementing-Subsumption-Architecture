#include "SAConnector.h"

#include "StochasticSelecter.hpp"

SAConnector::SAConnector(float* source, float* destination, int type)
	:source(source), destination(destination), type(type), timeToModify(0), timeLeftModified(0), _rand(0, 1) {
	ss = new StochasticSelector();
}

SAConnector::SAConnector(float* source, float* destination, int type, int timeToModify)
	:source(source), destination(destination), type(type), timeToModify(timeToModify), timeLeftModified(0), _rand(0, 1) {
	ss = new StochasticSelector();
}

SAConnector::SAConnector(float* source, float* destination, int type, int timeToModify, float probModify)
	:source(source), destination(destination), type(type), timeToModify(timeToModify), probModify(probModify), timeLeftModified(0), _rand(0, 1) {
	ss = new StochasticSelector(probModify);
}

SAConnector::SAConnector(float* source, float* destination, int type, float probModify)
	:source(source), destination(destination), type(type), timeToModify(0), probModify(probModify), timeLeftModified(0), _rand(0, 1) {
	ss = new StochasticSelector(probModify);
}

void SAConnector::Process(){
	float prob = _rand();
	switch(type){
	case 0:		//type = Wire
		*destination = *source;
		break;
	case 1:		//type = Inhibitor
		*destination = NO_SIGNAL;
		timeLeftModified--;
		if(timeLeftModified < 0){
			timeLeftModified = 0;
		}
		break;
	case 2:		//type = Suppressor
		if(*source != NO_SIGNAL){
			*destination = *source;
		}
		/*	//Suppression‚ðŠÔˆá‚¦‚Ä”FŽ¯‚µ‚Ä‚¢‚½
		if(*destination == NO_SIGNAL){
			*destination = *source;
		}*/
		timeLeftModified--;
		if(timeLeftModified < 0){
			timeLeftModified = 0;
		}
		break;
	case 3:		//type = Probability-based Selector
		if(*source != NO_SIGNAL || ss->get()){
			*destination = *source;
		}
		/*
		if(*source == NO_SIGNAL || !ss->get()){
			//‰º‘w‚ª‘¶‘±
		}else{
			*destination = *source;
		}
		*/
		timeLeftModified--;
		if(timeLeftModified < 0){
			timeLeftModified = 0;
		}
		break;
	case 4:		//type = Probability-based Superposer
		*destination = (int)(prob * ((float)(*source)) + (1.0f - prob) * ((float)(*destination)));
		timeLeftModified--;
		if(timeLeftModified < 0){
			timeLeftModified = 0;
		}
		break;
	default:
		break;
	}
}