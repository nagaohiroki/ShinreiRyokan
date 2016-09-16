#pragma once
class X3DVoiceState
{
private:
	FLOAT32 DpsMat[16];
	FLOAT32 EmiMat[16];
	X3DAUDIO_DSP_SETTINGS DPS;
	BOOL SetSend;
	D3DXVECTOR3 EmiPos;
public:	
	//�m�C�Y
	float m_fNoise;
	//�t�B���^�^�C�v
	int Type;
	//����
	float m_fVol;
	//���[�v���邩
	BOOL m_bLoop;
	//���̉������g�����̃t���O
	BOOL m_b3DSound;
	//�e�I�u�W�F�N�g
	X3DAUDIO_CONE Cone;
	X3DAUDIO_EMITTER  Emi;
	//�t�B���^
	XAUDIO2_FILTER_PARAMETERS Filter;
	//�R���X�g���N�^
	X3DVoiceState();
	virtual ~X3DVoiceState();
	//�X�V
	HRESULT Update(LoadWave*,IXAudio2SourceVoice*,CXAudio2*);
};
