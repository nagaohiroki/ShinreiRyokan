//==============================================================================
//����
//==============================================================================
Roof_Top::Roof_Top(){}
VOID Roof_Top::Set()
{
	P->FM.FldType = FD_Roof_Top;

	//�����蔻��I�u�W�F�N�g-------------------------------------------------------------
	//��
	pHit_Z0 = NewObj(new Ev::HitBox);
	pHit_Z0->Ob()->objPos = D3DXVECTOR3(0.0f,0.0f,16.3f); 
	pHit_Z0->Ob()->objScal = D3DXVECTOR3(34.4f,2.4f,1.35f); 

	pHit_Z1 = NewObj(new Ev::HitBox);
	pHit_Z1->Ob()->objPos = D3DXVECTOR3(0.0f,0.0f,-16.3f); 
	pHit_Z1->Ob()->objScal = D3DXVECTOR3(34.4f,2.4f,1.35f); 

	pHit_X0 = NewObj(new Ev::HitBox);
	pHit_X0->Ob()->objScal = D3DXVECTOR3(1.35f,2.4f,66.5f); 
	pHit_X0->Ob()->objPos = D3DXVECTOR3(8.23f,0.0f,0.0f); 
	
	pHit_X1 = NewObj(new Ev::HitBox);
	pHit_X1->Ob()->objScal = D3DXVECTOR3(1.35f,2.4f,66.5f); 
	pHit_X1->Ob()->objPos = D3DXVECTOR3(-8.23f,0.0f,0.0f); 

	//�K�i����
	pHitKai = NewObj(new Ev::HitBox);
	pHitKai->Ob()->objPos=D3DXVECTOR3(6.40f,0.90f,0.00f);	
	pHitKai->Ob()->objScal=D3DXVECTOR3(6.40f,3.90f,9.30f);
	//�{�C���[
	pBoiler = NewObj(new Ev::Boiler);
	pBoiler->Ob()->objPos=D3DXVECTOR3(7.0f,0.0f,3.0f);
	//�J����-------------------------------------------------------------------------
	pCamChar = NewObj(new CamChar);
	pCamChar->Ob()->objPos = D3DXVECTOR3(0.0f,3.0f,-7.0f);
	//�`��I�u�W�F�N�g-------------------------------------------------------------
	//�h�A
	pDoorExit = NewObj(new DoorRoofTop);
	pDoorExit->Ob()->objPos=D3DXVECTOR3(4.90f,0.00f,-1.25f);
	pDoorExit->Ob()->YPR=D3DXVECTOR3(0.00f,270.00f,0.00f);
	//����
	pRoofTop = NewObj(new drawObj);
	pRoofTop->Ob()->Type(x_roof_top);
	pRoofTop->Ob()->ShadowFlag=FALSE;
	//��
	pSky = NewObj(new drawObj);
	pSky->Ob()->Type(x_sky);
	pSky->Ob()->objScal=D3DXVECTOR3(5.0f,5.0f,5.0f);
	pSky->Ob()->ShadowFlag=FALSE;
	//��
	pMado = NewObj(new Ev::Mado_S);
	pMado->Ob()->objPos=D3DXVECTOR3(4.95f,1.00f,1.00f);
	pMado->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);
	pMado->Ob()->objScal=D3DXVECTOR3(0.80f,0.70f,5.70f);
	//�G
	if(P->FM.EventFlag < TL_ROOF_ENEMY)
	{
		P->FM.enemy.Level = 1;
		P->FM.enemy.pos = D3DXVECTOR3(5.0f,0.35f,3.0f);
		P->FM.enemy.rot = 90.0f; 
		P->FM.enemy.HP = 5;
		pEnemy = NewObj(new Enemy);
	}
	//�I�[�f�B�I-------------------------------------------------------------
	ML->Audio.Audio.Effect = AE_PLAIN;
	//�V�F�[�_-------------------------------------------------------------
	//���C�g
	ML->E.Ls.Col = D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);
	//�t�H�O
	ML->E.Fs.Col = D3DXVECTOR3(0.0f,0.0f,0.1f);
	//�t�B�[���h�̓����蔻��-------------------------------------------------------------
	EriaHit(&D3DXVECTOR3(-30.0f,0.0f,-30.0f),&D3DXVECTOR3(30.0f,10.0f,30.0f));
}
VOID Roof_Top::Update()
{
}
