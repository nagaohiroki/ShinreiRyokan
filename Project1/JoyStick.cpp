/*
#ifdef USE_GAMEPAD
//コールバック関数に使用するためグローバル宣言をする
LPDIRECTINPUT8		 g_pDirectInput = NULL;//DirectInputオブジェクト
LPDIRECTINPUTDEVICE8 g_pJoystick    = NULL;//ジョイスティック
//グローバル関数
//ジョイスティックのステータスを調べる
BOOL JoyStickState(LPDIRECTINPUTDEVICE8 pJoy, const DIDEVICEOBJECTINSTANCE* pdidoi )
{
//	HWND hWnd = (HWND)pContext;
	if( pdidoi->dwType & DIDFT_AXIS )
	{
		DIPROPRANGE diprg; 
		diprg.diph.dwSize       = sizeof(DIPROPRANGE);	// 必ずこう初期化しなければならない
		diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);	// 必ずこう初期化しなければならない
		diprg.diph.dwHow        = DIPH_BYID;			// dwObj メンバの解釈方法を指定する。詳細については、dwObj メンバに関する上の説明を参照すること。
		diprg.diph.dwObj        = pdidoi->dwType;		// dwHow メンバが DIPH_BYID の場合、このメンバは、設定または取得されるプロパティを持つオブジェクトの識別子とする。
		diprg.lMin              = -1000;			// 角度ディバイスの最小値
		diprg.lMax              = +1000;			// 角度ディバイスの最大値
		if(FAILED(pJoy->SetProperty( DIPROP_RANGE, &diprg.diph))){ return DIENUM_STOP; }
	}
	return DIENUM_CONTINUE;
}
//コールバック関数
//ジョイスティックを数えるコールバック関数
BOOL CALLBACK enumJoysticksCallback( const DIDEVICEINSTANCE* pdidInstance, VOID* pContext )
{
	if(FAILED(g_pDirectInput->CreateDevice( pdidInstance->guidInstance, &g_pJoystick, NULL )))
	{
		return DIENUM_CONTINUE;
	}
	return DIENUM_STOP;
}
//ジョイスティックのステータスを調べるコールバック関数
BOOL CALLBACK enumObjectsCallback( const DIDEVICEOBJECTINSTANCE* pdidoi,VOID* pContext )
{
	return JoyStickState(g_pJoystick,pdidoi );
}


JoyStick::JoyStick()
{
	g_pJoystick		= NULL;
	g_pDirectInput	= NULL;	
}
JoyStick::~JoyStick()
{
	if( g_pJoystick ){ g_pJoystick->Unacquire(); }
	SAFE_RELEASE( g_pJoystick );
	SAFE_RELEASE( g_pDirectInput );
}
//ジョイスティックの取得
HRESULT JoyStick::setupJoystick(LPDIRECTINPUT8 aDirectInput,HWND hWnd)
{
	HRESULT		hr;
	//ジョイスティックを探す
	hr = aDirectInput->EnumDevices(DI8DEVCLASS_GAMECTRL,enumJoysticksCallback,NULL,DIEDFL_ATTACHEDONLY);
	if(FAILED(hr))
	{
		CFile().Debug(_T("ジョイパッド列挙失敗\n"));
		return hr;
	}	
	return S_OK;
}
//ジョイスティックの設定
HRESULT JoyStick::setJoyState(LPDIRECTINPUTDEVICE8 input,HWND hWnd)
{
	if(input == NULL)
	{
		CFile().Debug(_T("ジョイパッドが接続されていません\n"));
		return E_FAIL;
	}
	if( FAILED(input->SetDataFormat( &c_dfDIJoystick2 ) ) )
	{
		CFile().Debug(_T("ジョイパッドデータフォーマット失敗\n"));
		return E_FAIL;
	}
	if( FAILED(input->SetCooperativeLevel( hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND ) ) )
	{
		CFile().Debug(_T("ジョイパッド強調レベル取得失敗\n"));
		return E_FAIL;
	}
	if( FAILED(input->EnumObjects( enumObjectsCallback, (VOID*)hWnd, DIDFT_ALL)))
	{
		CFile().Debug(_T("ジョイパッドステータス列挙失敗\n"));
		return E_FAIL;
	}
	input->Acquire();
	return S_OK;
}
//ジョイスティックの作成
HRESULT JoyStick::Create(  HWND hWnd , HINSTANCE hInstance )
{
	// DirectInputオブジェクトの生成
	if( FAILED(DirectInput8Create( hInstance , DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&g_pDirectInput, NULL ) ) )
	{
		CFile().Debug(_T("ダイレクトインプット取得失敗\n"));
		return  E_FAIL;
	}
	//ジョイスティックの設定
	if( FAILED(setupJoystick(g_pDirectInput,hWnd)))
	{
		CFile().Debug(_T("ジョイパッド初期化失敗\n"));
		return S_OK;
	}
	//各ジョイスティック
	if( FAILED(setJoyState(g_pJoystick,hWnd)))
	{
		CFile().Debug(_T("ジョイパッド取得失敗\n"));
		return S_OK; 
	}
	return S_OK;
}
//キーを取得
VOID JoyStick::getJoystick(int* Key,HWND hWnd,int* k0)
{
	if( NULL == g_pJoystick ){return;}
	if( FAILED(g_pJoystick->Poll()) )  
	{
		HRESULT hr = g_pJoystick->Acquire();
		while( hr == DIERR_INPUTLOST ) { hr = g_pJoystick->Acquire(); }
		if(FAILED(hr)){return;}
	}
	if( FAILED( g_pJoystick->GetDeviceState( sizeof(DIJOYSTATE2), &aJoystickState ) ) ){return;}
	//ps2
	//	00	△	01	○	02	×	03	□	04	L2	05	R2
	//  06	L1	07	R1	08	START	09	SELECT	0a	L3	0b	R3
	if(aJoystickState.lX >  500){	*k0 = 0;			*Key |= KEY_RIGHT;}
	else if(aJoystickState.lX < -500){*k0 = 0;			*Key |= KEY_LEFT;}
	if(aJoystickState.lY >  500){		*k0 = 0;		*Key |= KEY_DOWN;}	
	else if(aJoystickState.lY < -500){*k0 = 0;			*Key |= KEY_UP;}	
	if(aJoystickState.rgbButtons[0x00] & 0x80){*k0 = 0; *Key |= KEY_SPACE; }// △
	if(aJoystickState.rgbButtons[0x01] & 0x80){*k0 = 0; *Key |= KEY_Z; }// ○
	if(aJoystickState.rgbButtons[0x02] & 0x80){*k0 = 0; *Key |= KEY_X; }// ×
	if(aJoystickState.rgbButtons[0x03] & 0x80){*k0 = 0; *Key |= KEY_Z; }// □
	if(aJoystickState.rgbButtons[0x04] & 0x80){*k0 = 0; *Key |= KEY_X; }// L2
	if(aJoystickState.rgbButtons[0x05] & 0x80){*k0 = 0; *Key |= KEY_Z; }// R2
	if(aJoystickState.rgbButtons[0x06] & 0x80){*k0 = 0; *Key |= KEY_X; }// L1
	if(aJoystickState.rgbButtons[0x07] & 0x80){*k0 = 0; *Key |= KEY_Z; }// R1
	if(aJoystickState.rgbButtons[0x08] & 0x80){*k0 = 0; *Key |= KEY_SPACE;}	// START
	if(aJoystickState.rgbButtons[0x09] & 0x80){*k0 = 0; *Key |= KEY_SPACE;}	// START

}
	
#endif
	*/