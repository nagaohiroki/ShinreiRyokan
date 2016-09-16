#pragma once//ヘッダーの重複防止
//=======================================================
//waveファイル
//=======================================================
class LoadWave
{
private:
	enum{NOISE = 100};
	//メモリからよみとる
	char* m_ptr;
	//waveファイル
	HMMIO m_hMmio;
	//メディアからステータスを取得
	HRESULT Create(WAVEFORMATEX&);
public:
	//ファイル全体のサイズ
	DWORD m_dwSize;
	//wavフォーマット
	WAVEFORMATEX m_wfx;
	LoadWave();
	virtual ~LoadWave();
	//ファイルを開く
	HRESULT Open(TCHAR*);
	HRESULT Open(char*,UINT);
	//バッファを読み込む(バッファ,読み込むサイズ)
	LONG Read(BYTE*,LONG);
	//シーク(バイト単位)失敗なら-1を返す
	LONG SeekByte(LONG);
	//合計サンプル
	DWORD AllSamp();
	//合計再生時間
	float AllTime();
};
