//=======================================================
//wave�t�@�C��
//=======================================================
LoadWave::LoadWave()
{
	m_ptr =NULL;
	m_hMmio =NULL;
	m_dwSize = 0;
	ZeroMemory(&m_wfx,sizeof(WAVEFORMATEX));	
}
LoadWave::~LoadWave()
{
	mmioClose(m_hMmio, 0 );
	SAFE_DELETE_ARRAY(m_ptr);//�|�C���^�̔j��
}
//���f�B�A����X�e�[�^�X���擾
HRESULT LoadWave::Create(WAVEFORMATEX& waveFormat)
{
	//RIFF�`�����N����
	MMCKINFO riffChunk;
	MMRESULT mmRes;
	riffChunk.fccType=mmioFOURCC('W','A','V','E');
	mmRes = mmioDescend(m_hMmio,&riffChunk,NULL,MMIO_FINDRIFF);
	if(mmRes!=MMSYSERR_NOERROR)
	{	
		mmioClose(m_hMmio,0);
		CFile().Debug(_T("NotRIFF"));
		return E_FAIL;
	}
	//�t�H�[�}�b�g�`�����N����
	MMCKINFO formatChunk;
	formatChunk.ckid=mmioFOURCC('f','m','t',' ');
	mmRes=mmioDescend(m_hMmio,&formatChunk,&riffChunk,MMIO_FINDCHUNK);
	if(mmRes!=MMSYSERR_NOERROR)
	{
		mmioClose(m_hMmio,0);
		CFile().Debug(_T("NotFormatChunk\n"));
		return E_FAIL;
	}
	DWORD fmsize=formatChunk.cksize;
	DWORD size=mmioRead(m_hMmio,(HPSTR)&waveFormat,fmsize);
	if(size!=fmsize)
	{
		mmioClose(m_hMmio,0);
		CFile().Debug(_T("NotFormatChunkSize\n"));
		return E_FAIL;
	}
	mmioAscend(m_hMmio,&formatChunk,0);
	//�f�[�^�`�����N����
	MMCKINFO dataChunk;
	dataChunk.ckid=mmioFOURCC('d','a','t','a');
	mmRes=mmioDescend(m_hMmio,&dataChunk,&riffChunk,MMIO_FINDCHUNK);
	if(mmRes!=MMSYSERR_NOERROR)
	{
		mmioClose(m_hMmio,0);
		CFile().Debug(_T("NotDataChunk\n"));
		return E_FAIL;
	}
	//�S�̂̃t�@�C���T�C�Y
	m_dwSize = dataChunk.cksize;
	return S_OK;
}
//�o�b�t�@�̏�������
LONG LoadWave::Read(BYTE* ppBuffer,LONG dwSize)
{
	LONG rsize =  mmioRead(m_hMmio,(HPSTR)ppBuffer,dwSize);
	//�Ȃ̍Ō�ɂȂ����Ƃ��o�b�t�@��������O�ŏI������
	if(rsize < dwSize)
	{		
		//�i��ł��܂����V�[�N��߂�
		mmioSeek(m_hMmio,rsize,SEEK_END);
		return mmioRead(m_hMmio,(HPSTR)ppBuffer,rsize - NOISE);
	}
	return rsize;
	//mmioReed�͓ǂݍ��ނƃV�[�N�ʒu���i��(�ǂݍ��񂾕����̃o�b�t�@�T�C�Y��Ԃ�)
//	return mmioRead(m_hMmio,(HPSTR)ppBuffer,dwSize);
}
//�V�[�N(�o�C�g�P��)���s�Ȃ�-1��Ԃ�
LONG LoadWave::SeekByte(LONG off)
{
	LONG Off = off;
	if(Off <= NOISE){Off = NOISE;}
	//�V�[�N�ʒu�̑���SEEK_CUR�͌��݂̈ʒu����off�Z�b�g
	return mmioSeek(m_hMmio,Off,SEEK_SET);	
	
	//�V�[�N�ʒu�̑���SEEK_CUR�͌��݂̈ʒu����off�Z�b�g
//	return mmioSeek(m_hMmio,(LONG)off, SEEK_SET);	
}
//�t�@�C������ǂݍ���
HRESULT LoadWave::Open(TCHAR* filepath)
{
	MMIOINFO mmioInfo;
	//Wave�t�@�C���I�[�v��
	memset(&mmioInfo,0,sizeof(MMIOINFO));
	m_hMmio = mmioOpen(filepath,&mmioInfo,MMIO_READ);
	if(!m_hMmio)
	{
		TCHAR FileName[MAX_PATH];
		_stprintf_s(FileName,MAX_PATH,_T("%s��������܂���\n"),filepath);
		CFile().Debug(FileName);
		return E_FAIL;
	}

	if(FAILED(Create(m_wfx))){return E_FAIL;}
	return S_OK;
}
//�������[����ǂݍ���
HRESULT LoadWave::Open(char* mem,UINT size)
{
	//���������R�s�[
	m_ptr = new char[size];
	memcpy(m_ptr,mem,size);

	//Wave�t�@�C���I�[�v��
	MMIOINFO mmioInfo;
	memset(&mmioInfo,0,sizeof(MMIOINFO));
	mmioInfo.pchBuffer = m_ptr;	//�������[�o�b�t�@�[�̐擪�A�h���X
	mmioInfo.cchBuffer = size;	
	mmioInfo.fccIOProc = FOURCC_MEM;  //�������[����ǂݍ���
	m_hMmio = mmioOpen(NULL,&mmioInfo,MMIO_ALLOCBUF | MMIO_READ);
	if(!m_hMmio)
	{
		TCHAR FileName[MAX_PATH];
		_stprintf_s(FileName,MAX_PATH,_T("wav�t�@�C����������������܂���\n"));
		CFile().Debug(FileName);
		return E_FAIL;
	}
	//�X�e�[�^�X���擾
	if(FAILED(Create(m_wfx))){return E_FAIL;}
	return S_OK;
}
//���v�T���v��
DWORD LoadWave::AllSamp()
{
	return m_dwSize / m_wfx.nBlockAlign;
}
//���v�Đ�����
float LoadWave::AllTime()
{
	return (float)m_dwSize / (float)m_wfx.nBlockAlign / (float)m_wfx.nSamplesPerSec;
}
