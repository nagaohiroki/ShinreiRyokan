//==========================================================================
//�j�q�g�C��
//==========================================================================
Rest_Men::Rest_Men()
{
}
VOID Rest_Men::Set()
{
	P->FM.FldType = FD_Rest_Men;
	//�����蔻��I�u�W�F�N�g----------------------------------------------------------
	//���ʑ�
	pHitSenmen = NewObj(new HitBox);
	pHitSenmen->Ob()->objPos=D3DXVECTOR3(1.50f,0.00f,-2.00f);
	pHitSenmen->Ob()->objScal=D3DXVECTOR3(2.30f,2.20f,4.10f);
	
	//�d�؂�
	pHitSikiri = NewObj(new HitBox);
	pHitSikiri->Ob()->objPos=D3DXVECTOR3(1.23f,0.00f,-0.85f);
	pHitSikiri->Ob()->objScal=D3DXVECTOR3(3.50f,6.80f,0.70f);

	//�d�؂�1
	pHitSikiri1 = NewObj(new HitBox);
	pHitSikiri1->Ob()->objPos=D3DXVECTOR3(1.23f,0.00f,0.35f);
	pHitSikiri1->Ob()->objScal=D3DXVECTOR3(3.50f,6.80f,0.70f);

	//�d�؂�2
	pHitSikiri2 = NewObj(new HitBox);
	pHitSikiri2->Ob()->objPos=D3DXVECTOR3(1.23f,0.00f,1.68f);
	pHitSikiri2->Ob()->objScal=D3DXVECTOR3(3.50f,6.80f,0.70f);
	
	//�d�؂�3
	pHitSikiri3 = NewObj(new HitBox);
	pHitSikiri3->Ob()->objPos=D3DXVECTOR3(1.23f,0.00f,3.0f);
	pHitSikiri3->Ob()->objScal=D3DXVECTOR3(3.50f,6.80f,0.70f);

	//�`��I�u�W�F�N�g----------------------------------------------------------------
	//�j�q�g�C��
	pRoom = NewObj(new drawObj);
	pRoom->Ob()->Type(x_public_rest);
	pRoom->Ob()->ShadowFlag=FALSE;
	pRoom->Ob()->Bias=0.02f;
	pRoom->Ob()->SpColm=0.0f;

	//�g�C���h�A
	pDoor = NewObj(new Ev::Rest_Men_door);
	pDoor->Ob()->objPos=D3DXVECTOR3(0.55f,0.00f,0.10f);
	//�g�C���h�A
	pDoor1 = NewObj(new Ev::Rest_Men_door);
	pDoor1->Ob()->objPos=D3DXVECTOR3(0.55f,0.00f,1.405f);
	//�g�C���h�A
	pDoor2 = NewObj(new Ev::Rest_Men_door);
	pDoor2->Ob()->objPos=D3DXVECTOR3(0.55f,0.00f,2.765f);
	//�����n���h��
	pHandle=NewObj(new Rest_handle);
	pHandle->Ob()->objPos=D3DXVECTOR3(1.47f,0.555f,-1.47f);
	//�����n���h��
	pHandle1 = NewObj(new Rest_handle);
	pHandle1->Ob()->objPos=D3DXVECTOR3(1.47f,0.555f,-2.47f);
	

	//�ʋC��
	pDact = NewObj(new drawObj);
	pDact->Ob()->Type(x_tdact);
	pDact->Ob()->objPos=D3DXVECTOR3(0.00f,1.90f,3.00f);
	pDact->Ob()->ShadowFlag=FALSE;

	//���C�g
	pLight =NewObj(new Light);
	pLight->Ob()->objPos=D3DXVECTOR3(0.00f,2.20f,1.00f);


	//������h�A
	pExit = NewObj(new Door);
	pExit->Ob()->objPos=D3DXVECTOR3(0,0,-3.0f);

	//��
	pMirror = NewObj(new Mirror);
	pMirror->Fvf[0]->objPos = D3DXVECTOR3(2.1f,1.0f,-2.0f);
	pMirror->Fvf[0]->objScal = D3DXVECTOR3(2.4f,1.8f,0.0f);
	pMirror->Fvf[0]->YPR = D3DXVECTOR3(0.0f,90.0f,0.0f);

	//�����_��
	int r = rand() % 3;
	int t[3] = {1,1,1};
	t[r] = 0;

	//�g�C��
	pToile = NewObj(new Ev::Rest_Men_Toile(t[0]));
	pToile->Ob()->YPR.y = 270.0f;
	pToile->Ob()->objPos = D3DXVECTOR3(1.8f,0.0f,-0.3f);
	//�g�C��1
	pToile1 = NewObj(new Ev::Rest_Men_Toile(t[1]));
	pToile1->Ob()->YPR.y = 270.0f;
	pToile1->Ob()->objPos = D3DXVECTOR3(1.8f,0.0f,1.0f);

	//�g�C��2
	pToile2 = NewObj(new Ev::Rest_Men_Toile(t[2]));
	pToile2->Ob()->YPR.y = 270.0f;
	pToile2->Ob()->objPos = D3DXVECTOR3(1.8f,0.0f,2.3f);
	//����
	pMemo = NewObj(new ToileMemo(r));
	pMemo->Ob()->objPos =D3DXVECTOR3(-0.88f,0.65f,2.85f);
	//�I�[�f�B�I-------------------------------------------------------------
	ML->Audio.Audio.Effect = AE_SMALLROOM;
	//�V�F�[�_-----------------------------------------------------------------
	//���C�g
	ML->E.Ls.Near=6.50f;
	ML->E.Ls.Far=10.40f;
	ML->E.Ls.Pos=D3DXVECTOR3(0.00f,10.00f,1.00f);
	ML->E.Ls.Col = D3DXVECTOR4(0.7f,0.7f,0.8f,1.0f);
	//�t�H�O
	ML->E.Fs.Col.x = 0.600000f;
	ML->E.Fs.Col.y = 0.600000f;
	ML->E.Fs.Col.z = 0.700000f;
	ML->E.Fs.Far = 13.727310f;
	ML->E.Fs.Near = 3.000000f;
	ML->E.Fs.use = 1;
	//�t�B�[���h�̓����蔻��-------------------------------------------------------------
	EriaHit(&D3DXVECTOR3(-1.9f,0.0f,-2.9f),&D3DXVECTOR3(2.0f,2.2f,2.9f));

}

VOID Rest_Men::Update()
{
	if(pExit->HitObjFlag(0))
	{
		if(P->Check)
		{
			P->CheckSE(Personal::SE_OPEN);
			FldChange(new F3,&D3DXVECTOR3(-18.90f,2.55f,24.42f),0.0f);

		}
	}

	//�f�t�H���g�J�����ʒu
	D3DXVECTOR3 Eye(-1.9f,1.8f,-2.9f);
	D3DXVECTOR3 At = P->obj.objPos + D3DXVECTOR3(0,0.5f,0);
	//�g�C���̘���
	if(P->obj.objPos.x > 0.7f)
	{
		if(P->obj.objPos.z > -0.5f)
		{
			Eye = D3DXVECTOR3(0.95f,3.0f,-0.18f);
			At  = D3DXVECTOR3(1.5f,0.0f,-0.18f);
		}
		if(P->obj.objPos.z > 0.5f)
		{
			Eye = D3DXVECTOR3(0.95f,3.0f,1.0f);
			At  = D3DXVECTOR3(1.5f,0.0f,1.0f);
		}
		if(P->obj.objPos.z > 2.0f)
		{
			Eye = D3DXVECTOR3(0.95f,3.0f,2.3f);
			At  = D3DXVECTOR3(1.5f,0.0f,2.3f);
		}

	}

	ML->E.cam.CamSet(&Eye,&At);
}