#pragma once
class GetKey
{
private:
	
	//マウス可動領域
	RECT r;
public:
	//マウスを使っているかのフラグ
	BOOL MouseFlag;	
	int m_iActive;
	//キーボードマウスどちらを最後に使ったか
	int k0m1;
	//カーソルの移動速度
	POINT speed;
	//カーソルの位置
	POINT point;
	//コンストラクタ
	GetKey();
	//マウスカーソルの表示
	VOID MyShowCursor(BOOL);
	//マウスのモードを指定
	VOID MouseMode(BOOL,HWND);
	//マウスモードを切り替える
	VOID MouseChenge(HWND);
	//マウスを使用しているか
	BOOL UseMouse();
	//キーの取得
	VOID getWAKey(BOOL,BOOL,HWND,int*);

	
};

