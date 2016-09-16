//�R���X�g���N�^
GameText::GameText()
{
	Page = 0;
	Flag = 0;
	Count = 0;
	txt.drawSkip = TRUE;//�`�拖��
	txt.StrLen=0;//�`�敶����
	txt.objScal = D3DXVECTOR3(1.0f,1.0f,1.0f) * 1.0f;
	select.drawSkip = TRUE;
	select.MeshCol = D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f);
	bg.drawSkip = TRUE;
	feed.SetKey(0,0.0f);
	feed.SetKey(50,0.5f);
	feed.SetKey(100,0.0f);

}
//�e�I�u�W�F�N�g���V�[���ɃZ�b�g
VOID GameText::init(Scene* S)
{

	S->Ui.push_back(&bg);
	S->Ui.push_back(&select);
	S->UiTxt.push_back(&txt);
}
//�e�L�X�g�����
VOID GameText::s(TCHAR* t)
{
	tp tP;
	tP.first= t;
	str.push_back(tP);
}


VOID GameText::s(TCHAR* t,int i1)
{
	tp tP;
	tP.second.push_back(i1);
	tP.first = t;
	str.push_back(tP);

}

VOID GameText::s(TCHAR* t,int i1,int i2)
{
	tp tP;
	tP.second.push_back(i1);
	tP.second.push_back(i2);
	tP.first = t;
	str.push_back(tP);

}
//�e�L�X�g�X�^�[�g
VOID GameText::StartText(Personal* P)
{
	
	bg.drawSkip = FALSE;
	txt.drawSkip = FALSE;
	P->Mode = Personal::MODE_EVENT;//�񑀍샂�[�h
	P->gt.MotionType = gt_Anim::Motion_Wait;
	Page = 0;//�e�L�X�g�̃y�[�W��
	txt.drawSkip = FALSE;//�`�拖��
	txt.StrLen=0;//�`�敶����
	
}
//�X�V
int GameText::Update(Personal* P,MyLibrary* ML)
{	
	if(txt.drawSkip){return 0;}
	bg.MeshCol = D3DXVECTOR4(0.0f,0.0f,0.0f,0.8f);
	bg.objScal.x = (float)ML->GV.ClientWidth;
	bg.objScal.y = 110.0f;
	bg.objScal.z = 1.0f;	
	bg.objPos.x = 0.0f;
	bg.objPos.y = bg.objScal.y/2.0f - (float)(ML->GV.ClientHeight/2);
	bg.objPos.z = 0.2f;

	float x = (float)ML->CSMin.FontSize * txt.objScal.x * txt.intrval.x;
	float y = (float)ML->CSMin.FontSize * txt.objScal.y * txt.intrval.y;
	txt.intrval.y = 1.3f;
	txt.objPos.x = -450.0f;
	txt.objPos.y = bg.objPos.y + y; 
	txt.objPos.z = 0.0f;
	select.objScal = D3DXVECTOR3(x*10.0f,y,0.0f);
	select.objPos.x = txt.objPos.x + select.objScal.x * 0.5f; 
	select.objPos.z = 0.1f;
	select.drawSkip = TRUE;
	
	//�w��y�[�W�̃e�L�X�g��\��
	txt.SetText(str[Page].first);
	int size = str[Page].second.size();
	switch(size)
	{
	case 0:break;
	case 1:Flag = 0;break;
	default:
		if(txt.StrLen >= txt.Max())
		{
			select.MeshCol.w = feed.Val(Count);
			select.drawSkip = FALSE;
		}
		//�I����
		if(ML->C.UP.T() || ML->C.DOWN.T())
		{
			Flag = 1 - Flag;
			//�I������
			P->CheckSE(Personal::SE_SELECT);
		}
		break;
	}
	//�I��
	select.objPos.y =  txt.objPos.y - y * (float)Flag - y;	
	//�����̑���
	if(txt.Max() > txt.StrLen){	txt.StrLen++;}
	Count++;
	if(Count > 100){Count = 0;}
	//���ׂ�{�^���������ƃy�[�W�𑗂�
	if( P->Check )
	{
		if(txt.StrLen >= txt.Max())
		{		
			//������������Z�b�g
			txt.StrLen = 0;
			//�w��̔ԍ��������ꍇ�y�[�W��1����
			if(size == 0){	Page++;	}
			else{Page = str[Page].second[Flag];	}
		}			
			
	}	
	//�y�[�W���ő�ɒB�����烁�b�Z�[�W�I��
	if((int)str.size() <= Page)
	{
		Flag = 0;
		select.drawSkip = TRUE;

		bg.drawSkip = TRUE;
		txt.drawSkip = TRUE;//�`�撆�~
		P->Mode      = Personal::MODE_ACTIVE;//�ړ����[�h
		P->Check     = FALSE;//��x�ڂ��Ȃ��悤��
	}
	return Page;
	
}
//�e�L�X�g�y�[�W��
int GameText::Max()
{
	return (int)str.size();
}
//�f�o�b�O
VOID GameText::DebugText(TCHAR* t,int l)
{
	_stprintf_s(t,l,_T("%s")
		_T("%f,%f\n")
		,t
		,txt.vol.x
		,txt.vol.y
		);
}
