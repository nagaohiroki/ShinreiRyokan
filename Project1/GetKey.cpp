//コンストラクタ
GetKey::GetKey()
{
	MouseFlag = FALSE;
	RECT rc = {0,0,0,0};r = rc;
	speed.x = 0; 
	speed.y = 0; 
	point.x = 0;
	point.y = 0;
	k0m1 = 0;

	m_iActive = 0;

}
//マウスの表示(TRUEでマウス表示)
VOID GetKey::MyShowCursor(BOOL Flag)
{
	if(Flag)
	{
		for(;;)
		{
			if( ShowCursor(TRUE) >= 0  ){return;}
		}
	}
	else
	{
		for(;;)
		{
			if( ShowCursor(FALSE) < 0  ){return;}
		}

	}
}
//マウスのモードを指定
VOID GetKey::MouseMode(BOOL Flag,HWND hWnd)
{
	MouseFlag = Flag;
	if(MouseFlag)
	{
		MyShowCursor(FALSE);
		RECT cr;
		RECT dispRect;
		GetClientRect(hWnd,&cr);
		GetWindowRect(hWnd,&r);
		
		LONG FrameSize = ( (r.right - r.left) - cr.right ) / 2;
		LONG HandleSize = ( (r.bottom - r.top) - cr.bottom) - FrameSize;
		SystemParametersInfo(SPI_GETWORKAREA,0,&dispRect,0);
		r.top += HandleSize;
		r.bottom -= FrameSize;
		r.left += FrameSize;
		r.right -= FrameSize ;
	
		if( r.top	 < dispRect.top ){	 r.top    = dispRect.top; }
		if( r.bottom > dispRect.bottom ){r.bottom = dispRect.bottom; }
		if( r.left	 < dispRect.left  ){ r.left   = dispRect.left; }
		if( r.right  > dispRect.right ){ r.right  = dispRect.right; }
	}
	else
	{
		MyShowCursor( TRUE );
		ClipCursor( NULL );
	}
}
//マウスモードを切り替える
VOID GetKey::MouseChenge(HWND hWnd)
{
	if(MouseFlag){MouseMode(FALSE,hWnd);}
	else{	MouseMode(TRUE,hWnd);}

}
//マウスを使用しているか
BOOL GetKey::UseMouse(){return MouseFlag;}
//キーの取得
VOID GetKey::getWAKey(BOOL Active,BOOL MiniSize,HWND hWnd,int* Key)
{
	if(!Active || MiniSize)
	{
		m_iActive = 5;
		if(MouseFlag)
		{
			MouseMode(FALSE,hWnd);
		}
		*Key = KEY_NONE;
		return;
	}
	if(m_iActive != 0)
	{
		*Key = KEY_NONE;
		if(m_iActive > 0){m_iActive--;};
		return;
	}
	//キーボード
	if(GetKeyState('A') & 0x80){*Key |= KEY_A;}
	if(GetKeyState('D') & 0x80){*Key |= KEY_D;}
	if(GetKeyState('W') & 0x80){*Key |= KEY_W;}
	if(GetKeyState('S') & 0x80){*Key |= KEY_S;}
	if(GetKeyState('Z') & 0x80){*Key |= KEY_Z;}
	if(GetKeyState('X') & 0x80){*Key |= KEY_X;}
	if(GetKeyState('C') & 0x80){*Key |= KEY_C;}
	if(GetKeyState('V') & 0x80){*Key |= KEY_V;}
	if(GetKeyState('R') & 0x80){*Key |= KEY_R;}
	if(GetKeyState('Q') & 0x80){*Key |= KEY_Q;}
	if(GetKeyState('E') & 0x80){*Key |= KEY_E;}
	if(GetKeyState('F') & 0x80){*Key |= KEY_F;}
	if(GetKeyState('B') & 0x80){*Key |= KEY_B;}

	if(GetKeyState(VK_SPACE)      & 0x80){*Key |= KEY_SPACE;}
	if(GetKeyState(VK_CONTROL)    & 0x80){*Key |= KEY_Ctrl;}
	if(GetKeyState(VK_RETURN)     & 0x80){*Key |= KEY_Enter;}
	if(GetKeyState(VK_BACK)	      & 0x80){*Key |= KEY_Back; }//BackSpace	
	//方向キー
	if(GetKeyState(VK_LEFT)       & 0x80){k0m1 = 0;*Key |= KEY_LEFT;}
	else if(GetKeyState(VK_RIGHT) & 0x80){k0m1 = 0;*Key |= KEY_RIGHT;}
	if(GetKeyState(VK_UP)         & 0x80){k0m1 = 0;*Key |= KEY_UP;}
	else if(GetKeyState(VK_DOWN)  & 0x80){k0m1 = 0;*Key |= KEY_DOWN;}

	//マウス
	//センタークリック
	if(GetKeyState(VK_MBUTTON) & 0x80){*Key |= KEY_C;}
	if(MouseFlag)
	{	
		POINT center; 
		GetWindowRect(hWnd,&r);
		center.x = (r.left + ( r.right  - r.left )/ 2);
		center.y = (r.top  + ( r.bottom - r.top ) / 2);
		GetCursorPos( &point );
		ClipCursor( &r );	
		speed.x = point.x - center.x;
		speed.y = point.y - center.y;
		SetCursorPos(center.x,center.y);
		const LONG p = 0;
		if(speed.x <  p){k0m1 = 1;*Key |= KEY_LEFT;}
		if(speed.x > -p){k0m1 = 1;*Key |= KEY_RIGHT;}
		if(speed.y <  p){k0m1 = 1;*Key |= KEY_UP;}
		if(speed.y > -p){k0m1 = 1;*Key |= KEY_DOWN;}
		if(GetKeyState(VK_LBUTTON) & 0x80){*Key |= KEY_Z;}//マウス左クリック
		if(GetKeyState(VK_RBUTTON) & 0x80){*Key |= KEY_X;}//マウス右クリック	
	}
	else
	{
		//デバッグ時のみ==============
		if(GetKeyState(VK_LBUTTON) & 0x80){*Key |= KEY_Z;}//マウス左クリック
		if(GetKeyState(VK_RBUTTON) & 0x80){*Key |= KEY_X;}//マウス右クリック	
		speed = point; 
		GetCursorPos( &point );
		ScreenToClient( hWnd, &point);
		if(speed.x != point.x || speed.y != point.y){	k0m1 = 1;} 
	}
}

