
//===============================================
//�O
//===============================================
Soto::Soto()
{
}	
VOID Soto::Set()
{
		
	P->FM.FldType = FD_Soto;
	//�ړ�--------------------------------------------------------------
	pMoveRobby = NewObj(new HitFlag);
	pMoveRobby->Ob()->Type(x_cube);
	pMoveRobby->Ob()->objPos=D3DXVECTOR3(0.00f,0.40f,40.30f);
	pMoveRobby->Ob()->objScal=D3DXVECTOR3(5.20f,6.60f,1.60f);
	//�ǔ��J����---------------------------------------------------------
	pCamChar = NewObj(new CamChar);
	pCamChar->Ob()->objPos = D3DXVECTOR3(0.0f,3.0f,-7.0f);
	//�����蔻��---------------------------------------------------------
	//�E�ǔ���
	pHitKabeR = NewObj(new HitBox);
	pHitKabeR->Ob()->objPos=D3DXVECTOR3(12.84f,0.00f,-2.00f);
	pHitKabeR->Ob()->objScal=D3DXVECTOR3(34.00f,10.00f,120.00f);

	//���ǔ���
	pHitKabeL = NewObj(new HitBox);
	pHitKabeL->Ob()->objPos=D3DXVECTOR3(-12.80f,0.00f,-2.00f);
	pHitKabeL->Ob()->objScal=D3DXVECTOR3(34.00f,10.00f,120.00f);

	//���K�i����1
	pHitKiadan = NewObj(new HitBox);
	pHitKiadan->Ob()->objPos=D3DXVECTOR3(5.2f,-0.38f,37.50f);
	pHitKiadan->Ob()->objScal=D3DXVECTOR3(4.60f,0.60f,10.0f);
	pHitKiadan->Ob()->YPR=D3DXVECTOR3(0.00f,0.00f,-30.00f);

	//���K�i����2
	pHitKiadan1 = NewObj(new HitBox);
	pHitKiadan1->Ob()->objPos=D3DXVECTOR3(-5.20f,-0.38f,37.50f);
	pHitKiadan1->Ob()->objScal=D3DXVECTOR3(4.60f,0.60f,10.0f);
	pHitKiadan1->Ob()->YPR=D3DXVECTOR3(0.00f,0.00f,30.00f);

	//���K�i����3
	pHitKiadan2 = NewObj(new HitBox);
	pHitKiadan2->Ob()->objPos=D3DXVECTOR3(0.00f,-0.38f,34.10f);
	pHitKiadan2->Ob()->objScal=D3DXVECTOR3(4.60f,0.50f,18.90f);
	pHitKiadan2->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,-30.00f);

	//��K�i����
	pHitKiadan3 = NewObj(new HitBox);
	pHitKiadan3->Ob()->objPos=D3DXVECTOR3(0.00f,0.05f,37.63f);
	pHitKiadan3->Ob()->objScal=D3DXVECTOR3(15.719543f,1.2f,8.785065f);

	//�E��
	pHitHasiraR = NewObj(new HitBox);
	pHitHasiraR->Ob()->objPos=D3DXVECTOR3(-3.46f,0.00f,35.70f);
	pHitHasiraR->Ob()->objScal=D3DXVECTOR3(1.60f,13.50f,1.00f);

	//����
	pHitHasiraL = NewObj(new HitBox);
	pHitHasiraL->Ob()->objPos=D3DXVECTOR3(3.46f,0.00f,35.70f);
	pHitHasiraL->Ob()->objScal=D3DXVECTOR3(1.60f,13.50f,1.00f);

	//���������蔻��
	pHitYane = NewObj(new HitBox);
	pHitYane->Ob()->objPos = D3DXVECTOR3(0.0f,4.271698f,37.709900f);
	pHitYane->Ob()->objScal = D3DXVECTOR3(15.926788f,3.891911f, 10.059116f);
	//�`��-------------------------------------------------------------------
	//�C�x���g�J����
	if(P->FM.EventFlag == TL_INTRO_START)
	{
		
		pIntroCut  = NewObj(new Ev::IntroCut);
		pCamEvent = NewObj(new IntroSotoCam);	
	}
	else if(P->FM.EventFlag == TL_ENDING)
	{
		//�G���f�B���O
		pEnding = NewObj(new Ending);
	}
	else
	{
		//�C�x���g
		pSotoEvent = NewObj(new SotoEvent);
		//10�~�C�x���g
		pTenYen = NewObj(new TenYen);
		pTenYen->Ob()->objPos = D3DXVECTOR3(-0.8f,0.35f,41.0f);

	}
	//�K���X
	pGlass = NewObj(new GenGlass);
	pGlass ->Ob()->objPos=D3DXVECTOR3(0,1.5f,40.0f);
	//�{��
	pHonkan = NewObj(new Honkan);
	pHonkan->Ob()->objPos=D3DXVECTOR3(0,0,50.0f);

	//����
	pSky = NewObj(new drawObj);
	pSky->Ob()->objPos=D3DXVECTOR3(3.46f,0.00f,35.70f);
	pSky->Ob()->Type(x_sky);
	pSky->Ob()->ShadowFlag=FALSE;
	pSky->Ob()->objScal=D3DXVECTOR3(1.0f,1.0f,1.0f)*5.0f;
	pSky->Ob()->SpColm=0.0f;

	//�O
	pSoto = NewObj(new drawObj);
	pSoto->Ob()->Type(x_hiroba);
	pSoto->Ob()->ShadowFlag=FALSE;
	pSoto->Ob()->SpColm=0.0f;
	pSoto->Ob()->SpCol.w=10.0f;

	if(P->FM.EventFlag > TL_INTRO_START)
	{
		//???
		pCase = NewObj(new Case);
		pCase->Ob()->objPos = D3DXVECTOR3(-1.5f,0.0f,15.5f);
	}
	//���O�d�b
	pTel = NewObj(new publictel);
	pTel ->Ob()->objPos = D3DXVECTOR3(4.0f,0.0f,13.0f);
	pTel ->Ob()->YPR = D3DXVECTOR3(0.0f,270.0f,0.0f);
	//��
	pMoon = NewObj(new Moon);
	pMoon->Ob()->objPos = D3DXVECTOR3(0.0f,30.0f,20.0f);
	//��
	pKusa = NewObj(new drawObj);
	pKusa->Ob()->Type(x_hiroba_kusa);
	//�I�[�f�B�I-----------------------------------------------------------
	ML->Audio.Audio.Effect = AE_FOREST;
	//�V�F�[�_-----------------------------------------------------------------
	//�t�H�O
	ML->E.Fs.Near=-0.10f;
	ML->E.Fs.Far=36.10f;
	ML->E.Fs.Col=D3DXVECTOR3(0.14f,0.14f,0.29f);
	//���C�g	
	ML->E.Ls.Pos=D3DXVECTOR3(0.10f,70.10f,-30.10f);
	ML->E.Ls.EyePlus=D3DXVECTOR3(0.00f,19.10f,-24.10f);
	ML->E.Ls.Near=43.60f;
	ML->E.Ls.Far=75.40f;
	ML->E.Ls.Col=D3DXVECTOR4(0.80f,0.80f,1.00f,1.00f);
	ML->E.Ls.Bias=-1.00f;
	//�G���A�S�̂̓����蔻��-------------------------------------------------------------------------------
	EriaHit(&D3DXVECTOR3(-21.5f,0.0f,0.0f),&D3DXVECTOR3(21.5f,50.0f,40.0f));
}
VOID Soto::Update()
{
		
	if(P->Check)
	{
		if(pMoveRobby->HitObjFlag(0))
		{
			//���r�[�Ɉړ�
			//bgm�폜
			SAFE_DELETE(P->BGM);
			FldChange(new Lobby,&D3DXVECTOR3(0,0.35f,-12.0f),0.0f);
			P->FM.Door=1;
		}
	}
		
}