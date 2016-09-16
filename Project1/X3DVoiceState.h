#pragma once
class X3DVoiceState
{
private:
	FLOAT32 DpsMat[16];
	FLOAT32 EmiMat[16];
	X3DAUDIO_DSP_SETTINGS DPS;
	BOOL SetSend;
	D3DXVECTOR3 EmiPos;
public:	
	//ノイズ
	float m_fNoise;
	//フィルタタイプ
	int Type;
	//音量
	float m_fVol;
	//ループするか
	BOOL m_bLoop;
	//立体音響を使うかのフラグ
	BOOL m_b3DSound;
	//各オブジェクト
	X3DAUDIO_CONE Cone;
	X3DAUDIO_EMITTER  Emi;
	//フィルタ
	XAUDIO2_FILTER_PARAMETERS Filter;
	//コンストラクタ
	X3DVoiceState();
	virtual ~X3DVoiceState();
	//更新
	HRESULT Update(LoadWave*,IXAudio2SourceVoice*,CXAudio2*);
};
