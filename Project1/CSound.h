#pragma once
//�T�E���h
class CSound
{
private:
	//wav
	LoadWave m_Lw;
public:
	//wav�̎g�p��
	int m_iCount;
	//SourceVoive
	std::vector<SVoice*> m_pSv;
	//�R���X�g���N�^
	CSound();
	//�f�X�g���N�^
	virtual ~CSound();
	//�ǂݍ��݂�SVoice�̍쐬(���łɓǂݍ���ł���ꍇ��SVoice�̂ݍ쐬)
	HRESULT Load(int,Arc_Files*,FILE*,CXAudio2*,int*,X3DVoiceState*);
	//�X�V
	HRESULT Update();
	//�J�E���g�����炷
	int Release(int);
};
