#include "EnvUpdater.h"
#include "Constants.h"

#include <math.h>

EnvUpdater::EnvUpdater(int* field) : field(field), position(0), battery(100), progress(0){
}

void EnvUpdater::update(int progress){
	bool onCharger = false;
	if(field[position] == ONCHARGER){
		onCharger = true;
	}
	updateBatteryStatus(progress, onCharger);

	updatePosition(progress);
}

void EnvUpdater::updatePosition(int progress){
	this->progress = progress;
	position += progress;
}

void EnvUpdater::updateBatteryStatus(int progress, bool onCharger){
	battery -= 3 * abs(progress);
	if(onCharger){
		battery += 5;
		if(battery > 100){
			battery = 100;
		}
	}
}