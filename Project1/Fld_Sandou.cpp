//============================================
//�R��
//============================================
Sandou::Sandou(){}
VOID Sandou::Set()
{
	P->FM.FldType = FD_Sandou;
	//�ǔ��J����---------------------------------------------------------
	pCamChar = NewObj(new CamChar);
	pCamChar->Ob()->objPos = D3DXVECTOR3(0.0f,3.0f,-7.0f);
	//����
	pSky = NewObj(new drawObj);
	pSky->Ob()->objPos=D3DXVECTOR3(0.0f,0.00f,0.00f);
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

	//��
	pKusa = NewObj(new drawObj);
	pKusa->Ob()->Type(x_hiroba_kusa);

	//��
	pMoon = NewObj(new drawObj);
	pMoon->Ob()->Type(x_sphere);
	pMoon->Ob()->ShadowFlag = FALSE;
	pMoon->Ob()->BloomColor = D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);
	pMoon->Ob()->objPos = D3DXVECTOR3(0.0f,36.0f,0.0f);
	pMoon->Ob()->SpCol.w = 0.0f;
	pMoon->Ob()->SpColm = 1.0f;

	//�C�x���g
	pEvent = NewObj(new SandouEvent);


	//�I�[�f�B�I----------------------------------------------------------
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

	//�����蔻��
	EriaHit(&D3DXVECTOR3(-4.3f,0.0f,-15.0f),&D3DXVECTOR3(4.3f,10.0f,15.0f));

}
VOID Sandou::Update()
{
}
