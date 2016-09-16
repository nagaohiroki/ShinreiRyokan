//-----------------------------------------------------------------------------
//Win32API
//-----------------------------------------------------------------------------
//�A�N�e�B�u���ۂ�
BOOL g_bActive = FALSE;
//�ŏ������ۂ�
BOOL g_bMiniSize = FALSE;
//�E�B���h�E�t���O(1�Ȃ�E�B���h�E0�Ȃ�t���X�N���[��)
int g_bWindowedFlag = 1;
LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{	
	switch( msg )
	{		
		//esc�L�[�Ŕj��
        case WM_KEYUP: 
			if(wParam == VK_ESCAPE )
			{	
				//�t���X�N���[���̎��̓E�B���h�E���[�h�ɖ߂�
				if(g_bWindowedFlag == 0){	g_bWindowedFlag = 1;}
				else
				{
				//	GetKey().MyShowCursor( TRUE );
					//�m�F�f�o�b�O���͑����I��
				//	if( MessageBoxEx(hWnd, _T("�I�����܂���?"),_T("�I��"),MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2 ,LANG_JAPANESE) == IDYES )
					{
						PostQuitMessage( 0 );
						return 0; 
					}				
				}				
			}	
			break;
		//X�{�^���Ŕj��
		case WM_DESTROY:
			PostQuitMessage( 0 );
			return 0; 
			break;
		//�t���X�N���[���ƃE�B���h�E���[�h��؂�ւ���
		case WM_SYSKEYUP:
			if(wParam == VK_RETURN )
			{
				g_bWindowedFlag = 1 - g_bWindowedFlag;
			}
			break;	
		//�A�N�e�B�u����A�N�e�B�u��
		case WM_ACTIVATE:
			if( wParam == WA_INACTIVE )
			{		
				g_bActive = FALSE;	
			}
			else{	g_bActive = TRUE;	}
			break;
		//�ŏ���
		case WM_SYSCOMMAND:
			switch( LOWORD(wParam))
			{
			case SC_MINIMIZE:
				CFile().Debug(_T("mini\n"));
				g_bMiniSize = TRUE;	
				break;
			case SC_RESTORE:
				CFile().Debug(_T("minirestore\n"));
				g_bMiniSize = FALSE;
				break;
			default:break;
	   		}
			break;
		default:break;
	}
	return DefWindowProc( hWnd, msg, wParam, lParam );
}

int APIENTRY _tWinMain(HINSTANCE hInst, HINSTANCE , LPTSTR ,int nCmdShow)
{	
	_tsetlocale(0,_T(""));//�S�Ă̌���ɑΉ�
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//���������[�N�̌��o	
	//�����̏�����
	srand(timeGetTime());
	TCHAR GameTitle[MAX_PATH] = _T("shinrei_ryokan");
	// ���d�N���̃`�F�b�N
	HANDLE hMutex = CreateMutex(NULL, FALSE,GameTitle);
	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		// ���d�N�����Ă���
		if(hMutex){ CloseHandle(hMutex);}
		MessageBox( NULL, _T("���̃A�v���P�[�V�����͑��d�N���ł��܂���B"),_T("ERROR���������܂���"), MB_OK|MB_ICONHAND );
		return( E_FAIL );
	}
	// �E�B���h�E�N���X�̐ݒ�
	WNDCLASSEX wc = 
	{sizeof(WNDCLASSEX), CS_CLASSDC,WndProc,0L, 0L,	GetModuleHandle(NULL),NULL, NULL, NULL, NULL,GameTitle, NULL };
	if( !RegisterClassEx( &wc ) ){ return 0;}//�R�P����A��
	//�ő剻�{�^���������Ȃ��E���E�ύX�̂ł��Ȃ�window
	DWORD	dwWindowStyle = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU  |WS_MINIMIZEBOX );
	//DirectX�N���X�擾
	D3DXMain d3dx;
	//�X�N���[���T�C�Y�擾
	d3dx.SizeGet();
	//�A�v���P�[�V�����E�B���h�E�̐���
	HWND hWnd = CreateWindow(
		GameTitle,GameTitle,dwWindowStyle,d3dx.rect.left,d3dx.rect.top,d3dx.rect.right,d3dx.rect.bottom,
		GetDesktopWindow(),	NULL,wc.hInstance,NULL);
	if(!hWnd)
	{
		return 0;
	}

	// Direct3D�̏�����
	if( FAILED( d3dx.InitDirect3D( hWnd, hInst ) ))
	{
		MessageBox(NULL,_T("Direct3D�̏������Ɏ��s���܂���"),_T("ERROR���������܂���"),MB_OK | MB_ICONEXCLAMATION);
		if(hMutex){ CloseHandle(hMutex); }	
		return E_FAIL;
	}
	// �E�B���h�E�̕\��
	ShowWindow( hWnd,nCmdShow);
	// ���b�Z�[�W���[�v
	if(FAILED(d3dx.MsgLoop( hWnd )))
	{
		MessageBox(NULL,_T("���쒆�ɕs����������܂��������I�����܂�"),_T("ERROR���������܂���"),MB_OK | MB_ICONEXCLAMATION);
		if(hMutex){ CloseHandle(hMutex); }	
		return E_FAIL;
	
	}
	// Mutex�̊J��	
	if(hMutex){ CloseHandle(hMutex); }
	return 0;
}

//-----------------------------------------------------------------------------
//DirectX
//-----------------------------------------------------------------------------
D3DXMain::D3DXMain()
{
	m_pD3D = NULL;		
	m_pD3DDevice = NULL;

	rect.top = 50;
	rect.left = 50;
	rect.right = 1024;
	rect.bottom = 768;
	Lost = FALSE;
}
D3DXMain::~D3DXMain()
{
	SAFE_RELEASE( m_pD3DDevice );
	SAFE_RELEASE( m_pD3D );
}

HRESULT	D3DXMain::SizeGet()
{
	//�X�N���[���T�C�Y�擾
	SystemSave().Load(&main.ML.Sd);
	switch(main.ML.Sd.PixelMode)
	{
	case 0: rect.right = 1024;	rect.bottom = 768;	break;
	case 1: rect.right = 1280;	rect.bottom = 720;	break;
	default:rect.right = 1024;	rect.bottom = 768;	break;
	}
	//�^�񒆂�
	rect.top = ( GetSystemMetrics( SM_CYSCREEN ) - rect.bottom ) / 2;
	rect.left = ( GetSystemMetrics( SM_CXSCREEN ) - rect.right ) / 2;
	return S_OK;
}
//�r�f�I�J�[�h�̃`�F�b�N
HRESULT D3DXMain::CapsCheck()
{
	//�r�f�I�J�[�h�̐��\�`���b�N
	D3DCAPS9 caps;
	ZeroMemory(&caps, sizeof(D3DCAPS9));
	m_pD3DDevice->GetDeviceCaps(&caps);
	if(caps.VertexShaderVersion < D3DVS_VERSION(1,1))
	{
		MessageBox(NULL,_T("�r�f�I�J�[�h���Ή����Ă܂���B�N������ɂ͒��_�V�F�[�_ 1.1�ɑΉ������r�f�I�J�[�h���K�v�ł�"),_T("ERROR���������܂���"),MB_OK | MB_ICONEXCLAMATION);
		return E_FAIL;
	}
	if(	caps.PixelShaderVersion  < D3DPS_VERSION(2,0))
	{
		MessageBox(NULL,_T("�r�f�I�J�[�h���Ή����Ă܂���B�N������ɂ̓s�N�Z���V�F�[�_ 2.0�ɑΉ������r�f�I�J�[�h���K�v�ł�"),_T("ERROR���������܂���"),MB_OK | MB_ICONEXCLAMATION);
		return E_FAIL;
	}
	//2�̗ݏ�ӊO���T�|�[�g
	if(caps.TextureCaps == D3DPTEXTURECAPS_POW2)
	{
		MessageBox(NULL,_T("�r�f�I�J�[�h���Ή����Ă��܂���:D3DPTEXTURECAPS_POW2"),_T("ERROR���������܂���"),MB_OK | MB_ICONEXCLAMATION);
		return E_FAIL;

	}
	//�����`�ӊO���T�|�[�g
	if(caps.TextureCaps == D3DPTEXTURECAPS_SQUAREONLY)
	{
		MessageBox(NULL,_T("�r�f�I�J�[�h���Ή����Ă��܂���:D3DPTEXTURECAPS_SQUAREONLY"),_T("ERROR���������܂���"),MB_OK | MB_ICONEXCLAMATION);
		return E_FAIL;
	}
	//�A���t�@�e�N�X�`��
	if( (caps.AlphaCmpCaps & D3DPCMPCAPS_GREATEREQUAL) == 0 )
	{
		MessageBox(NULL,_T("�r�f�I�J�[�h���Ή����Ă��܂���:D3DPCMPCAPS_GREATEREQUAL"),_T("ERROR���������܂���"),MB_OK | MB_ICONEXCLAMATION);
		return E_FAIL;
	
	}
	//�t�H�O
	if((caps.RasterCaps & D3DPRASTERCAPS_WFOG) == 0)
	{
		MessageBox(NULL,_T("�r�f�I�J�[�h���Ή����Ă��܂���:D3DPRASTERCAPS_WFOG"),_T("ERROR���������܂���"),MB_OK | MB_ICONEXCLAMATION);
		return E_FAIL;
	}
	//�t�H�O�J���[
	if( (caps.PrimitiveMiscCaps & D3DPMISCCAPS_FOGANDSPECULARALPHA) == 0 )
	{
		MessageBox(NULL,_T("�r�f�I�J�[�h���Ή����Ă��܂���:D3DPMISCCAPS_FOGANDSPECULARALPHA"),_T("ERROR���������܂���"),MB_OK | MB_ICONEXCLAMATION);
		return E_FAIL;	
	}
	//�e�N�X�`����
	if(caps.MaxTextureWidth <   1024)
	{
		MessageBox(NULL,_T("�r�f�I�J�[�h���Ή����Ă��܂���:MaxTextureWidth"),_T("ERROR���������܂���"),MB_OK | MB_ICONEXCLAMATION);
		return E_FAIL;
	}
	//�e�N�X�`���c
	if(caps.MaxTextureHeight <  768)
	{
		MessageBox(NULL,_T("�r�f�I�J�[�h���Ή����Ă��܂���:MaxTextureHeight"),_T("ERROR���������܂���"),MB_OK | MB_ICONEXCLAMATION);
		return E_FAIL;
	}
	return S_OK;
}

//D3DX�Ƃ��̏�����
HRESULT	D3DXMain::InitDirect3D( HWND hWnd,HINSTANCE hInst)
{
	// D3D�I�u�W�F�N�g�̐����B
	if( NULL == ( m_pD3D = Direct3DCreate9( D3D_SDK_VERSION )))
	{
		MessageBox(NULL,_T("DirectX�̃o�[�W�������ŐV�̂��̂ɃA�b�v�f�[�g���Ă�������"),_T("ERROR���������܂���"),MB_OK | MB_ICONEXCLAMATION);
		return E_FAIL;
	}
	//�E�B���h�E�AZ�o�b�t�@�̐ݒ�
	//D3D�f�B�o�C�X�𐶐����邽�߂̍\���̂�ݒ肷��
	ZeroMemory( &m_D3DPParams, sizeof(D3DPRESENT_PARAMETERS) );
	//TRUE�̏ꍇ�E�B���h�E���[�hFALSE�̏ꍇ�t���X�N���[�����[�h
	m_D3DPParams.Windowed = TRUE;
	//�E�B���h�E���[�h
 	if(m_D3DPParams.Windowed){m_D3DPParams.BackBufferFormat = D3DFMT_UNKNOWN;  }
	//�t���X�N���[��
   else 
	{	
		//�f�B�X�v���C�����擾
		D3DDISPLAYMODE aDisplayMode;
		if(FAILED(m_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT , &aDisplayMode ))){return E_FAIL;}	
		m_D3DPParams.BackBufferFormat = aDisplayMode.Format;// �o�b�N�o�b�t�@�̃t�H�[�}�b�g   
		m_D3DPParams.BackBufferHeight = aDisplayMode.Height;// �o�b�N�o�b�t�@�̍���
		m_D3DPParams.BackBufferWidth  = aDisplayMode.Width;// �o�b�N�o�b�t�@�̕�
	}
	m_D3DPParams.SwapEffect					= D3DSWAPEFFECT_DISCARD;	  	
	m_D3DPParams.EnableAutoDepthStencil		= TRUE;						// Direct3D�ɐ[�x�o�b�t�@�̊Ǘ���C����
	m_D3DPParams.AutoDepthStencilFormat		= D3DFMT_D16;				// �[�x�o�b�t�@�̃t�H�[�}�b�g
	m_D3DPParams.BackBufferCount			= 1;						//�o�b�N�o�b�t�@�̐�
	m_D3DPParams.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;	// ���̃��t���b�V�����[�g�����̂܂܎g��

	m_D3DPParams.MultiSampleType = D3DMULTISAMPLE_NONE;
	m_D3DPParams.MultiSampleQuality = 0;
	m_D3DPParams.Flags = 0;
	m_D3DPParams.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	// CreateDevice��Direct3D������������Ƃ��AHAL�AHEL�̑g�ݍ��킹�̓v���O���}�����R�Ɍ��߂邱�Ƃ��ł��邪
	// ���ʂ͂��̑g�ݍ��킹�ŏ[��
	if( FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_HARDWARE_VERTEXPROCESSING,&m_D3DPParams,&m_pD3DDevice))){
	if( FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&m_D3DPParams,&m_pD3DDevice))){
	if( FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_REF,hWnd,D3DCREATE_HARDWARE_VERTEXPROCESSING,&m_D3DPParams,&m_pD3DDevice))){
	if( FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_REF,hWnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&m_D3DPParams,&m_pD3DDevice))){
		MessageBox(NULL,_T("Direct3D �̏������Ɏ��s���܂���"),_T("ERROR���������܂���"),MB_OK | MB_ICONEXCLAMATION);
		return E_FAIL; 
				}
			}
		}
	}
	//�r�f�I�J�[�h�̐��\�`�F�b�N
	if(FAILED(CapsCheck())){return E_FAIL;}
	// Direct3D�̏�����
	if( FAILED(main.Create(m_pD3DDevice,hWnd,hInst,&g_bActive,&g_bMiniSize)))
	{
		MessageBox(NULL,_T("Direct3D�̏������Ɏ��s���܂���"),_T("ERROR���������܂���"),MB_OK | MB_ICONEXCLAMATION);
	
		return E_FAIL;
	}	
	return  S_OK;
}

//���b�Z�[�W���[�v
HRESULT D3DXMain::MsgLoop( HWND hWnd)
{
	MSG msg;
	ZeroMemory( &msg, sizeof(msg) );	
	//FPS
	DWORD sync_old=timeGetTime();
	DWORD sync_now=0;
	timeBeginPeriod(1);
	do
	{	
		Sleep(1);
		sync_now = timeGetTime();
		if( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);//pon
			DispatchMessage(&msg);
		}
		//60fps
		else if(sync_now - sync_old >= 1000 / 60)
		{
			//FPS�Œ�
			sync_old = sync_now;

			//�N���A
			m_pD3DDevice->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(255,255,255), 1.0f, 0 );
	
			//�J�n
			m_pD3DDevice->BeginScene();
			//���C���`��			
			if(!Lost)
			{main.Render();}
			//�I��
			m_pD3DDevice->EndScene();

			//�t���X�N���[��<->�E�B���h�E
			if(FAILED(ChangeW(hWnd))){return E_FAIL;}
			
			//�f�o�C�X���X�g
			if( m_pD3DDevice->Present(NULL,NULL,NULL,NULL) == D3DERR_DEVICELOST )
			{
				DeviceLost(hWnd);
			}

		}		
	}while( msg.message != WM_QUIT);
	timeEndPeriod(1);
	return S_OK;
}
//�f�o�C�X���X�g
HRESULT D3DXMain::DeviceLost(HWND hWnd)
{

	main.ML.C.getkey.MouseMode(FALSE,hWnd);
	Lost = TRUE;
	//�}���`�����_�����O�p�o�b�N�o�b�t�@�̉��
	if(FAILED(main.Reset()))
	{
		CFile().Debug(_T("MyLibraryReset���s\n"));
		return S_OK;
	}
	if (m_pD3DDevice->TestCooperativeLevel() != D3DERR_DEVICENOTRESET )
	{
		::Sleep(150);
		CFile().Debug(_T("���A���s\n"));
		return S_OK;
	}		
	HRESULT hr = m_pD3DDevice->Reset( &m_D3DPParams );
	if ( hr != D3D_OK )
	{
		CFile().Debug(_T("�I��\n"));
		PostQuitMessage(0);
	}

	//���Z�b�g��ɍĎ擾
	if(FAILED(main.Restore()))
	{
		CFile().Debug(_T("MyLibraryRestore���s\n"));
		return S_OK;
	}
	Lost = FALSE;
	return S_OK;
}
//�E�B���h�E���[�h�̃t���X�N���[����؂�ւ���
HRESULT D3DXMain::ChangeW(HWND hWnd)
{	
	//Windowed��TRUE�Ȃ�E�B���h�E���[�h
	if( m_D3DPParams.Windowed == g_bWindowedFlag ){return S_OK;}
	//D3D�f�B�o�C�X�𐶐����邽�߂̍\���̂�ݒ肷��BZ�o�b�t�@���B
	ZeroMemory( &m_D3DPParams, sizeof(D3DPRESENT_PARAMETERS) );
	//�t���O���ς������E�B���h�E���[�h��؂�ւ���
	m_D3DPParams.Windowed = g_bWindowedFlag;
	if( m_D3DPParams.Windowed )
	{
		//�E�B���h�E���[�h
		WINDOWPLACEMENT wp;
		if(GetWindowPlacement(hWnd,&wp) == FALSE){return E_FAIL; }
		wp.rcNormalPosition.left  = rect.left;
		wp.rcNormalPosition.top   = rect.top;
		wp.rcNormalPosition.right = rect.left + rect.right;
		wp.rcNormalPosition.bottom= rect.top + rect.bottom;
		SetWindowPlacement(hWnd,&wp);
		m_D3DPParams.BackBufferFormat           = D3DFMT_UNKNOWN;

		 //�E�B���h�E���[�h�֕ύX����B(���ӂQ)
		::SetWindowLong( hWnd, GWL_STYLE, /*WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_VISIBLE*/WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU  |WS_MINIMIZEBOX  );
        //�E�B���h�E���[�h�֕ύX�����Ƃ��A�E�B���h�E�̈ʒu��ύX����B
        ::SetWindowPos( hWnd, 
                        HWND_NOTOPMOST,//�t���X�N���[���͍őO�ʕ\������Ă���̂ŁA��������B
						rect.left,
						rect.top,
                        rect.right,
                        rect.bottom,
                        SWP_SHOWWINDOW );		
		
	}
	else
	{
		//�t���X�N���[�����[�h
		//�E�C���h�E�̈ʒu���擾
		RECT r = {0,0,0,0};
		GetWindowRect(hWnd,&r);
		rect.left = r.left;
		rect.top = r.top;
		
		//�f�B�X�v���C���̎擾
		D3DDISPLAYMODE aDisplayMode;
		if(FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&aDisplayMode))){return E_FAIL;}
		//�t���X�N���[�����[�h
		m_D3DPParams.BackBufferFormat			= aDisplayMode.Format;// �o�b�N�o�b�t�@�̃t�H�[�}�b�g   
		m_D3DPParams.BackBufferHeight			= aDisplayMode.Height;// �o�b�N�o�b�t�@�̍���
		m_D3DPParams.BackBufferWidth			= aDisplayMode.Width;// �o�b�N�o�b�t�@�̕�

		::SetWindowLong( hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE );
		::SetWindowPos( hWnd, 
                        HWND_TOPMOST,
                        0,
                        0,
                        rect.right  - rect.left,
                        rect.bottom - rect.top,
                        SWP_SHOWWINDOW );       
	}
	m_D3DPParams.SwapEffect					= D3DSWAPEFFECT_DISCARD;	  	
	m_D3DPParams.EnableAutoDepthStencil		= TRUE;						// Direct3D�ɐ[�x�o�b�t�@�̊Ǘ���C����
	m_D3DPParams.AutoDepthStencilFormat		= D3DFMT_D16;				// �[�x�o�b�t�@�̃t�H�[�}�b�g
	m_D3DPParams.BackBufferCount			= 1;						//�o�b�N�o�b�t�@�̐�
	m_D3DPParams.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;	// ���̃��t���b�V�����[�g�����̂܂܎g��

	
	m_D3DPParams.MultiSampleType = D3DMULTISAMPLE_NONE;
	m_D3DPParams.MultiSampleQuality = 0;
	m_D3DPParams.Flags = 0;
	m_D3DPParams.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	// �T�[�t�F�C�X��X�v���C�g�Ȃǂ�����Ă���Ȃ炱���ɔj������R�[�h������
	//�}���`�����_�����O�p�o�b�N�o�b�t�@�̉��
	if(FAILED(main.Reset()))
	{
		CFile().Debug(_T("MyLibraryReset���s\n"));
		return E_FAIL;
	}
	//�p�����[�^�����Z�b�g
	HRESULT hr;
	hr = m_pD3DDevice->Reset(&m_D3DPParams);
	//���Z�b�g��ɍĎ擾
	if(FAILED(main.Restore()))
	{
		CFile().Debug(_T("MyLibraryRestore���s\n"));
		return E_FAIL;
	}
	hr = m_pD3DDevice->TestCooperativeLevel();
	if(FAILED(hr))
	{
		CFile().Debug(_T("ResetFAIL\n"));
		return E_FAIL;
	}
	CFile().Debug(_T("ModeChange\n"));
    ::Sleep(500);
	return S_OK;
}			

