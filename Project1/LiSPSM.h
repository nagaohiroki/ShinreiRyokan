#pragma once
//-================================================================
//LiSPSM(ライトスペースパースペクティブシャドウマップ)
//-================================================================
class LiSPSM
{
private:
	enum{PN=8};
	D3DXVECTOR3 Point[PN];
	D3DXVECTOR3 Point2[PN];
	D3DXMATRIX mView;
	D3DXMATRIX mProj;
	//UPベクトルを求める
	VOID UpVec(D3DXVECTOR3*,const D3DXVECTOR3*,const D3DXVECTOR3*);
	//行列を(-1,-1,-1)~(1,1,1)の範囲にあわせる
	VOID MatrixFit(D3DXMATRIX*,const D3DXVECTOR3*,const D3DXVECTOR3*);
	//ポイント関連
	//行列から変換
	VOID PointTransform(const D3DXMATRIX*);
	//AABBを取得する
	VOID GetAABB(D3DXVECTOR3*,D3DXVECTOR3*);
	VOID StandPoint(const D3DXMATRIX*,const float,const float,const float,const float);
public:
	LiSPSM();
	VOID MatLiSPSM(D3DXMATRIX*,const D3DXMATRIX*,D3DXVECTOR3*,D3DXVECTOR3*,D3DXVECTOR3*,const float,const float,const float,const float);

};