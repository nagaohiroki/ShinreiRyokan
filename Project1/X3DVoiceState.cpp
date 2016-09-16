
//�R���X�g���N�^
X3DVoiceState::X3DVoiceState()
{
	m_fNoise = 0.2f;
	SetSend = FALSE;
	m_fVol = 1.0f;
	m_bLoop = FALSE;	
	//���̉���������
	m_b3DSound = FALSE;
	//�t�B���^
	Filter.Frequency = 1.0f;
	Filter.OneOverQ = 1.0f;
	Filter.Type = LowPassFilter;
	Type = 0;
	//���̉����I�u�W�F�N�g
	ZeroMemory(&Cone,sizeof(X3DAUDIO_CONE));
	ZeroMemory(&DPS,sizeof(X3DAUDIO_DSP_SETTINGS));
	ZeroMemory(&Emi,sizeof(X3DAUDIO_EMITTER));
	//DPS
	DPS.pMatrixCoefficients = DpsMat;
	DPS.pDelayTimes = NULL;
	//�G�~�b�^�[�̃R�[���̐ݒ�
	Cone.InnerAngle  = 0.0f;
	Cone.OuterAngle  = 0.0f;
	Cone.InnerVolume = 0.0f;
	Cone.OuterVolume = 1.0f;
	Cone.InnerLPF    = 0.0f;
	Cone.OuterLPF    = 1.0f;
	Cone.InnerReverb = 0.0f;
	Cone.OuterReverb = 1.0f;
	//�G�~�b�^�[
	Emi.ChannelRadius = 0.0f;
	Emi.pChannelAzimuths = EmiMat;
	Emi.CurveDistanceScaler = 14.0f;
	Emi.DopplerScaler = 1.0f;
	Emi.OrientFront = D3DXVECTOR3(0.0f,0.0f,1.0f);
	Emi.OrientTop   = D3DXVECTOR3(0.0f,1.0f,0.0f);
	Emi.Position	= D3DXVECTOR3(0.0f,0.0f,0.0f);
	Emi.Velocity	= D3DXVECTOR3(1.0f,1.0f,1.0f);
	Emi.InnerRadius = 2.0f;
	Emi.InnerRadiusAngle = X3DAUDIO_PI/4.0f;
	Emi.pVolumeCurve = (X3DAUDIO_DISTANCE_CURVE*)&X3DAudioDefault_LinearCurve;
	Emi.pLFECurve= NULL;
	Emi.pReverbCurve =NULL; 
	Emi.pLPFDirectCurve = NULL;
	Emi.pLPFReverbCurve = NULL;
//	Emi.pCone = &Cone;
	Emi.pCone = NULL;
	//�x���V�e�B�ۑ��p
	EmiPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
}
X3DVoiceState::~X3DVoiceState()
{}
//�X�V
HRESULT X3DVoiceState::Update(LoadWave* pLw,IXAudio2SourceVoice* pSVoice,CXAudio2 *pXAudio2)
{
	//wav�t�@�C���̃`�����l���𓖂Ă�
	DPS.SrcChannelCount = pLw->m_wfx.nChannels;
	//�o�͑��̃`�����l����
	DPS.DstChannelCount = pXAudio2->m_wHardChannel;
	//�G�~�b�^�[��wav�t�@�C���̃`�����l���𓖂Ă�
	Emi.ChannelCount = pLw->m_wfx.nChannels;
	if(m_b3DSound)
	{
		if(!SetSend)
		{
			XAUDIO2_SEND_DESCRIPTOR sendDescriptors[2];
			sendDescriptors[0].Flags = XAUDIO2_SEND_USEFILTER; 
			sendDescriptors[0].pOutputVoice = pXAudio2->m_pMVoice;
			sendDescriptors[1].Flags = XAUDIO2_SEND_USEFILTER; 
			sendDescriptors[1].pOutputVoice = pXAudio2->m_pSubmixVoice;
			const XAUDIO2_VOICE_SENDS sendList = { 2, sendDescriptors };
			pSVoice->SetOutputVoices(&sendList);
			SetSend = TRUE;
		}
		//�x���V�e�B
		Emi.Velocity = EmiPos - Emi.Position;
		EmiPos = Emi.Position;
		//���̉������Z�b�g
		X3DAudioCalculate(pXAudio2->x3dIns,&pXAudio2->x3dLis,&Emi,pXAudio2->m_dwCalcFlag,&DPS);		
		XAUDIO2_FILTER_PARAMETERS FilterParametersDirect={LowPassFilter,2.0f * sinf(X3DAUDIO_PI/6.0f * DPS.LPFDirectCoefficient),1.0f}; 
		XAUDIO2_FILTER_PARAMETERS FilterParametersReverb={LowPassFilter,2.0f * sinf(X3DAUDIO_PI/6.0f * DPS.LPFReverbCoefficient),1.0f};
		//�h�b�v���[�̃Z�b�g
		pSVoice->SetFrequencyRatio(DPS.DopplerFactor);
		pSVoice->SetOutputMatrix(pXAudio2->m_pMVoice,DPS.SrcChannelCount,pXAudio2->m_wHardChannel,DPS.pMatrixCoefficients);
		pSVoice->SetOutputMatrix(pXAudio2->m_pSubmixVoice,DPS.SrcChannelCount,1,&DPS.ReverbLevel);
		//�T�u�~�b�N�X���Z�b�g
		pSVoice->SetOutputFilterParameters(pXAudio2->m_pMVoice,&FilterParametersDirect);
		pSVoice->SetOutputFilterParameters(pXAudio2->m_pSubmixVoice,&FilterParametersReverb);
	}
	else
	{	
		SetSend = FALSE;
		//�G�t�F�N�g���J�b�g
		pSVoice->SetOutputVoices(NULL);
	}
	//�t�B���^�̃Z�b�g
	Filter.Type =  (XAUDIO2_FILTER_TYPE)Type;
	pSVoice->SetFilterParameters(&Filter);
	return S_OK;
}
