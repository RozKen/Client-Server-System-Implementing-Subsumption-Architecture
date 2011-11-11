#include "World.h"

#include "Blackboard.h"
#include "Robot.h"

World::World(): clockCount(0){
	environment = new Blackboard();
}

void World::Run(){
	RunRobots();
	UpdateWorld();
	Log();
	clockCount++;
}

void World::RunRobots(){
	for(int i = 0; i < robots.size(); i++){
		robots[i]->Run();
	}
}


void World::UpdateWorld(){
	
}

void World::Log(){
	environment->Log();
}
