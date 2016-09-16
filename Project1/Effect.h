#pragma once

//パス
namespace fx
{
	enum Pass
	{
		Mesh,
		Mesh_Tex,
		Mesh_AlphaTex,
		Mesh_Bump,
		ShadowMap,
		ShadowAlphaMap,
		FVF,
		FVF_Tex,
		FVF_Tex_Point,
		FVF_Tex_One,
		Tone,
		GaussX,
		GaussY,
	};
};


//グローバル変数
namespace prm
{
	enum
	{
		float4x4_mW ,
		float4x4_mVP ,
		float4x4_mLight ,
		float4_vLightDir ,
		float4_vColor ,
		float3_vEyePos ,
		float4_SP ,
		float4_SBias ,
		float4_vFog ,
		float4_vFogColor ,
		int_vFogUse ,
		float4_PixelUV ,
		float4_BloomColor ,
		float3_CamPos ,
		float4_PLightDif ,
		float4_PLightPos ,
		float4_PLightVec ,
		texture_Tex,
		texture_ShadowTex,
		texture_NormalTex,
		float_w,
		float4_GaussMap ,
		PRM_MAX,
	};
};
//============================================
//HLSL
//============================================
class CEffect
{
private:
	D3DXHANDLE m_hTechnique;
	D3DXHANDLE *Handle;
	D3DXMATRIX matLight;	
	D3DXMATRIX matView;
	D3DXMATRIX matProj;	
	D3DXMATRIX mL;
	BOOL BeginFlag;//ビギンが呼ばれているかのフラグ
	BOOL PassFlag;//パスが閉じているかのフラグ
	int  fxPass;//現在のパス	

	//カメラ用カリング
	D3DXVECTOR3 CullPos;

	//ライトスペースパースぺクティブシャドウマップ
	LiSPSM Lisp;
	//エフェクト
	LPD3DXEFFECT	m_pEffect;
		//ハンドルのセット
	HRESULT SetHandle();
	//ハンドルを返す
	D3DXHANDLE Hn(size_t);
	//オブジェクト更新
	VOID UpdateLight();
	VOID UpdateFog();	
	VOID UpdatePointLight();
	
public:		
	VOID UpdateCam();		
	BOOL MirrorFlag;
	int MirrorPass;
	Cam Mirrorcam;
	
	D3DXMATRIX matPxV;
	
	//トーンマップ
	D3DXVECTOR4 Tone;
	//エフェクト情報
	unsigned int pass;//passの数
	float Fade;
	//ポイントライト関連
	PointSpotLight PSL;
	LightState Ls;
	FogState Fs;
	Cam cam;
	//シャドウマップパス1が影0が通常ドロー
	int ShadowPassNum;
	BOOL ShadowFlag;	
	CEffect();
	virtual ~CEffect();
	VOID begin();
	HRESULT Create(LPDIRECT3DDEVICE9);//ファイルからエフェクトを作成 
	HRESULT Create(LPDIRECT3DDEVICE9,char*,UINT);//メモリからエフェクトを作成
	HRESULT Reset();//リセット前に行う
	HRESULT Restore();//リセット後に行う
	VOID SetPLCol(D3DXVECTOR4*);//ポイントライト
	D3DXVECTOR3 LightCol(); 
	VOID LightLamSpc(D3DXMATRIX*,float);//鏡面反射とランバート反射
	VOID ShadowBias(float,float);
	//シャドウマップ
	VOID BeginSh();
	VOID ShadowMapSet(LPDIRECT3DTEXTURE9);
	
	//各エフェクト
	VOID mWVP(D3DXMATRIX*);//ローカル
	VOID vCol(D3DXVECTOR4*);//頂点カラー
	VOID SpCol(D3DXVECTOR4*);//スペキュラカラー
	VOID Tex(LPDIRECT3DTEXTURE9);//テクスチャ
	//バンプマップ
	VOID MTex(LPDIRECT3DTEXTURE9);//バンプマップテクスチャ
	
	//エフェクトの動作
	VOID BeginPass(int);
	VOID CommitChange();

	//カリング
	BOOL Culling(D3DXVECTOR3*,float);

	//トーン
	VOID ToneMap();

	//メッシュのブルームの色
	VOID BloomColor(D3DXVECTOR4*);

	//ガウスフィルタ
	VOID SetGaussMap(float,float);
	VOID SetGaussWeight(float);

	//スクリーン行列
	VOID ScreenView(LPDIRECT3DDEVICE9,UINT,UINT);
	//オブジェクトの更新
	VOID UpdateEffect(float,float);
	//オブジェクトの初期化
	VOID InitEffect();
	VOID UpdateEffect();

};

