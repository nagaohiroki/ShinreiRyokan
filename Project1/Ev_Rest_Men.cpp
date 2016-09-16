//=========================================
//�g�C������
//=========================================
const TCHAR *ToileMemo::name(){return _T("ToileMemo");}
ToileMemo::ToileMemo(int r)
{
	//�����蔻��box
	Msh.push_back(&hitbox);
	hitbox.Type(x_cube);
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.drawSkip = TRUE;
	//����
	for(int i = 0; i < MEMO_MAX; i ++)
	{
		Fvf.push_back(&memo[i]);
		memo[i].objScal = D3DXVECTOR3( 0.2f,0.2f,1.0f);
		memo[i].MeshCol = D3DXVECTOR4(0.8f,0.8f,0.8f,1.0f);
		memo[i].SetPare(&hitbox.mWorld);
	}
	memo[0].objPos = D3DXVECTOR3(-0.1f,-0.1f,0.0f);
	memo[1].objPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	memo[2].objPos = D3DXVECTOR3(0.05f,-0.05f,0.0f);
	memo[3].objPos = D3DXVECTOR3(0.5f,0.0f,0.0f);

	//�e�L�X�g
	text.init(this);
	text.s(_T("��������������͂��Ă���"));
	text.s(_T("�����ɂ͂���������Ă���"));
	text.s(_T("7/10\n���̃g�C�����S�ĉ��Ă���悤�ł�"));
	if(r == 0)
	{
		//�e�L�X�g�����͎�O	
		text.s(_T("7/11\n�m�荇���̋Ǝ҂ɒ����Ă��炢�܂������A\n�\�Z�����肸���̃g�C���͂��̂܂܂ł�"));
		text.s(_T("7/12\n���Ă���g�C���ׂ̗̃g�C������ꂽ�悤�ł�"));
	}
	if(r == 1)
	{
		//�e�L�X�g�����͐^��		
		text.s(_T("7/11\n�m�荇���̋Ǝ҂ɒ����Ă��炢�܂������A\n�\�Z�����肸���̃g�C���͂��̂܂܂ł�"));
		text.s(_T("7/12\n���Ă���g�C���ׂ̗���Ȃ����̃g�C������ꂽ�悤�ł�"));
	}
	if(r == 2)
	{
		//�e�L�X�g�����͉�
		text.s(_T("7/11\n�m�荇���̋Ǝ҂ɒ����Ă��炢�܂������A\n�\�Z�����肸��O�̃g�C���͂��̂܂܂ł�"));
		text.s(_T("7/12\n���Ă���g�C���ׂ̗̃g�C������ꂽ�悤�ł�"));
	}
	text.s(_T("7/15\n202�����̂��q�l�����[���L�[���g�C���ɗ��Ƃ����悤�ł�\n�g����g�C���ɗ����Ă���Ǝv���̂ŉ�����肢���܂�"));
}
VOID ToileMemo::Update()
{
	if(P->Mode != Personal::MODE_EVENT)
	if(hitbox.HitObj.Reaction == 1)
	if(P->Check)
	{
		text.StartText(P);
	}
	text.Update(P,ML);
}
//=========================================
//�j�q�g�C���h�A
//=========================================
const TCHAR *Rest_Men_door::name(){return _T("Rest_Men_door");}
//����
Rest_Men_door::Rest_Men_door()
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
	//�A�j���[�V����
	frame = 0;
	flag = 0;
	door.SetKey(0,0.0f);
	door.SetKey(50,90.0f);
	//Se
	gan.Set(wav_keylock);
	gan.m_b3DSound = TRUE;
}
VOID Rest_Men_door::Update()
{
	//SE
	gan.Emi.Position = pDoor.objPos;
	//�����Ă�Ƃ��͓����蔻�������
	if(flag == 0)
	{
		pDoor.HitMode(CT_OBB,CB_PLUS);
	}
	else
	{
		pDoor.HitMode(CT_OBB,CB_NONE);
	}
	//�����蔻��
	if(pDoor.HitObj.Reaction == 1)
	{
		if(P->Check)
		{
			if(flag == 0){flag = 1;}
			if(flag == 2){flag = 3;}
		}
	}
	//�h�A�̓����蔻��
	if(pDoor.HitObj.Reaction == 2)
	{
		P->AtcBullet(&pDoor.mWorld);
	}
	if(flag == 1)
	{
		frame++;
		if(frame > 48){flag = 2;}
	}
	if(flag == 3)
	{
		frame--;
		if(frame < 1)
		{
			gan.Start(ML);
			flag = 0;
		}
	}
	pDoor.YPR.y = door.Val(frame);
}
//=========================================
//�g�C��	
//=========================================
const TCHAR *name(){return _T("Rest_Men_Toile");}
Rest_Men_Toile::Rest_Men_Toile(int f)
{
	//�g�C��
	Msh.push_back(&pToile);
	pToile.Type(x_toile);
	pToile.HitMode(CT_OBB,CB_PLUS);
	pToile.Bias = 0.1f;
	//�����蔻��
	Msh.push_back(&hitbox);
	hitbox.Type(x_cube);
	hitbox.SetPare(&pToile.mWorld);
	hitbox.objScal = D3DXVECTOR3(1.0f,1.0f,3.0f);
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.drawSkip = TRUE;
	//�ӂ�
	Msh.push_back(&pHuta);
	pHuta.Type(x_tcover);
	pHuta.SetPare(&pToile.mWorld);
	pHuta.objPos.y=0.35f;
	pHuta.MeshCol=D3DXVECTOR4(2.5f,2.5f,2.5f,1.0f);
	pHuta.SpColm=0.0f;
	//�e�L�X�g
	text.init(this);
	text.s(_T("�g�C�����J���܂����H\n�J����\n�J���Ȃ�"),1,2);
	//�g�C���𒲂ׂ�
	text1.init(this);
	text1.s(_T("�g�C���̒��ɉ��������Ă���"));
	text1.s(_T("�y202�����̌��z����ɓ��ꂽ"));
	//�֍��A�j���[�V����
	flag = 0;
	hutaframe = 0;
	rot.SetKey(0,0.0f);
	rot.SetKey(10,-90.0f);
	//gt
	gtframe = 0;
	prot.SetKey(0,0.0f);
	prot.SetKey(10,190.0f);
	//�Q�[���I�[�o�[�����擾
	GOFlag = f;

	//SE
	//�ӂ��̂��܂鉹
	gan.Set(wav_keylock);
	gan.m_b3DSound = TRUE;
	Snd.push_back(&gan);
	//�т����艹
	oop.Set(wav_oop);
	Snd.push_back(&oop);
	//����
	water.Set(wav_water);
	Snd.push_back(&water);
	
}
VOID Rest_Men_Toile::Set()
{
	//�z�����܂��A�j���[�V����
	pos.SetKey(10,pToile.objPos + D3DXVECTOR3(-0.2f,1.0f,0.0f));
	pos.SetKey(50,pToile.objPos + D3DXVECTOR3(-0.2f,0.6f,0.0f));
	//SE
	gan.Emi.Position =	pToile.objPos;
}

VOID Rest_Men_Toile::Update()
{
	//���ׂ�
	if(P->Mode != Personal::MODE_EVENT)
	if(hitbox.HitObj.Reaction == 1)
	if(P->Check)
	{
		//�e�L�X�g��i�߂�
		if(flag == 0)
		{
			text.StartText(P);
			pos.SetKey(0,P->obj.objPos);

			D3DXVECTOR3 N(pToile.objPos - P->obj.objPos);
			D3DXVec3Normalize(&N,&N);
			P->obj.YPR.y = D3DXToDegree(atan2f(N.x,N.z));
		}
		//�A�C�e���擾�p�^�[��
		if( GOFlag == 0 )
		{
			//���������ĂȂ���
			if(flag == 2)
			{
				if(!P->FM.iGetedFlag(ITEM_202_KEY)){text1.StartText(P);}
				else{flag = 3;}
			}
		}		
	}
	//�e�L�X�g
	int t = text.Update(P,ML);
	//���̎擾
	if( text1.Update(P,ML) == 1 )
	{
		if(!P->FM.iGetedFlag(ITEM_202_KEY))
		{
			P->FM.iGet(ITEM_202_KEY);
			P->CheckSE(Personal::SE_ITEM);
		}
	}
	//�ӂ��J��
	if(t == 1){flag = 1;}
	//�A�j���[�V����
	if(flag == 1)
	{
		//�ӂ��J��
		hutaframe++;
		if(hutaframe > 8)
		{
			gan.Start(ML);
			if(GOFlag != 0 ){oop.Start(ML);}
			flag = 2;
		}
	}
	//�ӂ������
	if(GOFlag == 0 )
	{
		if(P->FM.iGetedFlag(ITEM_202_KEY))
		{
			if(flag == 3)
			{		
				hutaframe--;
				if(hutaframe < 1)
				{
					gan.Start(ML);
					flag = 0;
				}
			}
		}
	}
	//���S�p�^�[��
	else
	{
		if(flag == 2)
		{
			//����
			water.Start(ML);
			//�g�C���̓����蔻�������
			pToile.HitMode(CT_OBB,CB_NONE);
			P->Mode = Personal::MODE_EVENT;
			P->gt.MotionType = gt_Anim::Motion_Wait;
			//gt�Ђ�����Ԃ��ė���������
			gtframe++;
			P->obj.objPos = pos.Val(gtframe);
			P->obj.YPR.x = prot.Val(gtframe);
			if( gtframe> 8 ){flag = 3;}
		}
		if(flag == 3)
		{
			//��]�Ȃ��痎����
			gtframe++;
			//��
			if(gtframe== 145){	gan.Start(ML);	}
			//�ӂ���߂�
			if(gtframe> 150){flag = 4;}
			P->obj.objPos = pos.Val1(gtframe);
			P->obj.YPR.y += 10.0f;
		}
		if(flag == 4)
		{
			//�ӂ��܂�
			hutaframe--;
			if(hutaframe < 1){flag = 5;}
		}
		if(flag == 5)
		{
			//�Q�[���I�[�o�[
			P->obj.YPR =D3DXVECTOR3(0.0f,0.0f,0.0f); 
			m_pPare->FldChange(new Gameover,&D3DXVECTOR3(0.0f,0.0f,0.0f),0.0f);
		}
	}
	//�ӂ��̃A�j��
	pHuta.YPR.x = rot.Val(hutaframe);
}
VOID Rest_Men_Toile::DebugText(TCHAR* t,int l)
{
	_stprintf_s(t,l,
		_T("%s")
		_T("GOFlag = %d\n")
		,t
		,GOFlag
		);
}
