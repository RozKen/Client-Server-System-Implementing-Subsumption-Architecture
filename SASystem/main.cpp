#include <iostream>
#include <string>
#include "Modules.h"
#include "SAConnector.h"

#include "SAServer.h"
#include "EnvUpdater.h"

void main(){
	SAServer server;
	std::string tmp;
	
	std::cout << "Created Server" << std::endl;

	//Module‚Ì’è‹`
	ActMotor* leftMotor = new ActMotor();
	ActMotor* rightMotor = new ActMotor();
	MotorDriver* leftMD = new MotorDriver();
	MotorDriver* rightMD = new MotorDriver();
	SenseRange* senseRange = new SenseRange(server.getEnv());
	Avoid* avoid = new Avoid();
	Wander* wander = new Wander();
	Return* turn = new Return();

	//Module‚Ì“o˜^
	server.addModule(leftMotor);
	server.addModule(rightMotor);
	server.addModule(leftMD);
	server.addModule(rightMD);
	server.addModule(senseRange);
	server.addModule(avoid);
	server.addModule(wander);
	server.addModule(turn);

	std::vector<SAConnector *> connectors;
	//Wire‚Ì’è‹`
	connectors.push_back( new SAConnector(&(leftMD->getOutputsPtr()[0]), &(leftMotor->getInputsPtr()[0]), 0) );
	connectors.push_back( new SAConnector(&(rightMD->getOutputsPtr()[0]), &(rightMotor->getInputsPtr()[0]), 0) );
	connectors.push_back( new SAConnector(&(senseRange->getOutputsPtr()[0]), &(avoid->getInputsPtr()[0]), 0) );
	connectors.push_back( new SAConnector(&(avoid->getOutputsPtr()[0]), &(leftMD->getInputsPtr()[0]), 0) );
	connectors.push_back( new SAConnector(&(avoid->getInputsPtr()[1]), &(rightMD->getInputsPtr()[0]), 0) );
	//Inhibitor‚Ì’è‹`

	//Suppressor‚Ì’è‹`
	connectors.push_back( new SAConnector(&(wander->getOutputsPtr()[0]), &(leftMD->getInputsPtr()[0]), 2) );
	connectors.push_back( new SAConnector(&(wander->getOutputsPtr()[1]), &(rightMD->getInputsPtr()[0]), 2) );

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
		if(count > 1000){
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