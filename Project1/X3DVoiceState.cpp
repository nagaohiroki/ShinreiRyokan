
//コンストラクタ
X3DVoiceState::X3DVoiceState()
{
	m_fNoise = 0.2f;
	SetSend = FALSE;
	m_fVol = 1.0f;
	m_bLoop = FALSE;	
	//立体音響初期化
	m_b3DSound = FALSE;
	//フィルタ
	Filter.Frequency = 1.0f;
	Filter.OneOverQ = 1.0f;
	Filter.Type = LowPassFilter;
	Type = 0;
	//立体音響オブジェクト
	ZeroMemory(&Cone,sizeof(X3DAUDIO_CONE));
	ZeroMemory(&DPS,sizeof(X3DAUDIO_DSP_SETTINGS));
	ZeroMemory(&Emi,sizeof(X3DAUDIO_EMITTER));
	//DPS
	DPS.pMatrixCoefficients = DpsMat;
	DPS.pDelayTimes = NULL;
	//エミッターのコーンの設定
	Cone.InnerAngle  = 0.0f;
	Cone.OuterAngle  = 0.0f;
	Cone.InnerVolume = 0.0f;
	Cone.OuterVolume = 1.0f;
	Cone.InnerLPF    = 0.0f;
	Cone.OuterLPF    = 1.0f;
	Cone.InnerReverb = 0.0f;
	Cone.OuterReverb = 1.0f;
	//エミッター
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
	//ベロシティ保存用
	EmiPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
}
X3DVoiceState::~X3DVoiceState()
{}
//更新
HRESULT X3DVoiceState::Update(LoadWave* pLw,IXAudio2SourceVoice* pSVoice,CXAudio2 *pXAudio2)
{
	//wavファイルのチャンネルを当てる
	DPS.SrcChannelCount = pLw->m_wfx.nChannels;
	//出力側のチャンネル数
	DPS.DstChannelCount = pXAudio2->m_wHardChannel;
	//エミッターのwavファイルのチャンネルを当てる
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
		//ベロシティ
		Emi.Velocity = EmiPos - Emi.Position;
		EmiPos = Emi.Position;
		//立体音響をセット
		X3DAudioCalculate(pXAudio2->x3dIns,&pXAudio2->x3dLis,&Emi,pXAudio2->m_dwCalcFlag,&DPS);		
		XAUDIO2_FILTER_PARAMETERS FilterParametersDirect={LowPassFilter,2.0f * sinf(X3DAUDIO_PI/6.0f * DPS.LPFDirectCoefficient),1.0f}; 
		XAUDIO2_FILTER_PARAMETERS FilterParametersReverb={LowPassFilter,2.0f * sinf(X3DAUDIO_PI/6.0f * DPS.LPFReverbCoefficient),1.0f};
		//ドップラーのセット
		pSVoice->SetFrequencyRatio(DPS.DopplerFactor);
		pSVoice->SetOutputMatrix(pXAudio2->m_pMVoice,DPS.SrcChannelCount,pXAudio2->m_wHardChannel,DPS.pMatrixCoefficients);
		pSVoice->SetOutputMatrix(pXAudio2->m_pSubmixVoice,DPS.SrcChannelCount,1,&DPS.ReverbLevel);
		//サブミックスをセット
		pSVoice->SetOutputFilterParameters(pXAudio2->m_pMVoice,&FilterParametersDirect);
		pSVoice->SetOutputFilterParameters(pXAudio2->m_pSubmixVoice,&FilterParametersReverb);
	}
	else
	{	
		SetSend = FALSE;
		//エフェクトをカット
		pSVoice->SetOutputVoices(NULL);
	}
	//フィルタのセット
	Filter.Type =  (XAUDIO2_FILTER_TYPE)Type;
	pSVoice->SetFilterParameters(&Filter);
	return S_OK;
}
