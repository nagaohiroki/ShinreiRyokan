Fld_202::Fld_202(){}
VOID Fld_202::Set()
{
	P->FM.FldType = FD_202;
	//������
	pHitOsiire = NewObj(new Ev::HitBox);
	pHitOsiire->Ob()->objPos=D3DXVECTOR3(-4.00f,1.40f,1.30f);
	pHitOsiire->Ob()->objScal=D3DXVECTOR3(4.10f,5.90f,9.30f);
	//���̊�(�e���r��)
	pHitTokonoma = NewObj(new Ev::HitBox);
	pHitTokonoma->Ob()->objPos=D3DXVECTOR3(0.82f,1.50f,3.43f);
	pHitTokonoma->Ob()->objScal=D3DXVECTOR3(1.3f,5.80f,2.00f);
	//����
	pHitEngawa = NewObj(new Ev::HitBox);
	pHitEngawa->Ob()->objPos=D3DXVECTOR3(3.10f,1.40f,2.50f);
	pHitEngawa->Ob()->objScal=D3DXVECTOR3(0.70f,5.80f,2.50f);
	//����1
	pHitEngawa1 = NewObj(new Ev::HitBox);
	pHitEngawa1->Ob()->objPos=D3DXVECTOR3(3.10f,1.40f,-2.60f);
	pHitEngawa1->Ob()->objScal=D3DXVECTOR3(0.70f,5.80f,2.50f);
	//���̊ԏ�
	pHitTokoUe = NewObj(new Ev::HitBox);
	pHitTokoUe->Ob()->objPos=D3DXVECTOR3(0.0f,2.28f,3.57f);
	pHitTokoUe->Ob()->objScal=D3DXVECTOR3(11.93f,2.5f,2.0f);
	//����������
	pHitTanas = NewObj(new Ev::HitBox);
	pHitTanas->Ob()->objPos=D3DXVECTOR3(-2.36f,1.14f,3.22f);
	pHitTanas->Ob()->objScal=D3DXVECTOR3(2.28f,4.0f,1.0f);
	//�d�؂��
	pHitSikiriUe = NewObj(new Ev::HitBox);
	pHitSikiriUe->Ob()->objPos=D3DXVECTOR3(3.11f,2.18f,0.0f);
	pHitSikiriUe->Ob()->objScal=D3DXVECTOR3(0.5f,2.28f,14.1f);
	/*
	//�i������
	pHitSaka = NewObj(new HitBox);
	pHitSaka->Ob()->objScal.z = 8.0f;
	pHitSaka->Ob()->YPR.z = 45.0f;
	pHitSaka->Ob()->objPos = D3DXVECTOR3(3.2f, -0.2f,0.0f);
	//�i�����֑�
	pHitSakaGen = NewObj(new HitBox);
	pHitSakaGen->Ob()->YPR.z = 45.0f;
	pHitSakaGen->Ob()->objPos = D3DXVECTOR3(-3.2f,-0.2f,-2.0f);
	pHitSakaGen->Ob()->objScal = D3DXVECTOR3(1.0f,1.0f,4.0f);
	*/
	//�`��I�u�W�F�N�g-----------------------------------
	//����
	pRoom = NewObj(new Ev::drawObj);
	pRoom->Ob()->ShadowFlag=FALSE;
	pRoom->Ob()->Type(x_room);
	pRoom->Ob()->SpCol.w=50.0f;
	//�h�A-------------------------------------------------------�Q�K�L���ֈړ�
	pDoor = NewObj(new Door);
	pDoor->Ob()->objPos=D3DXVECTOR3(-4.86f,0.00f,-2.18f);
	pDoor->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);
	//�o�X���[���ւ̃h�A
	pDoorBath = NewObj(new bathdoor);
	pDoorBath->Ob()->objPos=D3DXVECTOR3(-2.012070f, 0.124773f,-2.9f);
	//�d�C
	pDenki = NewObj(new Denki202);
	pDenki->Ob()->objPos=D3DXVECTOR3(0,2.8f,0);
	//��
	pMado=NewObj(new Ev::Mado_S);
	pMado->Ob()->objPos=D3DXVECTOR3(4.83f,1.22f,0.00f);
	pMado->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);
	pMado->Ob()->objScal=D3DXVECTOR3(1.20f,1.40f,1.50f);
	//�o�X���[���e�L�X�g(�h�A�J���Ȃ�)
	pBathText = NewObj(new Ev::BathDoor202);
	pBathText->Ob()->objPos = D3DXVECTOR3(-2.012070f, 0.124773f,-2.9f);
	//�I�[�f�B�I
	ML->Audio.Audio.Effect = AE_LIVINGROOM;
	//�V�F�[�_-----------------------------------------------------------------
	//���C�g
	ML->E.Ls.Near=12.40f;
	ML->E.Ls.Far=15.00f;
	ML->E.Ls.Pos=D3DXVECTOR3(0.00f,14.40f,0.20f);
	ML->E.Ls.Col = D3DXVECTOR4(0.5f,0.5f,0.6f,1.0f);
	//�t�H�O
	ML->E.Fs.Col = D3DXVECTOR3(0.58f,0.58f,0.7f);
	ML->E.Fs.Far = 30.000015f;
	ML->E.Fs.Near = 0.000000f;
	ML->E.Fs.use = 1;
	//�t�B�[���h�̓����蔻��-------------------------------------------------------------
	EriaHit(&D3DXVECTOR3(-4.8f,0.0f,-2.9f),&D3DXVECTOR3(4.8f,2.8f,3.5f));
}
VOID Fld_202::Update()
{
	if(pDoor->HitObjFlag(0))
	{
		if(P->Check)
		{
			//���ʉ�
			P->CheckSE(Personal::SE_OPEN);
			FldChange(new F3, &D3DXVECTOR3(0.5f,2.55f,18.0f),90.0f);
		}
	}
	D3DXVECTOR3 Eye(0,0,-5.0f);
	D3DXVECTOR3 At(0,0,0);
	Eye=D3DXVECTOR3(2.7f,2.46f,-2.9f);
	At=P->obj.objPos;	
	if(P->obj.objPos.x>=3.0f)
	{
		Eye=D3DXVECTOR3(4.7f,2.05f,-2.9f);
	}
	ML->E.cam.CamSet(&Eye,&At);

}
