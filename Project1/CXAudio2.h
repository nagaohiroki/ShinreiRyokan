#pragma once

enum Audio_Effect
{
	AE_DEFAULT,
	AE_FOREST,
	AE_GENERIC,
	AE_PADDEDCELL,
	AE_ROOM,
	AE_BATHROOM,
	AE_LIVINGROOM,
	AE_STONEROOM,
	AE_AUDITORIUM,
	AE_CONCERTHALL,
	AE_CAVE,
	AE_ARENA,
	AE_HANGAR,
	AE_CARPETEDHALLWAY,
	AE_HALLWAY,
	AE_STONECORRIDOR,
	AE_ALLEY,
	AE_CITY,
	AE_MOUNTAINS,
	AE_QUARRY,
	AE_PLAIN,
	AE_PARKINGLOT,
	AE_SEWERPIPE,
	AE_UNDERWATER,
	AE_SMALLROOM,
	AE_MEDIUMROOM,
	AE_LARGEROOM,
	AE_MEDIUMHALL,
	AE_LARGEHALL,
	AE_PLATE,
};

class CXAudio2
{	
private:
	D3DXVECTOR3 LisPos;
	int Effect1;
	//リバーブ
	IUnknown* m_pReverb;
	//リバーブを変更する
	HRESULT SetEffect(int);
public:
	int Effect;
	float Volume;
	//XAudio2オブジェクト
	IXAudio2* m_pXAudio2;
	//マスターボイス
	IXAudio2MasteringVoice* m_pMVoice;	
	//サブミックスボイス
	IXAudio2SubmixVoice* m_pSubmixVoice;
	//立体音響フラグ
	UINT32 m_dwCalcFlag;

	//チャンネル数
	UINT32 m_wHardChannel;
	//リスナーコーン
	X3DAUDIO_CONE	  x3dCone;
	//リスナー
	X3DAUDIO_LISTENER x3dLis;	
	//インスタンス
	X3DAUDIO_HANDLE   x3dIns;
	//コンストラクタ
	CXAudio2();
	//デストラクタ
	virtual ~CXAudio2();
	//ボイスの取得
	HRESULT Create();
	
	HRESULT Update();
};
