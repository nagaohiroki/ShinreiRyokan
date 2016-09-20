#pragma once
//======================================================
//�Q�[�����C�u����
//======================================================
enum SURFACE
{
	SU_SHADOWMAP,
	SU_TONE,
	SU_HDR,
	SU_GAUSSX,
	SU_GAUSSY,
	SU_MIRROR,
	SU_MAX,
};
//�O���[�o���ϐ��̑���
class GlobalVal
{
private:
	DWORD nowTime;
	DWORD oldTime;//���[�v�^�C�����v��
	int FCount;// �t���[���E�J�E���^
public:
	//�A�N�e�B�u���ǂ���
	BOOL *m_bActive;
	//�ŏ�������Ă���ꍇ
	BOOL *m_bMiniSize;
	float fps;	
	//�`��̈�̃T�C�Y
	UINT ClientWidth;
	UINT ClientHeight;
	//�X�N���[���̃T�C�Y
	UINT ScreenWidth;
	UINT ScreenHeight;
	//�}�E�X�J�[�\���̈ʒu
	D3DXVECTOR2 mPos;
	GlobalVal();
	//fps�̌v��
	VOID FPScount();
};

class MyLibrary
{
private:
	//�T�[�t�F�C�X
	CSTexState m_STex[SU_MAX];
public:	
	//�V�X�e���f�[�^
	SystemData Sd;
	//�A�C�e�����X�g
	CItemList itemList;
	HWND hW;
	LPDIRECT3DDEVICE9 D;
	CollParfect Col;
	DirectIn C;
	GlobalVal GV;
	CEffect	 E;
	CSoundManager Audio;
	CTextureManager T;
	CModelManager M;
	CString	 CSMin;
	FVF		 F;
	FVFMirror	 FMirror;

	CText	 Tx;
	CSurf	 Sf;
	Arc_Files af;
	FILE *fp;
	MyLibrary();
	virtual ~MyLibrary();
	HRESULT Reset();
	HRESULT Restore();
	VOID Update();
	HRESULT Create(LPDIRECT3DDEVICE9,HWND,HINSTANCE,BOOL*,BOOL*);

	//�V�X�e���f�[�^���X�V
	VOID UpdateSys();

};
