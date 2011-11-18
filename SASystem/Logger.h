#ifndef _Logger_H_
#define _Logger_H_

#include <string>
#include <vector>
#include <fstream>

class Logger{
public:
	/**
		@brief Default Constructor: <b>filePath����Ŏw�肷��K�v������</b>
	 */
	Logger();
	/**
		@brief Constructor
		@param filePath ���O�t�@�C���������o��File�ւ�path
		@sa logFilePath
	 */
	Logger(std::string filePath);
	/**
		@brief Constructor
		@param directoryPath ���O�t�@�C���������o��Directory�ւ�path
		@sa logDirectoryPath ���O�t�@�C����
		@sa logFileName
	 */
	Logger(std::string directoryPath, std::string fileName);

	/**
		@brief Destructor
	 */
	~Logger();
	/**
		@brief ���݂̏��(�ϐ�)���L�^
	 */
	void Log();

	/**
		@brief �����ϐ��̏�����. ofstream�̐ݒ�Ȃ�
	 */
	void Initialize();

	/**
		@brief int�^�̕ϐ����L�^����悤�o�^����
		@param title �ϐ����������^�C�g��
		@param pointer_to_integer_variable int�^�ϐ��ւ̃|�C���^
		@sa logTitles
		@sa logTypes
		@sa logContents
	 */
	void add(std::string title, int* pointer_to_integer_variable);
	/**
		@brief float�^�̕ϐ����L�^����悤�o�^����
		@param title �ϐ����������^�C�g��
		@param pointer_to_float_variable float�^�ϐ��ւ̃|�C���^
	 */
	void add(std::string title, float* pointer_to_float_variable);
	/**
		@brief float�^��vector�Ɋ܂܂�Ă���l���L�^����悤�o�^����
		@param title �ϐ����������^�C�g��
		@param vector �l���܂܂�Ă���vector
		@param index vector�ɂ�����Cindex
	 */
	void add(std::string title, std::vector<float>* vector, int index);
	/**
		@brief logFilePath��ݒ肷��
		@param filePath logFilePath
		@sa logFilePath
	 */
	void setFilePath(std::string filePath);
	/**
		@brief logFilePath��^����
		@return logFilePath
		@sa logFilePath
	 */
	std::string getFilePath() const;
	/**
		@brief �����^�̐����C�l���̐����̕�����֕ϊ�����
		@param number �ϊ������������^�̐�
		@return �l���̐����̕�����
	 */
	std::string intToString(int number);
protected:
	std::string logDirectoryPath;
	std::string logFileName;
	///���O�t�@�C���������o���ꏊ�ւ�path
	std::string logFilePath;
	///���O�̎�ނ��������^�C�g���D��s�ڂɕ\�������
	std::vector<std::string> logTitles;
	/**
		@brief ���O�̕ϐ��̎��
		<ul>
			<li>0 : int�^</li>
			<li>1 : float�^</li>
			<li>2 : std::vector<float*> �^�z�񒆂�
				logArrayIndex�ɏ����Ă���index�̗v�f</li>
		</ul>
	 */
	std::vector<int>	logTypes;
	///�L�^����ϐ��ւ̃|�C���^
	std::vector<void *> logContents;
	std::vector<int>	logArrayIndex;
	///Log�����񐔂̃J�E���^
	int count;
	/**
		@brief File Output Stream
	 */
	std::ofstream ofs;
};

#endif	//_Logger_H_