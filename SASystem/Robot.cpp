#include "Robot.h"

Robot::Robot(){
	this->modules = new std::vector<SAModule*>();
	this->arbiters = new std::vector<Arbiter*>();
	this->innerWireSrcType = new std::vector<int>();
	this->innerWireSrcIndex = new std::vector<int>();
	this->innerWireDestType = new std::vector<int>();
	this->innerWireDestIndex = new std::vector<int>();
}

Robot::Robot(std::string directoryPath, std::string fileName){
	this->modules = new std::vector<SAModule*>();
	this->arbiters = new std::vector<Arbiter*>();
	this->innerWireSrcType = new std::vector<int>();
	this->innerWireSrcIndex = new std::vector<int>();
	this->innerWireDestType = new std::vector<int>();
	this->innerWireDestIndex = new std::vector<int>();
	this->innerMemory->setLogFilePath(directoryPath, fileName);
}

Robot::~Robot(){
	delete(modules);
	delete(arbiters);
}

void Robot::Initialize(){
}

void Robot::Run(){
	ProcessInputs();
	RunModules();
	//Log();				//Arbiterの挙動を調べるため，ダブログ
	ProcessArbiters();
	ProcessOutputs();
	Log();
}

void Robot::RunModules(){
	for(int i = 0; i < modules->size(); i++){
		modules->at(i)->Run();
	}
}

void Robot::ProcessArbiters(){
	for(int i = 0; i < arbiters->size(); i++){
		arbiters->at(i)->Run();
	}
}

void Robot::ProcessInputs(){
	for(int i = 0; i < this->innerWireSrcType->size(); i++){
		//Source が inputs:inputsはmemory上
		if(this->innerWireSrcType->at(i) == 0){
			float signal = this->getInput(this->innerWireSrcIndex->at(i));
			//Destination が iBoard: iBoardはinnerMemory上
			if(this->innerWireDestType->at(i) == 2){
				innerMemory->setIBoard(this->innerWireDestIndex->at(i)
					, (int)(signal));
			}
			//Destination が fBoard: fBoardはinnerMemory上
			else if(this->innerWireDestType->at(i) == 3){
				innerMemory->setFBoard(this->innerWireDestIndex->at(i)
					, signal);
			}
		}
	}
}

void Robot::ProcessOutputs(){
	for(int i = 0; i < this->innerWireDestType->size(); i++){
		//Destination が outputs: outputsはmemory上
		if(this->innerWireDestType->at(i) == 1){
			//SourceがiBoard: iBoardはinnerMemory上
			if(this->innerWireSrcType->at(i) == 2){
				this->setOutput(this->innerWireDestIndex->at(i)
					, (float)(innerMemory->getIBoard(this->innerWireSrcIndex->at(i))));
			}
			//SourceがfBoard: fBoardはinnerMemory上
			else if(this->innerWireSrcType->at(i) == 3){
				this->setOutput(this->innerWireDestIndex->at(i)
					, innerMemory->getFBoard(this->innerWireSrcIndex->at(i)));
			}
		}
	}
}

void Robot::addModule(SAModule *module){
	//moduleをrobotに登録
	modules->push_back(module);
	//moduleの親として，robot自身を登録
	module->setParent(this);
	int index;
	//moduleの入力を，このロボットのinnerMemoryの出力と接続
	for(int i = 0; i < module->getNumOfInputPorts(); i++){
		index = this->innerMemory->addOutputPort(module->getInputTitles()->at(i));
		module->addInputIndex(index);
	}

	//moduleの出力を，このロボットのinnerMemoryの入力と接続
	for(int i = 0; i < module->getNumOfOutputPorts(); i++){
		index = this->innerMemory->addInputPort(module->getOutputTitles()->at(i));
		module->addOutputIndex(index);
	}
	
	//ModuleはController(Robotのように単体で入力も出力も扱う場合もある)
	int flag = 0;
	//Sensorの時
	if(module->getNumOfInputPorts() == 0
		&& module->getNumOfOutputPorts() > 0){
		flag = 1;		//ModuleはSensor
	}
	//Actuatorの時
	if(module->getNumOfInputPorts() > 0 
		&& module->getNumOfOutputPorts() == 0){
		flag = 2;		//ModuleはActuator
	}

	//moduleのint入出力を、このロボットのinnerMemoryのiBoardと接続
	std::vector<std::string>* titles = module->getIBoardTitles();
	for(int i = 0; i < titles->size(); i++){
		index = this->innerMemory->addIntPort(titles->at(i));
		module->addIBoardIndex(index);
		if(flag != 2){
			std::string title = titles->at(i);
			this->addInput(title);
			//this->addIBoard(title.append("_i"));
			//InnerWireの接続を定義
			this->innerWireSrcType->push_back(0);
			this->innerWireSrcIndex->push_back(this->inputTitles->size() - 1);
			this->innerWireDestType->push_back(2);
			this->innerWireDestIndex->push_back(index);
		}
		if(flag != 1){
			std::string title = titles->at(i);
			this->addOutput(title);
			//this->addIBoard(title.append("_i"));
			//InnerWireの接続を定義
			this->innerWireSrcType->push_back(2);
			this->innerWireSrcIndex->push_back(index);
			this->innerWireDestType->push_back(1);
			this->innerWireDestIndex->push_back(this->outputTitles->size() - 1);
		}
	}
	//moduleのfloat入出力を、このロボットのinnerMemoryのfBoardと接続
	titles = (module->getFBoardTitles());
	for(int i = 0; i < titles->size(); i++){
		index = this->innerMemory->addFloatPort(titles->at(i));
		module->addFBoardIndex(index);
		if(flag != 2){
			std::string title = titles->at(i);
			this->addInput(title);
			//this->addFBoard(title.append("_i"));
			//InnerWireの接続を定義
			this->innerWireSrcType->push_back(0);
			this->innerWireSrcIndex->push_back(this->inputTitles->size() - 1);
			this->innerWireDestType->push_back(3);
			this->innerWireDestIndex->push_back(index);
		}
		if(flag != 1){
			std::string title = titles->at(i);
			this->addOutput(title);
			//this->addFBoard(title.append("_i"));
			//InnerWireの接続を定義
			this->innerWireSrcType->push_back(3);
			this->innerWireSrcIndex->push_back(index);
			this->innerWireDestType->push_back(1);
			this->innerWireDestIndex->push_back(this->outputTitles->size() - 1);
		}
	}
}

void Robot::addArbiter(Arbiter *arbiter){
	//arbiterをrobotに登録
	arbiters->push_back(arbiter);
	//arbiterの親として，robot自身を登録
	arbiter->setParent(this);
	//int index;
	///Arbiterにはmemoryの割り当て不要
	/**
		Arbiterには，setSource, setDestinationの時点で，
		inputIndex, outputIndexが構築されている
	 */
}

void Robot::setLogDirectoryPath(std::string directoryPath, std::string fileName){
	this->innerMemory->setLogFilePath(directoryPath, fileName);
}

std::string Robot::getLogFilePath() const{
	return this->innerMemory->getLogFilePath();
}