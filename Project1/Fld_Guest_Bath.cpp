Guest_Bath::Guest_Bath(){}
VOID Guest_Bath::Set()
{
	P->FM.FldType = FD_Guest_Bath;
	//�`��I�u�W�F�N�g
	//����
	pRoom = NewObj(new drawObj);
	pRoom->Ob()->Type(x_guestbath);
	pRoom->Ob()->ShadowFlag = FALSE;
	pRoom->Ob()->MeshCol = D3DXVECTOR4(0.5f,0.5f,0.5f,1.0f);
	//����
	pSink = NewObj(new drawObj);
	pSink ->Ob()->Type(x_tsink);
	pSink ->Ob()->objPos = D3DXVECTOR3(0.5f,0.55f,-2.0f);
	//�g�C��
	pToile = NewObj(new Ev::Toile);
	pToile ->Ob()->objPos = D3DXVECTOR3(-1.68f,0.0f,-1.69f);
	pToile ->Ob()->YPR = D3DXVECTOR3(0.0f,90.0f,0.0f);
	//�h�A
	pDoor = NewObj(new bathdoor);
	pDoor->Ob()->objPos.z = 2.0f;
	//���C�g
	pLight =NewObj(new Light);
	pLight->Ob()->objPos=D3DXVECTOR3(0.00f,2.00f,0.00f);
	//�����̓����蔻��
	pHitBath = NewObj(new HitBox);
	pHitBath->Ob()->objPos = D3DXVECTOR3(1.4f,0.17f,-1.0f);
	pHitBath->Ob()->objScal = D3DXVECTOR3(2.0f,1.6f,4.0f);
	//�G
	pEnemy = NewObj(new Enemy);
	P->FM.enemy.pos = D3DXVECTOR3(0.0f,0.35f,1.5f);
	P->FM.enemy.rot = 180.0f;
	
	if(P->FM.EventFlag <= TL_GUEST_ENEMY_START)
	{
		//�G�C�x���g
		pEnemyEvent = NewObj(new EnemyGuestBath);

		//�G���A���܂������ꍇ
		if(P->FM.enemy.mode == Enemy::MODE_STALK || P->FM.enemy.mode == Enemy::MODE_STALK_ATTACK)
		{
			pActiveEnemy = NewObj(new ActiveEnemy);
			if(P->FM.enemy.mode == Enemy::MODE_STALK)
			{
				P->FM.enemy.pos = D3DXVECTOR3(0.0f,0.35f,0.0f);
				P->FM.enemy.rot = 180.0f;
			}
			if(P->FM.enemy.mode == Enemy::MODE_STALK_ATTACK)
			{
				P->FM.enemy.pos = D3DXVECTOR3(0.0f,0.35f,1.5f);
				P->FM.enemy.rot = 0.0f;
			}
		}
	}
	//��
	pAir = NewObj(new Air);
	pAir->Ob()->objPos = D3DXVECTOR3(-2.0f,1.73f,-1.66f);
	pAir->Ob()->YPR = D3DXVECTOR3(0.0f,90.0f,0.0f);

	//�󒲃X�C�b�`
	pAirSwitch = NewObj(new AirSwitch);
	pAirSwitch->Ob()->objPos = D3DXVECTOR3(-2.0f,0.7f,-1.0f);
	pAirSwitch->Ob()->YPR = D3DXVECTOR3(0.0f,270.0f,0.0f);

	//�I�[�f�B�I-------------------------------------------------------------
	ML->Audio.Audio.Effect = AE_BATHROOM;


	//���C�g
	ML->E.Ls.Near=6.50f;
	ML->E.Ls.Far=10.40f;
	ML->E.Ls.Col = D3DXVECTOR4(0.7f,0.7f,0.8f,1.0f);
	//�t�H�O
	ML->E.Fs.Col.x = 0.600000f;
	ML->E.Fs.Col.y = 0.600000f;
	ML->E.Fs.Col.z = 0.700000f;
	ML->E.Fs.Far = 13.727310f;
	ML->E.Fs.Near = 3.000000f;
	ML->E.Fs.use = 1;

	//�t�B�[���h�̓����蔻��-------------------------------------------------------------
	EriaHit(&D3DXVECTOR3(-2.0f,0.0f,-2.0f),&D3DXVECTOR3(2.0f,2.0f,2.0f));

}
VOID Guest_Bath::Update()
{


	if(pDoor->HitObjFlag(0))
	{
		if(P->Check)
		{
			P->CheckSE(Personal::SE_OPEN);
			FldChange(new Guest_Room, &D3DXVECTOR3(-2.0f,0.42f,-1.9f),  0.0f);
		}
	}

	D3DXVECTOR3 Eye(0,0,-5.0f);
	D3DXVECTOR3 At(0,0,0);
	Eye=D3DXVECTOR3(1.9f,1.9f,-1.9f);
	At = P->obj.objPos;	
	ML->E.cam.CamSet(&Eye,&At);
}
VOID Guest_Bath::DebugText(TCHAR*,int ){}
