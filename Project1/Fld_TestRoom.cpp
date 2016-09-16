TestRoom::TestRoom(){}
VOID TestRoom::Set()
{	
	P->FM.FldType = FD_TestRoom;
	//��
	pFloor = NewObj(new drawObj);
	pFloor->Ob()->objPos.y=-0.25f;
	pFloor->Ob()->Type(x_cube);
	pFloor->Ob()->objScal=D3DXVECTOR3(40.0f,1.0f,40.0f);
	pFloor->Ob()->MeshCol=D3DXVECTOR4(0.5f,0.5f,0.5f,1.0f);
	pFloor->Ob()->SpColm=0.1f;
	//���b�Z�[�W�\��
	pMess = NewObj(new Message);
	pMess->Ob()->objPos=D3DXVECTOR3(0.0f,0.5f,4.0f);
	pMess->Ob()->objScal=D3DXVECTOR3(2.0f,2.0f,2.0f) * 1.0f;
	pMess->Ob()->BloomColor=D3DXVECTOR4(1.00f,1.00f,17.60f,1.00f);	
	/*
	//���b�Z�[�W�\��
	pMess1 = NewObj(new Message);
	pMess1->Ob()->objPos=D3DXVECTOR3(-1.0f,0.5f,3.0f);
	pMess1->Ob()->objScal=D3DXVECTOR3(2.0f,2.0f,2.0f) * 1.0f;
	pMess1->Ob()->BloomColor=D3DXVECTOR4(1.00f,1.00f,17.60f,1.00f);
	//*/
	
	
	//�A�C�e��
	pItem = NewObj(new Darts);
	pItem->Ob()->objPos=D3DXVECTOR3(1.0f,0.0f,0.0f);

	//���v
	pMoveChange = NewObj(new publictel );
	pMoveChange->Ob()->objPos=D3DXVECTOR3(-5.00f,0.00f,5.00f);
	pMoveChange->Ob()->YPR.y = 180.0f;
	//�ǔ��J����
	pCamChar = NewObj(new CamChar(&D3DXVECTOR3(0.0f,4.0f,-7.0f)));

	//�Œ�J����
	pCamSet1 = NewObj(new CamFix(&D3DXVECTOR3(-2.0f,5.0f,-2.0f),&D3DXVECTOR3(0.0f,0.0f,0.0f)));
	pCamSet1->Ob()->objPos.x = 2.0f;
	//�G
	pEnemy = NewObj(new Secret_Door);
	//�p�[�e�B�N��
	pPart = NewObj(new Particl);
	//�V�F�[�_-----------------------------------------------------------------
	//�t�H�O
	ML->E.Fs.Far=0.00f;
	//���C�g
	ML->E.Ls.Near=0.10f;
	ML->E.Ls.Far=100.00f;
	ML->E.Ls.Pos=D3DXVECTOR3(-5.00f,45.0f,-5.00f);
	//�t�B�[���h�̓����蔻��---------------------------------------------------

	P->FM.EventFlag = TL_READ_TIPS;
}

VOID TestRoom::Update()
{
	
}	
VOID TestRoom::draw()
{}	
VOID TestRoom::UI()
{}
VOID TestRoom::DebugText(TCHAR*,int)
{}
