#pragma once

//�T�E���h�}�l�[�W��
class CSoundManager
{
private:
	//�T�E���h�̃}�b�v
	typedef std::map<int,CSound*> mapc;
	mapc Sound;
public:
	//�I�[�f�B�I�I�u�W�F�N�g
	CXAudio2 Audio;
	//�R���X�g���N�^
	CSoundManager();
	//�f�X�g���N�^
	virtual ~CSoundManager();
	//�I�[�f�B�I�I�u�W�F�N�g�̍쐬
	HRESULT Create();
	//wav���w�肵�ēǂݍ���
	HRESULT Load(int,Arc_Files*,FILE*,int*,X3DVoiceState*);
	//�S�ẴT�E���h�ƃI�[�f�B�I�I�u�W�F�N�g���X�V
	HRESULT Update();
	//wav��index���w�肵�č폜
	VOID Release(int,int);
	//wav��index���w�肵��SVoice��Ԃ�
	SVoice* Sv(int,int);
	//�}�b�v�̈ꗗ
	VOID Debug(TCHAR*,int,Arc_Files*);

};