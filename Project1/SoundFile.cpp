//=======================================================
//waveファイル
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
	SAFE_DELETE_ARRAY(m_ptr);//ポインタの破棄
}
//メディアからステータスを取得
HRESULT LoadWave::Create(WAVEFORMATEX& waveFormat)
{
	//RIFFチャンク検索
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
	//フォーマットチャンク検索
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
	//データチャンク検索
	MMCKINFO dataChunk;
	dataChunk.ckid=mmioFOURCC('d','a','t','a');
	mmRes=mmioDescend(m_hMmio,&dataChunk,&riffChunk,MMIO_FINDCHUNK);
	if(mmRes!=MMSYSERR_NOERROR)
	{
		mmioClose(m_hMmio,0);
		CFile().Debug(_T("NotDataChunk\n"));
		return E_FAIL;
	}
	//全体のファイルサイズ
	m_dwSize = dataChunk.cksize;
	return S_OK;
}
//バッファの書き込み
LONG LoadWave::Read(BYTE* ppBuffer,LONG dwSize)
{
	LONG rsize =  mmioRead(m_hMmio,(HPSTR)ppBuffer,dwSize);
	//曲の最後になったときバッファを少し手前で終了する
	if(rsize < dwSize)
	{		
		//進んでしまったシークを戻す
		mmioSeek(m_hMmio,rsize,SEEK_END);
		return mmioRead(m_hMmio,(HPSTR)ppBuffer,rsize - NOISE);
	}
	return rsize;
	//mmioReedは読み込むとシーク位置が進む(読み込んだ部分のバッファサイズを返す)
//	return mmioRead(m_hMmio,(HPSTR)ppBuffer,dwSize);
}
//シーク(バイト単位)失敗なら-1を返す
LONG LoadWave::SeekByte(LONG off)
{
	LONG Off = off;
	if(Off <= NOISE){Off = NOISE;}
	//シーク位置の操作SEEK_CURは現在の位置からoffセット
	return mmioSeek(m_hMmio,Off,SEEK_SET);	
	
	//シーク位置の操作SEEK_CURは現在の位置からoffセット
//	return mmioSeek(m_hMmio,(LONG)off, SEEK_SET);	
}
//ファイルから読み込む
HRESULT LoadWave::Open(TCHAR* filepath)
{
	MMIOINFO mmioInfo;
	//Waveファイルオープン
	memset(&mmioInfo,0,sizeof(MMIOINFO));
	m_hMmio = mmioOpen(filepath,&mmioInfo,MMIO_READ);
	if(!m_hMmio)
	{
		TCHAR FileName[MAX_PATH];
		_stprintf_s(FileName,MAX_PATH,_T("%sが見つかりません\n"),filepath);
		CFile().Debug(FileName);
		return E_FAIL;
	}

	if(FAILED(Create(m_wfx))){return E_FAIL;}
	return S_OK;
}
//メモリーから読み込む
HRESULT LoadWave::Open(char* mem,UINT size)
{
	//メモリをコピー
	m_ptr = new char[size];
	memcpy(m_ptr,mem,size);

	//Waveファイルオープン
	MMIOINFO mmioInfo;
	memset(&mmioInfo,0,sizeof(MMIOINFO));
	mmioInfo.pchBuffer = m_ptr;	//メモリーバッファーの先頭アドレス
	mmioInfo.cchBuffer = size;	
	mmioInfo.fccIOProc = FOURCC_MEM;  //メモリーから読み込む
	m_hMmio = mmioOpen(NULL,&mmioInfo,MMIO_ALLOCBUF | MMIO_READ);
	if(!m_hMmio)
	{
		TCHAR FileName[MAX_PATH];
		_stprintf_s(FileName,MAX_PATH,_T("wavファイルメモリが見つかりません\n"));
		CFile().Debug(FileName);
		return E_FAIL;
	}
	//ステータスを取得
	if(FAILED(Create(m_wfx))){return E_FAIL;}
	return S_OK;
}
//合計サンプル
DWORD LoadWave::AllSamp()
{
	return m_dwSize / m_wfx.nBlockAlign;
}
//合計再生時間
float LoadWave::AllTime()
{
	return (float)m_dwSize / (float)m_wfx.nBlockAlign / (float)m_wfx.nSamplesPerSec;
}
