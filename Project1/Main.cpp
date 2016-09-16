//======================================================
//ゲームメイン
//======================================================
Main::Main()
{
	t_Time	=0;	
	loopNum=0;
	int i;
	for(i=0;i<Dnum;i++){loop[i]=0;}
}
//オブジェクトのリセット前に破棄
HRESULT Main::Reset()
{
	if(FAILED(ML.Reset())){return E_FAIL;}	
	return S_OK;
}
//リセット後の再取得 
HRESULT Main::Restore()
{	
	if(FAILED(ML.Restore())){return E_FAIL;}
	return S_OK;
}
//オブジェクトの読み込み
HRESULT Main::Create(LPDIRECT3DDEVICE9 theDevice,HWND hWnd,HINSTANCE hInst,BOOL* pAct,BOOL* pMin)
{  
	//ライブラリの作成	
	if(FAILED(ML.Create(theDevice,hWnd,hInst,pAct,pMin))){return E_FAIL;}	
	//フィールドセット(ロード)	
	m_Psn.FM.StaticPos(&D3DXVECTOR3(0.0f,0.42f,2.0f),180.0f);
#ifdef MY_DEBUG
	m_Scene.AddField(new TestRoom);
#else
	m_Scene.AddField(new Fld::Title);
#endif
//	m_Scene.AddField(new Fld::Intro);
//	m_Scene.AddField(new Soto);
//	m_Scene.AddField(new Lobby);
//	m_Scene.AddField(new Fld::Guest_Room);
//	m_Scene.AddField(new Fld::F3);
//	m_Scene.AddField(new Fld::Rest_Men);
//	m_Scene.AddField(new Fld::Bath_Pass);
//	m_Scene.AddField(new Fld::Gameover);
/*
	//速度の計測用
	DWORD t_Start = timeGetTime();		
	int i=0;
	for(i=0; i < 1000; i++)
	{
	}
	DWORD t_End = timeGetTime();
	t_Time = t_End-t_Start;
	
//*/

	//システムデータをロード
//	SystemSave().Load(&ML.Sd);
	ML.UpdateSys();
	//デバッグ用のボタンセット
	Db.Set(&ML,-500.0f,370.0f);
	return S_OK;
}


//メイン処理
VOID Main::Render()
{		
#ifdef MY_DEBUG 
	//ループの計測
	DWORD t_Start = 0;
	t_Start = timeGetTime();
#endif
	//ライブラリの更新
	ML.Update();
	//フィールドの更新
	m_Scene.Begin(&m_Psn,&ML,&Db);
#ifdef MY_DEBUG 	
	//描画============================================================
	//デバッグテキスト-------------------------------------------------------------
	TCHAR txt[2000] = _T("");//デバッグテキスト	
	//ループの計測
	loop[loopNum] = timeGetTime() - t_Start;
	loopNum++;
	if(loopNum >= Dnum){loopNum = 0;}

	TCHAR ttt[1500] = _T("");
//	ML.T.Debug(ttt,1500,&ML.af);
//	ML.M.Debug(ttt,1500,&ML.af);
//	ML.Audio.Debug(ttt,1500,&ML.af);
//	ML.CSMin.Debug(ttt,1500);
	//日付
	SYSTEMTIME st;
	GetLocalTime(&st);
	TCHAR *wk[8] ={ _T("日"),_T("月"),_T("火"),_T("水"),_T("木"),_T("金"),_T("土")};
	_stprintf_s(txt,2000,
		_T("\nfps:%f\n")
		_T("%d年 %d月 %d日 %s曜日 %d時 %d分 %d秒 %dミリ秒\n")
		_T("1フレーム速度")
		_T("%s\n")	
		,ML.GV.fps
		,st.wYear,st.wMonth,st.wDay,wk[st.wDayOfWeek],st.wHour,st.wMinute,st.wSecond,st.wMilliseconds
		,ttt
	
		);
	//1ループの速度を表示
	int i;
	for(i = 0; i < Dnum; i++)
	{
		_stprintf_s(txt,2000,_T("%s %d"),txt,loop[i]);
	}	



	_stprintf_s(txt,2000,_T("%s\n")
		_T("x = %f y = %f\n")
		_T("Atc = %d\n")
		_T("speedx = %ld\n")
		_T("speedy = %ld\n")
		_T("MouseFlag = %d\n")
		,txt
		,ML.GV.mPos.x,ML.GV.mPos.y
		,ML.C.getkey.m_iActive
		,ML.C.getkey.speed.x
		,ML.C.getkey.speed.y
		,ML.C.getkey.MouseFlag
		);

	ML.Tx.draw(txt,400,0);
#endif
}
