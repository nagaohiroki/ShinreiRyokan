#pragma once//�w�b�_�[�̏d���h�~
//=============================================================================
//�}���`�����_�����O�^�[�Q�b�g
//=============================================================================
//�T�[�t�F�C�X�̃X�e�[�^�X
class CSTexState
{
public:
	BOOL		m_bUse;
	UINT        m_uiW;
	UINT        m_uiH;
	int         m_iPass;
	BOOL        m_bZ;
	D3DFORMAT   m_Fmt;
	D3DXVECTOR4 m_vColor;	
	CSTexState();
	VOID Set(BOOL,UINT,UINT,int,BOOL,D3DFORMAT,D3DXVECTOR4*);
};
//�T�[�t�F�C�X�̗v�f
class CSTex
{
private:
	LPDIRECT3DSURFACE9 m_pTexSurface;//�e�N�X�`������擾����T�[�t�F�[�X	
	LPDIRECT3DSURFACE9 m_pTexZ;		 //�e�N�X�`���p��Z �o�b�t�@�[
	LPDIRECT3DTEXTURE9 m_pSurfTex;	 //�Ԃ��悤
public:
	CSTexState* m_pState;
	CSTex();
	virtual ~CSTex();
	HRESULT Set(LPDIRECT3DDEVICE9,CSTexState*);
	HRESULT Begin(LPDIRECT3DDEVICE9);
	VOID Reset();
	HRESULT Restore(LPDIRECT3DDEVICE9);
	LPDIRECT3DTEXTURE9 Retex();	
};
//�T�[�t�F�C�X
class CSurf
{
private:
	LPDIRECT3DSURFACE9 m_pBackbuffer;//�o�b�N�o�b�t�@
	LPDIRECT3DSURFACE9 m_pBackZ;	 //�o�b�N�o�b�t�@�p��Z�o�b�t�@�[
public:	
	int m_iNum;
	CSTex** m_ppCSTex;
	CSurf();
	virtual ~CSurf();
	HRESULT Create(LPDIRECT3DDEVICE9,int);//�쐬
	HRESULT End(LPDIRECT3DDEVICE9);//�T�[�t�F�C�X�I��
	HRESULT Reset();//���Z�b�g
	HRESULT Restore(LPDIRECT3DDEVICE9);//���Z�b�g��擾
	HRESULT Begin(int,LPDIRECT3DDEVICE9);//�T�[�t�F�C�X�J�n
	LPDIRECT3DTEXTURE9 Retex(int);//�e�N�X�`����Ԃ�
	HRESULT Load(LPDIRECT3DDEVICE9,CSTexState*);//�f�[�^�̃��[�h�Ɣj��
};