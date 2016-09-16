
GlobalVal::GlobalVal()
{
	ScreenWidth = 0;
	ScreenHeight = 0;
	//�}�E�X�J�[�\���̈ʒu
	mPos = D3DXVECTOR2(0.0f,0.0f) ;
	ClientWidth = 0;
	ClientHeight = 0;
	m_bActive = NULL;
	m_bMiniSize = NULL;
	fps = 0.0f;
	nowTime=0;
	oldTime=0;//���[�v�^�C�����v��
	FCount=0;// �t���[���E�J�E���^

}	
//fps�̌v��
VOID GlobalVal::FPScount()
{
	if(FCount <= 0)
	{
		oldTime = nowTime;
		nowTime = timeGetTime();
		FCount = 10;
	}
	FCount--;
	fps = 10.0f / (nowTime - oldTime) * 1000.0f;
}	
//======================================================
//�Q�[�����C�u����
//======================================================
MyLibrary::MyLibrary()
{
	D=NULL;
	fp = NULL;
}
MyLibrary::~MyLibrary()
{
	SystemSave().Save(&Sd);
	if(fp != NULL)
	{
		fclose(fp);
		fp = NULL;
	}
}
//���Z�b�g�O�ɍs��
HRESULT MyLibrary::Reset()
{	
	if(FAILED(Sf.Reset())){return E_FAIL;}
	if(FAILED(Tx.Reset())){return E_FAIL;}
	if(FAILED(E.Reset())){return E_FAIL;}
	CSMin.Reset();
	return S_OK;
}

//���Z�b�g��ɍs��
HRESULT MyLibrary::Restore()
{	
	//�T�C�Y�̕ύX���������ꍇ
	RECT r;
	GetClientRect(hW,&r);
	GV.ScreenWidth = r.right;
	GV.ScreenHeight = r.bottom;
	if(FAILED(Sf.Restore(D))){return E_FAIL;}
	if(FAILED(Tx.Restore())){return E_FAIL;}
	if(FAILED(E.Restore())){return E_FAIL;}
	return S_OK;
}

//���t���[���X�V
VOID MyLibrary::Update()
{
	//Fps�v��
	GV.FPScount();	
	//�V�F�[�_�̍X�V
	E.UpdateEffect((float)GV.ClientWidth,(float)GV.ClientHeight);
	//�R���g���[��
	C.Update(hW,*GV.m_bActive,*GV.m_bMiniSize);

	float w  = (float)GV.ClientWidth;
	float h  = (float)GV.ClientHeight;	
	float w1 = (float)C.getkey.point.x * (w/(float)GV.ScreenWidth);
	float h1 = (float)C.getkey.point.y * (h/(float)GV.ScreenHeight);
	//�|�C���^�̈ʒu(FVF���)
	GV.mPos.x  = w1 - w / 2.0f;
	GV.mPos.y  = h / 2.0f - h1;


	//���X�i�[
	D3DXVECTOR3 Front;
	D3DXVECTOR3 r;
	D3DXVec3Normalize(&Front,&(E.cam.At - E.cam.Eye));
	D3DXVec3Cross(&r,&Front,&D3DXVECTOR3(0.0f,1.0f,0.0f));
	D3DXVec3Cross(&r,&r,&Front);
	Audio.Audio.x3dLis.Position = E.cam.Eye;
	Audio.Audio.x3dLis.OrientFront = Front;
	Audio.Audio.x3dLis.OrientTop = r;
	//�I�[�f�B�I
	Audio.Update();


}


//���C�u����������
HRESULT MyLibrary::Create(LPDIRECT3DDEVICE9 theDevice,HWND hWnd,HINSTANCE hInst,BOOL* pAct,BOOL* pMin)
{	
	//�n���h���̎擾
	hW = hWnd;
	//�f�o�C�X���擾
	D = theDevice;
	//�N���C�A���g�̎擾
	RECT r;
	GetClientRect(hWnd,&r);
	GV.ClientWidth = r.right;
	GV.ClientHeight = r.bottom;
	GV.ScreenWidth = r.right;
	GV.ScreenHeight = r.bottom;
	GV.m_bActive = pAct;
	GV.m_bMiniSize = pMin;

	//�C���v�b�g�̐���
	if(FAILED(C.Create(hWnd,hInst)))
	{
		return E_FAIL;
	}	
	//�t�H���g
	//�f�o�b�N�p�t�H���g	
	if(FAILED(Tx.Create(theDevice))){return E_FAIL;}
	//Surf
	int w = GV.ClientWidth;
	int h = GV.ClientHeight;
	if(FAILED(Sf.Create(theDevice,SU_MAX))){return E_FAIL;}	
	m_STex[SU_SHADOWMAP].Set(TRUE,1024,1024,0,TRUE,D3DFMT_A8R8G8B8,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f));
	m_STex[SU_TONE].Set(TRUE,w,h,0,TRUE,D3DFMT_A8R8G8B8,&D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f));
	m_STex[SU_HDR].Set(TRUE,w,h,1,FALSE,D3DFMT_A8R8G8B8,&D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f));
	m_STex[SU_GAUSSX].Set(TRUE,w/4,h/4,0,FALSE,D3DFMT_A8R8G8B8,&D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f));
	m_STex[SU_GAUSSY].Set(TRUE,w/4,h/4,0,FALSE,D3DFMT_A8R8G8B8,&D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f));

	m_STex[SU_MIRROR].Set(TRUE,512,512,0,TRUE,D3DFMT_A8R8G8B8,&D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f));
	
	if(FAILED(Sf.Load(D,m_STex))){return E_FAIL;}	
	//FVF	
	if(FAILED(F.Create(theDevice))){return E_FAIL;}
	if(FAILED(FMirror.Create(theDevice))){return E_FAIL;}

	//�G�t�F�N�g
	char* ptr = NULL;
	TCHAR Cur[MAX_PATH];
	TCHAR Path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,Cur);//�J�����g�t�H���_
	_stprintf_s(Path,MAX_PATH,_T("%s\\data.dat"),Cur);//�t�@�C���p�X
	if(_tfopen_s(&fp,Path,_T("rb")) != NULL)
	{
		CFile().Debug(_T("�A�[�J�C�u�t�@�C���I�[�v�����s\n"));
		return E_FAIL;
	}
	ptr = new char[af.af[cfx_main_hlsl].size];
	fseek(fp,af.af[cfx_main_hlsl].point, SEEK_SET);
	fread(ptr,sizeof(char),af.af[cfx_main_hlsl].size,fp);	
	if(FAILED(E.Create(theDevice,ptr,af.af[cfx_main_hlsl].size)))
	{
		return E_FAIL;
	}	
	SAFE_DELETE(ptr);	
	//XAudio2
	if(FAILED(Audio.Create())){return E_FAIL;}
	return S_OK;
}
//�V�X�e���f�[�^���X�V
VOID MyLibrary::UpdateSys()
{
	Audio.Audio.Volume = Sd.Volume;

	E.Tone.z = 4.0f + Sd.Lum;
}
