#pragma once

//サウンド
class CObjSound: public X3DVoiceState
{
private:


	//wavの中のインデックス
	int SoundIndex;
	//wavの種類
	int wavType;
	//ライブラリ
	MyLibrary* ML;
	//サウンドを取得していなかったら取得
	VOID GetSound(MyLibrary*);
public:
	//コンストラクタ
	CObjSound();
	//デストラクタ
	virtual ~CObjSound();
	//wavを指定
	VOID Set(arc);
	//再生開始
	VOID Start(MyLibrary*);
	//再生を停止してシークの位置を指定
	VOID Stop(MyLibrary*,float);
	//一時停止
	VOID Pause(MyLibrary*);
	//デバッグ
	VOID Debug(MyLibrary*,TCHAR*,int);
	//コーンを使用
	VOID ConeSet(BOOL);
	//SVoiceを返す
	SVoice* Sv(MyLibrary*);
};
