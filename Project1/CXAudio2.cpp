CXAudio2::CXAudio2()
{
	Effect = 0;
	Effect1 = 1;
	Volume = 1.0f;
	m_pXAudio2 = NULL;
	m_pMVoice  = NULL;	
	m_pReverb  = NULL;
	m_pSubmixVoice=NULL;
	m_dwCalcFlag = 0;
	m_wHardChannel = 0;
	//���X�i�[�R�[��
	ZeroMemory(&x3dCone,sizeof(X3DAUDIO_CONE));
	ZeroMemory(&x3dLis,sizeof(X3DAUDIO_LISTENER));
	x3dCone.InnerAngle = X3DAUDIO_PI * 5.0f / 6.0f;
	x3dCone.OuterAngle = X3DAUDIO_PI * 11.0f / 6.0f;
	x3dCone.InnerVolume = 1.0f;
	x3dCone.OuterVolume = 0.75f;
	x3dCone.InnerLPF = 0.0f;
	x3dCone.OuterLPF = 0.25f;
	x3dCone.InnerReverb = 0.708f;
	x3dCone.OuterReverb = 1.0f;
	//���X�i�[
	x3dLis.pCone =(X3DAUDIO_CONE*)&x3dCone;
	x3dLis.OrientFront = D3DXVECTOR3(0.0f,0.0f,1.0f);
	x3dLis.OrientTop   = D3DXVECTOR3(0.0f,1.0f,0.0f);
	x3dLis.Position	   = D3DXVECTOR3(0.0f,0.0f,0.0f);
	x3dLis.Velocity	   = D3DXVECTOR3(0.0f,0.0f,0.0f);
	//�x���V�e�B�ۑ��p
	LisPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
}
CXAudio2::~CXAudio2()
{
	//�T�u�~�b�N�X�{�C�X��j��
	if(m_pSubmixVoice != NULL)
	{
		m_pSubmixVoice->DestroyVoice();
		m_pSubmixVoice = NULL;	
	}
	//���o�[�u�G�t�F�N�g�̉��
	SAFE_RELEASE(m_pReverb);
	//�}�X�^�����O�{�C�X�̉��
	if(m_pMVoice != NULL)
	{
		m_pMVoice->DestroyVoice();
		m_pMVoice = NULL;
	}
	
	//XAudio�̉��
	if(m_pXAudio2 != NULL)
	{
		m_pXAudio2->StopEngine();
	}
	
	SAFE_RELEASE(m_pXAudio2);	
	//COM�̏I��
	CoUninitialize();
}
//�擾
HRESULT CXAudio2::Create()
{
	//COM������
	HRESULT hr;
	if(FAILED(hr = CoInitializeEx(NULL,COINIT_MULTITHREADED)))
	{
		CFile().Debug(_T("COM���������s\n"));
		return E_FAIL; 
	}
	//XAudio2�̎擾
	UINT32 flag = 0;	
#ifdef _DEBUG
	flag |= XAUDIO2_DEBUG_ENGINE;
#endif
	if(FAILED(hr = XAudio2Create(&m_pXAudio2,flag)))
	{
		CFile().Debug(_T("XAudio2�f�o�C�X�̎擾���s\n"));
		return E_FAIL;
	}
	//�}�X�^�[�{�C�X�̎擾
	if(FAILED(hr = m_pXAudio2->CreateMasteringVoice(&m_pMVoice)))
	{
		CFile().Debug(_T("�}�X�^�[�{�C�X�擾���s\n"));
		return E_FAIL;
	}	
	
	//�n�[�h���̃`�����l���̐���������
	XAUDIO2_DEVICE_DETAILS details;
	if(FAILED(	m_pXAudio2->GetDeviceDetails(0, &details )))
	{
		CFile().Debug(_T("�I�[�f�B�I�f�o�C�X���擾���s\n"));
		return E_FAIL;
	}
	//�`�����l����
	m_wHardChannel= details.OutputFormat.Format.nChannels;	
	//-------------------------------------------------
	//�G�t�F�N�g�̍쐬
	//-------------------------------------------------
	//���o�[�u���쐬
	flag = 0;
#ifdef _DEBUG
    flag |= XAUDIO2FX_DEBUG;
#endif
	if(FAILED(hr =XAudio2CreateReverb(&m_pReverb,flag)))
	{
		CFile().Debug(_T("���o�[�u�擾���s\n"));
		return E_FAIL;
	}	
	XAUDIO2_EFFECT_DESCRIPTOR effects[] = { { m_pReverb, TRUE, 1 } };
	XAUDIO2_EFFECT_CHAIN effectChain = { 1, effects };
	//-------------------------------------------------
	//���̉���
	//-------------------------------------------------	
	//���̉����̃t���O�̍쐬
	m_dwCalcFlag =  X3DAUDIO_CALCULATE_MATRIX     | X3DAUDIO_CALCULATE_DOPPLER 	|X3DAUDIO_CALCULATE_LPF_DIRECT 
				  | X3DAUDIO_CALCULATE_LPF_REVERB | X3DAUDIO_CALCULATE_REVERB;
	if((details.OutputFormat.dwChannelMask & SPEAKER_LOW_FREQUENCY) != 0)
	{
		m_dwCalcFlag |= X3DAUDIO_CALCULATE_REDIRECT_TO_LFE;
	}	
	//�T�u�~�b�N�X�{�C�X
	if(FAILED( hr = m_pXAudio2->CreateSubmixVoice(&m_pSubmixVoice,1,details.OutputFormat.Format.nSamplesPerSec,0,0,NULL,&effectChain)))
	{		
		CFile().Debug(_T("�T�u�~�b�N�X�{�C�X�擾���s\n"));
		return E_FAIL;
	}
	//X3DAudio�̏�����
	X3DAudioInitialize( details.OutputFormat.dwChannelMask,	X3DAUDIO_SPEED_OF_SOUND,x3dIns);	
	return S_OK;
}

//���o�[�u��ύX����
HRESULT CXAudio2::SetEffect(int Param)
{
	//���o�[�u
	XAUDIO2FX_REVERB_I3DL2_PARAMETERS RP[ 30 ] =
	{
		XAUDIO2FX_I3DL2_PRESET_DEFAULT,		
		XAUDIO2FX_I3DL2_PRESET_FOREST,
		XAUDIO2FX_I3DL2_PRESET_GENERIC,
		XAUDIO2FX_I3DL2_PRESET_PADDEDCELL,
		XAUDIO2FX_I3DL2_PRESET_ROOM,
		XAUDIO2FX_I3DL2_PRESET_BATHROOM,
		XAUDIO2FX_I3DL2_PRESET_LIVINGROOM,
		XAUDIO2FX_I3DL2_PRESET_STONEROOM,
		XAUDIO2FX_I3DL2_PRESET_AUDITORIUM,
		XAUDIO2FX_I3DL2_PRESET_CONCERTHALL,
		XAUDIO2FX_I3DL2_PRESET_CAVE,
		XAUDIO2FX_I3DL2_PRESET_ARENA,
		XAUDIO2FX_I3DL2_PRESET_HANGAR,
		XAUDIO2FX_I3DL2_PRESET_CARPETEDHALLWAY,
		XAUDIO2FX_I3DL2_PRESET_HALLWAY,
		XAUDIO2FX_I3DL2_PRESET_STONECORRIDOR,
		XAUDIO2FX_I3DL2_PRESET_ALLEY,
		XAUDIO2FX_I3DL2_PRESET_CITY,
		XAUDIO2FX_I3DL2_PRESET_MOUNTAINS,
		XAUDIO2FX_I3DL2_PRESET_QUARRY,
		XAUDIO2FX_I3DL2_PRESET_PLAIN,
		XAUDIO2FX_I3DL2_PRESET_PARKINGLOT,
		XAUDIO2FX_I3DL2_PRESET_SEWERPIPE,
		XAUDIO2FX_I3DL2_PRESET_UNDERWATER,
		XAUDIO2FX_I3DL2_PRESET_SMALLROOM,
		XAUDIO2FX_I3DL2_PRESET_MEDIUMROOM,
		XAUDIO2FX_I3DL2_PRESET_LARGEROOM,
		XAUDIO2FX_I3DL2_PRESET_MEDIUMHALL,
		XAUDIO2FX_I3DL2_PRESET_LARGEHALL,
		XAUDIO2FX_I3DL2_PRESET_PLATE,
	};
	XAUDIO2FX_REVERB_PARAMETERS native;
    ReverbConvertI3DL2ToNative( &RP[Param],&native );
	if(FAILED(	m_pSubmixVoice->SetEffectParameters(0,&native,sizeof(native))))
	{
		CFile().Debug(_T("�I�[�f�B�I�G�t�F�N�g�擾���s"));
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CXAudio2::Update()
{
	//�G�t�F�N�g
	if(Effect != Effect1)
	{
		if(FAILED(SetEffect(Effect))){return E_FAIL;}
		Effect1 = Effect;
	}
	//�x���V�e�B
	x3dLis.Velocity = 	LisPos - x3dLis.Position;
	LisPos = x3dLis.Position;
	//�{�����[��
	if(FAILED(m_pMVoice->SetVolume(Volume))){return E_FAIL;}
	return S_OK; 
}
