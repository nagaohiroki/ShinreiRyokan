//======================================================
//�H��
//======================================================
Dining_Room::Dining_Room()
{
}
VOID Dining_Room::Set()
{
		P->FM.FldType = FD_Dining_Room;

	//�����蔻��I�u�W�F�N�g
	pHitSikiri = NewObj(new HitBox);
	pHitSikiri->Ob()->objPos=D3DXVECTOR3(1.29f,0.39f,4.94f);
	pHitSikiri->Ob()->objScal=D3DXVECTOR3(14.00f,1.50f,0.90f);

	pHitSikiri1 = NewObj(new HitBox);
	pHitSikiri1->Ob()->objPos=D3DXVECTOR3(-3.62f,2.0f,4.94f);
	pHitSikiri1->Ob()->objScal=D3DXVECTOR3(1.70f,9.85f,0.90f);

	//�d�؂��
	pHitSikiriUe= NewObj(new HitBox);
	pHitSikiriUe->Ob()->objPos=D3DXVECTOR3(0.0f,2.41f,4.94f);
	pHitSikiriUe->Ob()->objScal=D3DXVECTOR3(18.108652f,2.0f,0.9f);
	//�d�؂荶
	pHitSikiriL = NewObj(new HitBox);
	pHitSikiriL->Ob()->objPos=D3DXVECTOR3(-1.67f,1.40f,4.94f);
	pHitSikiriL->Ob()->objScal=D3DXVECTOR3(1.81f,2.21f,0.9f);
	//�d�؂�E
	pHitSikiriR = NewObj(new HitBox);
	pHitSikiriR->Ob()->objPos=D3DXVECTOR3(3.53f,1.40f,4.94f);
	pHitSikiriR->Ob()->objScal=D3DXVECTOR3(1.81f,2.21f,0.9f);

	//�L�b�`��
	pHitKichin = NewObj(new HitBox);
	pHitKichin->Ob()->objPos=D3DXVECTOR3(1.67f,0.20f,7.58f);
	pHitKichin->Ob()->objScal=D3DXVECTOR3(5.44f,1.40f,1.65f);
	//�L�b�`��
	pHitKichin1 = NewObj(new HitBox);
	pHitKichin1->Ob()->objPos=D3DXVECTOR3(3.50f,0.27f,6.30f);
	pHitKichin1->Ob()->objScal=D3DXVECTOR3(1.76f,1.10f,4.80f);
	//�{�C���[
	pHitKichinBoiler = NewObj(new HitBox);
	pHitKichinBoiler->Ob()->objPos=D3DXVECTOR3(1.2f,1.81f,7.44f);
	pHitKichinBoiler->Ob()->objScal=D3DXVECTOR3(2.4f,1.4f,1.0f);

	//�{�C���[
	pHitKichinBoiler = NewObj(new HitBox);
	pHitKichinBoiler->Ob()->objPos=D3DXVECTOR3(3.34f,1.81f,5.8f);
	pHitKichinBoiler->Ob()->objScal=D3DXVECTOR3(1.0f,1.4f,2.4f);
	//�`��I�u�W�F�N�g
	//�h�A
	pDoor = NewObj(new Door);
	pDoor->Ob()->objPos=D3DXVECTOR3(-4.00f,0.00f,-3.00f);
	pDoor->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);

	//�h�A1
	pDoor1 = NewObj(new Dining_Door_In);
	pDoor1->Ob()->objPos=D3DXVECTOR3(-4.00f,0.00f,6.70f);
	pDoor1->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);

	//�_�C�j���O���[��
	pRoom = NewObj(new drawObj);
	pRoom->Ob()->Type(x_dining_room);
	pRoom->Ob()->ShadowFlag=FALSE;
	pRoom->Ob()->SpColm=0.0f;

	//�u����
	pLight = NewObj(new Keikou);
	pLight->Ob()->objPos=D3DXVECTOR3(0.00f,2.50f,-1.60f);
	pLight->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);
	//�u����
	pLight1 = NewObj(new Keikou);
	pLight1->Ob()->objPos=D3DXVECTOR3(0.00f,2.50f,1.60f);
	pLight1->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);
	
	//��
	pMado = NewObj(new Mado_S);
	pMado->Ob()->objPos=D3DXVECTOR3(4.00f,1.20f,1.40f);
	pMado->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);

	//��1
	pMado1 = NewObj(new Mado_S);
	pMado1->Ob()->objPos=D3DXVECTOR3(4.00f,1.20f,-2.10f);
	pMado1->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);

	//�֎q
	pChair = NewObj(new Wood_Chair);
	if(!P->FM.iGetedFlag(ITEM_STAFF_KEY))
	{
		P->FM.enemy.HP = 5;
		P->FM.enemy.pos = D3DXVECTOR3(0.0f,0.35f,2.0f);
		P->FM.enemy.rot = 0.0f;
		pEnemy = NewObj(new Enemy);
	}
	//�I�[�f�B�I--------------------------------------------------------------
	ML->Audio.Audio.Effect = AE_MEDIUMHALL;
	//�V�F�[�_-----------------------------------------------------------------
	//�t�H�O
	
	ML->E.Fs.Near=0.00f;
	ML->E.Fs.Far=50.00f;
	//���C�g
	ML->E.Ls.Col = D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);
	//�t�B�[���h�̓����蔻��-------------------------------------------------------------
	EriaHit(&D3DXVECTOR3(-3.90f,0.0f,-5.0f),&D3DXVECTOR3(3.90f,2.5f,7.90f));

}

VOID Dining_Room::Update()
{
	if(P->Check)
	{
		//���r�[��
		if(pDoor->HitObjFlag(0))
		{
			FldChange(new Lobby,&D3DXVECTOR3(2.3f,0.0f,32.0f),270.0f);
		}
	}
	D3DXVECTOR3 Eye(0.0f,2.0f,0.0f),At(P->obj.objPos);
	Eye = D3DXVECTOR3(-3.9f,2.4f,-4.9f);
	if(P->obj.objPos.z > 4.5f){	Eye = D3DXVECTOR3(3.9f,1.3f,7.9f);	}
	ML->E.cam.CamSet(&Eye,&At);
}