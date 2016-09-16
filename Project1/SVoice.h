#pragma once
class SVoice
{
private:
	enum VOICE_MODE
	{
		VM_STOP,
		VM_START,
		VM_STOP_SIG,
		VM_START_SIG,
		VM_PAUSE_SIG,		
	};
	//ボイスの状態
	XAUDIO2_VOICE_STATE m_State;
	//バッファ
	XAUDIO2_BUFFER m_buffer;	
	//XAudio2
	CXAudio2 *m_pXAudio2;	
	//バッファポインタ
	BYTE* m_pBuffer[2];
	//バッファのカウンタ
	int m_iCount;
	//バッファのサイズ
	DWORD m_dwSwapSize;
	//ノイズ軽減処理
	float m_fNoiseVol;
	//停止時のサンプルを保存
	UINT64 m_OnceSamp;
	//再生開始位置指定
	LONG SeekPos;
	//バッファの交換
	LONG Seek;
	//再生モード
	VOICE_MODE Mode;
	//waveデータ
	LoadWave *m_pLw;
	//立体音響
	X3DVoiceState* m_X3d;
	//ソースボイス
	IXAudio2SourceVoice* m_pSVoice;
public:	
	//コンストラクタ
	SVoice();
	//デストラクタ
	virtual ~SVoice();
	//取得
	HRESULT Create(CXAudio2*,LoadWave*,X3DVoiceState*);
	//更新
	HRESULT Update();
	//一時停止
	HRESULT Pause();
	//シーク
	HRESULT Stop(float);
	//再生
	HRESULT Start();
	//現在の再生時間
	float Time();	
	//フィルターのセット
	VOID SetFilter();
	//再生中ならTRUEを返す
	BOOL Idol();	
	//デバッグ
	VOID Debug(TCHAR*,int);
	float EndTime();
};