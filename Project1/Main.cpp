//======================================================
//�Q�[�����C��
//======================================================
Main::Main()
{
	t_Time	=0;	
	loopNum=0;
	int i;
	for(i=0;i<Dnum;i++){loop[i]=0;}
}
//�I�u�W�F�N�g�̃��Z�b�g�O�ɔj��
HRESULT Main::Reset()
{
	if(FAILED(ML.Reset())){return E_FAIL;}	
	return S_OK;
}
//���Z�b�g��̍Ď擾 
HRESULT Main::Restore()
{	
	if(FAILED(ML.Restore())){return E_FAIL;}
	return S_OK;
}
//�I�u�W�F�N�g�̓ǂݍ���
HRESULT Main::Create(LPDIRECT3DDEVICE9 theDevice,HWND hWnd,HINSTANCE hInst,BOOL* pAct,BOOL* pMin)
{  
	//���C�u�����̍쐬	
	if(FAILED(ML.Create(theDevice,hWnd,hInst,pAct,pMin))){return E_FAIL;}	
	//�t�B�[���h�Z�b�g(���[�h)	
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
	//���x�̌v���p
	DWORD t_Start = timeGetTime();		
	int i=0;
	for(i=0; i < 1000; i++)
	{
	}
	DWORD t_End = timeGetTime();
	t_Time = t_End-t_Start;
	
//*/

	//�V�X�e���f�[�^�����[�h
//	SystemSave().Load(&ML.Sd);
	ML.UpdateSys();
	//�f�o�b�O�p�̃{�^���Z�b�g
	Db.Set(&ML,-500.0f,370.0f);
	return S_OK;
}


//���C������
VOID Main::Render()
{		
#ifdef MY_DEBUG 
	//���[�v�̌v��
	DWORD t_Start = 0;
	t_Start = timeGetTime();
#endif
	//���C�u�����̍X�V
	ML.Update();
	//�t�B�[���h�̍X�V
	m_Scene.Begin(&m_Psn,&ML,&Db);
#ifdef MY_DEBUG 	
	//�`��============================================================
	//�f�o�b�O�e�L�X�g-------------------------------------------------------------
	TCHAR txt[2000] = _T("");//�f�o�b�O�e�L�X�g	
	//���[�v�̌v��
	loop[loopNum] = timeGetTime() - t_Start;
	loopNum++;
	if(loopNum >= Dnum){loopNum = 0;}

	TCHAR ttt[1500] = _T("");
//	ML.T.Debug(ttt,1500,&ML.af);
//	ML.M.Debug(ttt,1500,&ML.af);
//	ML.Audio.Debug(ttt,1500,&ML.af);
//	ML.CSMin.Debug(ttt,1500);
	//���t
	SYSTEMTIME st;
	GetLocalTime(&st);
	TCHAR *wk[8] ={ _T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("�y")};
	_stprintf_s(txt,2000,
		_T("\nfps:%f\n")
		_T("%d�N %d�� %d�� %s�j�� %d�� %d�� %d�b %d�~���b\n")
		_T("1�t���[�����x")
		_T("%s\n")	
		,ML.GV.fps
		,st.wYear,st.wMonth,st.wDay,wk[st.wDayOfWeek],st.wHour,st.wMinute,st.wSecond,st.wMilliseconds
		,ttt
	
		);
	//1���[�v�̑��x��\��
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
