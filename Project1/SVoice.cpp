//SVoice------------------------------------------------------------------------------
//コンストラクタ
SVoice::SVoice()
{
	ZeroMemory(&m_State,sizeof(XAUDIO2_VOICE_STATE));
	ZeroMemory(&m_buffer,sizeof(XAUDIO2_BUFFER));	
	m_pLw = NULL;
	m_X3d = NULL;
	m_pXAudio2 = NULL;
	m_pSVoice = NULL;
	m_pBuffer[0] = NULL;
	m_pBuffer[1] = NULL;
	m_iCount = 0;
	m_dwSwapSize = 0;
	Mode = VM_STOP;
	m_OnceSamp = 0;
	m_fNoiseVol = 0.0f;
	Seek = 0;
	SeekPos = 0;
}
//デストラクタ
SVoice::~SVoice()
{
	if(m_pSVoice != NULL)
	{
		m_pSVoice->Stop();
		m_pSVoice->DestroyVoice();
		m_pSVoice = NULL;
	}
	SAFE_DELETE_ARRAY(m_pBuffer[0]);
	SAFE_DELETE_ARRAY(m_pBuffer[1]);
}
//取得
HRESULT SVoice::Create(CXAudio2* audio,LoadWave* lw,X3DVoiceState* x3d)
{	
	//各オブジェクトを参照
	m_pXAudio2 = audio;
	m_pLw = lw;
	//ソースボイスの作成
	if(FAILED(m_pXAudio2->m_pXAudio2->CreateSourceVoice(&m_pSVoice,&m_pLw->m_wfx,XAUDIO2_VOICE_USEFILTER)))
	{
		CFile().Debug(_T("ソースボイスの作成失敗\n"));
		return E_FAIL;
	}	
	//一秒より多いの場合バッファは二つ
	m_dwSwapSize = m_pLw->m_wfx.nAvgBytesPerSec;
	m_pBuffer[0] = new BYTE[m_dwSwapSize];
	m_pBuffer[1] = new BYTE[m_dwSwapSize];
	m_X3d = x3d;
	return S_OK;
}

//一時停止
HRESULT SVoice::Pause()
{
	if(Mode == VM_START){	Mode = VM_PAUSE_SIG;}
	return S_OK;
}
//シーク
HRESULT SVoice::Stop(float time)
{
	if(Mode == VM_START)
	{
		LONG t = (LONG)(time * (float)m_pLw->m_wfx.nAvgBytesPerSec);
		if(t < (LONG)m_pLw->m_dwSize){	SeekPos = t;	}	
		Mode = VM_STOP_SIG;
	}
	return S_OK;
}
//開始
HRESULT SVoice::Start()
{
	if(Mode == VM_STOP)
	{
		m_fNoiseVol =  0.0f;
		m_pSVoice->Start();	
		Mode = VM_START_SIG;
	}
	return S_OK;
}
//現在の再生位置
float SVoice::Time()
{
	return (float)(m_State.SamplesPlayed - m_OnceSamp)/ (float)m_pLw->m_wfx.nSamplesPerSec +  ((float)SeekPos / (float)m_pLw->m_wfx.nAvgBytesPerSec );
}
//再生時間の長さ
float SVoice::EndTime()
{
	return m_pLw->AllTime();
}

//フィルターのセット
VOID SVoice::SetFilter()
{
	m_pSVoice->SetFilterParameters(&m_X3d->Filter);
}
//再生中かの判定
BOOL SVoice::Idol()
{
	return Mode == VM_START || Mode == VM_START_SIG;
}
//更新
HRESULT SVoice::Update()
{
	//ステートの取得
	m_pSVoice->GetState(&m_State);
	//3D更新
	m_X3d->Update(m_pLw,m_pSVoice,m_pXAudio2);
	//徐々に音量を上げる
	//Start
	if(Mode == VM_START_SIG)
	{		
		m_fNoiseVol += m_X3d->m_fNoise;
		if(m_fNoiseVol >= m_X3d->m_fVol)
		{
			m_fNoiseVol = m_X3d->m_fVol;
			Mode = VM_START;
		}
	}
	//Pause
	else if(Mode == VM_PAUSE_SIG)
	{		
		//徐々に音量を下げる
		m_fNoiseVol -= m_X3d->m_fNoise;
		if(m_fNoiseVol <= 0.0f)
		{
			m_fNoiseVol = 0.0f;
			m_pSVoice->Stop();
			Mode = VM_STOP;
		}		
	}
	//Stop
	else if(Mode == VM_STOP_SIG)
	{
		m_fNoiseVol -= m_X3d->m_fNoise;
		if(m_fNoiseVol <= 0.0f)
		{
			m_fNoiseVol = 0.0f;
			m_pSVoice->Stop();
			Seek = SeekPos;
			m_OnceSamp = m_State.SamplesPlayed; 
			m_pSVoice->FlushSourceBuffers();
			Mode = VM_STOP;
		}		
	}
	//スタートしている場合ボリューム変動可能
	if(Mode == VM_START)
	{
		m_pSVoice->SetVolume(m_X3d->m_fVol);
	}
	else
	{
		//音量
		m_pSVoice->SetVolume(m_fNoiseVol);

	}

	//終了フラグが立ってた場合スワップを実行しない
	if(m_buffer.Flags == XAUDIO2_END_OF_STREAM)
	{
		//再生完全に終了した場合頭だし
		if(m_State.BuffersQueued == 0)
		{
			m_OnceSamp = 0;
			m_buffer.Flags = 0;
			Mode = VM_STOP;	
			SeekPos = 0;
			Seek = 0;
			m_pSVoice->Stop();	
			m_pSVoice->FlushSourceBuffers();
		}
	}
	else
	{
		//バッファの入れ替え
		if(m_State.BuffersQueued < 2)
		{
			//バッファの読み込みと読み込んだサイズを代入
			m_pLw->SeekByte(Seek);
			m_buffer.AudioBytes = m_pLw->Read(m_pBuffer[m_iCount],m_dwSwapSize);
			Seek += m_buffer.AudioBytes;
			m_buffer.pAudioData = m_pBuffer[m_iCount];
			//指定バッファ未満だった場合終了フラグ
			if(m_buffer.AudioBytes < m_dwSwapSize )
			{				
				if(m_X3d->m_bLoop)
				{				
					m_OnceSamp = m_State.SamplesPlayed;//サンプルを一時保存				
					Seek = 0;//ループフラグがある場合シーク位置を0に
				}
				else{ m_buffer.Flags = XAUDIO2_END_OF_STREAM; }
			}	
			//ボイスにバッファを送る
			if(m_buffer.AudioBytes > 0 ){ m_pSVoice->SubmitSourceBuffer(&m_buffer);	}
			//プライマリをセカンダリの入れ替え
			m_iCount = 1 - m_iCount;
		}
	}	
	return S_OK;
}
//デバッグ
VOID SVoice::Debug(TCHAR* txt,int len)
{
	_stprintf_s(txt,len,
		_T("vol%f\ntime %f\nALLTime %f\nMode = %d\n")
		_T("seekpos = %d\nIdol = %d\n")
		_T("Seek = %ld\n")
		,m_fNoiseVol,Time(),m_pLw->AllTime(),Mode
		,SeekPos,Idol(),Seek
		);
}

