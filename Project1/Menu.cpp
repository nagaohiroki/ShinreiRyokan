//==========================================================
//���j���[�y�[�W���I�u�W�F�N�g
//==========================================================
MenuPage::MenuPage(){}
MenuPage::~MenuPage(){}
int MenuPage::Update(MenuMtrl*){	return 1;}
int MenuPage::MainUpdate(MenuMtrl* mm)
{
	if(mm->UpdateMenu() == 1){return 1;}
	//�y�[�W�̍X�V
	return Update(mm);
}
VOID MenuPage::draw(MenuMtrl*){}

//==========================================================
//���C�����j���[
//==========================================================
MainPage::MainPage(){}
int MainPage::Update(MenuMtrl* mm)
{
	mm->Title.SetText(_T("���j���["));
	mm->Cell.SetText(_T("������\n�Z�[�u\n�ݒ�ύX\n�^�C�g���ɖ߂�"));
	mm->info.SetText(_T(""));
	mm->tSelect.SetText(_T("�^�C�g���ɖ߂�?\n     �͂�\n     ������"));	

	mm->CtrlOpe.SetText(
		_T("�����L�[���}�E�X�őI��   ")
		_T("Z�����N���b�N�Ō���   ")
		_T("X���E�N���b�N��Space�Ń��j���[�����"));
	//�I������I��Ń^�C�g���ɖ߂�
	if(mm->GetSelect(0))
	{
		mm->Sp = 0;	
		return -1;
	}
	
	//�L�����Z���������ƃ��j���[�����
	if(mm->Cansel)
	{
		mm->Sp = 0;
		return 0;
	}	
	//�`�F�b�N�{�^���������Ɗe�y�[�W�Ɉڂ�
	if(mm->Check)
	{
		
		//�A�C�e��
		if(mm->Sp == 0){mm->Sp = 0;mm->Page = MP_ITEM;}
		//�Z�[�u
		if(mm->Sp == -1)
		{
			//�G������ƃZ�[�u�ł��Ȃ�
			if(mm->FM->enemy.mode == Enemy::MODE_CLEAR)
			{
		
				mm->Sp = 0;
				mm->Page = MP_SAVE;
			}
		}
		//�ݒ�
		if(mm->Sp == -2){mm->Sp = 0;mm->Page = MP_OPTION;}
		//�^�C�g���I�������[�h�ɂ���
		if(mm->Sp == -3){	mm->SetSelect();	}	
		
		mm->ML->C.getkey.k0m1 = 0;//�}�E�X�̈ʒu�ɃJ�[�\����u���Ȃ��悤��
	}
	//�G������ƃZ�[�u�ł��Ȃ�
	if(mm->Sp == 0)
	{
		mm->info.SetText(_T("���������m�F����\n���j���[���玝�������g�p���邱�Ƃ͂ł��Ȃ�"));
	}
	else if(mm->Sp == -1)
	{
		if(mm->FM->enemy.mode != Enemy::MODE_CLEAR)
		{
			mm->info.SetText(_T("�Z�[�u�ł��Ȃ�"));
	
		}
		else
		{
			mm->info.SetText(_T("���̏�Ԃ��L�^����\n�Â�����ĊJ�ł���"));
		}
	}
	else if(mm->Sp == -2)
	{		
		mm->info.SetText(_T("���ʁA�P�x�A�𑜓x��ύX�ł���"));
	}
	else if(mm->Sp == -3)
	{
		mm->info.SetText(_T("�^�C�g���ɖ߂�B�Z�[�u�����Y��Ȃ�"));

	}

	return 1;
}
//==========================================================
//�A�C�e�����j���[
//==========================================================
ItemPage::ItemPage()
{
	_stprintf_s(t,ITEMMAX,_T(""));
}
int ItemPage::Update(MenuMtrl* mm)
{
	mm->Title.SetText(_T("������"));
	mm->CtrlOpe.SetText(
		_T("�����L�[���}�E�X�őI��   ")
		_T("X���E�N���b�N�Ŗ߂�   ")
		_T("Space�Ń��j���[�����"));


	
	int index[ITEM_MAX] = {0};
	int in = 0;
	//�Z������
	_stprintf_s(t,ITEMMAX,_T("�m�[�g"));
	for(int i = 0; i < ITEM_MAX; i++)
	{
		if(mm->FM->iGetFlag((ITEM)i))
		{			
			_stprintf_s(t,ITEMMAX,_T("%s\n%s"),t,mm->ML->itemList.item[i].name);
			index[in] = i;
			in++;
		}
	}
	//info
	if(mm->Sp == 0){mm->info.SetText(_T("�L�^�⎝��������������m�[�g"));}
	else
	{
		//�A�C�e�����
		int n =  index[-mm->Sp-1];
		mm->info.SetText(mm->ML->itemList.item[n].info);
	}
	mm->Cell.SetText(t);
	//�L�����Z���{�^���Ŗ߂�
	if(mm->Cansel)
	{
		mm->ML->C.getkey.k0m1 = 0;
		mm->Sp = 0;
		mm->Page = MP_MAIN;
	}
	return 1;
}
//==========================================================
//�Z�[�u���j���[
//==========================================================
SavePage::SavePage()
{	
	InfoClear = FALSE;
	LoadNum = -1;
	_stprintf_s(t,FMMAX,_T(""));
	for( int i = 0; i < GameSave::MAX_SAVE; i++ )
	{
		LoadSuc[i] = GameSave().Load(&Fm[i],i);
	}
}
int SavePage::Update(MenuMtrl* mm)
{
	//�L�����Z���{�^���Ŗ߂�
	if(mm->Cansel || mm->FM->enemy.mode != Enemy::MODE_CLEAR)
	{		
		mm->ML->C.getkey.k0m1 = 0;
 		mm->Sp = -1;
		mm->Page = MP_MAIN;		
	}
	//�e�L�X�g�̃Z�b�g
	mm->Title.SetText(_T("�Z�[�u"));
	mm->Cell.SetText(_T("�Z�[�u�f�[�^1\n�Z�[�u�f�[�^2\n�Z�[�u�f�[�^3"));	
	mm->CtrlOpe.SetText(
		_T("�����L�[���}�E�X�őI��   ")
		_T("Z�����N���b�N�Ō���   ")
		_T("X���E�N���b�N�Ŗ߂�   ")
		_T("Space�Ń��j���[�����"));
	//�I�����̌��ʂ��o����Z�[�u
	if(mm->GetSelect(0))
	{
		//�Z�[�u����
		if(GameSave().Save(mm->FM,-mm->Sp))
		{
			//���[�h���X�V
			LoadSuc[-mm->Sp] = GameSave().Load(&Fm[-mm->Sp],-mm->Sp);
			mm->info.SetText(_T("�Z�[�u���܂���"));	
		}
		else{	mm->info.SetText(_T("�Z�[�u�Ɏ��s���܂���"));}
		//���͑҂����Ăяo���A�Z�[�u���܂����̕���������
		mm->SetWait();
		InfoClear = TRUE;
	}
	//�Z�[�u���܂����̕���������
	if(InfoClear)
	{
		if(!mm->Wait)
		{
			mm->info.SetText(_T(""));
			InfoClear = FALSE;
		}
	}

	if(mm->Check)
	{		
		//�I�������Ăяo��
		mm->SetSelect();
		mm->tSelect.SetText(_T("�Z�[�u���܂���?\n     �͂�\n     ������"));
	}
	//�Z�[�u�f�[�^�̏���\��
	if(!mm->Wait)
	{
		if(LoadSuc[-mm->Sp])
		{
			Fm[-mm->Sp].ShowData(t,FMMAX);
			mm->info.SetText(t);
		}
		else{mm->info.SetText(_T("�f�[�^������܂���"));	}
	}
	
	return 1;
}
//==========================================================
//�ݒ�ύX�̃V�[�N�o�[
//==========================================================
SeekBer::SeekBer()
{
	Hold = FALSE;
	mater.objScal = D3DXVECTOR3(20.0f,20.0f,0.0f);
	ber.objScal = D3DXVECTOR3(20.0f,20.0f,0.0f);
	ber.MeshCol = D3DXVECTOR4(0.5f,0.5f,0.5f,1.0f);
}
//2D�����蔻��
BOOL SeekBer::Hit2D(D3DXVECTOR2* m,D3DXVECTOR2* mx,D3DXVECTOR2* mn)
{
	return !(m->x > mx->x || m->x < mn->x || m->y > mx->y || m->y < mn->y);
}
//�V�[�N�̍X�V(ml,�ύX����l,�ʒu,�o�[�̃T�C�Y,�ŏ��l,�ő�l) 
VOID SeekBer::update(MyLibrary* ml,float* now,D3DXVECTOR2* pos,float size,float mn,float mx)
{
	mater.MeshCol.w = 1.0f;
	if(Hold)
	{	
		if(ml->C.getkey.k0m1 == 0)
		{
			//�L�[�{�[�h
			if(ml->C.RIGHT.T()|| ml->C.RIGHT.time() > 20){*now += 0.01f; }
			if(ml->C.LEFT.T() || ml->C.LEFT.time()  > 20){*now -= 0.01f;}
		}
		else{	*now = (mx - mn) * ( ml->GV.mPos.x - pos->x ) / size + mn;	}
		mater.MeshCol.w = 0.2f;

	}
	if(*now > mx){*now = mx;}
	if(*now < mn){*now = mn;}
	//�g�O���̃X�e�[�^�X
	mater.objPos = D3DXVECTOR3(pos->x + ((*now - mn) / (mx - mn)) * size,pos->y,0.0f);
	//�o�[�̃X�e�[�^�X
	ber.objPos.y = pos->y;
	ber.objPos.x = pos->x + size * 0.5f ;
	ber.objScal.x= 100.0f+ mater.objScal.x ;
}
//�g�O���̓����蔻��
BOOL SeekBer::Hit(MyLibrary* ml)
{	
	D3DXVECTOR2 mx(mater.objPos.x + mater.objScal.x*0.5f,mater.objPos.y + mater.objScal.y*0.5f);
	D3DXVECTOR2 mn(mater.objPos.x - mater.objScal.x*0.5f,mater.objPos.y - mater.objScal.y*0.5f);
	return Hit2D(&ml->GV.mPos,&mx,&mn);
}
//�`��
VOID SeekBer::draw(MyLibrary* ml)
{
	ber.draw(ml);
	mater.draw(ml);
}
//==========================================================
//�ݒ�ύX
//==========================================================
OptionPage::OptionPage()
{
	HoldPix = FALSE;
	_stprintf_s(t,tn,_T(""));
	k = 0;
	PixelSize.SetText(_T("1024x768 1280x720"));
	PixelSize.objPos = D3DXVECTOR3(-200.0f,80.0f,0.0f);
	ber.objScal.x = 120.0f;
	ber.MeshCol.w = 0.5f;
	ber.objPos.y = 80.0f;

	PrePix = 0;

	Key = 0;
	alpha.SetKey(0,0.0f);
	alpha.SetKey(50,0.5f);
	alpha.SetKey(100,0.0f);
}
int OptionPage::Update(MenuMtrl* mm)
{	
	if(HoldPix){mm->Sp = -3;}
	//�e�L�X�g�̃Z�b�g
	mm->Title.SetText(_T("�ݒ�ύX"));
	_stprintf_s(t,tn,_T("�ݒ�������ɖ߂�\n���� %.2f\n�P�x %.2f\n�𑜓x")	,mm->ML->Sd.Volume	,mm->ML->Sd.Lum	);
	//����
	mm->Cell.SetText(t);
	//������@
	mm->CtrlOpe.SetText(
		_T("�����L�[���}�E�X�őI��   ")
		_T("Z�����N���b�N�Ō���   ")
		_T("X���E�N���b�N�Ŗ߂�   ")
		_T("Space�Ń��j���[�����"));


	//�ω��𔽉f������
	mm->ML->UpdateSys();
	//�L�����Z���{�^���Ŗ߂�
	if(mm->Cansel)
	{
		mm->ML->C.getkey.k0m1 = 0;
		mm->Page = MP_MAIN;	
		SystemSave().Save(&mm->ML->Sd);
		mm->Sp = -2;
	}
	if(mm->Close){SystemSave().Save(&mm->ML->Sd);}
	//������
	if( mm->Sp == 0 )
	{
		if(mm->Check){	mm->ML->Sd.InitOption();	}
	}
	//�}�E�X����
	if(mm->ML->C.getkey.k0m1 == 1)
	{
		if(mm->ML->C.Z.K())
		{
			if(k == 0)
			{
				if(volume.Hit(mm->ML)){k = 1;}
				if(lum.Hit(mm->ML)){k = 2;}
			}	
		}
		else
		{
			k = 0;
			lum.Hold = FALSE;
			volume.Hold = FALSE;
		}	
		if(k == 1){		volume.Hold = TRUE;}
		if(k == 2){		lum.Hold = TRUE;}
		//�i��
		if(volume.Hold){mm->Sp = -1;}
		if(lum.Hold){mm->Sp = -2;}
		mm->Choice.objPos.y = 200.0f + (float)mm->ML->CSMin.FontSize * mm->Cell.intrval.y * (float)mm->Sp;
	}
	//�L�[�{�[�h����
	else
	{		
		k = 0;
		lum.Hold = FALSE;
		volume.Hold = FALSE;
		if(mm->Sp == -1){volume.Hold = TRUE;}
		if(mm->Sp == -2){lum.Hold = TRUE;}
	}
	//�G�f�B�^
	float inv = (float)mm->ML->CSMin.FontSize* mm->Cell.intrval.y;//�i��
	volume.update(mm->ML,&mm->ML->Sd.Volume,&D3DXVECTOR2(100.0f,mm->Cell.objPos.y -inv*1.0f),100.0f,0.0f,4.0f);
	lum.update(mm->ML,&mm->ML->Sd.Lum,&D3DXVECTOR2(100.0f,mm->Cell.objPos.y -inv*2.0f),100.0f,0.0f,4.0f);
	if(mm->Sp == 0)
	{
		mm->info.SetText(_T(""));
	}
	if(mm->Sp == -1)
	{
		mm->info.SetText(_T("�E�̃X���C�_�[�𓮂���\n�������́����L�[�ŉ��ʒ���\n�傫������Ɖ����ꂷ��\��������܂�"));
	}
	if(mm->Sp == -2)
	{
		mm->info.SetText(_T("�E�̃X���C�_�[�𓮂���\n�������́����L�[�ŋP�x����"));
	}
	if(mm->Sp == -3)
	{
		mm->info.SetText(_T("�𑜓x�̕ύX\n����N�����ɔ��f����܂�"));	
		if(HoldPix)
		{
			//�A���t�@�Œ�
			mm->Key = 25; 
			//�_��
			Key++;
			if(Key > alpha.MaxKey()){Key = 0;}
			ber.MeshCol.w = alpha.Val(Key);
			//���ʉ�
			if(	PrePix != mm->ML->Sd.PixelMode ){mm->SelectSE();}
			PrePix = mm->ML->Sd.PixelMode;
			//�}�E�X����
			if(mm->ML->C.getkey.k0m1 == 1)
			{
				if( mm->ML->GV.mPos.x < -85.0f ){mm->ML->Sd.PixelMode = 0;}
				if( mm->ML->GV.mPos.x > -85.0f ){mm->ML->Sd.PixelMode = 1;}
				
			}
			else
			{
				//�L�[�{�[�h����
				if(mm->ML->C.LEFT.T()){	mm->ML->Sd.PixelMode--;	}
				else if(mm->ML->C.RIGHT.T()){mm->ML->Sd.PixelMode++;}
				if( mm->ML->Sd.PixelMode < 0 ){ mm->ML->Sd.PixelMode = 1; }
				if( mm->ML->Sd.PixelMode > 1 ){ mm->ML->Sd.PixelMode = 0; }
			}
		}
		if(mm->Check)
		{
			if(HoldPix){HoldPix = FALSE;}
			else{HoldPix = TRUE;}
		}
		
	}
	else{ber.MeshCol.w = 0.5f;} 
	
	//�J�[�\���ʒu
	ber.objScal.y = (float)mm->ML->CSMin.FontSize * PixelSize.objScal.y * PixelSize.intrval.y;
	switch( mm->ML->Sd.PixelMode )
	{
	case 0:ber.objPos.x = -145.0f;break;
	case 1:ber.objPos.x = -25.0f;break;
	default:ber.objPos.x = -145.0f;break;
	}
	return 1;
}
VOID OptionPage::draw(MenuMtrl* mm)
{
	volume.draw(mm->ML);
	lum.draw(mm->ML);

	ber.draw(mm->ML);
	PixelSize.draw(mm->ML);
}
//==========================================================
//���C�����j���[
//==========================================================
Menu::Menu()
{
	drawFlag = FALSE;

}
VOID Menu::Set(MyLibrary* ml,FlagManager* fm)
{
	vecPage.push_back(&PgMain);
	vecPage.push_back(&PgItem);
	vecPage.push_back(&PgSave);
	vecPage.push_back(&PgOption);
	mm.Set(ml,fm);
}
int Menu::Update(BOOL Check,BOOL Cansel,BOOL Close)
{	
	mm.ML->C.MouseLock(TRUE,mm.ML->hW);

	drawFlag = TRUE;
	mm.Update(Check,Cansel,Close);
	//�I���̈ʒu
	//�y�[�W�̍X�V
	//�߂�l0���j���[�����,1�ʏ�X�V,-1�^�C�g���ɖ߂�
	return vecPage[mm.Page]->MainUpdate(&mm);
}
VOID Menu::draw()
{
	if(drawFlag == FALSE){return;}
	mm.draw();
	vecPage[mm.Page]->draw(&mm);
}
VOID Menu::CloseMenu()
{
	mm.ML->C.MouseLock(FALSE,mm.ML->hW);
	drawFlag = FALSE;
	mm.Select = 0;
	mm.SelectMode = 0;
	mm.Wait = FALSE;
	mm.Page = MP_MAIN;
	mm.Sp = 0;
}
VOID Menu::DebugText(TCHAR* t,int l)
{
	//*
	_stprintf_s(t,l,
		_T("%s\n")
		_T("Page = %d\n")
		_T("select = %d\n")
		_T("selectflag = %d\n")
		_T("Sp = %d\n")
		,t
		,mm.Page
		,mm.Select
		,mm.SelectMode
		,mm.Sp 	
		
		);
	//	*/
	//mm.Debug(t,l);
}
