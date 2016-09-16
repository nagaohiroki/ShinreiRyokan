//======================================
//���r�[�ɏo���
//======================================
const TCHAR* Lobby_Door::name(){return _T("Lobby_Door");}
Lobby_Door::Lobby_Door()
{
	//�����蔻��
	Msh.push_back(&pBox);
	pBox.Type(x_cube);
	pBox.drawSkip=TRUE;
	pBox.HitMode(CT_OBB,CB_NONE);
	//�h�A�g
	Msh.push_back(&pWaku);
	pWaku.Type(x_wood_door_waku);
	pWaku.objScal=D3DXVECTOR3(0.8f,0.9f,1.0f);
	pWaku.ShadowFlag=FALSE;
	pWaku.SetPare(&pBox.mWorld);
	//�h�A
	Msh.push_back(&pDoor);
	pDoor.Type(x_wood_door);
	pDoor.SetPare(&pWaku.mWorld);
	pDoor.objPos.x=-0.47f;
	pDoor.ShadowFlag=FALSE;
	//�h�A�m�u
	Msh.push_back(&pNobu);
	pNobu.Type(x_doornobu);
	pNobu.SetPare(&pDoor.mWorld);
	pNobu.objPos=D3DXVECTOR3(0.82f,0.75f,0);
	pNobu.ShadowFlag=FALSE;	
}
VOID Lobby_Door::Update()
{
	//�ړ�
	if(pBox.HitObj.Reaction == 1)
	if(P->Check)
	if(P->Mode != Personal::MODE_EVENT)
	{
		P->CheckSE(Personal::SE_OPEN);	
		m_pPare->FldChange(new Lobby,&D3DXVECTOR3(12.00f,0.00f,13.20f),270.0f);
	}
}
//======================================
//��
//======================================
const TCHAR* Desk::name(){return _T("Desk");}
Desk::Desk()
{
	//��
	desk.Type(x_desk);
	desk.Bias = 0.3f;
	desk.MeshCol = D3DXVECTOR4(0.4f,0.4f,0.4f,1.0f);
	Msh.push_back(&desk);
	//�����蔻��
	hitbox.Type(x_cube);
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.SetPare(&desk.mWorld);
	hitbox.objPos =D3DXVECTOR3(0.25f,0.0f,0.25f);
	hitbox.drawSkip = TRUE;
	Msh.push_back(&hitbox);
	//�e�L�X�g
	text.init(this);
	text.s(_T("���̒��ɂ͂Ȃɂ��Ȃ�"));
}
VOID Desk::Update()
{
	if(hitbox.HitObj.Reaction == 1)
	if(P->Check)
	if(P->Mode != Personal::MODE_EVENT)
	{
		text.StartText(P);
	}
	text.Update(P,ML);
}

//======================================
//��
//======================================
const TCHAR* KeyDesk::name(){return _T("KeyDesk");}
KeyDesk::KeyDesk()
{
	//��
	desk.Type(x_desk);
	desk.Bias = 0.3f;
	desk.MeshCol = D3DXVECTOR4(0.4f,0.4f,0.4f,1.0f);
	Msh.push_back(&desk);
	//�����蔻��
	hitbox.Type(x_cube);
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.SetPare(&desk.mWorld);
	hitbox.objPos =D3DXVECTOR3(0.25f,0.0f,0.25f);
	hitbox.drawSkip = TRUE;
	Msh.push_back(&hitbox);
	//�e�L�X�g
	text.init(this);
	text.s(_T("�y���̌��z���g����"));
	text.s(_T("���̒��ɂ͉�������"));
	//�e�L�X�g1
	text1.init(this);
	text1.s(_T("���̈����o���ɂ͌����������Ă���"));

	//�����������Ă鉹
	lock.Set(wav_keylock);
	lock.m_b3DSound = TRUE;
	Snd.push_back(&lock);
	//�J����
	unlock.Set(wav_dooropen);
	unlock.Filter.Type = BandPassFilter;
	unlock.Filter.OneOverQ = 0.1f;
	unlock.m_b3DSound = TRUE;
	Snd.push_back(&unlock);
}
VOID KeyDesk::Update()
{
	
	if(P->FM.iGetedFlag(ITEM_DESK_KEY))
	if(!P->FM.iGetFlag(ITEM_DESK_KEY))
	{
		return;
	}
	
	
	if(hitbox.HitObj.Reaction == 1)
	if(P->Check)
	if(P->Mode != Personal::MODE_EVENT)
	{ 
		if(P->FM.iGetedFlag(ITEM_DESK_KEY))
		{
			//�J��
			unlock.Emi.Position = desk.objPos;
			unlock.Start(ML);
			text.StartText(P);
		}
		else
		{
			//�����������Ă�
			lock.Emi.Position = desk.objPos;
			lock.Start(ML);

			text1.StartText(P);
		}
	
	}
	text1.Update(P,ML);
	int t = text.Update(P,ML);

	//�����̂Ă�
	if(t == 2)
	{
		P->FM.iRelease(ITEM_DESK_KEY);
	}
		
	
}

//======================================
//�z���C�g�{�[�h
//======================================
const TCHAR* WhiteBord::name(){return _T("WhiteBord");}
WhiteBord::WhiteBord()
{
	flag = 0;
	frame = 0;

	//�z���C�g�{�[�h
	white.Type(x_whitebord);
	white.Bias = 0.3f;
	Msh.push_back(&white);

	hitbox.Type(x_cube);
	hitbox.drawSkip = TRUE;
	hitbox.HitMode(CT_OBB,CB_PLUS);
	hitbox.objScal = D3DXVECTOR3(4.054777f,7.0f,0.362946f);
	hitbox.objPos  = D3DXVECTOR3(0.0f,0.0f,0.0f);
	Msh.push_back(&hitbox);

	head.Type(x_sphere);
	head.HitMode(CT_SPHERE,CB_NONE);
	head.objScal = D3DXVECTOR3(1.0f,1.0f,1.0f) * 0.3f;
	head.drawSkip = TRUE;
	Msh.push_back(&head);

	rot.SetKey(0,0.0f);
	rot.SetKey(90,20.0f);
	rot.SetKey(100,70.0f);
	
	se.Set(wav_oop);
	se.m_b3DSound = TRUE;
	se.Filter.Frequency = 0.1f;
	Snd.push_back(&se);
}
VOID WhiteBord::Update()
{
	head.SetHit(ML);
	hitbox.SetHit(ML);
	hitbox.objPos = white.objPos;
	hitbox.YPR = white.YPR;
	head.objPos = P->obj.objPos + D3DXVECTOR3(0.0f,1.0f,0.0f);
	if(	P->FM.EventFlag >= TL_WHITEBORD)
	{
		white.YPR.x = 70.0f;
		hitbox.YPR.x = 70.0f;
		return;
	}
	if(flag == 0)
	{
		if(P->FM.iGetedFlag(ITEM_DESK_KEY))
		if(!P->FM.iGetFlag(ITEM_DESK_KEY))
		{
			flag = 1;
	
		}	
	}
	if(flag == 1)
	{
		frame++;
		if(frame > 100)
		{
			se.Emi.Position = white.objPos;
			se.Start(ML);
			flag = 2;
		}
		float r = rot.Val1(frame);
		white.YPR.x =  r;
		//���ɓ�����ƃQ�[���I�[�o�[
		if(frame > 90)
		{
			
			if(ML->Col.Hit(&head.HitObj,&hitbox.HitObj))
			{
				m_pPare->FldChange(new Gameover,&D3DXVECTOR3(0.0f,0.0f,0.0f),0.0f);
				
			}
		}
	}
	if(flag == 2)
	{
		P->FM.EventFlag = TL_WHITEBORD;
	}
}
VOID WhiteBord::DebugText(TCHAR* t,int l)
{
	_stprintf_s(t,l,
		_T("%s\n")
		_T("flag = %d\n")
		,t
		,flag
		
		);
}

//======================================
//��
//======================================
const TCHAR* Key203::name(){return _T("Key203");}
Key203::Key203()
{
	
	hitbox.Type(x_cube);
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.drawSkip = TRUE;
	hitbox.MeshCol.w = 0.5f;
	Msh.push_back(&hitbox);
	
	key.Type(x_key);
	key.SetPare(&hitbox.mWorld);
	key.objScal = D3DXVECTOR3(0.15f,0.15f,0.15f);
	Msh.push_back(&key);
	
	text.init(this);
	text.s(_T("�y203�����̌��z����ɓ��ꂽ"));

}
VOID Key203::Update()
{
	if(P->FM.iGetedFlag(ITEM_203_KEY))
	{
		key.drawSkip = TRUE;
		return;
	}
	if(hitbox.HitObj.Reaction == 1)
	if(P->Check)
	if(P->Mode != Personal::MODE_EVENT)
	{
		P->CheckSE(Personal::SE_ITEM);
		text.StartText(P);
	}
	if(text.Update(P,ML) == 1)
	{
		P->FM.iGet(ITEM_203_KEY);
	}
	
}

//======================================
//�֎q
//======================================
const TCHAR* StaffChair::name(){return _T("StaffChair");}
StaffChair::StaffChair()
{
	chair.HitMode(CT_OBB,CB_PLUS);
	chair.Type(x_dining_chair);
	chair.SpColm = 0.0f;
	Msh.push_back(&chair);
	chair1.Type(x_dining_chair);
	chair1.SpColm = 0.0f;
	chair1.SetPare(&chair.mWorld);
	chair1.objPos = D3DXVECTOR3(0.0f,0.75f,-0.15f);
	chair1.YPR = D3DXVECTOR3(180.0f,15.0f,0.0f);
	Msh.push_back(&chair1);
}

//======================================
//�x�z�l�̊�
//======================================
const TCHAR* MasterDesk::name(){return _T("MasterDesk");}
MasterDesk::MasterDesk()
{
	//��
	desk.Type(x_desk);
	desk.Bias = 0.3f;
	desk.MeshCol = D3DXVECTOR4(0.4f,0.4f,0.4f,1.0f);
	Msh.push_back(&desk);

	//��
	desk1.Type(x_desk);
	desk1.Bias = 0.3f;
	desk1.MeshCol = D3DXVECTOR4(0.4f,0.4f,0.4f,1.0f);
	desk1.objPos = D3DXVECTOR3(0.1f,1.05f,0.1f);
	desk1.YPR = D3DXVECTOR3(180.0f,10.0f,0.0f);
	desk1.SetPare(&desk.mWorld);
	Msh.push_back(&desk1);
	//�����蔻��
	hitbox.Type(x_cube);
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.SetPare(&desk.mWorld);
	hitbox.objPos =D3DXVECTOR3(0.25f,0.0f,0.25f);
	hitbox.drawSkip = TRUE;
	Msh.push_back(&hitbox);
	//�����蔻��1
	hitbox1.Type(x_cube);
	hitbox1.HitMode(CT_OBB,CB_PLUS);
	hitbox1.SetPare(&desk.mWorld);
	hitbox1.drawSkip = TRUE;
	hitbox1.objScal = D3DXVECTOR3(1.5f,6.0f,1.7f);
	Msh.push_back(&hitbox1);
	//�e�L�X�g
	text.init(this);
	
text.s(_T("�����o���Ƀm�[�g������"));
text.s(_T("���̗��ق̎x�z�l�̓����̂悤��"));
text.s(_T("6/4\n�����H���������̗\���蒷�����Ă���B"));
text.s(_T("�����I��点�Ă��炢�������A\n����΂�����͑҂����Ȃ����낤"));
text.s(_T("11/2\n�����ɂ͗H�삪����悤���B"));
text.s(_T("��Ȗ�ȋ�����������������A\n�����B���ꂽ�肷��"));
text.s(_T("�F�X�΍���������A\n���܂���ʂ͖����悤��"));
text.s(_T("�������A�����΂߂Ă��邪�A\n��ɐS�����肪�Ȃ�"));
text.s(_T("���҂��o��悤�Ȏ������͖̂������A\n���ɂ��킭�̂���y�n�ł��Ȃ�"));
text.s(_T("�]�ƈ��̈�l�����삩������Ȃ��ƌ����Ă����B"));
text.s(_T("����?"));
text.s(_T("12/11\n�o�c���������Ȃ��Ă����B"));
text.s(_T("�H��̌������邪�A\n�����H�����������ăV�[�Y���Ƃ��Ԃ��Ă��܂����̂��傫���B"));
text.s(_T("1/20\n���������ς��ŉ��U���鎖�ɂȂ����B"));
text.s(_T("�����͂Ƃ��鐻���Ђ��������炵��\n�Ј��Ƃ͉��x��������B�������A����"));
text.s(_T("2/26\n�����ŉ��U���B\n�ǂ����ԂƎd�����o�������ƂɊ��ӂ�����"));
text.s(_T("�E�E�E�E�E"));
text.s(_T("�m�[�g�͂����ŏI����Ă���"));

	/*
	text.s(_T("�����o���Ƀm�[�g������"));
	text.s(_T("�x�z�l�̓����̂悤��"));
	
	text.s(_T("11/10\n���̗��قɂ͗H�삪����"));
	text.s(_T("�����B�����艹�𗧂Ă��肷�邭�炢�ŁA\n������ł͂Ȃ��Ǝ��͎v���Ă�"));
	text.s(_T("�]�ƈ������͐F�X�΍�����Ă������A\n���ʂ͖���������"));

	text.s(_T("9/2\n���ق̌o�c���������Ȃ��Ă���"));
	text.s(_T("�H��̌������邪\n���̃^�C�v�̗��ق�����x��ɂȂ��Ă��Ă�̂��낤"));

	text.s(_T("10/5\n�����͐����Ђ��������炵��\n�Ј��Ƃ͉��x�������"));
	text.s(_T("���ɂ͂��Ȃ����������A����"));

	text.s(_T("11/9\n�����ŉ��U��"));
	text.s(_T("���������Ă��������ɏ������т����C����������"));
	
	text.s(_T("�E�E�E�E�E"));
	text.s(_T("�m�[�g�͂����ŏI����Ă���"));
	*/
	/*
	text.s(_T("�����o���̒��Ƀm�[�g������"));
	text.s(_T("�x�z�l�̓����̂悤��"));
	text.s(_T("������ǂ�"));
	text.s(_T("11/10\n���̗��قɂ͗H�삪����"));
	text.s(_T("�����B�����蕨���𗧂Ă��肷�邭�炢�œ��ɊQ������"));
	text.s(_T("5/4\n�V���肪����\n�^�ʖڂň��ݍ��݂�����"));
	text.s(_T("�H��̂��Ƃ�b���Ə������b�Ȋ��������\n�|����l�q�͂Ȃ�"));
	text.s(_T("�����΍������ƌ����Ă���\n���͎^�������˂�"));
	text.s(_T("5/20\n���ӂ����H�����̕������ʂ�����ƕ񍐂��Ă���"));
	text.s(_T("�����A204�����ŉ�����T���Ă���\n�H�������B���ꂽ�炵��"));
	text.s(_T("7/10\n�����A�]�ƈ��S���ɍ���̂��Ƃ�b����\n�F�A�@���Ă����̂������҂͂��Ȃ�����"));
	text.s(_T("�����͂Ƃ��鐻���Ђ��������\n�Ј��Ƃ͉��x�������"));
	text.s(_T("���ɂ͂��Ȃ����������A����"));
	text.s(_T("8/9\n�����ŉ��U���B�݂�Ȃ̍s����͌��܂��Ă���\n�K�^�Ȏ���"));
	text.s(_T("�����ԓ����Ă�����\n��ŗǂ��v���o�΂��肾"));
	text.s(_T("�����A�V����Ƃ��̎q�̏����荇����\n�����Ȃ��Ȃ�̂͏��X�₵��"));
	text.s(_T("�V�����V�ё��肪������Ɨǂ���"));
	text.s(_T("�E�E�E�E�E"));
	text.s(_T("�m�[�g�͂����ŏI����Ă���"));
	*/
}
VOID MasterDesk::Update()
{
	if( hitbox.HitObj.Reaction == 1 )
	if( P->Check )
	if( P->Mode != Personal::MODE_EVENT )
	{
		text.StartText(P);
	}
	text.Update(P,ML);
}
