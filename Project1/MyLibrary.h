#pragma once
//======================================================
//ゲームライブラリ
//======================================================
enum SURFACE
{
	SU_SHADOWMAP,
	SU_TONE,
	SU_HDR,
	SU_GAUSSX,
	SU_GAUSSY,
	SU_MIRROR,
	SU_MAX,
};
//グローバル変数の代わり
class GlobalVal
{
private:
	DWORD nowTime;
	DWORD oldTime;//ループタイムを計測
	int FCount;// フレーム・カウンタ
public:
	//アクティブかどうか
	BOOL *m_bActive;
	//最小化されている場合
	BOOL *m_bMiniSize;
	float fps;	
	//描画領域のサイズ
	UINT ClientWidth;
	UINT ClientHeight;
	//スクリーンのサイズ
	UINT ScreenWidth;
	UINT ScreenHeight;
	//マウスカーソルの位置
	D3DXVECTOR2 mPos;
	GlobalVal();
	//fpsの計測
	VOID FPScount();
};

class MyLibrary
{
private:
	//サーフェイス
	CSTexState m_STex[SU_MAX];
public:	
	//システムデータ
	SystemData Sd;
	//アイテムリスト
	CItemList itemList;
	HWND hW;
	LPDIRECT3DDEVICE9 D;
	CollParfect Col;
	DirectIn C;
	GlobalVal GV;
	CEffect	 E;
	CSoundManager Audio;
	CTextureManager T;
	CModelManager M;
	CString	 CSMin;
	FVF		 F;
	FVFMirror	 FMirror;

	CText	 Tx;
	CSurf	 Sf;
	Arc_Files af;
	FILE *fp;
	MyLibrary();
	virtual ~MyLibrary();
	HRESULT Reset();
	HRESULT Restore();
	VOID Update();
	HRESULT Create(LPDIRECT3DDEVICE9,HWND,HINSTANCE,BOOL*,BOOL*);

	//システムデータを更新
	VOID UpdateSys();

};
