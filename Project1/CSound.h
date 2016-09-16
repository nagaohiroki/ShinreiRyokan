#pragma once
//サウンド
class CSound
{
private:
	//wav
	LoadWave m_Lw;
public:
	//wavの使用数
	int m_iCount;
	//SourceVoive
	std::vector<SVoice*> m_pSv;
	//コンストラクタ
	CSound();
	//デストラクタ
	virtual ~CSound();
	//読み込みとSVoiceの作成(すでに読み込んでいる場合はSVoiceのみ作成)
	HRESULT Load(int,Arc_Files*,FILE*,CXAudio2*,int*,X3DVoiceState*);
	//更新
	HRESULT Update();
	//カウントを減らす
	int Release(int);
};
