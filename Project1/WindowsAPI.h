//====================================================================================================
//ウィンドウズアプリケーションの初期化
//====================================================================================================
#pragma once//ヘッダーの重複防止
//メイン関数
class D3DXMain
{
private:
	LPDIRECT3D9             m_pD3D;			// D3Dディバイス生成のため
	D3DPRESENT_PARAMETERS	m_D3DPParams;
	LPDIRECT3DDEVICE9       m_pD3DDevice;			// レンダリングディバイス
	BOOL Lost;
	HRESULT ChangeW(HWND);//ウィンドウモード⇔フルスクリーンを切り替える
	HRESULT CapsCheck();
public:
	RECT rect;
	Main main;
	D3DXMain();
	virtual ~D3DXMain();
	//ゲームの中身
	HRESULT	SizeGet();
	HRESULT	InitDirect3D( HWND, HINSTANCE );//D3DXとかの初期化
	HRESULT MsgLoop( HWND );//メッセージループ
	HRESULT DeviceLost( HWND );
};



