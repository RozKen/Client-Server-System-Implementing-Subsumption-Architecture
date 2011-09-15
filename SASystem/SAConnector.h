#ifndef SAConnector_H_
#define SAConnector_H_
/**
	@brief 
 */
class SAConnector
{
public:
	
	/**
		@brief Default Constructor
	 */
	SAConnector(float* source, float* destination, int type);
	/**
		@brief Default Constructor for Modifiers
	 */
	SAConnector(float* source, float* destination, int type, int timeToModify);
	/**
		@brief Constructor for Original Modifiers
	 */
	SAConnector(float* source, float* destination, int type, int timeToModify, float probModify);

	/**
		@brief Transfer/Modify Signal
	 */
	void Process();
protected:
	///�ڑ����̗v�f�ւ̃|�C���^
	float* source;
	///�ڑ���̗v�f�ւ̃|�C���^
	float* destination;
	/**
		@brief �ڑ��̕��@.
		<ul>
			<li>Wire = 0</li>
			<li>Inhibit = 1</li>
			<li>Suppress = 2</li>
			<li>...Modified Suppress...</li>
		</ul>
	 */
	int type;
	///����Modify���L���Ȏ��ԁD�P�ʂ�clock. null�̏ꍇ������
	int timeToModify;
	///Modify���邩���Ȃ��������߂��肷��m���Dnull�̏ꍇ������
	float probModify;
};

inline SAConnector::SAConnector(float* source, float* destination, int type)
	:source(source), destination(destination), type(type) {
}

inline SAConnector::SAConnector(float* source, float* destination, int type, int timeToModify)
	:source(source), destination(destination), type(type), timeToModify(timeToModify) {
}

inline SAConnector::SAConnector(float* source, float* destination, int type, int timeToModify, float probModify)
	:source(source), destination(destination), type(type), timeToModify(timeToModify), probModify(probModify) {
}

inline SAConnector::Process(){
	*destination = *source;
}
#endif //SAConnector_H_