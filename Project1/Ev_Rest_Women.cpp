//==============================================
//�����p�g�C���h�A
//==============================================
const TCHAR *Rest_Women_Door::name(){return _T("Rest_Women_Door");}
Rest_Women_Door::Rest_Women_Door()
{
	//�h�A
	Msh.push_back(&pDoor);
	pDoor.Type(x_rest_door);
	pDoor.ShadowFlag=FALSE;
	pDoor.HitMode(CT_OBB,CB_PLUS);
	//��
	Msh.push_back(&pGreen);
	pGreen.Type(x_cube);
	pGreen.SetPare(&pDoor.mWorld);
	pGreen.objPos=D3DXVECTOR3(0.02f,0.775f,-0.764f);//��
	pGreen.objScal=D3DXVECTOR3(0.10f,0.05f,0.04f);
	pGreen.MeshCol=D3DXVECTOR4(0.0f,1.0f,0.0f,1.0f);
	pGreen.ShadowFlag=FALSE;
	Msh.push_back(&pRed);
	pRed.Type(x_cube);
	pRed.ShadowFlag=FALSE;
	pRed.SetPare(&pGreen.mWorld);
	pRed.objPos=D3DXVECTOR3(-0.00f,0.00f,0.50f);
	pRed.MeshCol=D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f);
	pGreen.objPos.z=-0.764f;
	//Se
	gan.Set(wav_keylock);
	gan.m_b3DSound = TRUE;
	Snd.push_back(&gan);
	//oop
	oop.Set(wav_oop);
	Snd.push_back(&oop);
	//�A�j���[�V����
	frameDoor = 0;
	frameLock = 0;
	KeyLock.SetKey(0,-0.785f);
	KeyLock.SetKey(10,-0.764f);

	DoorRot.SetKey(0,180.0f);
	DoorRot.SetKey(10,360.0f);


}
VOID Rest_Women_Door::Set()
{
	if(P->FM.iGetedFlag(ITEM_ROOF_KEY))
	{
		frameDoor = DoorRot.MaxKey();
		frameLock = KeyLock.MaxKey();
	}
}

VOID Rest_Women_Door::Update()
{

	if(P->FM.enemy.mode == Enemy::MODE_REMOVE)
	{
		P->FM.enemy.mode = Enemy::MODE_CLEAR;
	}
	//�A�C�e�����擾����ƌ����J��
	if(P->FM.iGetedFlag(ITEM_ROOF_KEY))
	{
		if(frameLock < 10){frameLock++;}
	}
	//�G���U�����[�h�ɂȂ�ƃh�A���J��
	if(P->FM.enemy.mode == Enemy::MODE_STALK_ATTACK)
	{		
		if(frameDoor < 10){frameDoor++;}
		if(frameDoor == 3)
		{
			oop.Start(ML);
			gan.Start(ML);
		}
		gan.Emi.Position = pDoor.objPos;
		pDoor.HitMode(CT_OBB,CB_PLUS);
	}
	pGreen.objPos.z = KeyLock.Val1(frameLock);
	pDoor.YPR.y = DoorRot.Val1(frameDoor);
	
}

//==============================================
//��
//==============================================
const TCHAR *Rest_Women_Key::name(){return _T("Rest_Women_Key");}
Rest_Women_Key::Rest_Women_Key()
{
	//��
	key.Type(x_key);
	key.objScal = D3DXVECTOR3(1.0f,1.0f,1.0f) * 0.2f;
	key.HitMode(CT_OBB,CB_NONE);
	Msh.push_back(&key);
	//�e�L�X�g
	text.init(this);
	text.s(_T("���������Ă���"));
	text.s(_T("�y�ǂ����̌��z����ɓ��ꂽ"));

}
VOID Rest_Women_Key::Update()
{
	//���ׂ��
	if(P->Mode != Personal::MODE_EVENT)
	if(key.HitObj.Reaction == 1)
	if(P->Check)
	{		
		if(!P->FM.iGetedFlag(ITEM_ROOF_KEY))
		{
			text.StartText(P);
		}
	}
	//�A�C�e���Q�b�g
	int t = text.Update(P,ML);
	if(t == 1)
	{
		if(!P->FM.iGetedFlag(ITEM_ROOF_KEY))
		{
			P->CheckSE(Personal::SE_ITEM);
			P->FM.iGet(ITEM_ROOF_KEY);
			key.drawSkip = TRUE;
		}
	}
	//�G�U�����[�h
	if(t == 2)
	{
		P->FM.enemy.mode = Enemy::MODE_STALK_ATTACK;
	}

}

//==============================================
//�e�L�X�g
//==============================================
const TCHAR *Rest_Women_Text::name(){return _T("Rest_Women_Text");}
Rest_Women_Text::Rest_Women_Text()
{
	//�����蔻��BOX
	hitbox.Type(x_cube);
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.drawSkip = TRUE;
	Msh.push_back(&hitbox);
	//�e�L�X�g
	text.init(this);
	text.s(_T("�J���Ȃ�"));
	//�L�[���b�N��
	gan.Set(wav_keylock);
	gan.m_b3DSound = TRUE;
	Snd.push_back(&gan);
}
VOID Rest_Women_Text::Update()
{
	//�G���U�����[�h��������
	if(P->FM.enemy.mode == Enemy::MODE_STALK_ATTACK)
	{
		if(P->Mode != Personal::MODE_EVENT)
		if(hitbox.HitObj.Reaction == 1)
		if(P->Check)
		{
			gan.Emi.Position = hitbox.objPos;
			gan.Start(ML);
			text.StartText(P);
		}
		text.Update(P,ML);
	}
}
