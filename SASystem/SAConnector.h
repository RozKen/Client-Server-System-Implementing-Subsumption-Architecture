#ifndef SAConnector_H_
#define SAConnector_H_

///無信号状態
#ifndef NO_SIGNAL	//先にSAModule.hで定義されているかも知れない
#define NO_SIGNAL	-12345.67f
#endif //NO_SIGNAL
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

	/**
		@brief getter of type
	 */
	int getType() const;
protected:
	///接続元の要素へのポインタ
	float* source;
	///接続先の要素へのポインタ
	float* destination;
	/**
		@brief 接続の方法.
		<ul>
			<li>Wire = 0</li>
			<li>Inhibit = 1</li>
			<li>Suppress = 2</li>
			<li>...Modified Suppress...</li>
		</ul>
	 */
	int type;
	///一回のModifyが有効な時間．単位はclock. nullの場合もある
	int timeToModify;
	///Modifyするかしないかを決めたりする確率．nullの場合もある
	float probModify;
	///残りModify時間.
	int timeLeftModified;
};

inline SAConnector::SAConnector(float* source, float* destination, int type)
	:source(source), destination(destination), type(type), timeToModify(0), timeLeftModified(0) {
}

inline SAConnector::SAConnector(float* source, float* destination, int type, int timeToModify)
	:source(source), destination(destination), type(type), timeToModify(timeToModify), timeLeftModified(0) {
}

inline SAConnector::SAConnector(float* source, float* destination, int type, int timeToModify, float probModify)
	:source(source), destination(destination), type(type), timeToModify(timeToModify), probModify(probModify), timeLeftModified(0) {
}

inline int SAConnector::getType() const{
	return type;
}

#endif //SAConnector_H_