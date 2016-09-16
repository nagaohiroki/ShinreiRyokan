#pragma once

enum Audio_Effect
{
	AE_DEFAULT,
	AE_FOREST,
	AE_GENERIC,
	AE_PADDEDCELL,
	AE_ROOM,
	AE_BATHROOM,
	AE_LIVINGROOM,
	AE_STONEROOM,
	AE_AUDITORIUM,
	AE_CONCERTHALL,
	AE_CAVE,
	AE_ARENA,
	AE_HANGAR,
	AE_CARPETEDHALLWAY,
	AE_HALLWAY,
	AE_STONECORRIDOR,
	AE_ALLEY,
	AE_CITY,
	AE_MOUNTAINS,
	AE_QUARRY,
	AE_PLAIN,
	AE_PARKINGLOT,
	AE_SEWERPIPE,
	AE_UNDERWATER,
	AE_SMALLROOM,
	AE_MEDIUMROOM,
	AE_LARGEROOM,
	AE_MEDIUMHALL,
	AE_LARGEHALL,
	AE_PLATE,
};

class CXAudio2
{	
private:
	D3DXVECTOR3 LisPos;
	int Effect1;
	//���o�[�u
	IUnknown* m_pReverb;
	//���o�[�u��ύX����
	HRESULT SetEffect(int);
public:
	int Effect;
	float Volume;
	//XAudio2�I�u�W�F�N�g
	IXAudio2* m_pXAudio2;
	//�}�X�^�[�{�C�X
	IXAudio2MasteringVoice* m_pMVoice;	
	//�T�u�~�b�N�X�{�C�X
	IXAudio2SubmixVoice* m_pSubmixVoice;
	//���̉����t���O
	UINT32 m_dwCalcFlag;

	//�`�����l����
	UINT32 m_wHardChannel;
	//���X�i�[�R�[��
	X3DAUDIO_CONE	  x3dCone;
	//���X�i�[
	X3DAUDIO_LISTENER x3dLis;	
	//�C���X�^���X
	X3DAUDIO_HANDLE   x3dIns;
	//�R���X�g���N�^
	CXAudio2();
	//�f�X�g���N�^
	virtual ~CXAudio2();
	//�{�C�X�̎擾
	HRESULT Create();
	
	HRESULT Update();
};
