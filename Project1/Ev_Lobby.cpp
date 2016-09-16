//====================================================
//�G����
//====================================================
const TCHAR* EnemyWalk::name(){return _T("EnemyWalk");}
EnemyWalk::EnemyWalk()
{
	flag = 0;
	frame = 0;
	ap.SetKey(0,D3DXVECTOR3(1.0f,0.35f,42.0f));
	ap.SetKey(200,D3DXVECTOR3(-1.0f,0.35f,42.0f));

	//BGM
	bgm.Set(wav_fish);
	Snd.push_back(&bgm);

}
VOID EnemyWalk::Set()
{
	P->FM.enemy.HP = 5;
	P->FM.enemy.mode = Enemy::MODE_MANUAL;
}
VOID EnemyWalk::Update()
{
	if(P->Mode == Personal::MODE_EVENT){return;}
	P->FM.enemy.rot = 270.0f;
	if(flag == 0)
	{
		if(P->obj.objPos.x < 3.53f)
		{
			P->FM.EventFlag = TL_ENEMY_WALK;
			flag = 1;
		}
	}
	if(flag == 1)
	{	
		//bgm
		bgm.Start(ML);
		frame++;
		if(frame > 200)
		{
			bgm.Stop(ML,0.0f);
			P->FM.enemy.mode = Enemy::MODE_CLEAR;
			flag = 2;
		}
		P->FM.enemy.pos = ap.Val1(frame);
	}
}
//====================================================
//�H������O
//====================================================
const TCHAR* Dining_Door::name(){return _T("Dining_Door");}
Dining_Door::Dining_Door()
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
	//�h�A�v���[�g
	Txt.push_back(&roomPlate);
	roomPlate.objScal=D3DXVECTOR3(0.002f,0.002f,1.0f);
	roomPlate.objPos=D3DXVECTOR3(-0.05f,0.0f,-0.042f);
	roomPlate.drawSkip = FALSE;
	roomPlate.SetText(_T("�H��"));
	roomPlate.SetPare(&pPlate.mWorld);
	roomPlate.MeshCol=D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
	//�e�L�X�g
	text.init(this);
	text.s(_T("�����������Ă���"));
	//�e�L�X�g1
	text1.init(this);
	text1.s(_T("�y�H���̌��z���g����"));
	//SE
	se.Set(wav_keylock);
	se.m_b3DSound = TRUE; 
	Snd.push_back(&se);
	//�J����
	unlock.Set(wav_dooropen);
	unlock.Filter.Type = BandPassFilter;
	unlock.Filter.OneOverQ = 0.1f;
	unlock.m_b3DSound = TRUE;
	Snd.push_back(&unlock);
}
VOID Dining_Door::Update()
{
	
	//���������Ă�
	if(P->FM.iGetedFlag(ITEM_DINING_KEY))
	{
		//���������Ă��Ȃ�
		if(pBox.HitObj.Reaction == 1)
		if(P->Check)
		if(P->Mode != Personal::MODE_EVENT)
		{
			//�J��
			if(P->FM.iGetFlag(ITEM_DINING_KEY))
			{
				P->FM.iRelease(ITEM_DINING_KEY);
				text1.StartText(P);
				unlock.Emi.Position = pBox.objPos;
				unlock.Start(ML);
			}
			//�����J���Ă���
			else
			{
				P->CheckSE(Personal::SE_OPEN);
				m_pPare->FldChange( new Dining_Room,&D3DXVECTOR3(-3.30f,0.00f,-3.00f),90.0f);
			}
		}
		text1.Update(P,ML);
	}
	else
	{
		//���������Ă��Ȃ�
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
}

//====================================================
//�H��������������J����
//====================================================
const TCHAR* Dining_Door2::name(){return _T("Dining_Door2");}
Dining_Door2::Dining_Door2()
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
	pPlate.objPos=D3DXVECTOR3(0.47f,1.3f,0.0f);
	pPlate.objScal=D3DXVECTOR3(1.8f,1.0f,1.0f);

	pPlate.ShadowFlag=FALSE;
	//�h�A�v���[�g
	Txt.push_back(&roomPlate);
	roomPlate.objScal=D3DXVECTOR3(0.001f,0.002f,1.0f);
	roomPlate.objPos=D3DXVECTOR3(-0.05f,0.0f,-0.042f);
	roomPlate.drawSkip = FALSE;
	roomPlate.SetText(_T("�]�ƈ���p"));
	roomPlate.SetPare(&pPlate.mWorld);
	roomPlate.MeshCol=D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
	//�e�L�X�g
	text.init(this);
	text.s(_T("�����������Ă���"));

	//SE
	se.Set(wav_keylock);
	se.m_b3DSound = TRUE; 
	Snd.push_back(&se);
}
VOID Dining_Door2::Update()
{	
	if(pBox.HitObj.Reaction == 1)
	if(P->Check)
	if(P->Mode != Personal::MODE_EVENT)
	{		
		if(	P->FM.trick.dinigDoor == 0)
		{
			text.StartText(P);
			se.Start(ML);
			se.Emi.Position = pBox.objPos;
		}
		else
		{
			P->CheckSE(Personal::SE_OPEN);
			m_pPare->FldChange( new Dining_Room,&D3DXVECTOR3(-3.30f,0.00f,6.70f),90.0f);
		}
	}
	text.Update(P,ML);
}
//====================================================
//�]�ƈ�����
//====================================================
const TCHAR* Staff_Door::name(){return _T("Staff_Door");}
Staff_Door::Staff_Door()
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
	//�h�A�v���[�g
	Txt.push_back(&roomPlate);
	roomPlate.objScal=D3DXVECTOR3(0.002f,0.002f,1.0f);
	roomPlate.objPos=D3DXVECTOR3(-0.1f,0.0f,-0.042f);
	roomPlate.drawSkip = FALSE;
	roomPlate.SetText(_T("�]�ƈ���"));
	roomPlate.SetPare(&pPlate.mWorld);
	roomPlate.MeshCol=D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
	//�e�L�X�g
	text.init(this);
	text.s(_T("�����������Ă���"));
	//�e�L�X�g1
	text1.init(this);
	text1.s(_T("�y�]�ƈ����̌��z���g����"));
	//SE
	se.Set(wav_keylock);
	se.m_b3DSound = TRUE; 
	Snd.push_back(&se);
	//�J����
	unlock.Set(wav_dooropen);
	unlock.Filter.Type = BandPassFilter;
	unlock.Filter.OneOverQ = 0.1f;
	unlock.m_b3DSound = TRUE;
	Snd.push_back(&unlock);
}
VOID Staff_Door::Update()
{
	//���������Ă�
	if(P->FM.iGetedFlag(ITEM_STAFF_KEY))
	{
		//���������Ă��Ȃ�
		if(pBox.HitObj.Reaction == 1)
		if(P->Check)
		if(P->Mode != Personal::MODE_EVENT)
		{
			//�J��
			if(P->FM.iGetFlag(ITEM_STAFF_KEY))
			{
				P->FM.iRelease(ITEM_STAFF_KEY);
				text1.StartText(P);
				unlock.Emi.Position = pBox.objPos;
				unlock.Start(ML);
			}
			//�����J���Ă���
			else
			{
				//�X�^�b�t���[���Ɉړ�
				P->CheckSE(Personal::SE_OPEN);
				m_pPare->FldChange( new Staff_Room,&D3DXVECTOR3(0.00f,0.35f,-2.30f),0.0f);
			}
		}
		text1.Update(P,ML);
	}
	else
	{
		//���������Ă��Ȃ�
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
}
//============================================
//���r�[��
//============================================
const TCHAR *LobbyWindow::name(){return _T("LobbyWindow");}
LobbyWindow::LobbyWindow()
{
	//���g
	Msh.push_back(&pMado);
	pMado.Type(x_mado);
	pMado.ShadowFlag=FALSE;
	//�K���X
	Msh.push_back(&pGlass);
	pGlass.Type(x_cube);
	pGlass.objScal=D3DXVECTOR3(6.0f,4.8f,0.1f);
	pGlass.MeshCol=D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
	pGlass.ShadowFlag=FALSE;
	pGlass.SetPare(&pMado.mWorld);
	//�J�[�e��
	Msh.push_back(&pKaten);
	pKaten.Type(x_katen);
	pKaten .SetPare(&pMado.mWorld);
	pKaten .objPos=D3DXVECTOR3(-1.5f,0,-0.2f);
	pKaten .ShadowFlag=FALSE;
	pKaten .objScal=D3DXVECTOR3(1.0f,1.0f,0.2f);
	pKaten .objScal=D3DXVECTOR3(0.2f,1.0f,0.2f);
}
//============================================
//�A��
//============================================
const TCHAR *Ueki::name(){return _T("Ueki");}
Ueki::Ueki()
{
	Msh.push_back(&pPlanter);
	pPlanter.Type(x_planter);
	pPlanter.HitMode(CT_OBB,CB_PLUS);
	Msh.push_back(&pUeki);
	pUeki.Type(x_reaf);
	pUeki.Type(x_reaf);
	pUeki.SetPare(&pPlanter.mWorld);
	pUeki.objScal=D3DXVECTOR3(0.15f,0.5f,0.15f);
	pUeki.objPos=D3DXVECTOR3(0.0f,0.1f,0.0f);
}