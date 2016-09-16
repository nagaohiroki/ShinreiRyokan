#pragma once
//=============================================================================
//FVF�ݒ�
//=============================================================================
//FVF
class FVF
{
private:
	//FVF�̃^�C�v
	enum{ FVF_CUSTOM = D3DFVF_XYZ| D3DFVF_TEX1 };
	//���_�o�b�t�@
	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;
	//���_�o�b�t�@�̍쐬
	HRESULT CreateVertex(LPDIRECT3DDEVICE9);
protected:
	//�o�b�t�@�̃X�e�[�^�X
	struct CUSTOMVERTEX
	{	
		float	x,y,z;	//���_�ʒu
		float	u,v;	//�e�N�X�`�����W
	};	
	//�o�b�t�@�̃X�e�[�^�X���Z�b�g����
	virtual HRESULT SetVertex(LPDIRECT3DVERTEXBUFFER9);

public:
	//�R���X�g���N�^
	FVF();
	//�f�X�g���N�^
	virtual ~FVF();
	//�쐬
	HRESULT Create(LPDIRECT3DDEVICE9);
	//�X�g���[��������
	VOID SetStream(LPDIRECT3DDEVICE9);	

};

//====================================================
//�e�N�X�`�����]
//====================================================
class FVFMirror : public FVF
{
public:
	FVFMirror(); 
	HRESULT SetVertex(LPDIRECT3DVERTEXBUFFER9);
};