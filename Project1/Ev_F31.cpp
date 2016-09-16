//===========================================
//2�K����
//===========================================
const TCHAR *F3_EXIT::name(){return _T("F3_EXIT");}
F3_EXIT::F3_EXIT()
{
	//�����蔻�蔠
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.Type(x_cube);
	hitbox.drawSkip = TRUE;
	Msh.push_back(&hitbox);
	//�e�L�X�g
	text.init(this);
	text.s(_T("�J�������ɂȂ�"));
	//SE
	se.Set(wav_keylock);
	se.m_b3DSound = TRUE; 
	se.Filter.OneOverQ = 0.01f;
	Snd.push_back(&se);
	
}
VOID F3_EXIT::Update()
{
	if(hitbox.HitObj.Reaction == 1)
	if(P->Check)
	if(P->Mode != Personal::MODE_EVENT)
	{
		text.StartText(P);
		se.Start(ML);
		se.Emi.Position = hitbox.objPos;
	}
	text.Update(P,ML);
}
//===========================================
//���̋@
//===========================================
const TCHAR *F3_Zihanki::name(){return _T("Zihanki");}
F3_Zihanki::F3_Zihanki()
{
	Msh.push_back(&pZihanki);
	pZihanki.Type(x_zihanki);
	pZihanki.BloomColor.w=2.0f;
	pZihanki.Bias=0.5f;
	pZihanki.HitMode(CT_OBB,CB_PLUS);
	//�e�L�X�g
	text.init(this);
	text.s(_T("���̋@��\n�{�^���������Ă��������Ȃ�"));

	text1.init(this);
	text1.s(_T("���̋@��\n���˂��ĐԂ����̂�������"));

}
VOID F3_Zihanki::Update()
{
	if(pZihanki.HitObj.Reaction == 1)
	if(P->Check)
	if(P->Mode != Personal::MODE_EVENT)
	{
		if(P->FM.iGetedFlag(ITEM_SYOUKAKI)){text.StartText(P);}
		else{text1.StartText(P);	}
	}
	text.Update(P,ML);
	text1.Update(P,ML);

}
//===========================================
//203�����h�A
//===========================================
const TCHAR *Door203::name(){return _T("Door203");}
Door203::Door203()
{
	Msh.push_back(&pBox);
	pBox.Type(x_cube);
	pBox.drawSkip=TRUE;
	pBox.HitMode(CT_OBB,CB_NONE);

	Msh.push_back(&pWaku);
	pWaku.Type(x_wood_door_waku);
	pWaku.objScal=D3DXVECTOR3(0.8f,0.9f,1.0f);
	pWaku.ShadowFlag=FALSE;
	pWaku.SetPare(&pBox.mWorld);

	Msh.push_back(&pDoor);
	pDoor.Type(x_wood_door);
	pDoor.SetPare(&pWaku.mWorld);
	pDoor.objPos.x=-0.47f;
	pDoor.ShadowFlag=FALSE;
	pDoor.HitMode(CT_OBB,CB_PLUS);

	Msh.push_back(&pNobu);
	pNobu.Type(x_doornobu);
	pNobu.SetPare(&pDoor.mWorld);
	pNobu.objPos=D3DXVECTOR3(0.82f,0.75f,0);
	pNobu.ShadowFlag=FALSE;	

	Msh.push_back(&pPlate);
	pPlate.Type(x_door_plate);
	pPlate.drawSkip = TRUE;
	pPlate.drawSkip = FALSE;
	pPlate.SetPare(&pDoor.mWorld);
	pPlate.objPos=D3DXVECTOR3(0.47f,1.3f,0);
	pPlate.ShadowFlag=FALSE;
	//��
	Msh.push_back(&pBlack);
	pBlack.Type(x_cube);
	pBlack.Amb = 0.0f;
	pBlack.SpColm = 0.0f;
	pBlack.MeshCol = D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
	pBlack.SetPare(&pBox.mWorld);
	pBlack.objPos = D3DXVECTOR3(0.0f,0.7f,0.0f);
	pBlack.objScal = D3DXVECTOR3(1.6f,3.2f,0.15f);
	pBlack.ShadowFlag = FALSE;
	//���[���v���[�g
	Txt.push_back(&roomPlate);
	roomPlate.objScal=D3DXVECTOR3(0.002f,0.002f,1.0f);
	roomPlate.objPos=D3DXVECTOR3(-0.04f,0.0f,-0.042f);
	roomPlate.drawSkip = FALSE;
	roomPlate.SetText(_T("203"));
	roomPlate.SetPare(&pPlate.mWorld);
	roomPlate.MeshCol=D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);

	//SE
	se.Set(wav_keylock);
	se.m_b3DSound = TRUE; 
	se.m_fVol = 2.0f;
	Snd.push_back(&se);
	//�h�A�I�[�v��
	open.Set(wav_dooropen);
	open.m_b3DSound = TRUE;
	open.m_fVol = 2.0f;
	Snd.push_back(&open);
	//�e�L�X�g
	text.init(this);
	text.s(_T("�����������Ă���"));

	flag = 0; 
	frame = 0;
	rot.SetKey(0,0.0f);
	rot.SetKey(100,130.0f);
}
VOID Door203::Update()
{
	//�^�C�����C�����i�ނƕ��ʂ̃h�A�ɂȂ�
	if(P->FM.EventFlag < TL_203_EXIT)
	{
		//���������ꍇ
		if(!P->FM.iGetedFlag(ITEM_203_KEY))
		{
			//�����������Ă�
			if(pBox.HitObj.Reaction == 1)
			if(P->Check)
			if(P->Mode != Personal::MODE_EVENT)
			{
				text.StartText(P);
				se.Start(ML);
				se.Emi.Position = pBox.objPos;
			}
			text.Update(P,ML);
		}
		else
		{
			//�J���ƃ^�C�����C�����i��
			if(P->FM.EventFlag < TL_203_OPEN)
			{
				if(flag == 0)
				{
					if( D3DXVec3LengthSq(&(pBox.objPos - P->obj.objPos)) < 15.0f)
					{
						open.Emi.Position = pBox.objPos;
						open.Start(ML);
						flag = 1;
					}
				}
				else if(flag == 1)
				{
					//�h�A���J��
					frame++;
					if(rot.MaxKey() < frame)
					{
						P->FM.EventFlag = TL_203_OPEN;
					}
					pDoor.YPR.y = rot.Val1(frame);
				}
			}
			else
			{
				//�ړ�
				if(pBox.HitObj.Reaction == 1)
				{
				//	if(P->Check)
					{
						m_pPare->FldChange( new Fld_203,&D3DXVECTOR3(-3.95f,0.40f,-2.27f),90.0f);
					}
				}
				pDoor.YPR.y = 130.0f;
			}
		}
	}
	//���ʂɓ����
	else
	{
		if(pBox.HitObj.Reaction == 1)
		{
			if(P->Check)
			{
				P->CheckSE(Personal::SE_OPEN);
				m_pPare->FldChange( new Fld_203,&D3DXVECTOR3(-3.95f,0.40f,-2.27f),90.0f);
			}
		}
	}
}
VOID Door203::DebugText(TCHAR* t,int l)
{
	_stprintf_s(t,l,
		_T("%s\n")
		_T("maxKey = %d\n")
		_T("flag = %d\n")
		_T("Length = %f\n")

		,t
		,rot.MaxKey()
		,flag
		,D3DXVec3LengthSq(&(pBox.objPos - P->obj.objPos)) 
		);
}

//===========================================
//�S�~������
//===========================================
const TCHAR *DustMemo::name(){return _T("DustMemo");}
DustMemo::DustMemo()
{
	//�S�~��
	dust.HitMode(CT_OBB,CB_PLUS);
	dust.Type(x_trashbox);
	dust.Bias = 0.35f;
	Msh.push_back(&dust);
	//�e�L�X�g
	text.init(this);
	text.s(_T("�S�~���̒��ɏd�v�����ȃ���������"));
	text.s(_T("�����ɂ͂���������Ă���"));
	text.s(_T("���̖�͉䂪��������(�Ȃ��̂����₭)�̒n�ʂ�\n����ɍ������邾�낤"));
	text.s(_T("���̖�͐l�Ԃ̑�Z����ڊo�߂�����"));
	text.s(_T("�܂�A�삪������悤�ɂȂ�"));
	text.s(_T("���������ԋ߂��B�����A�ق�̍��ׂȖ�肪����"));
	text.s(_T("������񂾐l����ƐG��Ă��܂���\n�A��čs����Ă��܂�"));
	text.s(_T("�܂�A���̐��ɂ����Ă��܂��ƌ�������"));
	text.s(_T("�킪�Ђ̋@���͐�΂ɘR��Ă͂����Ȃ�"));
	text.s(_T("���̃����͓ǂ񂾂炷���ɔj�����邱��"));
}
VOID DustMemo::Update()
{
	if( dust.HitObj.Reaction == 1 )
	if(P->Check)
	if(P->Mode != Personal::MODE_EVENT)
	{
		text.StartText(P);
	}
	text.Update(P,ML);

}

