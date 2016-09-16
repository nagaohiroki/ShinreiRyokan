//-----------------------------------------------------------------------------
//Win32API
//-----------------------------------------------------------------------------
//アクティブか否か
BOOL g_bActive = FALSE;
//最小化か否か
BOOL g_bMiniSize = FALSE;
//ウィンドウフラグ(1ならウィンドウ0ならフルスクリーン)
int g_bWindowedFlag = 1;
LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{	
	switch( msg )
	{		
		//escキーで破棄
        case WM_KEYUP: 
			if(wParam == VK_ESCAPE )
			{	
				//フルスクリーンの時はウィンドウモードに戻る
				if(g_bWindowedFlag == 0){	g_bWindowedFlag = 1;}
				else
				{
				//	GetKey().MyShowCursor( TRUE );
					//確認デバッグ時は即時終了
				//	if( MessageBoxEx(hWnd, _T("終了しますか?"),_T("終了"),MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2 ,LANG_JAPANESE) == IDYES )
					{
						PostQuitMessage( 0 );
						return 0; 
					}				
				}				
			}	
			break;
		//Xボタンで破棄
		case WM_DESTROY:
			PostQuitMessage( 0 );
			return 0; 
			break;
		//フルスクリーンとウィンドウモードを切り替える
		case WM_SYSKEYUP:
			if(wParam == VK_RETURN )
			{
				g_bWindowedFlag = 1 - g_bWindowedFlag;
			}
			break;	
		//アクティブか非アクティブか
		case WM_ACTIVATE:
			if( wParam == WA_INACTIVE )
			{		
				g_bActive = FALSE;	
			}
			else{	g_bActive = TRUE;	}
			break;
		//最小化
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
	_tsetlocale(0,_T(""));//全ての言語に対応
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//メモリリークの検出	
	//乱数の初期化
	srand(timeGetTime());
	TCHAR GameTitle[MAX_PATH] = _T("shinrei_ryokan");
	// 多重起動のチェック
	HANDLE hMutex = CreateMutex(NULL, FALSE,GameTitle);
	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		// 多重起動している
		if(hMutex){ CloseHandle(hMutex);}
		MessageBox( NULL, _T("このアプリケーションは多重起動できません。"),_T("ERRORが発生しました"), MB_OK|MB_ICONHAND );
		return( E_FAIL );
	}
	// ウィンドウクラスの設定
	WNDCLASSEX wc = 
	{sizeof(WNDCLASSEX), CS_CLASSDC,WndProc,0L, 0L,	GetModuleHandle(NULL),NULL, NULL, NULL, NULL,GameTitle, NULL };
	if( !RegisterClassEx( &wc ) ){ return 0;}//コケたら帰る
	//最大化ボタンを持たない・境界変更のできないwindow
	DWORD	dwWindowStyle = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU  |WS_MINIMIZEBOX );
	//DirectXクラス取得
	D3DXMain d3dx;
	//スクリーンサイズ取得
	d3dx.SizeGet();
	//アプリケーションウィンドウの生成
	HWND hWnd = CreateWindow(
		GameTitle,GameTitle,dwWindowStyle,d3dx.rect.left,d3dx.rect.top,d3dx.rect.right,d3dx.rect.bottom,
		GetDesktopWindow(),	NULL,wc.hInstance,NULL);
	if(!hWnd)
	{
		return 0;
	}

	// Direct3Dの初期化
	if( FAILED( d3dx.InitDirect3D( hWnd, hInst ) ))
	{
		MessageBox(NULL,_T("Direct3Dの初期化に失敗しました"),_T("ERRORが発生しました"),MB_OK | MB_ICONEXCLAMATION);
		if(hMutex){ CloseHandle(hMutex); }	
		return E_FAIL;
	}
	// ウィンドウの表示
	ShowWindow( hWnd,nCmdShow);
	// メッセージループ
	if(FAILED(d3dx.MsgLoop( hWnd )))
	{
		MessageBox(NULL,_T("動作中に不具合が発生しました強制終了します"),_T("ERRORが発生しました"),MB_OK | MB_ICONEXCLAMATION);
		if(hMutex){ CloseHandle(hMutex); }	
		return E_FAIL;
	
	}
	// Mutexの開放	
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
	//スクリーンサイズ取得
	SystemSave().Load(&main.ML.Sd);
	switch(main.ML.Sd.PixelMode)
	{
	case 0: rect.right = 1024;	rect.bottom = 768;	break;
	case 1: rect.right = 1280;	rect.bottom = 720;	break;
	default:rect.right = 1024;	rect.bottom = 768;	break;
	}
	//真ん中に
	rect.top = ( GetSystemMetrics( SM_CYSCREEN ) - rect.bottom ) / 2;
	rect.left = ( GetSystemMetrics( SM_CXSCREEN ) - rect.right ) / 2;
	return S_OK;
}
//ビデオカードのチェック
HRESULT D3DXMain::CapsCheck()
{
	//ビデオカードの性能チャック
	D3DCAPS9 caps;
	ZeroMemory(&caps, sizeof(D3DCAPS9));
	m_pD3DDevice->GetDeviceCaps(&caps);
	if(caps.VertexShaderVersion < D3DVS_VERSION(1,1))
	{
		MessageBox(NULL,_T("ビデオカードが対応してません。起動するには頂点シェーダ 1.1に対応したビデオカードが必要です"),_T("ERRORが発生しました"),MB_OK | MB_ICONEXCLAMATION);
		return E_FAIL;
	}
	if(	caps.PixelShaderVersion  < D3DPS_VERSION(2,0))
	{
		MessageBox(NULL,_T("ビデオカードが対応してません。起動するにはピクセルシェーダ 2.0に対応したビデオカードが必要です"),_T("ERRORが発生しました"),MB_OK | MB_ICONEXCLAMATION);
		return E_FAIL;
	}
	//2の累乗意外もサポート
	if(caps.TextureCaps == D3DPTEXTURECAPS_POW2)
	{
		MessageBox(NULL,_T("ビデオカードが対応していません:D3DPTEXTURECAPS_POW2"),_T("ERRORが発生しました"),MB_OK | MB_ICONEXCLAMATION);
		return E_FAIL;

	}
	//正方形意外もサポート
	if(caps.TextureCaps == D3DPTEXTURECAPS_SQUAREONLY)
	{
		MessageBox(NULL,_T("ビデオカードが対応していません:D3DPTEXTURECAPS_SQUAREONLY"),_T("ERRORが発生しました"),MB_OK | MB_ICONEXCLAMATION);
		return E_FAIL;
	}
	//アルファテクスチャ
	if( (caps.AlphaCmpCaps & D3DPCMPCAPS_GREATEREQUAL) == 0 )
	{
		MessageBox(NULL,_T("ビデオカードが対応していません:D3DPCMPCAPS_GREATEREQUAL"),_T("ERRORが発生しました"),MB_OK | MB_ICONEXCLAMATION);
		return E_FAIL;
	
	}
	//フォグ
	if((caps.RasterCaps & D3DPRASTERCAPS_WFOG) == 0)
	{
		MessageBox(NULL,_T("ビデオカードが対応していません:D3DPRASTERCAPS_WFOG"),_T("ERRORが発生しました"),MB_OK | MB_ICONEXCLAMATION);
		return E_FAIL;
	}
	//フォグカラー
	if( (caps.PrimitiveMiscCaps & D3DPMISCCAPS_FOGANDSPECULARALPHA) == 0 )
	{
		MessageBox(NULL,_T("ビデオカードが対応していません:D3DPMISCCAPS_FOGANDSPECULARALPHA"),_T("ERRORが発生しました"),MB_OK | MB_ICONEXCLAMATION);
		return E_FAIL;	
	}
	//テクスチャ横
	if(caps.MaxTextureWidth <   1024)
	{
		MessageBox(NULL,_T("ビデオカードが対応していません:MaxTextureWidth"),_T("ERRORが発生しました"),MB_OK | MB_ICONEXCLAMATION);
		return E_FAIL;
	}
	//テクスチャ縦
	if(caps.MaxTextureHeight <  768)
	{
		MessageBox(NULL,_T("ビデオカードが対応していません:MaxTextureHeight"),_T("ERRORが発生しました"),MB_OK | MB_ICONEXCLAMATION);
		return E_FAIL;
	}
	return S_OK;
}

//D3DXとかの初期化
HRESULT	D3DXMain::InitDirect3D( HWND hWnd,HINSTANCE hInst)
{
	// D3Dオブジェクトの生成。
	if( NULL == ( m_pD3D = Direct3DCreate9( D3D_SDK_VERSION )))
	{
		MessageBox(NULL,_T("DirectXのバージョンを最新のものにアップデートしてください"),_T("ERRORが発生しました"),MB_OK | MB_ICONEXCLAMATION);
		return E_FAIL;
	}
	//ウィンドウ、Zバッファの設定
	//D3Dディバイスを生成するための構造体を設定する
	ZeroMemory( &m_D3DPParams, sizeof(D3DPRESENT_PARAMETERS) );
	//TRUEの場合ウィンドウモードFALSEの場合フルスクリーンモード
	m_D3DPParams.Windowed = TRUE;
	//ウィンドウモード
 	if(m_D3DPParams.Windowed){m_D3DPParams.BackBufferFormat = D3DFMT_UNKNOWN;  }
	//フルスクリーン
   else 
	{	
		//ディスプレイ情報を取得
		D3DDISPLAYMODE aDisplayMode;
		if(FAILED(m_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT , &aDisplayMode ))){return E_FAIL;}	
		m_D3DPParams.BackBufferFormat = aDisplayMode.Format;// バックバッファのフォーマット   
		m_D3DPParams.BackBufferHeight = aDisplayMode.Height;// バックバッファの高さ
		m_D3DPParams.BackBufferWidth  = aDisplayMode.Width;// バックバッファの幅
	}
	m_D3DPParams.SwapEffect					= D3DSWAPEFFECT_DISCARD;	  	
	m_D3DPParams.EnableAutoDepthStencil		= TRUE;						// Direct3Dに深度バッファの管理を任せる
	m_D3DPParams.AutoDepthStencilFormat		= D3DFMT_D16;				// 深度バッファのフォーマット
	m_D3DPParams.BackBufferCount			= 1;						//バックバッファの数
	m_D3DPParams.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;	// 今のリフレッシュレートをそのまま使う

	m_D3DPParams.MultiSampleType = D3DMULTISAMPLE_NONE;
	m_D3DPParams.MultiSampleQuality = 0;
	m_D3DPParams.Flags = 0;
	m_D3DPParams.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	// CreateDeviceでDirect3Dを初期化するとき、HAL、HELの組み合わせはプログラマが自由に決めることができるが
	// 普通はこの組み合わせで充分
	if( FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_HARDWARE_VERTEXPROCESSING,&m_D3DPParams,&m_pD3DDevice))){
	if( FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&m_D3DPParams,&m_pD3DDevice))){
	if( FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_REF,hWnd,D3DCREATE_HARDWARE_VERTEXPROCESSING,&m_D3DPParams,&m_pD3DDevice))){
	if( FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_REF,hWnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&m_D3DPParams,&m_pD3DDevice))){
		MessageBox(NULL,_T("Direct3D の初期化に失敗しました"),_T("ERRORが発生しました"),MB_OK | MB_ICONEXCLAMATION);
		return E_FAIL; 
				}
			}
		}
	}
	//ビデオカードの性能チェック
	if(FAILED(CapsCheck())){return E_FAIL;}
	// Direct3Dの初期化
	if( FAILED(main.Create(m_pD3DDevice,hWnd,hInst,&g_bActive,&g_bMiniSize)))
	{
		MessageBox(NULL,_T("Direct3Dの初期化に失敗しました"),_T("ERRORが発生しました"),MB_OK | MB_ICONEXCLAMATION);
	
		return E_FAIL;
	}	
	return  S_OK;
}

//メッセージループ
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
			//FPS固定
			sync_old = sync_now;

			//クリア
			m_pD3DDevice->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(255,255,255), 1.0f, 0 );
	
			//開始
			m_pD3DDevice->BeginScene();
			//メイン描画			
			if(!Lost)
			{main.Render();}
			//終了
			m_pD3DDevice->EndScene();

			//フルスクリーン<->ウィンドウ
			if(FAILED(ChangeW(hWnd))){return E_FAIL;}
			
			//デバイスラスト
			if( m_pD3DDevice->Present(NULL,NULL,NULL,NULL) == D3DERR_DEVICELOST )
			{
				DeviceLost(hWnd);
			}

		}		
	}while( msg.message != WM_QUIT);
	timeEndPeriod(1);
	return S_OK;
}
//デバイスロスト
HRESULT D3DXMain::DeviceLost(HWND hWnd)
{

	main.ML.C.getkey.MouseMode(FALSE,hWnd);
	Lost = TRUE;
	//マルチレンダリング用バックバッファの解放
	if(FAILED(main.Reset()))
	{
		CFile().Debug(_T("MyLibraryReset失敗\n"));
		return S_OK;
	}
	if (m_pD3DDevice->TestCooperativeLevel() != D3DERR_DEVICENOTRESET )
	{
		::Sleep(150);
		CFile().Debug(_T("復帰失敗\n"));
		return S_OK;
	}		
	HRESULT hr = m_pD3DDevice->Reset( &m_D3DPParams );
	if ( hr != D3D_OK )
	{
		CFile().Debug(_T("終了\n"));
		PostQuitMessage(0);
	}

	//リセット後に再取得
	if(FAILED(main.Restore()))
	{
		CFile().Debug(_T("MyLibraryRestore失敗\n"));
		return S_OK;
	}
	Lost = FALSE;
	return S_OK;
}
//ウィンドウモード⇔フルスクリーンを切り替える
HRESULT D3DXMain::ChangeW(HWND hWnd)
{	
	//WindowedはTRUEならウィンドウモード
	if( m_D3DPParams.Windowed == g_bWindowedFlag ){return S_OK;}
	//D3Dディバイスを生成するための構造体を設定する。Zバッファつき。
	ZeroMemory( &m_D3DPParams, sizeof(D3DPRESENT_PARAMETERS) );
	//フラグが変わったらウィンドウモードを切り替える
	m_D3DPParams.Windowed = g_bWindowedFlag;
	if( m_D3DPParams.Windowed )
	{
		//ウィンドウモード
		WINDOWPLACEMENT wp;
		if(GetWindowPlacement(hWnd,&wp) == FALSE){return E_FAIL; }
		wp.rcNormalPosition.left  = rect.left;
		wp.rcNormalPosition.top   = rect.top;
		wp.rcNormalPosition.right = rect.left + rect.right;
		wp.rcNormalPosition.bottom= rect.top + rect.bottom;
		SetWindowPlacement(hWnd,&wp);
		m_D3DPParams.BackBufferFormat           = D3DFMT_UNKNOWN;

		 //ウィンドウモードへ変更する。(注意２)
		::SetWindowLong( hWnd, GWL_STYLE, /*WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_VISIBLE*/WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU  |WS_MINIMIZEBOX  );
        //ウィンドウモードへ変更したとき、ウィンドウの位置を変更する。
        ::SetWindowPos( hWnd, 
                        HWND_NOTOPMOST,//フルスクリーンは最前面表示されているので、解除する。
						rect.left,
						rect.top,
                        rect.right,
                        rect.bottom,
                        SWP_SHOWWINDOW );		
		
	}
	else
	{
		//フルスクリーンモード
		//ウインドウの位置を取得
		RECT r = {0,0,0,0};
		GetWindowRect(hWnd,&r);
		rect.left = r.left;
		rect.top = r.top;
		
		//ディスプレイ情報の取得
		D3DDISPLAYMODE aDisplayMode;
		if(FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&aDisplayMode))){return E_FAIL;}
		//フルスクリーンモード
		m_D3DPParams.BackBufferFormat			= aDisplayMode.Format;// バックバッファのフォーマット   
		m_D3DPParams.BackBufferHeight			= aDisplayMode.Height;// バックバッファの高さ
		m_D3DPParams.BackBufferWidth			= aDisplayMode.Width;// バックバッファの幅

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
	m_D3DPParams.EnableAutoDepthStencil		= TRUE;						// Direct3Dに深度バッファの管理を任せる
	m_D3DPParams.AutoDepthStencilFormat		= D3DFMT_D16;				// 深度バッファのフォーマット
	m_D3DPParams.BackBufferCount			= 1;						//バックバッファの数
	m_D3DPParams.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;	// 今のリフレッシュレートをそのまま使う

	
	m_D3DPParams.MultiSampleType = D3DMULTISAMPLE_NONE;
	m_D3DPParams.MultiSampleQuality = 0;
	m_D3DPParams.Flags = 0;
	m_D3DPParams.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	// サーフェイスやスプライトなどを作っているならここに破棄するコードを書く
	//マルチレンダリング用バックバッファの解放
	if(FAILED(main.Reset()))
	{
		CFile().Debug(_T("MyLibraryReset失敗\n"));
		return E_FAIL;
	}
	//パラメータをリセット
	HRESULT hr;
	hr = m_pD3DDevice->Reset(&m_D3DPParams);
	//リセット後に再取得
	if(FAILED(main.Restore()))
	{
		CFile().Debug(_T("MyLibraryRestore失敗\n"));
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

