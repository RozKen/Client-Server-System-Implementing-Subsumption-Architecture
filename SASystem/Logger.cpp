#include "Logger.h"
#include <time.h>
#include <sstream>
#include <iostream>
#include <direct.h>

Logger::Logger(): count(0), logFilePath(""), logDirectoryPath("")
	, logFileName(""){
}

Logger::Logger(std::string filePath)
	:count(0), logFilePath(filePath), logDirectoryPath(""), logFileName(""){

	Initialize();
}
Logger::Logger(std::string directoryPath, std::string fileName)
	:count(0), logFilePath(directoryPath.append("/").append(fileName))
	, logDirectoryPath(directoryPath), logFileName(fileName){
	
		_mkdir(directoryPath.c_str());
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
		case 2:
			ofs << ((std::vector<float> *)logContents.at(i))->at(logArrayIndex.at(i)) << ",";
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
		std::cerr << "Error:���O�t�@�C���̕ۑ���(logFilePath)���w�肵�ĉ�����" << std::endl;
	}else{
		///�L�^�t�@�C����ݒ�
		ofs.open(logFilePath);
		this->add("count", &count);
	}
}

void Logger::add(std::string title, int* pointer_to_integer_variable){
	logTitles.push_back(title);
	logTypes.push_back(0);
	logContents.push_back((void*) pointer_to_integer_variable);
	logArrayIndex.push_back(-1);
}

void Logger::add(std::string title, float* pointer_to_float_variable){
	logTitles.push_back(title);
	logTypes.push_back(1);
	logContents.push_back((void*) pointer_to_float_variable);
	logArrayIndex.push_back(-1);
}

void Logger::add(std::string title, std::vector<float>* vector, int index){
	logTitles.push_back(title);
	logTypes.push_back(2);
	//logContents�ɂ͔z��S�̂����Ă���
	logContents.push_back((void *) vector);
	//push�͂��Ȃ����ǁC�Ȃɂ���������ˁc
	logArrayIndex.push_back(index);
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
	Initialize();
}

void Logger::setFilePath(std::string fileDirectoryPath, std::string fileName){
	logDirectoryPath = fileDirectoryPath;
	logFileName = fileName;
	logFilePath = logDirectoryPath;
	logFilePath.append("/");
	logFilePath.append(fileName);
	_mkdir(logDirectoryPath.c_str());
	Initialize();
}

std::string Logger::getFilePath() const{
	return logFilePath;
}