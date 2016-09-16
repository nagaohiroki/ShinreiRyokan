//SVoice------------------------------------------------------------------------------
//�R���X�g���N�^
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
//�f�X�g���N�^
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
//�擾
HRESULT SVoice::Create(CXAudio2* audio,LoadWave* lw,X3DVoiceState* x3d)
{	
	//�e�I�u�W�F�N�g���Q��
	m_pXAudio2 = audio;
	m_pLw = lw;
	//�\�[�X�{�C�X�̍쐬
	if(FAILED(m_pXAudio2->m_pXAudio2->CreateSourceVoice(&m_pSVoice,&m_pLw->m_wfx,XAUDIO2_VOICE_USEFILTER)))
	{
		CFile().Debug(_T("�\�[�X�{�C�X�̍쐬���s\n"));
		return E_FAIL;
	}	
	//��b��葽���̏ꍇ�o�b�t�@�͓��
	m_dwSwapSize = m_pLw->m_wfx.nAvgBytesPerSec;
	m_pBuffer[0] = new BYTE[m_dwSwapSize];
	m_pBuffer[1] = new BYTE[m_dwSwapSize];
	m_X3d = x3d;
	return S_OK;
}

//�ꎞ��~
HRESULT SVoice::Pause()
{
	if(Mode == VM_START){	Mode = VM_PAUSE_SIG;}
	return S_OK;
}
//�V�[�N
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
//�J�n
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
//���݂̍Đ��ʒu
float SVoice::Time()
{
	return (float)(m_State.SamplesPlayed - m_OnceSamp)/ (float)m_pLw->m_wfx.nSamplesPerSec +  ((float)SeekPos / (float)m_pLw->m_wfx.nAvgBytesPerSec );
}
//�Đ����Ԃ̒���
float SVoice::EndTime()
{
	return m_pLw->AllTime();
}

//�t�B���^�[�̃Z�b�g
VOID SVoice::SetFilter()
{
	m_pSVoice->SetFilterParameters(&m_X3d->Filter);
}
//�Đ������̔���
BOOL SVoice::Idol()
{
	return Mode == VM_START || Mode == VM_START_SIG;
}
//�X�V
HRESULT SVoice::Update()
{
	//�X�e�[�g�̎擾
	m_pSVoice->GetState(&m_State);
	//3D�X�V
	m_X3d->Update(m_pLw,m_pSVoice,m_pXAudio2);
	//���X�ɉ��ʂ��グ��
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
		//���X�ɉ��ʂ�������
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
	//�X�^�[�g���Ă���ꍇ�{�����[���ϓ��\
	if(Mode == VM_START)
	{
		m_pSVoice->SetVolume(m_X3d->m_fVol);
	}
	else
	{
		//����
		m_pSVoice->SetVolume(m_fNoiseVol);

	}

	//�I���t���O�������Ă��ꍇ�X���b�v�����s���Ȃ�
	if(m_buffer.Flags == XAUDIO2_END_OF_STREAM)
	{
		//�Đ����S�ɏI�������ꍇ������
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
		//�o�b�t�@�̓���ւ�
		if(m_State.BuffersQueued < 2)
		{
			//�o�b�t�@�̓ǂݍ��݂Ɠǂݍ��񂾃T�C�Y����
			m_pLw->SeekByte(Seek);
			m_buffer.AudioBytes = m_pLw->Read(m_pBuffer[m_iCount],m_dwSwapSize);
			Seek += m_buffer.AudioBytes;
			m_buffer.pAudioData = m_pBuffer[m_iCount];
			//�w��o�b�t�@�����������ꍇ�I���t���O
			if(m_buffer.AudioBytes < m_dwSwapSize )
			{				
				if(m_X3d->m_bLoop)
				{				
					m_OnceSamp = m_State.SamplesPlayed;//�T���v�����ꎞ�ۑ�				
					Seek = 0;//���[�v�t���O������ꍇ�V�[�N�ʒu��0��
				}
				else{ m_buffer.Flags = XAUDIO2_END_OF_STREAM; }
			}	
			//�{�C�X�Ƀo�b�t�@�𑗂�
			if(m_buffer.AudioBytes > 0 ){ m_pSVoice->SubmitSourceBuffer(&m_buffer);	}
			//�v���C�}�����Z�J���_���̓���ւ�
			m_iCount = 1 - m_iCount;
		}
	}	
	return S_OK;
}
//�f�o�b�O
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

