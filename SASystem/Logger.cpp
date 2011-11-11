#include "Logger.h"
#include <time.h>
#include <sstream>
#include <iostream>

Logger::Logger(): count(0), logFilePath(""), logDirectoryPath("")
	, logFileName(""){
}

Logger::Logger(std::string filePath)
	:count(0), logFilePath(filePath), logDirectoryPath(""), logFileName(""){

	Initialize();
}
Logger::Logger(std::string directoryPath, std::string fileName)
	:count(0), logFilePath(directoryPath.append(fileName))
	, logDirectoryPath(directoryPath), logFileName(fileName){

	Initialize();
}

Logger::~Logger(){
	ofs.close();
}

void Logger::Log(){
	if(count == 0){
		for(int i = 0; i < logTitles.size(); i++){
			ofs << logTitles[i] << ",";
		}
		ofs << std::endl;
	}
	for(int i = 0; i < logContents.size(); i++){
		switch(logTypes[i]){
		case 0:
			ofs << *((int *)(logContents[i])) << ",";
			break;
		case 1:
			ofs << *((float *)(logContents[i])) << ",";
			break;
		default:
			ofs << "Invalid Type Value,";
		}
	}
	ofs << std::endl;
	count++;
}

void Logger::Initialize(){
	if(logFilePath.length() == 0){
		std::cerr << "Error:ログファイルの保存先(logFilePath)を指定して下さい" << std::endl;
	}else{
		//現在時刻
		time_t now;
		time(&now);
		///記録ファイルを設定
		ofs.open(logFilePath);
		this->add("count", &count);
	}
}

void Logger::add(std::string title, int* pointer_to_integer_variable){
	logTitles.push_back(title);
	logTypes.push_back(0);
	logContents.push_back((void*) pointer_to_integer_variable);
}

void Logger::add(std::string title, float* pointer_to_float_variable){
	logTitles.push_back(title);
	logTypes.push_back(1);
	logContents.push_back((void*) pointer_to_float_variable);
}

std::string Logger::intToString(int number){
	std::string str = "";
	std::stringstream ss;
	ss << number;
	if(number / 1000 > 0){
		str = ss.str();
	}else if(number / 100 > 0){
		str = "0";
		str.append(ss.str());
	}else if(number / 10 > 0){
		str = "00";
		str.append(ss.str());
	}else{
		str = "000";
		str.append(ss.str());
	}
	return str;
}

void Logger::setFilePath(std::string filePath){
	logFilePath = filePath;
}

std::string Logger::getFilePath() const{
	return logFilePath;
}