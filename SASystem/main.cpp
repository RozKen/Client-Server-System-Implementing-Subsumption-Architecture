#include <iostream>
#include <string>

#include "SAServer.h"

void main(){
	std::cout << "Begin" << std::endl;
	std::cout << "twotwo" << std::endl;
	SAServer server;
	std::string tmp;
	
	std::cout << "Created Server" << std::endl;

	while(true){
		std::cin >> tmp;
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
		server.Process();
	}

	std::cout << "End" <<std::endl;
	
	std::cin >> tmp;
	return;
}