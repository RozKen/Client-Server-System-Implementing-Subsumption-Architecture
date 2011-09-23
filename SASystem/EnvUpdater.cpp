#include "EnvUpdater.h"

EnvUpdater::EnvUpdater(int* field) : position(0), field(field){
}

void EnvUpdater::update(int progress){
	updatePosition(progress);
}

void EnvUpdater::updatePosition(int progress){
	position += progress;
}