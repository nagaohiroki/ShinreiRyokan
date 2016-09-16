#pragma once
class SVoice
{
private:
	enum VOICE_MODE
	{
		VM_STOP,
		VM_START,
		VM_STOP_SIG,
		VM_START_SIG,
		VM_PAUSE_SIG,		
	};
	//�{�C�X�̏��
	XAUDIO2_VOICE_STATE m_State;
	//�o�b�t�@
	XAUDIO2_BUFFER m_buffer;	
	//XAudio2
	CXAudio2 *m_pXAudio2;	
	//�o�b�t�@�|�C���^
	BYTE* m_pBuffer[2];
	//�o�b�t�@�̃J�E���^
	int m_iCount;
	//�o�b�t�@�̃T�C�Y
	DWORD m_dwSwapSize;
	//�m�C�Y�y������
	float m_fNoiseVol;
	//��~���̃T���v����ۑ�
	UINT64 m_OnceSamp;
	//�Đ��J�n�ʒu�w��
	LONG SeekPos;
	//�o�b�t�@�̌���
	LONG Seek;
	//�Đ����[�h
	VOICE_MODE Mode;
	//wave�f�[�^
	LoadWave *m_pLw;
	//���̉���
	X3DVoiceState* m_X3d;
	//�\�[�X�{�C�X
	IXAudio2SourceVoice* m_pSVoice;
public:	
	//�R���X�g���N�^
	SVoice();
	//�f�X�g���N�^
	virtual ~SVoice();
	//�擾
	HRESULT Create(CXAudio2*,LoadWave*,X3DVoiceState*);
	//�X�V
	HRESULT Update();
	//�ꎞ��~
	HRESULT Pause();
	//�V�[�N
	HRESULT Stop(float);
	//�Đ�
	HRESULT Start();
	//���݂̍Đ�����
	float Time();	
	//�t�B���^�[�̃Z�b�g
	VOID SetFilter();
	//�Đ����Ȃ�TRUE��Ԃ�
	BOOL Idol();	
	//�f�o�b�O
	VOID Debug(TCHAR*,int);
	float EndTime();
};