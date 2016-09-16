#pragma once//ヘッダーの重複防止
//=============================================================================
//DirectInput関連
//===========================================================================

//コントローラ関連
class DirectIn
{
private:	
	//キー情報	
	int Key;
#ifdef USE_GAMEPAD
	JoyStick joy;
#endif
	//マウスモードの変更をスキップ
	BOOL SkipMouse;
	//ロックした時のマウスの状態
	BOOL LTMMode;
public:	
	//マウスキーボード
	GetKey getkey;
	//各キー
	Key_Set
	UP,
	DOWN,
	LEFT,
	RIGHT,
	W,
	A,
	S,
	D,
	X,
	Z,
	Q,
	E,
	C,
	V,
	Enter,
	Space,
	Ctrl,
	Back;

	DirectIn();
	HRESULT Create( HWND , HINSTANCE );//インプットの読み込み	
	VOID Update(HWND,BOOL,BOOL);
	VOID MouseLock(BOOL,HWND);


};