#include "SAConnector.h"

void SAConnector::Process(){
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
		if(*destination == NO_SIGNAL){
			*destination = *source;
		}
		timeLeftModified--;
		if(timeLeftModified < 0){
			timeLeftModified = 0;
		}
		break;
	default:
		break;
	}
}