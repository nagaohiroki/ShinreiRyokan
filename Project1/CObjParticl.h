#pragma once


//�p�[�e�B�N��
class CParticl
{
public:	
	float timeLine;//�^�C�����C��
	float OverTime;//���ł܂ł̎���
	D3DXVECTOR3 randVec;//���q���U�炷	
	D3DXVECTOR3 objPos;
	D3DXVECTOR3 objScal;
	float alpha;
	CParticl();
};
class CObjParticl
{
private:
	std::map<int,CTexture*>::iterator it;
	MyLibrary* ML;
	int TexType;
	D3DXMATRIX  mR;//��]�̍s��
	const D3DXMATRIX* Pare;//�e�I�u�W�F�N�g 
	std::vector<CParticl> prt;
	//������Ԃ������͗����͈̔�(�ŏ��͈�,�ő�͈�)
	float randf(float,float);
	//���q�ЂƂ̍X�V
	VOID Update(CParticl*);
public:
	D3DXVECTOR3	objPos;// �r���{�[�h�̍��W
	D3DXVECTOR3 objScal;//�X�P�[���̔{��
	D3DXVECTOR3 YPR;//���[�s�b�`���[��
	D3DXVECTOR4 MeshCol;//���b�V���̐F
	D3DXVECTOR4 BloomColor;
	D3DXMATRIX  mWorld;//�s�񌋉�
	BOOL drawSkip;//�h���[���X�L�b�v����
	float Height;//����
	float Ext;//�L����
	float Speed;//���x
	float PrtTime;//�p������
	CObjParticl();
	virtual ~CObjParticl();
	VOID SetPare(const D3DXMATRIX* );
	VOID SetTex(arc);
	VOID draw(MyLibrary*);
};
