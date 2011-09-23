#ifndef _EnvUpdater_H_
#define _EnvUpdater_H_

/**
	@class EnvUpdater
	@brief ���{�b�g�̃A�N�`���G�[�^�[�ɉ����Ċ����X�V�����́D
	PhysX�Ȃǂ̑���ɂ��񂽂�Ȃ��̂��d���ށD
	<b>����ł́C��̈�̂�envUpdater���d���ނ悤�ȑz��ł���D</b>
	@date 23th September 2011
	@author Kenichi Yorozu
*/
class EnvUpdater {
public:
	/**
		@brief Constructor
		@param field Task Field
	*/
	EnvUpdater(int* field);
	/**
		@brief ���ϐ��̍X�V.
		@param progress �ǂ̂��炢�i�񂾂�(�߂�����)�DPositionUpdater�̏o�͂�����D
		@sa PositionUpdator
	*/
	void update(int progress);

	int getPosition();
	int* getField();

protected:
	/**
		@brief �ʒu(position)�̍X�V
		@param progress �ǂ̂��炢�i�񂾂�(�߂�����)�DPositionUpdater�̏o�͂�����D
		@sa PositionUpdater
	*/
	void updatePosition(int progress);

	///���݈ʒu
	int position;
	///Field�z��
	int* field;
};

inline int EnvUpdater::getPosition(){
	return position;
}

inline int* EnvUpdater::getField(){
	return field;
}

#endif //_EnvUpdater_H_