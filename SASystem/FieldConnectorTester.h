#ifndef _FieldConnectorTester_H_
#define _FieldConnectorTester_H_

#include <string>

/**
	@class FieldConnectorTester
	@brief �^����ꂽfield��p���ăe�X�g������N���X
	Test���ĂԍۂɁC���s�񐔁C���̎��s��clock���Ȃǂ��w�肷��
	@date 18th October 2011
	@author Kenichi Yorozu
 */
class FieldConnectorTester{
public:
	/**
		@brief Constructor
		@param field �t�B�[���h
		@param mode Test����Connector��Mode
		<ol>
			<li>Inhibitor</li>
			<li>Suppressor</li>
			<li>Probability-based Selector</li>
			<li>Probability-based Superposer</li>
		</ol>
		default: Wire
	 */
	FieldConnectorTester(const int* field, int mode);
	/**
		@brief Battery�Ԃ̍ő�̋������v��
		@param field �t�B�[���h
		@return Battery�Ԃ̍ő�̋���
	 */
	int maxBatteryDistance();
	/**
		@brief Battery�Ԃ̍ŏ��̋������v��
		@param field �t�B�[���h
		@return Battery�Ԃ̍ŏ��̋���
	 */
	int minBatteryDistance();
	/**
		@brief Battery�Ԃ̕��ς̋������v��
		@param field �t�B�[���h
		@return Battery�Ԃ̕��ϋ���
	 */
	double averageBatteryDistance();
	/**
		@brief Field����Battery�𐔂��グ��
		@return Field���Ɋ܂܂��Battery�̐�
	 */
	int countNumOfBatteries();
	/**
		@brief Execute Test
		maxTime = 100
		maxCount = 70 * 3  = 210
		�Ƃ����f�t�H���g�̃e�X�g
	 */
	void Test();
	/**
		@brief Execute Test
		@param maxTime ���s��
		@param maxCount ���̎��s��clock��
	 */
	void Test(int maxTime, int maxCount);
protected:
	///�^�X�N�t�B�[���h
	const int* field;
	///Test����Connector��Mode
	int mode;
	///Battery�̐�
	int numOfBattery;
	///���O�t�@�C����
	std::string testLogFileName;
	///���O�L�^�t�H���_path
	std::string testLogDirectoryPath;
	///���݂�clock��
	int count;
	///�S�[���ɂ��ǂ蒅�������s�̐�
	int numOfSuccess;
	///�S�[�����B�܂ł̕���clock��
	double aveSuccessClock;
	///���ς̐i�񂾋���
	double aveDistance;
	///�ő�o�b�e���[�ԋ���
	int maxBatD;
	///�ŏ��o�b�e���[�ԋ���
	int minBatD;
	///���σo�b�e���[�ԋ���
	double aveBatD;
};

#endif	//_FieldConnectorTester_H_