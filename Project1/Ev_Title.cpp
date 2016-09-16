const TCHAR* EvTitle::name(){return _T("EvTitie");}
EvTitle::EvTitle()
{
	_stprintf_s(LoadInfo,IL,_T(""));
	ModeSelect = 0;
	NextPage = 0;
	LoadNum = -1;
	//����
	tLoad.objPos.y = -160.0f;
	UiTxt.push_back(&tLoad);

	//���[�h���
	tInfo.SetText(_T(""));
	tInfo.objScal = D3DXVECTOR3(1.0f,1.0f,1.0f)*0.8f;
	tInfo.intrval.y = 2.0f;
	tInfo.objPos = D3DXVECTOR3(-150.0f,100.0f,0.0f);
	UiTxt.push_back(&tInfo);
	//������@
	tCtrl.objScal = D3DXVECTOR3(1.0f,1.0f,1.0f)*0.7f;
	tCtrl.objPos = D3DXVECTOR3(-280.0f,-320.0f,0.0);
	tCtrl.SetText(_T(""));
	UiTxt.push_back(&tCtrl);
	
	//�I��
	Choice.MeshCol = D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f);
	Ui.push_back(&Choice);
	//�Z�[�u�f�[�^�̓ǂݍ���
	for(int i = 0;i < 3; i++)
	{
		if(GameSave().Load(&Fm[i],i))
		{
			ModeSelect = -1;
			LFlag[i] = TRUE;
		}
		else{LFlag[i] = FALSE;}
	}
	Key = 0;
	PreMS = 0;
	alpha.SetKey(0,0.0f);
	alpha.SetKey(50,0.5f);
	alpha.SetKey(100,0.0f);
	//�e�L�X�g
	

	_stprintf_s(tmax,TMAX,_T(""));
	tTime.SetText(_T(""));
	tTime.objPos = D3DXVECTOR3(200.0f,-300.0f,0.0f);
	tTime.objScal = D3DXVECTOR3(1.0f,1.0f,1.0f) * 0.8f;
	tTime.MeshCol.w = 0.8f;
	UiTxt.push_back(&tTime);

	//��
	mode = 0;
	frame = 0;
	AngleNeck = 0.0f;
	neck = 0.0f;
	body = 0.0f;
	Rot = 0.0f;
	fAt = D3DXVECTOR3(0.0f,0.0f,0.0f);
	//�^�C�g��
	Title.SetText(_T("�S�엷��"));
//	Title.objPos = D3DXVECTOR3(-300.0f,0.0f,0.0f);
	Title.MeshCol.w = 0.5f;
	UiTxt.push_back(&Title);

}


VOID EvTitle::NeckAngle(D3DXVECTOR3* p,float r)
{
	D3DXMATRIX m;
	D3DXVECTOR3 mp(fish.Null.mWorld._41,fish.Null.mWorld._42,fish.Null.mWorld._43);
	D3DXMatrixRotationY(&m,-D3DXToRadian(fish.Null.YPR.y));
	D3DXVECTOR3 v,N(*p - mp );
	D3DXVec3Normalize(&N,&N);
	D3DXVec3TransformCoord(&v,&N,&m);
	float y = D3DXToDegree(atan2(v.x,v.z));
	float fy = fabsf(y);
	float by = 0.0f;
	if(fy > 50.0f)
	{
		by = fy - 50.0f; 
		if(by > 30.0f){by = 30.0f;}
		if(y > 0.0f)
		{
			by *= 1.0f; 
			y= 50.0f;
		}
		else
		{
			by *= -1.0f; 
			y= -50.0f;
		}
	}
	neck = y * r;
	body = by * r;
}
VOID EvTitle::Set()
{
	P->Mode = Personal::MODE_EVENT;
	P->gt.drawSkip = TRUE;
	Choice.objScal = D3DXVECTOR3(200.0f,(float)ML->CSMin.FontSize*tLoad.intrval.y,1.0f);
	SAFE_DELETE(P->BGM);
	if( ML->Sd.First != 0 )
	{
		int	Bsec= ML->Sd.Best / 1000;
		int	BS  = Bsec % 60; 
		int	BM  = Bsec / 60 % 60;
		int	BH  = Bsec / 60 / 60;
		int	Fsec= ML->Sd.First / 1000;
		int	FS  = Fsec % 60; 
		int	FM  = Fsec / 60 % 60;
		int	FH  = Fsec / 60 / 60;
		_stprintf_s(tmax,TMAX,
			_T("���� %02d : %02d : %02d\n")
			_T("�ő� %02d : %02d : %02d")
			,FH,FM,FS
			,BH,BM,BS
			);
		tTime.SetText(tmax);
	}
}
//�^�C�g��
VOID EvTitle::TitleMenu()
{
	tTime.drawSkip = FALSE;

	tInfo.SetText(_T(" "));
	tCtrl.SetText(_T("�����L�[���}�E�X�őI��   Z�����N���b�N�Ō���"));
	tLoad.SetText(_T("�͂��߂���\n�Â�����"));	
	//���
	if(ModeSelect <-1){ModeSelect = 0;}
	if(ModeSelect > 0){ModeSelect =-1;}
	//���[�h�Z���N�g
	if(P->Check)
	{
		//SE
		P->CheckSE(Personal::SE_CHECK);
		switch(ModeSelect)
		{
		case 0://�j���[�Q�[��
			P->FM.Init();
			ML->C.MouseLock(FALSE,ML->hW);
			P->Mode = Personal::MODE_ACTIVE;
			m_pPare->FldChange(new Fld::Intro,&D3DXVECTOR3(0.0f,0.0f,0.0f),0.0f);
			break;		
		case-1://���[�h�Q�[��
			ML->C.getkey.k0m1 = 0;
			ModeSelect = 0;
			NextPage = 1;	
			break;
		default:break;
		}
	}
	switch(ModeSelect)
	{
	case 0://�j���[�Q�[��
	
		tInfo.objPos = D3DXVECTOR3(-200.0f,-50.0f,0.0f);
		tInfo.SetText(_T("�Q�[�����J�n���܂��B�����o��̂ł����ӂ�������\nZ�����N���b�N�Ń��[�r�[���X�L�b�v����܂�"));
		break;
	case-1://���[�h�Q�[��
		break;
	default:break;
	
	}
}
//�t�B�[���h�����ւ���
Scene* EvTitle::FLoad(int f)
{
	switch(f)
	{
	case FD_TestRoom:			return new Fld::TestRoom;
	case FD_Soto:				return new Fld::Soto;
	case FD_Lobby:				return new Fld::Lobby;
	case FD_LobbyRestRoom:		return new Fld::LobbyRestRoom;
	case FD_Dining_Room:		return new Fld::Dining_Room;
	case FD_Bath_Pass:			return new Fld::Bath_Pass;
	case FD_Bath_Datui_Man:		return new Fld::Bath_Datui_Man;
	case FD_Bath_Datui_Woman:	return new Fld::Bath_Datui_Woman;
	case FD_Bath_Room_Man:		return new Fld::Bath_Room_Man;
	case FD_Bath_Room_Woman:	return new Fld::Bath_Room_Woman;
	case FD_Guest_Room:			return new Fld::Guest_Room;
	case FD_Guest_Bath:			return new Fld::Guest_Bath;
	case FD_Rest_Men:			return new Fld::Rest_Men;
	case FD_Rest_Women:			return new Fld::Rest_Women;
	case FD_F3:					return new Fld::F3;
	case FD_Roof_Kai:			return new Fld::Roof_Kai;
	case FD_Roof_Top:			return new Fld::Roof_Top;
	case FD_201:				return new Fld::Fld_201;
	case FD_201_Bath:			return new Fld::Fld_201_Bath;
	case FD_202:				return new Fld::Fld_202;
	case FD_203:				return new Fld::Fld_203;
	case FD_Staff_Room:			return new Fld::Staff_Room;
	case FD_Sandou:				return new Fld::Sandou;
	default:
		CFile().Debug(_T("Filed:FldChenge\n"));
		break;

	}
	return NULL;
}

//���[�h���
VOID EvTitle::Load()
{
	
	tInfo.objPos = D3DXVECTOR3(-150.0f,-50.0f,0.0f);
	tTime.drawSkip = TRUE;
	tCtrl.SetText(_T("�����L�[���}�E�X�|�C���^�őI��   Z�����N���b�N�Ō���   X���E�N���b�N�Ŗ߂�"));
	tLoad.SetText(_T("�Z�[�u�f�[�^1\n�Z�[�u�f�[�^2\n�Z�[�u�f�[�^3"));
	if(ModeSelect < -(GameSave::MAX_SAVE - 1)){ModeSelect = 0;}
	if(ModeSelect > 0){ModeSelect =-(GameSave::MAX_SAVE - 1);}
	
	//���[�h����\��
	for(int i = 0;i < GameSave::MAX_SAVE; i++)
	{
		if(ModeSelect == -i)
		{
			if(LFlag[i])
			{
				Fm[i].ShowData(LoadInfo,IL);
				tInfo.SetText(LoadInfo);
			}
			else{tInfo.SetText(_T("�f�[�^������܂���"));}
		}
	}
	//�^�C�g����ʂɖ߂�
	if(P->Cansel)
	{
		//SE
		P->CheckSE(Personal::SE_CANSEL);
		ModeSelect = -1;
		NextPage = 0;
	}
	//�I�������f�[�^�����[�h	
	if(P->Check)
	{
		//SE
		P->CheckSE(Personal::SE_CHECK);
		//���[�h
		if(GameSave().Load(&P->FM,-ModeSelect))
		{
			ML->C.MouseLock(FALSE,ML->hW);
			P->Mode = Personal::MODE_ACTIVE;
			m_pPare->FldChange(FLoad(P->FM.FldType),&P->FM.Pos,P->FM.RotY);			
		}
		//���[�h���s
		else{tInfo.SetText(_T("���[�h�ł��܂���"));}	
	}
}
//���X�V
VOID EvTitle::FishUpdate()
{


	if(mode == 0)
	{
		//�ҋ@
		AngleNeck = 0.0f;		
		fish.MotType = fish_anim::FM_WAIT;
		frame++;
		if(frame > 100)
		{
			frame = 0;
			mode = 1;
			fAt.x = 20.0f * (float)rand() / (float)RAND_MAX - 10.0f;
			fAt.z = 20.0f * (float)rand() / (float)RAND_MAX - 10.0f;
		}
	}
	if(mode == 1)
	{
		//��
		AngleNeck += 0.01f;
		if(AngleNeck >= 1.0f)
		{
			rAnim.DeleteAll();
			mode = 2;
			AngleNeck = 1.0f;	
		}
	}
	if(mode == 2)
	{
		//����
		D3DXVECTOR3 rot(fAt - fish.Null.objPos);
		D3DXVec3Normalize(&rot,&rot);
		rAnim.SetKey(0,fish.Null.YPR.y);
		rAnim.SetKey(70,D3DXToDegree(atan2f(rot.x,rot.z)));

		frame++;
		fish.Null.YPR.y = rAnim.Val1(frame);
		if(frame >= rAnim.MaxKey() )
		{
			frame = 0;
			mode = 3;
		}	
	}
	if(mode == 3)
	{
		//�ړ�
		D3DXVECTOR3 rot(fAt - fish.Null.objPos);
		float len = D3DXVec3Length(&rot);
		D3DXVec3Normalize(&rot,&rot);

		fish.Null.objPos.x += rot.x * 0.01f;  
		fish.Null.objPos.z += rot.z * 0.01f; 
		fish.MotType = fish_anim::FM_WALK;
		frame++;
		if(len < 0.2f)
		{
			frame = 0;
			mode = 0;
		}
	}

	
	NeckAngle(&fAt,AngleNeck);
	//�J����
	ML->E.cam.CamSet(&D3DXVECTOR3(2.0f,4.0f,-20.0f),&D3DXVECTOR3(0.0f,0.0f,0.0f));
	//��
	fish.Update(ML);
	fish.body.YPR.y += body;
	fish.head.YPR.y += neck;
}
//�X�V
VOID EvTitle::Update()
{	

	Title.objPos.x = -(Title.vol.x * 0.5f + (Title.objScal.x * (float)ML->CSMin.FontSize) * 0.5f);
	Title.objPos.y = 100.0f;
	if(ML->Sd.First == 0)
	{
		fish.drawSkip = TRUE;
	}
	else
	{
		//���X�V
		fish.drawSkip = FALSE;
		FishUpdate();
	}
	//�I������
	if(	PreMS != ModeSelect){P->CheckSE(Personal::SE_SELECT);}
	PreMS = ModeSelect;
	//�A���t�@�A�j���[�V����
	Key++;
	if(Key > alpha.MaxKey()){Key = 0;}
	Choice.MeshCol.w = alpha.Val(Key);
	//�}�E�X���b�N
	ML->C.MouseLock(TRUE,ML->hW);	
	//�I�����𓮂���
	if(ML->C.getkey.k0m1 == 1)
	{
		//�}�E�X
		float ysize = (float)ML->CSMin.FontSize * tLoad.intrval.y;
		float ytop  = tLoad.objPos.y + ysize * 0.5f;
		int nLen = -tLoad.hN(ML);
		for(int i = 0; i <= nLen; i++)
		{
			if(ML->GV.mPos.y < ytop - ysize * (float)i)
			if(ML->GV.mPos.y > ytop - ysize * ((float)i + 1.0f)){	ModeSelect =  -i;	}
		}
	}
	else
	{
		//�L�[�{�[�h
		if(ML->C.UP.T()){ ModeSelect++;}
		if(ML->C.DOWN.T()){ModeSelect--;}
	}
	//�y�[�W
	switch(NextPage)
	{
	case 0:	TitleMenu();	break;
	case 1:	Load();	break;	
	default:break;
	}
	//�e�L�X�g�I�����̈ʒu
	tLoad.objPos.x = -tLoad.intrval.x * tLoad.vol.x*0.5f;
	Choice.objPos = D3DXVECTOR3(	
		tLoad.objPos.x + tLoad.intrval.x * tLoad.vol.x*0.5f,
		tLoad.objPos.y + (float)ML->CSMin.FontSize * tLoad.intrval.y * (float)ModeSelect,
		0.0f);
	
	

}
VOID EvTitle::DebugText(TCHAR* t,int l)
{
		D3DXVECTOR3 rot(fAt - fish.Null.objPos);
		float len = D3DXVec3Length(&rot);
	_stprintf_s(t,l,
		_T("mode = %d\n")
		_T("len = %f\n")
		_T("%f,%f,%f\n")
	
		,mode
		,len
		,fAt.x,fAt.y,fAt.z
		);
}
VOID EvTitle::DebugBtn(DebugButton*)
{
}
VOID EvTitle::draw()
{
	fish.draw(ML);
}
