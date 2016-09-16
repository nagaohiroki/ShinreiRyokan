/*
#ifdef USE_GAMEPAD
//�R�[���o�b�N�֐��Ɏg�p���邽�߃O���[�o���錾������
LPDIRECTINPUT8		 g_pDirectInput = NULL;//DirectInput�I�u�W�F�N�g
LPDIRECTINPUTDEVICE8 g_pJoystick    = NULL;//�W���C�X�e�B�b�N
//�O���[�o���֐�
//�W���C�X�e�B�b�N�̃X�e�[�^�X�𒲂ׂ�
BOOL JoyStickState(LPDIRECTINPUTDEVICE8 pJoy, const DIDEVICEOBJECTINSTANCE* pdidoi )
{
//	HWND hWnd = (HWND)pContext;
	if( pdidoi->dwType & DIDFT_AXIS )
	{
		DIPROPRANGE diprg; 
		diprg.diph.dwSize       = sizeof(DIPROPRANGE);	// �K���������������Ȃ���΂Ȃ�Ȃ�
		diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);	// �K���������������Ȃ���΂Ȃ�Ȃ�
		diprg.diph.dwHow        = DIPH_BYID;			// dwObj �����o�̉��ߕ��@���w�肷��B�ڍׂɂ��ẮAdwObj �����o�Ɋւ����̐������Q�Ƃ��邱�ƁB
		diprg.diph.dwObj        = pdidoi->dwType;		// dwHow �����o�� DIPH_BYID �̏ꍇ�A���̃����o�́A�ݒ�܂��͎擾�����v���p�e�B�����I�u�W�F�N�g�̎��ʎq�Ƃ���B
		diprg.lMin              = -1000;			// �p�x�f�B�o�C�X�̍ŏ��l
		diprg.lMax              = +1000;			// �p�x�f�B�o�C�X�̍ő�l
		if(FAILED(pJoy->SetProperty( DIPROP_RANGE, &diprg.diph))){ return DIENUM_STOP; }
	}
	return DIENUM_CONTINUE;
}
//�R�[���o�b�N�֐�
//�W���C�X�e�B�b�N�𐔂���R�[���o�b�N�֐�
BOOL CALLBACK enumJoysticksCallback( const DIDEVICEINSTANCE* pdidInstance, VOID* pContext )
{
	if(FAILED(g_pDirectInput->CreateDevice( pdidInstance->guidInstance, &g_pJoystick, NULL )))
	{
		return DIENUM_CONTINUE;
	}
	return DIENUM_STOP;
}
//�W���C�X�e�B�b�N�̃X�e�[�^�X�𒲂ׂ�R�[���o�b�N�֐�
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
//�W���C�X�e�B�b�N�̎擾
HRESULT JoyStick::setupJoystick(LPDIRECTINPUT8 aDirectInput,HWND hWnd)
{
	HRESULT		hr;
	//�W���C�X�e�B�b�N��T��
	hr = aDirectInput->EnumDevices(DI8DEVCLASS_GAMECTRL,enumJoysticksCallback,NULL,DIEDFL_ATTACHEDONLY);
	if(FAILED(hr))
	{
		CFile().Debug(_T("�W���C�p�b�h�񋓎��s\n"));
		return hr;
	}	
	return S_OK;
}
//�W���C�X�e�B�b�N�̐ݒ�
HRESULT JoyStick::setJoyState(LPDIRECTINPUTDEVICE8 input,HWND hWnd)
{
	if(input == NULL)
	{
		CFile().Debug(_T("�W���C�p�b�h���ڑ�����Ă��܂���\n"));
		return E_FAIL;
	}
	if( FAILED(input->SetDataFormat( &c_dfDIJoystick2 ) ) )
	{
		CFile().Debug(_T("�W���C�p�b�h�f�[�^�t�H�[�}�b�g���s\n"));
		return E_FAIL;
	}
	if( FAILED(input->SetCooperativeLevel( hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND ) ) )
	{
		CFile().Debug(_T("�W���C�p�b�h�������x���擾���s\n"));
		return E_FAIL;
	}
	if( FAILED(input->EnumObjects( enumObjectsCallback, (VOID*)hWnd, DIDFT_ALL)))
	{
		CFile().Debug(_T("�W���C�p�b�h�X�e�[�^�X�񋓎��s\n"));
		return E_FAIL;
	}
	input->Acquire();
	return S_OK;
}
//�W���C�X�e�B�b�N�̍쐬
HRESULT JoyStick::Create(  HWND hWnd , HINSTANCE hInstance )
{
	// DirectInput�I�u�W�F�N�g�̐���
	if( FAILED(DirectInput8Create( hInstance , DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&g_pDirectInput, NULL ) ) )
	{
		CFile().Debug(_T("�_�C���N�g�C���v�b�g�擾���s\n"));
		return  E_FAIL;
	}
	//�W���C�X�e�B�b�N�̐ݒ�
	if( FAILED(setupJoystick(g_pDirectInput,hWnd)))
	{
		CFile().Debug(_T("�W���C�p�b�h���������s\n"));
		return S_OK;
	}
	//�e�W���C�X�e�B�b�N
	if( FAILED(setJoyState(g_pJoystick,hWnd)))
	{
		CFile().Debug(_T("�W���C�p�b�h�擾���s\n"));
		return S_OK; 
	}
	return S_OK;
}
//�L�[���擾
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
	//	00	��	01	��	02	�~	03	��	04	L2	05	R2
	//  06	L1	07	R1	08	START	09	SELECT	0a	L3	0b	R3
	if(aJoystickState.lX >  500){	*k0 = 0;			*Key |= KEY_RIGHT;}
	else if(aJoystickState.lX < -500){*k0 = 0;			*Key |= KEY_LEFT;}
	if(aJoystickState.lY >  500){		*k0 = 0;		*Key |= KEY_DOWN;}	
	else if(aJoystickState.lY < -500){*k0 = 0;			*Key |= KEY_UP;}	
	if(aJoystickState.rgbButtons[0x00] & 0x80){*k0 = 0; *Key |= KEY_SPACE; }// ��
	if(aJoystickState.rgbButtons[0x01] & 0x80){*k0 = 0; *Key |= KEY_Z; }// ��
	if(aJoystickState.rgbButtons[0x02] & 0x80){*k0 = 0; *Key |= KEY_X; }// �~
	if(aJoystickState.rgbButtons[0x03] & 0x80){*k0 = 0; *Key |= KEY_Z; }// ��
	if(aJoystickState.rgbButtons[0x04] & 0x80){*k0 = 0; *Key |= KEY_X; }// L2
	if(aJoystickState.rgbButtons[0x05] & 0x80){*k0 = 0; *Key |= KEY_Z; }// R2
	if(aJoystickState.rgbButtons[0x06] & 0x80){*k0 = 0; *Key |= KEY_X; }// L1
	if(aJoystickState.rgbButtons[0x07] & 0x80){*k0 = 0; *Key |= KEY_Z; }// R1
	if(aJoystickState.rgbButtons[0x08] & 0x80){*k0 = 0; *Key |= KEY_SPACE;}	// START
	if(aJoystickState.rgbButtons[0x09] & 0x80){*k0 = 0; *Key |= KEY_SPACE;}	// START

}
	
#endif
	*/