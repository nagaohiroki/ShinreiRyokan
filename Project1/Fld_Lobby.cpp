
//=====================================================
//���r�[
//=====================================================
Lobby::Lobby()
{	
}
VOID Lobby::Set()
{
	P->FM.FldType = FD_Lobby;
	//�ړ�----------------------------------------------------
	//��K��
	pMoveF2 = NewObj(new HitFlag);
	pMoveF2->Ob()->objPos=D3DXVECTOR3(8.66f,2.90f,23.90f);
	pMoveF2->Ob()->objScal=D3DXVECTOR3(7.40f,1.00f,1.00f);

	//�����
	pMoveBath = NewObj(new HitFlag); 
	pMoveBath->Ob()->objPos=D3DXVECTOR3(-0.20f,0.00f,42.30f);
	pMoveBath->Ob()->objScal=D3DXVECTOR3(1.00f,1.00f,6.10f);
//*	

	//�����蔻��----------------------------------------------------
	//�����蔻��(�t�����g�J�E���^�[)
	pHitFront = NewObj(new HitBox);
	pHitFront->Ob()->objPos=D3DXVECTOR3(8.64f,0.13f,6.91f);
	pHitFront->Ob()->objScal=D3DXVECTOR3(1.50f,2.40f,21.08f);

	//�����蔻��(�t�����g�J�E���^�[)
	pHitFront1 = NewObj(new HitBox);
	pHitFront1->Ob()->objPos=D3DXVECTOR3(10.90f,0.13f,1.30f);
	pHitFront1->Ob()->objScal=D3DXVECTOR3(10.30f,2.20f,1.50f);

	//�E��
	pHitRightTemae = NewObj(new HitBox);
	pHitRightTemae->Ob()->objPos=D3DXVECTOR3(8.14f,2.00f,19.00f);
	pHitRightTemae->Ob()->objScal=D3DXVECTOR3(20.90f,12.68f,20.70f);

	//�K�i�x���
	pHitOdoriba = NewObj(new HitBox);
	pHitOdoriba->Ob()->objPos=D3DXVECTOR3(8.4f,-0.54f,23.50f);
	pHitOdoriba->Ob()->objScal=D3DXVECTOR3(7.00f,13.00f,14.17f);
//	pHitOdoriba->Ob()->drawSkip = FALSE;
	//�K�i
	pHitKaidan = NewObj(new HitBox);
	pHitKaidan->Ob()->objPos=D3DXVECTOR3(5.00f,0.75f,25.60f);
	pHitKaidan->Ob()->objScal=D3DXVECTOR3(8.90f,3.00f,6.90f);
	pHitKaidan->Ob()->YPR=D3DXVECTOR3(0.00f,0.00f,36.00f);
//	pHitKaidan->Ob()->drawSkip = FALSE;
	//�E��(��)
	pHitRightOku = NewObj(new HitBox);
	pHitRightOku->Ob()->objPos=D3DXVECTOR3(7.71f,2.70f,63.74f);
	pHitRightOku->Ob()->objScal=D3DXVECTOR3(19.20f,11.80f,146.20f);

	//�K�i�̉�
	pHitKaidanOku = NewObj(new HitBox);
	pHitKaidanOku->Ob()->objPos=D3DXVECTOR3(11.80f,2.90f,24.70f);
	pHitKaidanOku->Ob()->objScal=D3DXVECTOR3(9.30f,9.30f,23.20f);
	//����
	pHitLeft = NewObj(new HitBox);
	pHitLeft->Ob()->objPos=D3DXVECTOR3(-6.60f,1.60f,31.80f);
	pHitLeft->Ob()->objScal=D3DXVECTOR3(26.30f,6.80f,71.40f);

	//�V��t���A
	pHitCeilingFloor = NewObj(new HitBox);
	pHitCeilingFloor->Ob()->objPos = D3DXVECTOR3(0.0f,3.2f,0.0f);
	pHitCeilingFloor->Ob()->objScal = D3DXVECTOR3(52.3f,1.0f,57.2f);
	//�V��ʘH
	pHitCeilingPass = NewObj(new HitBox);
	pHitCeilingPass->Ob()->objPos = D3DXVECTOR3(1.31f,3.2f,27.5f);
	pHitCeilingPass->Ob()->objScal = D3DXVECTOR3(6.84f,1.0f,72.23f);
	//�V��K�i
	pHitCeilingStairs = NewObj(new HitBox);
	pHitCeilingStairs->Ob()->objPos = D3DXVECTOR3(5.41f,4.82f,25.35f);
	pHitCeilingStairs->Ob()->objScal = D3DXVECTOR3(11.4f,1.0f,8.24f);
	pHitCeilingStairs->Ob()->YPR = D3DXVECTOR3(0.0f,0.0f,32.95f);
	//�t�����g�̒�
	pHitFrontHasira = NewObj(new HitBox);
	pHitFrontHasira->Ob()->objPos = D3DXVECTOR3(8.76f,1.81f,1.40f);
	pHitFrontHasira->Ob()->objScal= D3DXVECTOR3(1.6f,4.62f,1.6f);

	//�J����----------------------------------------------------
	//�J����
	pCamCenter = NewObj(new HitFlag);
	pCamCenter->Ob()->Type(x_sphere);
	pCamCenter->Ob()->objScal=D3DXVECTOR3(2.0f,2.0f,2.0f);
	pCamCenter->Ob()->HitMode(CT_SPHERE,CB_NONE);
	pCamKaidan = NewObj(new HitFlag);
	pCamKaidan->Ob()->objPos=D3DXVECTOR3(10.50f,1.50f,25.80f);
	pCamKaidan->Ob()->objScal=D3DXVECTOR3(26.50f,13.70f,6.50f);

	//�`��----------------------------------------------------
	

	//���̘L���̃��C�g
	pLight = NewObj(new Light);
	pLight->Ob()->objPos=D3DXVECTOR3(1.20f,3.0f,26.5f);

	//��t�̊G
	pKaiga = NewObj(new drawObj);
	pKaiga->Ob()->Type(x_kaiga);
	pKaiga->Ob()->objPos=D3DXVECTOR3(12.89f,2.40f,7.40f);
	pKaiga->Ob()->YPR=D3DXVECTOR3(17.00f,-90.00f,0.00f);
	pKaiga->Ob()->ShadowFlag=FALSE;

	//���W�X�^�[
	pRezi = NewObj(new drawObj);
	pRezi->Ob()->Type(x_rezi);
	pRezi->Ob()->objPos=D3DXVECTOR3(9.50f,0.65f,1.30f);

	//���I
	pKeyBox = NewObj(new drawHitObj);
	pKeyBox->Ob()->Type(x_kagidana);
	pKeyBox->Ob()->objPos=D3DXVECTOR3(12.10f,0.00f,4.30f);
	pKeyBox->Ob()->YPR=D3DXVECTOR3(0.00f,-90.00f,0.00f);

	//TV
	pTV = NewObj(new Ev::TV);
	pTV->Ob()->objPos=D3DXVECTOR3(-12.00f,0.00f,-13.00f);
	pTV->Ob()->objScal=D3DXVECTOR3(1.00f,1.00f,1.00f);
	pTV->Ob()->YPR=D3DXVECTOR3(0.00f,22.00f,0.00f);

	//�e�[�u��
	pTableA = NewObj(new drawHitObj);
	pTableA->Ob()->Type(x_table);
	pTableA->Ob()->objPos=D3DXVECTOR3(-8.00f,0.00f,-10.90f);
	pTableA->Ob()->objScal=D3DXVECTOR3(1.80f,1.00f,1.00f);

	//�\�t�@
	pSofa_A = NewObj(new Chair);
	pSofa_A->Ob()->objPos=D3DXVECTOR3(-8.00f,-0.00f,-13.20f);//13.20f
	pSofa_A->Ob()->objScal=D3DXVECTOR3(2.00f,1.00f,1.00f);
	pSofa_A->Ob()->YPR=D3DXVECTOR3(0.00f,180.00f,0.00f);

	//�\�t�@
	pSofa_A1 = NewObj(new Chair);	
	pSofa_A1->Ob()->objPos=D3DXVECTOR3(-8.34f,0.00f,-9.00f);
	
	//�\�t�@���
	pSofa_A2 = NewObj(new LobbyChair);
	pSofa_A2->Ob()->objPos=D3DXVECTOR3(-6.86f,0.00f,-9.00f);

	//�e�[�u��
	pTableB = NewObj(new drawHitObj);
	pTableB->Ob()->Type(x_table);
	pTableB->Ob()->objPos=D3DXVECTOR3(-8.00f,0.00f,-2.90f);
	pTableB->Ob()->objScal=D3DXVECTOR3(1.80f,1.00f,1.00f);


	//�\�t�@
	pSofa_B = NewObj(new Chair);
	pSofa_B->Ob()->objPos=D3DXVECTOR3(-8.00f,-0.00f,-1.00f);
	pSofa_B->Ob()->objScal=D3DXVECTOR3(2.00f,1.00f,1.00f);

	//�\�t�@
	pSofa_B1 = NewObj(new Chair);
	pSofa_B1->Ob()->objPos=D3DXVECTOR3(-8.34f,0.00f,-5.20f);
	pSofa_B1->Ob()->YPR=D3DXVECTOR3(0.00f,180.00f,0.00f);

	//�\�t�@
	pSofa_B2 = NewObj(new Chair);
	pSofa_B2->Ob()->objPos=D3DXVECTOR3(-6.36f,0.00f,-5.20f);
	pSofa_B2->Ob()->YPR=D3DXVECTOR3(0.00f,190.00f,0.00f);

	//�X�C�b�`
	pSwitch = NewObj(new LightSwitch);
	pSwitch->Ob()->objPos=D3DXVECTOR3(-9.61f,1.00f,13.97f);

	//�g�C���h�A----------------------------------------------------------------�g�C���ֈړ�
	pToile = NewObj(new Door(Door::F0_WC,Door::F1_KEY_GREEN,Door::F2_WOOD));//�v���[�g,��
	pToile->Ob()->objPos=D3DXVECTOR3(-10.20f,0.00f,13.95f);

	//�X�^�b�t�h�A
	pStuff = NewObj(new Staff_Door);
	pStuff->Ob()->objPos=D3DXVECTOR3(13.10f,0.00f,13.20f);
	pStuff->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);
	

	//LobbyWindow
	pWindow = NewObj(new LobbyWindow);
	pWindow->Ob()->YPR.y=-90.0f;
	pWindow->Ob()->objPos=D3DXVECTOR3(-13.1f,1.2f,-10.0f);

	//LobbyWindow
	pWindow1 = NewObj(new LobbyWindow);
	pWindow1->Ob()->YPR.y=-90.0f;
	pWindow1->Ob()->objPos=D3DXVECTOR3(-13.1f,1.2f,-5.0f);
		
	//Lobby
	pLobby = NewObj(new drawObj);
	pLobby->Ob()->Type(x_lobby);
	pLobby->Ob()->ShadowFlag=FALSE;
	pLobby->Ob()->SpColm=0.0f;
	
	//�h�A
	pDoor = NewObj(new Dining_Door);
	pDoor->Ob()->objPos=D3DXVECTOR3(3.00f,0.00f,32.0f);
	pDoor->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);

	//�h�A
	pDoor1 = NewObj(new Dining_Door2);
	pDoor1->Ob()->objPos=D3DXVECTOR3(3.00f,0.00f,41.7f);
	pDoor1->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);
	
	//�L����
	pSWindow = NewObj(new Mado_S);
	pSWindow->Ob()->objPos=D3DXVECTOR3(-0.08f,1.30f,29.50f);
	pSWindow->Ob()->YPR=D3DXVECTOR3(0.00f,-90.00f,0.00f);


	//�L����1
	pSWindow1 = NewObj(new Mado_S);
	pSWindow1->Ob()->objPos=D3DXVECTOR3(-0.08f,1.30f,34.60f);
	pSWindow1->Ob()->YPR=D3DXVECTOR3(0.00f,-90.00f,0.00f);

	//�A���t�@,�A���t�@�e�N�X�`���֌W�͍Ō�ɐ錾
	//�����
	pIriguti = NewObj(new LobbyIriguti);
	pIriguti->Ob()->ShadowFlag=FALSE;
	pIriguti->Ob()->objPos=D3DXVECTOR3(0,1.1f,-13.95f);
	pIriguti->Ob()->YPR.y=180.0f;

	//�A��
	pUeki = NewObj(new Ueki);
	pUeki->Ob()->objPos=D3DXVECTOR3(-12.80f,0.00f,12.50f);

	//�G
	if(P->FM.EventFlag <= TL_BOUKA_OPEN)
	{
		pEnemy = NewObj(new Enemy);
		pEnemyWalk = NewObj(new EnemyWalk);
	}
	//�I�[�f�B�I
	ML->Audio.Audio.Effect = AE_HALLWAY;
	//�G���A�S�̂̓����蔻��-------------------------------------------------------------------------------
	EriaHit(&D3DXVECTOR3(-13.0f,0.0f,-14.0f),&D3DXVECTOR3(13.0f,5.5f,44.0f));
	//�V�F�[�_---------------------------------------------------------------------------------------------
	//���C�g
	ML->E.Ls.Near=34.5f;	
	ML->E.Ls.Far=42.5f;
	ML->E.Ls.Pos=D3DXVECTOR3(0.00f,40.30f,1.00f);
	ML->E.Ls.At=D3DXVECTOR3(0.00f,0.00f,0.00f);
	ML->E.Ls.Col=D3DXVECTOR4(0.5f,0.5f,0.75f,1.00f);
	//�t�H�O
	ML->E.Fs.Near=-50.00f;
	ML->E.Fs.Far=120.00f;
	ML->E.Fs.Col=D3DXVECTOR3(0.5f,0.5f,0.75f);
	ML->E.Fs.use = TRUE;
}

VOID Lobby::Update()
{
	//�G���A�ړ�======================================================================================
	if(P->Check)
	{
		//�g�C����
		if(pToile->HitObjFlag(0))
		{
			P->CheckSE(Personal::SE_OPEN);
			FldChange(new LobbyRestRoom,&D3DXVECTOR3(0,0.35f,-1.0f),0.0f);
		}
	}
	//��K��
	if(pMoveF2->HitObjFlag(0))
	{
		FldChange(new Fld::F3,&D3DXVECTOR3(8.0f,0.35f,7.0f),180.0f);
	}

	//����ʘH��
	if(pMoveBath->HitObjFlag(0))
	{
		FldChange(new Fld::Bath_Pass,&D3DXVECTOR3(5.10f,0.95f,0.00f),-90.0f);
	}

	//�J����(�G���A����)================================================================
	ML->E.Ls.Near=34.5f;	
	ML->E.Ls.Far=42.5f;
	ML->E.Ls.Pos=D3DXVECTOR3(0.00f,40.30f,1.00f);
	ML->E.Ls.At=D3DXVECTOR3(0.00f,0.00f,0.00f);
	D3DXVECTOR3 Eye(0.0f,2.0f,0.0f),At(P->obj.objPos);

	if(pCamCenter->HitObjFlag(0))
	{	
		Eye=D3DXVECTOR3(-10.0f,2.0f,-10.0f);
		At=D3DXVECTOR3(0.0f,0.0f,0.1f);
	}

	//�L����
	if(P->obj.objPos.z > 19.0f)
	{
		Eye=D3DXVECTOR3(0.5f,2.5f,16.0f);
		At=D3DXVECTOR3(0,0,P->obj.objPos.z);
		if(At.z<21.5f){At.z=21.5f;}

		ML->E.Ls.Near=37.100f;
		ML->E.Ls.Far=42.00f;
	    ML->E.Ls.Pos=D3DXVECTOR3(0.00f,40.30f,28.90f);
	    ML->E.Ls.At=D3DXVECTOR3(0.00f,0.00f,28.50f);
	}
	//�K�i
	if(pCamKaidan->HitObjFlag(0))
	{
		Eye = D3DXVECTOR3(-1.9f,1.0f,25.5f);
		At  = D3DXVECTOR3(P->obj.objPos.x,P->obj.objPos.y,25.5f);
	}
	
	ML->E.cam.CamSet(&Eye,&At);
//	*/
}
