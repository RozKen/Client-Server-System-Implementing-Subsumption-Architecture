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