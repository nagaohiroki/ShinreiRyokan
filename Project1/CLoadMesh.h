#pragma once
//�}�e���A��
class CMtrl
{
private:
	//�e�N�X�`���̖��O�Ńe�N�X�`���ԍ���Ԃ�
	int ReTexNum(TCHAR*,Arc_Files* );
public:
	//���f�����̃e�N�X�`���̖��O
	TCHAR TexName[MAX_PATH];
	//�}�e���A��
	D3DMATERIAL9 m_Mtrl;
	//�e�N�X�`���ԍ�
	int m_iTex;
	//�@���e�N�X�`���ԍ�
	int m_iNTex;
	//�G�t�F�N�g�p�X
	int m_iTexPass;
	//�R���X�g���N�^
	CMtrl();
	//�e�N�X�`���̃i���o�[��Ԃ�
	VOID SetTexNum(Arc_Files*);	
};
//���f��
class CModel
{
private:
	
	//�}�e���A���A�e�N�X�`���A�T�C�Y�̎擾
	HRESULT LoadMtrl(LPD3DXBUFFER,LPDIRECT3DDEVICE9,Arc_Files*);	
	//�@���}�b�v�̍쐬
	HRESULT SetNormal(LPDIRECT3DDEVICE9);
public:
	//�g�p��
	int	m_iCount;	
	
	//���b�V���I�u�W�F�N�g
	LPD3DXMESH	m_pMesh;	
	//�}�e���A���̐�
	DWORD		m_dwMatNum;	
	//�G�t�F�N�g�p�X
	int			TexPass;	
	//�ő咸�_
	D3DXVECTOR3	Max;
	//�ŏ����_
	D3DXVECTOR3	Min;
	//�e���a
	D3DXVECTOR3	ren;
	//���̒��S�_
	D3DXVECTOR3	Center;
	//���̔��a
	float		Sren;
	//�}�e���A��
	std::vector<CMtrl> m_pCMtrl;
	//�R���X�g���N�^
	CModel();
	//�f�X�g���N�^
	virtual ~CModel();
	//���f���̓ǂݍ���
	HRESULT LoadModel(LPDIRECT3DDEVICE9,int,Arc_Files*,FILE*);	
	//���f���̃J�E���g
	int Release();
};


class CModelManager
{
private:
	typedef std::map<int,CModel*> mapc;
	mapc Mod;
public:
	CModelManager();
	virtual ~CModelManager();
	mapc::iterator Load(int,LPDIRECT3DDEVICE9,Arc_Files*,FILE*);
	VOID Release(int);
	//�f�o�b�O
	VOID Debug(TCHAR*,int,Arc_Files*);
};
