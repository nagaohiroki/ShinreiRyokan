//======================================
//�{�C���[
//======================================
const TCHAR* Boiler::name(){return _T("Boiler");}	
Boiler::Boiler()
{
	//�{�C���[
	boiler.Type(x_roof_boiler);
//	boiler.HitMode(CT_OBB,CB_PLUS);
	boiler.Bias = 0.3f;
	Msh.push_back(&boiler);
	//�񔽎˔�
	black.Type(x_cube);
	black.SetPare(&boiler.mWorld);
	black.MeshCol = D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
	black.SpCol = D3DXVECTOR4(0.0f,0.0f,0.0f,20.0f);
	black.SpColm = 0.0f;
	black.objPos = D3DXVECTOR3(-0.294411f,0.559326f,0.000000f);
	black.ShadowFlag = FALSE;
	Msh.push_back(&black);
	
	//�{�C���[�ӂ�
	huta.Type(x_tdact);
	huta.SetPare(&hutaNull.mWorld);
	huta.Bias = 0.3f;
	huta.HitMode(CT_OBB,CB_NONE);
	huta.objPos = D3DXVECTOR3(0.167f,0.167f,0.05f);
	huta.SpCol = D3DXVECTOR4(0.0f,0.0f,0.0f,20.0f);
	huta.SpColm = 0.0f;	
	Msh.push_back(&huta);
	//�ӂ����_
	hutaNull.Type(x_cube);
	hutaNull.SetPare(&boiler.mWorld);
	hutaNull.HitMode(CT_OBB,CB_NONE);
	hutaNull.MeshCol.w = 0.5f;
	hutaNull.objPos.x = 2.0f;
	hutaNull.YPR= D3DXVECTOR3(360.0f,90.0f,90.0f);
	hutaNull.objScal= D3DXVECTOR3(1.65f,1.0f,1.0f);
	hutaNull.objPos = D3DXVECTOR3(-0.79f,0.274811f,-0.176f);
	hutaNull.drawSkip = TRUE;
	Msh.push_back(&hutaNull);
	//�����蔻��{�f�B
	hitbody.Type(x_cube);
	hitbody.objPos = D3DXVECTOR3(0.0f,0.5f,0.0f);
	hitbody.objScal = D3DXVECTOR3(2.8f,1.92f,1.4f);
	hitbody.SetPare(&boiler.mWorld);
	hitbody.HitMode(CT_OBB,CB_PLUS);
	hitbody.drawSkip = TRUE;
	Msh.push_back(&hitbody);
	//�G���A�`�F���W
	FldHit.Type(x_cube);
	FldHit.SetPare(&boiler.mWorld);
	FldHit.HitMode(CT_OBB,CB_NONE);
	FldHit.objPos = D3DXVECTOR3(-0.8f,0.0f,0.0f);
	Msh.push_back(&FldHit);
	FldHit.drawSkip = TRUE;
	//BGM
	bgm.Set(wav_suzumusi);
	bgm.m_bLoop = TRUE;
	bgm.m_fVol = 0.3f;
	Snd.push_back(&bgm);
	//SE
	se.Set(wav_ari);
	se.m_b3DSound = TRUE;
	se.m_bLoop = TRUE;
	Snd.push_back(&se);
	//�o��
	ban.Set(wav_oop);
	ban.m_b3DSound = TRUE;
	ban.Filter.Frequency = 0.1f;
	Snd.push_back(&ban);

	
	oop.Set(wav_oop);
	Snd.push_back(&oop);
	//�A�j���[�V����	
	flag = 0;
	frame = 0;
	p.SetKey(0,D3DXVECTOR3(-0.79f,0.274811f,-0.176f));
	p.SetKey(10,D3DXVECTOR3(-0.9f,0.0f,-0.176f));

	r.SetKey(0,D3DXVECTOR3(360.0f,90.0f,90.0f));
	r.SetKey(10,D3DXVECTOR3(360.0f,90.0f,90.0f));
	r.SetKey(20,D3DXVECTOR3(270.0f,90.0f,90.0f));

	//��������
	frame1 = 0;
	gata.SetKey(0,D3DXVECTOR3(0.0f,0.0f,0.0f));
	gata.SetKey(2,D3DXVECTOR3(0.0f,0.0f,2.0f));
	gata.SetKey(4,D3DXVECTOR3(0.0f,0.0f,-2.0f));
	gata.SetKey(6,D3DXVECTOR3(0.0f,0.0f,0.0f));
	//text�ӂ��L��
	text.init(this);
	text.s(_T("�{�C���[������"));
	//text�ӂ�����
	text1.init(this);
	text1.s(_T("�{�C���[������\n�ӂ����͂���Ă���"));

}
VOID Boiler::Update()
{
	bgm.Start(ML);
	ban.Emi.Position = boiler.objPos;
	se.Emi.Position = boiler.objPos;
	se.Start(ML);
	hutaNull.SetHit(ML);
	hutaNull.objPos = p.Val1(frame);
	hutaNull.YPR = r.Val1(frame);


	if(P->FM.EventFlag >= TL_ROOF_DUCT)
	{
		//�G���A��ς���
		if(FldHit.HitObj.Reaction == 1)
		{
			P->FM.enemy.mode = Enemy::MODE_CLEAR;
			m_pPare->FldChange(new Fld::Fld_201_Bath,&D3DXVECTOR3(-1.4f,0.35f,-1.2f),90.0f);
		}
		hutaNull.objPos = D3DXVECTOR3(-0.9f,0.0f,-0.176f);
		hutaNull.YPR = D3DXVECTOR3(270.0f,90.0f,90.0f);

		//�{�̓����蔻��
		if(hitbody.HitObj.Reaction == 1)
		if(P->Check)
		if(P->Mode != Personal::MODE_EVENT)
		{
			text1.StartText(P);
		}
		text1.Update(P,ML);
	}
	else
	{
		//�^�C�����C����i�߂�
		if(frame == 18){ban.Start(ML);}
		if(flag == 0)
		{
			if(huta.HitObj.Reaction == 2)
			{
				P->AtcBullet(&huta.mWorld);
				flag = 1;
			}
			//���������A�j���[�V����
			frame1++;
			if(frame1 > gata.MaxKey()){	frame1 = 0;	}
			huta.YPR = gata.Val(frame1);
		}
		else if(flag == 1)
		{
			frame++;
			if(frame > 20)
			{	
				//�G���o�����ĂȂ��ꍇ�o��
				if(P->FM.EventFlag < TL_ROOF_ENEMY)
				if(P->FM.enemy.mode == Enemy::MODE_CLEAR)
				{
					P->FM.enemy.mode = Enemy::MODE_STALK_ATTACK;
					oop.Start(ML);
				}
				flag = 2;
			}
		
		}
		else if(flag == 2)
		{
			P->FM.EventFlag = TL_ROOF_DUCT;
		}
		//�{�̓����蔻��
		if(hitbody.HitObj.Reaction == 1)
		if(P->Check)
		if(P->Mode != Personal::MODE_EVENT)
		{
			text.StartText(P);
		}
		text.Update(P,ML);
	}

	

	
}
VOID Boiler::DebugText(TCHAR* t,int l)
{
	_stprintf_s(t,l,
	_T("%s")
	_T("Size = %f,%f,%f")
	,t
	,huta.itMod->second->ren.x
	,huta.itMod->second->ren.y
	,huta.itMod->second->ren.z);

}



//======================================
//�����
//======================================
const TCHAR* DoorRoofTop::name(){return _T("DoorRoofTop");}
DoorRoofTop::DoorRoofTop()
{

	//�����蔻��p�{�b�N�X
	Msh.push_back(&pBox);
	pBox.Type(x_cube);
	pBox.drawSkip=TRUE;
	pBox.HitMode(CT_OBB,CB_NONE);

	Msh.push_back(&pWaku);
	pWaku.Type(x_exit_door_waku);
	pWaku.objScal=D3DXVECTOR3(0.8f,0.9f,1.0f);
	pWaku.ShadowFlag=FALSE;
	pWaku.SetPare(&pBox.mWorld);
	Msh.push_back(&pDoor);

	pDoor.Type(x_exit_door);
	pDoor.SetPare(&pWaku.mWorld);
	pDoor.objPos.x=-0.47f;
	pDoor.ShadowFlag=FALSE;
	Msh.push_back(&pNobu);

	pNobu.Type(x_exit_door_nobu);
	pNobu.SetPare(&pDoor.mWorld);
	pNobu.objPos=D3DXVECTOR3(0.82f,0.75f,0);
	pNobu.ShadowFlag=FALSE;	

	//�e�L�X�g
	text.init(this);
	text.s(_T("�����Ȃ�"));
	//SE
	se.Set(wav_keylock);
	se.m_b3DSound = TRUE; 
	se.Filter.OneOverQ = 0.01f;
	Snd.push_back(&se);

	oop.Set(wav_oop);
	Snd.push_back(&oop);

}
VOID DoorRoofTop::Update()
{
	//�G�ɋC�Â����
	if(P->FM.EventFlag < TL_ROOF_ENEMY)
	{
		if(P->FM.enemy.mode == Enemy::MODE_CLEAR)
		{
			if(P->obj.objPos.z > 2.5f)
			{
				if(	D3DXVec3LengthSq(&(P->obj.objPos - P->FM.enemy.pos)) < 6.0f  )
				{
					P->FM.enemy.mode = Enemy::MODE_STALK_ATTACK;
					oop.Start(ML);
				}
			}
		}
	}
	//���[�h���N���A
	if(P->FM.enemy.mode  == Enemy::MODE_REMOVE)
	{
		P->FM.EventFlag = TL_ROOF_ENEMY;
		P->FM.enemy.mode  = Enemy::MODE_CLEAR;
	}
	//�U����
	if(P->FM.enemy.mode == Enemy::MODE_STALK_ATTACK)
	{
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
		if(pBox.HitObj.Reaction == 1)
		if(P->Check)
		{
			P->CheckSE(Personal::SE_OPEN);
			m_pPare->FldChange(new Roof_Kai,&D3DXVECTOR3(0.84f,2.30f,-1.3f),0.0f);
		}
	}

}