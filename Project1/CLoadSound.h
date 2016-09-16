#pragma once

//サウンドマネージャ
class CSoundManager
{
private:
	//サウンドのマップ
	typedef std::map<int,CSound*> mapc;
	mapc Sound;
public:
	//オーディオオブジェクト
	CXAudio2 Audio;
	//コンストラクタ
	CSoundManager();
	//デストラクタ
	virtual ~CSoundManager();
	//オーディオオブジェクトの作成
	HRESULT Create();
	//wavを指定して読み込み
	HRESULT Load(int,Arc_Files*,FILE*,int*,X3DVoiceState*);
	//全てのサウンドとオーディオオブジェクトを更新
	HRESULT Update();
	//wavをindexを指定して削除
	VOID Release(int,int);
	//wavをindexを指定してSVoiceを返す
	SVoice* Sv(int,int);
	//マップの一覧
	VOID Debug(TCHAR*,int,Arc_Files*);

};