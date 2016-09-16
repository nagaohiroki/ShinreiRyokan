//=====================================================================
//DirectInput�̐ݒ�
//=====================================================================
DirectIn::DirectIn()
{
	Key=0;
	SkipMouse = FALSE;
	LTMMode = FALSE;
	//�L�[���Z�b�g
	UP.Get_Key(KEY_UP,&Key);
	DOWN.Get_Key(KEY_DOWN,&Key);
	LEFT.Get_Key(KEY_LEFT,&Key);
	RIGHT.Get_Key(KEY_RIGHT,&Key);
	W.Get_Key(KEY_W,&Key);
	A.Get_Key(KEY_A,&Key);
	S.Get_Key(KEY_S,&Key);
	D.Get_Key(KEY_D,&Key);
	X.Get_Key(KEY_X,&Key);
	Z.Get_Key(KEY_Z,&Key);
	Q.Get_Key(KEY_Q,&Key);
	E.Get_Key(KEY_E,&Key);
	C.Get_Key(KEY_C,&Key);
	V.Get_Key(KEY_V,&Key);
	Enter.Get_Key(KEY_Enter,&Key);
	Space.Get_Key(KEY_SPACE,&Key);
	Ctrl.Get_Key(KEY_Ctrl,&Key);
	Back.Get_Key(KEY_Back,&Key);

}

//directinput�ǂݍ���
HRESULT DirectIn::Create( HWND hWnd , HINSTANCE)
{
	getkey.MouseMode(FALSE,hWnd);

#ifdef USE_GAMEPAD
	HRESULT hr = S_OK;
	hr = joy.Create(hWnd,hInstance);
	if(FAILED(hr)){return E_FAIL;}
#endif
	return S_OK;
}
//�}�E�X�����b�N����true�Ȃ烍�b�N
VOID DirectIn::MouseLock(BOOL b,HWND hWnd)
{	
	
	if(b)
	{
		if(SkipMouse){return;}
		//�}�E�X�̕ύX���X�L�b�v
		SkipMouse = TRUE;
		//���b�N���̃}�E�X�̏�Ԃ�ێ�
		LTMMode = getkey.UseMouse();
		//�}�E�X���g�p���Ȃ����[�h
		getkey.MouseMode(FALSE,hWnd);
	}
	else
	{
		if(!SkipMouse){return;}
		//�}�E�X�̕ύX���X�L�b�v���Ȃ�
		SkipMouse = FALSE;
		//�L�����Ă����}�E�X���[�h�ɖ߂�
		getkey.MouseMode(LTMMode,hWnd);

	}
}


VOID DirectIn::Update(HWND hWnd,BOOL Active,BOOL MiniSize)
{	
	Key = 0;	
	getkey.getWAKey(Active,MiniSize,hWnd,&Key);
#ifdef USE_GAMEPAD
	joy.getJoystick(&Key,hWnd,&getkey.k0m1); 
#endif
	//�}�E�X�̃I���I�t
	if(!SkipMouse)
	{
		if(getkey.m_iActive == 0){
		if(C.T()){getkey.MouseChenge(hWnd);}
		}
	}
}
