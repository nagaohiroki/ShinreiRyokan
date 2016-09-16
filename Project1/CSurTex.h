#pragma once

class CSurTex
{
private:
	LPDIRECT3DSURFACE9 m_pTexSurface;//�e�N�X�`������擾����T�[�t�F�[�X	
	LPDIRECT3DSURFACE9 m_pTexZ;		 //�e�N�X�`���p��Z �o�b�t�@�[

	UINT W,H;
	D3DFORMAT Fmt;
	BOOL Z;

public:
	LPDIRECT3DTEXTURE9 m_pSurfTex;	 //�Ԃ��悤
	//�R���X�g���N�^
	CSurTex();
	//�f�X�g���N�^
	virtual ~CSurTex();
	//���Z�b�g
	VOID Reset();
	//���X�g�A
	HRESULT Restore(LPDIRECT3DDEVICE9);
	//�T�[�t�F�C�X�J�n
	HRESULT Begin(LPDIRECT3DDEVICE9,int,D3DXVECTOR4*);
	//�쐬(dev,Z�o�b�t�@�̗L��,��,�c,�t�H�[�}�b�g
	HRESULT Create(LPDIRECT3DDEVICE9,BOOL,UINT,UINT,D3DFORMAT);
};