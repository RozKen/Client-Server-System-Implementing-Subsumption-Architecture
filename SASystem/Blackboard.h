#ifndef _Blackboard_H_
#define _Blackboard_H_

#include "Constants.h"
#include "Logger.h"

/**
	@class Blackboard
	@brief Base of Blackboard System. Hold Data and provide getter and setter.
	To provide semantic data to sensors, this class builds internal world
	from some data

	@sa H. Penny Nii, Blackboard Application Systems
		and a Knowledge Engineering Perspective (1986 AI Magazine vol. 7)

	@date 9th November 2011
	@author Kenichi Yorozu
 */
class Blackboard {
public:
	/**
		@brief Constructor
	*/
	Blackboard();
	/**
		@brief Constructor
		@param logFilePath ログファイルへのpath
	 */
	Blackboard(std::string logFilePath);
	Blackboard(std::string directoryPath, std::string fileName);
	/**
		@brief Destructor
		Delete pointers of std::vectors
	 */
	virtual ~Blackboard();
	/**
		@brief Update Internal World from inputs and set outputs according to the World
	*/
	virtual void Update();

	/**
		@brief Log Blackboard Data into a File.
	 */
	void Log();
	
	/**
		@brief 入力Portを追加
		@param title Portの名前
	 */
	int addInputPort(std::string title);
	/**
		@brief 出力Portを追加
		@param title Portの名前
	 */
	int addOutputPort(std::string title);

	//Setters and Getters
	/**
		@brief このBlackboardで利用するログファイルへのPathを設定
		@sa logger
	 */
	void setLogFilePath(std::string logFilePath);
	void setLogFilePath(std::string fileDirectoryPath, std::string fileName);
	float getInput(int index) const;
	float getOutput(int index) const;
	void setInput(int index, float signal);
	void setOutput(int index, float signal);
	int getNumOfOutputs() const;
	int getNumOfInputs() const;

protected:
	std::vector<float> *inputs;
	std::vector<float> *outputs;
	///入力信号ポート数
	int numOfInputPorts;
	///出力信号ポート数
	int numOfOutputPorts;

	/**
		@brief 記録をとるモジュール
		@sa Logger
	 */
	Logger* logger;
};

inline Blackboard::Blackboard(): numOfInputPorts(0), numOfOutputPorts(0){
	inputs = new std::vector<float>();
	outputs = new std::vector<float>();
	logger = new Logger();
}

inline Blackboard::Blackboard(std::string logFilePath)
	:numOfInputPorts(0), numOfOutputPorts(0){
	setLogFilePath(logFilePath);
	inputs = new std::vector<float>();
	outputs = new std::vector<float>();
	logger = new Logger(logFilePath);
}

inline Blackboard::Blackboard(std::string directoryPath, std::string fileName){
	inputs = new std::vector<float>();
	outputs = new std::vector<float>();
	logger = new Logger(directoryPath, fileName);
}

inline Blackboard::~Blackboard(){
	delete(inputs);
	delete(outputs);
}

inline void Blackboard::setLogFilePath(std::string logFilePath){
	this->logger->setFilePath(logFilePath);
}

inline void Blackboard::setLogFilePath(std::string fileDirectoryPath, std::string fileName){
	this->logger->setFilePath(fileDirectoryPath, fileName);
}

inline float Blackboard::getInput(int index) const{
	return inputs->at(index);
}
inline float Blackboard::getOutput(int index) const{
	return outputs->at(index);
}
inline void Blackboard::setInput(int index, float signal){
	inputs->at(index) = signal;
}
inline void Blackboard::setOutput(int index, float signal){
	outputs->at(index) = signal;
}
inline int Blackboard::getNumOfOutputs() const{
	return numOfOutputPorts;
}
inline int Blackboard::getNumOfInputs() const{
	return numOfInputPorts;
}

#endif //_Blackboard_H_