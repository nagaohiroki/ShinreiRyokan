#pragma once

//�T�E���h
class CObjSound: public X3DVoiceState
{
private:


	//wav�̒��̃C���f�b�N�X
	int SoundIndex;
	//wav�̎��
	int wavType;
	//���C�u����
	MyLibrary* ML;
	//�T�E���h���擾���Ă��Ȃ�������擾
	VOID GetSound(MyLibrary*);
public:
	//�R���X�g���N�^
	CObjSound();
	//�f�X�g���N�^
	virtual ~CObjSound();
	//wav���w��
	VOID Set(arc);
	//�Đ��J�n
	VOID Start(MyLibrary*);
	//�Đ����~���ăV�[�N�̈ʒu���w��
	VOID Stop(MyLibrary*,float);
	//�ꎞ��~
	VOID Pause(MyLibrary*);
	//�f�o�b�O
	VOID Debug(MyLibrary*,TCHAR*,int);
	//�R�[�����g�p
	VOID ConeSet(BOOL);
	//SVoice��Ԃ�
	SVoice* Sv(MyLibrary*);
};
