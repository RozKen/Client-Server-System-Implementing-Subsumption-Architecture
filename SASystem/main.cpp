#include <iostream>
#include <string>

#include "Constants.h"

#include "EnvUpdater.h"
#include "SAServer.h"
#include "Modules.h"
#include "SAConnector.h"

void main(){
	int field[LENGTH];
	for(int i = 0; i < LENGTH; i++){
		if(i % 10 == 3){
			field[i] = ONCHARGER;
		}else{
			field[i] = NORMAL;
		}
	}
	field[0] = ONSTART;
	field[LENGTH - 1] = ONGOAL;
	/*
	for(int i = 0; i < LENGTH; i++){
		std::cout << field[i] << "\t";
	}
	std::cout << std::endl;
	*/

	SAServer server(field);
	std::string tmp;
	
	std::cout << "Created Server" << std::endl;

	std::vector<SAModule *> modules;
	//Module‚Ì’è‹`
	//Actuators
	modules.push_back(new PositionUpdater());
	//Sensors
	modules.push_back(new BatteryStatus(server.getEnv()));
	modules.push_back(new VisionScope(server.getEnv()));
	modules.push_back(new ProgressCounter(server.getEnv()));
	modules.push_back(new StepCounter());
	//Controllers
	modules.push_back(new Alive());
	modules.push_back(new Progress());

	//Module‚Ì“o˜^
	for(int i = 0; i < modules.size(); i++){
		server.addModule(modules[i]);
	}

	std::vector<SAConnector *> connectors;
	//Wire‚Ì’è‹`
	connectors.push_back( new SAConnector(&(modules[1]->getOutputsPtr()[0]), &(modules[0]->getInputsPtr()[1]), 0) );
	connectors.push_back( new SAConnector(&(modules[1]->getOutputsPtr()[0]), &(modules[5]->getInputsPtr()[RANGEVISION]), 0) );
	connectors.push_back( new SAConnector(&(modules[5]->getOutputsPtr()[0]), &(modules[0]->getInputsPtr()[0]), 0) );
	for(int i = 0; i < RANGEVISION; i++){
		connectors.push_back( new SAConnector(&(modules[2]->getOutputsPtr()[i]), &(modules[5]->getInputsPtr()[i]), 0) );
		connectors.push_back( new SAConnector(&(modules[2]->getOutputsPtr()[i]), &(modules[6]->getInputsPtr()[i]), 0) );
	}
	connectors.push_back( new SAConnector(&(modules[4]->getOutputsPtr()[0]), &(modules[6]->getInputsPtr()[RANGEVISION]), 0) );
	connectors.push_back( new SAConnector(&(modules[3]->getOutputsPtr()[0]), &(modules[6]->getInputsPtr()[RANGEVISION+1]), 0) );
	//Inhibitor‚Ì’è‹`

	//Suppressor‚Ì’è‹`
	connectors.push_back( new SAConnector(&(modules[6]->getOutputsPtr()[0]), &(modules[0]->getInputsPtr()[0]), 2) );

	//Server‚Ö“o˜^
	for(int i = 0; i < connectors.size(); i++){
		server.addConnector(connectors[i]);
	}

	int count = 0;
	while(true){
		/*std::cin >> tmp;
		if(tmp.compare("q") == 0){
			break;
		}else{
			if(tmp.compare("4") == 0){
			}else if(tmp.compare("8") == 0){
			}else if(tmp.compare("6") == 0){
			}else if(tmp.compare("2") == 0){
			}else{
			}
		}
		*/
		if(count > 100){
			break;
		}
		server.Process();
		count++;
	}

	std::cout << "End" <<std::endl;
	std::cout << "Enter any character and Enter Key" << std::endl;
	
	std::cin >> tmp;
	return;
}