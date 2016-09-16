//�Œ�J�����͈͎w��
const TCHAR* CamFix::name(){return _T("CamFix");}
CamFix::CamFix()
{
	Init();
}
CamFix::CamFix(D3DXVECTOR3* eye,D3DXVECTOR3* at)
{
	Init();
	At.objPos = *at;
	Eye.objPos = *eye;	
}
VOID CamFix::Init()
{
	Msh.push_back(&Hit);
	Msh.push_back(&Eye);
	Msh.push_back(&At);
	Hit.Type(x_cube);
	Hit.HitMode(CT_OBB,CB_NONE);

	Hit.drawSkip = TRUE;
	Hit.MeshCol = D3DXVECTOR4(0.0f,0.0f,1.0f,0.5f);
	Eye.Type(x_cube);
	Eye.drawSkip = TRUE;
	Eye.MeshCol = D3DXVECTOR4(0.0f,1.0f,0.0f,0.5f);
	At.Type(x_cube);
	At.drawSkip = TRUE;
	At.MeshCol = D3DXVECTOR4(1.0f,0.0f,0.0f,0.5f);
}

VOID CamFix::Update()
{
	At.drawSkip  = Hit.drawSkip;
	Eye.drawSkip = Hit.drawSkip;
	if(Hit.ShadowFlag)
	{
		if(Hit.HitObj.Reaction == 1)
		{
			ML->E.cam.Eye = Eye.objPos;
			ML->E.cam.At = At.objPos;
		}
	}
} 
//�Œ�J�����͈͎w��Ȃ�
const TCHAR* CamFixFree::name(){return _T("CamFixFree");}
CamFixFree::CamFixFree()
{
	Init();
}
CamFixFree::CamFixFree(D3DXVECTOR3* eye,D3DXVECTOR3* at)
{
	Init();
	At.objPos = *at;
	Eye.objPos = *eye;	
}
VOID CamFixFree::Init()
{
	
	Msh.push_back(&Eye);
	Msh.push_back(&At);
	Eye.Type(x_cube);
	Eye.drawSkip = TRUE;
	Eye.MeshCol = D3DXVECTOR4(0.0f,1.0f,0.0f,0.5f);
	At.Type(x_cube);
	At.drawSkip = TRUE;
	At.MeshCol = D3DXVECTOR4(1.0f,0.0f,0.0f,0.5f);
	
}
VOID CamFixFree::Update()
{
	ML->E.cam.Eye = Eye.objPos;
	ML->E.cam.At = At.objPos;
}

//�ǔ��J����
const TCHAR* CamChar::name(){return _T("CharCam");}
CamChar::CamChar()
{

	Msh.push_back(&pCam);
	pCam.Type(x_cube);
	pCam.drawSkip = TRUE;
}
CamChar::CamChar(D3DXVECTOR3* Pos)
{
	Msh.push_back(&pCam);
	pCam.Type(x_cube);
	pCam.drawSkip = TRUE;
	pCam.objPos = *Pos;
}

VOID CamChar::Set()
{
	ML->E.cam.At = P->FM.Pos;
}
VOID CamChar::Update()
{
	//�J�����̒����_�ƃL�����̈ʒu��������ăS���Ђ��ɂ���
	D3DXVECTOR3 Vec(P->obj.objPos - ML->E.cam.At);//(��ʒu-���݈ʒu)
	float Ln = D3DXVec3LengthSq(&Vec);
	D3DXVec3Normalize(&Vec,&Vec);
	Vec *= Ln * 0.02f;//�����̊���
	ML->E.cam.At	+= Vec;
	ML->E.cam.Eye = ML->E.cam.At + pCam.objPos;	
}