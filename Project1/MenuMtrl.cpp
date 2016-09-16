//���j���[�̑f��
MenuMtrl::MenuMtrl()
{
	Page = MP_MAIN;
	ML = NULL;
	FM = NULL;
	Sp = 0;
	Select = 0;
	SelectMode = 0;
	Wait = FALSE;
	Close = FALSE;
	Key = 0;
	alpha.SetKey(0,0.0f);
	alpha.SetKey(50,0.5f);
	alpha.SetKey(100,0.0f);

	PreSelect = 0;
	PreSp = 0;

	//�I����
	for(int i = 0; i < SMAX ; i++)
	{
		slct[i].Set(wav_step2);
	}
}
//�I����
VOID MenuMtrl::SelectSE()
{
	for(int i = 0; i < SMAX ; i++)
	{
		if(!slct[i].Sv(ML)->Idol())
		{
			slct[i].m_fVol = 0.5f;
			slct[i].Filter.Frequency = 0.1f;
			slct[i].Start(ML);
			return;
		}		
	}		
}

VOID MenuMtrl::SetWait(){Wait = TRUE;}
VOID MenuMtrl::Set(MyLibrary* ml,FlagManager* fm)
{
	ML = ml;
	FM = fm;
	//�e�L�X�g�I�u�W�F�N�g
	//�I��
	Choice.MeshCol.w = 0.5f;
	Choice.objScal = D3DXVECTOR3(240.0f,(float)(ML->CSMin.FontSize) * 1.1f,1.0f);
	Choice.objPos = D3DXVECTOR3(-80.0f,0.0f,0.0f);
	//�^�C�g��
	Title.SetText(_T(" "));
	Title.objPos.y = 310.0f;
	Title.objPos.x = -220.0f;
	//���
	info.objPos.y = -215.0f;
	info.SetText(_T(" "));
	info.objPos.x = -200.0f;
	//����
	Cell.SetText(_T(" "));
	Cell.objPos.y =  200.0f;
	Cell.objPos.x = -200.0f;
	//�I����
	tSelect.SetText(_T(" "));
	tSelect.drawSkip = TRUE;
	tSelect.objPos.x = -120.0f;
	tSelect.objPos.y = (float)ML->CSMin.FontSize;
	//�������
	CtrlOpe.SetText(_T(" "));
	CtrlOpe.objPos = D3DXVECTOR3(300.0f,250.0f,0.0f);
	CtrlOpe.objPos = D3DXVECTOR3(-390.0f,-320.0f,0.0f);
	CtrlOpe.objScal= D3DXVECTOR3(1.0f,1.0f,1.0f) * 0.7f;

	//FVF�I�u�W�F�N�g
	//�w�i
	BackGround.SetTex(bmp_note);
	float w = (float)ML->GV.ClientHeight * 1.3333f;
	BackGround.objScal = D3DXVECTOR3(w,(float)ML->GV.ClientHeight,1.0f);
	BackGround.MeshCol = D3DXVECTOR4(0.5f,0.5f,0.5f,1.0f);
	//�I�����̔w�i
	SlctBg.objScal = D3DXVECTOR3(400.0f,(float)(ML->CSMin.FontSize) * 1.1f*3.5f,0.0f);
	SlctBg.MeshCol = D3DXVECTOR4(0.0f,0.0f,0.0f,0.5f);
	//�I�����̑I��
	Slct.objScal =  D3DXVECTOR3(150.0f,(float)(ML->CSMin.FontSize) * 1.1f,1.0f);
	Slct.MeshCol = D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f);	
	//�����w�i��
	bgBlackL.MeshCol = D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f);
	bgBlackL.objScal = D3DXVECTOR3(500.0f,1.0f,0.0f);
	bgBlackL.objPos = D3DXVECTOR3(25.0f,260.0f,0.0f);
	//�����w�i��
	bgBlackM.MeshCol = D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f);
	bgBlackM.objScal =  D3DXVECTOR3(500.0f,1.0f,0.0f);
	bgBlackM.objPos = D3DXVECTOR3(25.0f,-190.0f,0.0f);




}

//�I�������Ăяo��
VOID MenuMtrl::SetSelect()
{
	SelectMode = 1;
	Select = 0;
}
//�I�����̌��ʂ��o��(0��̑I����-1���̑I����)
BOOL MenuMtrl::GetSelect(int n)
{
	if(SelectMode == -1)
	{
		SelectMode = 0;
		if(Select == n)
		{
			Select = 0;
			return TRUE;
		}
	}
	return FALSE;
}
//�X�V
VOID MenuMtrl::Update(BOOL ch,BOOL ca,BOOL cl)
{
	Close = cl;
	Check = ch;
	Cansel = ca;
}
//�I�����̍X�V�I�������o�Ă���Ƃ���1�łĂ��Ȃ��Ƃ���0��Ԃ�
int MenuMtrl::UpdateSelect()
{
	if(SelectMode != 1)
	{
		//�I�����̔�\��
		SlctBg.drawSkip = TRUE;
		Slct.drawSkip = TRUE;
		tSelect.drawSkip = TRUE;
		return 0;
	}
	//�I�����̕\��
	tSelect.drawSkip = FALSE;
	SlctBg.drawSkip = FALSE;
	Slct.drawSkip = FALSE;
	int ssize = tSelect.hN(ML) + 1;
	
	//���ʉ�
	if(PreSelect != Select){SelectSE();}
	PreSelect = Select;

	//�L�[�{�[�h����̏ꍇ
	if(ML->C.getkey.k0m1 == 0)
	{
		//�I�����𓮂���
		if(ML->C.UP.T()){	Select++;	}
		else if(ML->C.DOWN.T()){Select--;}

		//�I�����̏��
		if(Select < ssize){	Select = 0;	}
		else if(Select > 0){Select = ssize;}
	}
	//�}�E�X����
	else
	{
		float y = (float)ML->CSMin.FontSize * 1.1f;
		float hy = y * 0.5f;
		float uy = tSelect.objPos.y + hy;
		int s = 1;//�X�^�[�g�̍s
		//�㉺�̓����蔻��
		for(int i = s; i <= -tSelect.hN(ML); i++)
		{
			if(ML->GV.mPos.y < uy - ( i * y ))
			if(ML->GV.mPos.y > uy - ((i + 1 ) * y))
			{
				Select = -(i-s);
			}
		}
	}	
	
	//����
	if(Check){	SelectMode = -1;}
	//�L�����Z��
	else if(Cansel)
	{
		Select = 0;
		SelectMode = 0;
	}
	//�J�[�\���̈ʒu
	Slct.objPos.y = (float)ML->CSMin.FontSize * tSelect.intrval.x * (float)Select;
	Slct.MeshCol.w = alpha.Val(Key);
	Choice.MeshCol.w = 0.5f;
	return 1;
}
//���j���[�̍X�V
int MenuMtrl::UpdateMenu()
{	
	//�A�j���[�V����
	Key++;
	if(Key > alpha.MaxKey()){Key = 0;}
	//���͑҂�
	if(Wait)
	{
		if(Check || Cansel || Close){Wait = FALSE;}
		return 1;
	}
	//�I����������ꍇ�I��
	if(UpdateSelect() == 1){return 1;}

	//���ʉ�
	if(PreSp != Sp){SelectSE();}
	PreSp= Sp;

	//�y�[�W���̃J�[�\���𓮂���
	int ysize = Cell.hN(ML);
	//�L�[�{�[�h����̏ꍇ
	if(ML->C.getkey.k0m1 == 0)
	{
		//�I�����𓮂���
		if(ML->C.UP.T()){	Sp++;	}
		else if(ML->C.DOWN.T())	{	Sp--;}
	}
	//�}�E�X����
	else
	{
		float y = (float)ML->CSMin.FontSize * 1.0f;
		float hy = y * 0.5f;
		float uy = Cell.objPos.y + hy;
		int s = 0;//�X�^�[�g�̍s
		//�㉺�̓����蔻��
		for(int i = s; i <= -Cell.hN(ML); i++)
		{
			if(ML->GV.mPos.y < uy - ( i * y ))
			if(ML->GV.mPos.y > uy - ((i + 1 ) * y))
			{
				Sp  = -(i-s);
			}
		}
	}	
	
	if(Sp < ysize){Sp = 0;}
	else if(Sp > 0){Sp = ysize;}
	Choice.objPos.y = 200.0f + (float)ML->CSMin.FontSize * Cell.intrval.y * (float)Sp;
	Choice.MeshCol.w = alpha.Val(Key);
	return 0;
}

//�`��
VOID MenuMtrl::draw()
{
	BackGround.draw(ML);
	bgBlackL.draw(ML);
	bgBlackM.draw(ML);
	Choice.draw(ML);
	Title.draw(ML);
	info.draw(ML);
	Cell.draw(ML);
	SlctBg.draw(ML);
	Slct.draw(ML);
	tSelect.draw(ML);
	CtrlOpe.draw(ML);
}

VOID MenuMtrl::Debug(TCHAR* ,int )
{
	
}
