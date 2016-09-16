#pragma once
//�e�N�X�`���f�[�^
class CTexture
{
private:	
public:	
	//�g�p��
	int m_iCount;
	//�e�N�X�`��
	LPDIRECT3DTEXTURE9 m_pTex;
	//�R���X�g���N�^
	CTexture();
	//�f�X�g���N�^
	virtual ~CTexture();
	//�쐬
	HRESULT Create(int,LPDIRECT3DDEVICE9,Arc_Files*,FILE*);
	//�J�E���g�����炷1�ȉ��Ȃ�j��
	int Release();	
};

class CTextureManager
{
	typedef std::map<int,CTexture*> mapc;
	
public:
	mapc tex;
	//�R���X�g���N�^
	CTextureManager();
	//�f�X�g���N�^
	virtual ~CTextureManager();
	//�e�N�X�`���̓ǂݍ���(���łɂ���ꍇ�̓J�E���g�𑝂₷)
	HRESULT Load(int,LPDIRECT3DDEVICE9,Arc_Files*,FILE*);

	mapc::iterator load(int,LPDIRECT3DDEVICE9,Arc_Files*,FILE*);
	//�J�E���g�����炷1�ȉ��Ȃ�j��
	VOID Release(int);	
	//�f�o�b�O
	VOID Debug(TCHAR*,int,Arc_Files*);
	//�e�N�X�`����Ԃ�
	LPDIRECT3DTEXTURE9 Retex(int);
};
