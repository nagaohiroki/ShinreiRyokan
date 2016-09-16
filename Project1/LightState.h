#pragma once

//============================================
//カメラのステータス
//============================================
class Cam
{
private:

public:
	float Near;
	float Far;
	D3DXVECTOR3 Eye;//カメラの位置
	D3DXVECTOR3 At;//注視点
	D3DXVECTOR3 Up;	//上方ベクトル
	D3DXVECTOR2 wh;	//アス比
	float Pars;//パース
	Cam();
	VOID Init();
	VOID Cast(const Cam*);
	VOID CamSet(D3DXVECTOR3*,D3DXVECTOR3*);
};
//============================================
//ポイントスポットライトステータス
//============================================
class PointSpotLight
{
private:	
public:
	float dis;//減衰率
	float Lcos;//ライトの射影角
	D3DXVECTOR3 Pos;//ポジション
	D3DXVECTOR3 Vec;//ライトのベクトル	
	D3DXVECTOR4 Col;//ライトの色wはアビエント
	PointSpotLight()
	{
		dis=0.0f;
		Lcos=0.0f;
		Pos=D3DXVECTOR3(0,0.5f,0);//ポジション
		Vec=D3DXVECTOR3(0,0.5f,1.0f);//ベクトル
		Col=D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);//ライトの色wは全体の強さ
	}
	VOID Init()
	{
		dis=0.0f;
		Lcos=0.0f;
		Pos=D3DXVECTOR3(0,0.5f,0);//ポジション
		Vec=D3DXVECTOR3(0,0.5f,1.0f);//ベクトル
		Col=D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);//ライトの色wは全体の強さ

	}
	
};

//============================================
//ライトステータス
//============================================
class LightState
{
public:
	D3DXVECTOR3 EyePlus;//カメラの上乗せ分
	D3DXVECTOR3 Pos;//ライトの向き
	D3DXVECTOR3 At;//ライトの対象の位置
	D3DXVECTOR4 Col;//wは全オブジェクトのアビエント
	float Near;//ライトの近影
	float Far;//ライトの遠影
	float Pars;//ライトの射影
	float Shadow;//影の濃さ
	float Bias;//バイアス
	LightState()
	{
		Near=60.0f;
		Far=65.0f;
		Col=D3DXVECTOR4(1.0f,1.0f,1.0f,1.0);
		Pos=D3DXVECTOR3(0.0f,63.0f,3.0f);
		At=D3DXVECTOR3(0.0f,0.0f,0.0f);
		Pars=45.0f;//ライトの視角
		Shadow=1.0f;
		Bias=1.0f;
		EyePlus=D3DXVECTOR3(0.0f,0.0f,0.0f);
	}
	VOID Init()
	{
		Near=60.0f;
		Far=65.0f;
		Col=D3DXVECTOR4(1.0f,1.0f,1.0f,1.0);
		Pos=D3DXVECTOR3(0.0f,63.0f,3.0f);
		At=D3DXVECTOR3(0.0f,0.0f,0.0f);
		Pars=45.0f;//ライトの視角
		Shadow=1.0f;
		Bias=1.0f;
		EyePlus=D3DXVECTOR3(0.0f,0.0f,0.0f);

	}
	VOID Cast(const LightState *Ls)
	{
		Near   = Ls->Near;
		Far    = Ls->Far;
		Col    = Ls->Col;
		Pos    = Ls->Pos;
		At     = Ls->At;
		Pars   = Ls->Pars;
		Shadow = Ls->Shadow;
		Bias   = Ls->Bias;
		EyePlus= Ls->EyePlus;

	}

};

//============================================
//フォグ
//============================================
class FogState
{
public:
	D3DXVECTOR3 Col;//カラー
	float Near;//最遠距離
	float Far;//最近距離
	BOOL use;//オンオフ
	FogState()
	{
		use = TRUE;
		Near= 0.0f;
		Far = 50.0f;
		Col = D3DXVECTOR3(0.84f,0.89f,0.99f);
	}
	VOID Init()
	{
		use = TRUE;
		Near= 0.0f;
		Far = 50.0f;
		Col = D3DXVECTOR3(0.84f,0.89f,0.99f);

	}
	//比較
	BOOL EqualEqual(const FogState* Fs)
	{
		if(Col.x != Fs->Col.x){return FALSE;}
		if(Col.y != Fs->Col.y){return FALSE;}
		if(Col.z != Fs->Col.z){return FALSE;}
		if(Near  != Fs->Near ){return FALSE;}
		if(Far   != Fs->Far  ){return FALSE;}
		if(use   != Fs->use  ){return FALSE;}
		return TRUE;
	}
	//代入
	VOID Cast(const FogState* Fs)
	{
		Col.x = Fs->Col.x;
		Col.y = Fs->Col.y;
		Col.z = Fs->Col.z;		
		Near  = Fs->Near;
		Far   = Fs->Far;
		use   = Fs->use;
	}


};
