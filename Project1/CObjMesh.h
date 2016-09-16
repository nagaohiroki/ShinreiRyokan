#pragma once
//���b�V��
class CObjMesh
{
private:
	std::vector<std::map<int,CTexture*>::iterator> itT,itNT;

int MdlType;// �I�u�W�F�N�g�̃��f���̎��
	MyLibrary* ML;
	VOID MeshDraw();
	VOID ShadowDraw();
	VOID UpdateMat();//�s����X�V
	VOID SetSp();
	VOID SetObb();	
public:
	std::map<int,CModel*>::iterator itMod;
	
	D3DXVECTOR3	objPos;//���W
	D3DXVECTOR3 objScal;//�X�P�[���̔{��
	D3DXVECTOR3 YPR;//���[�s�b�`���[��
	D3DXVECTOR4 MeshCol;	
	D3DXVECTOR4 SpCol;//�X�y�L�����[�̐F
	D3DXVECTOR4 BloomColor;//���C�g�u���[��
	D3DXMATRIX *mCustom;//�s����ʂɐݒ肷��ꍇ
	D3DXMATRIX  mWorld;//�s�񌋉�
	const D3DXMATRIX* Pare;//�e�I�u�W�F�N�g 
	BOOL drawSkip;//�h���[���X�L�b�v����
	BOOL ShadowFlag;//�V���h�E�}�b�v�t���O
	float SpColm;//�X�y�L�����̂��炳
	float Amb;//�A�r�G���g�J���[�̖��邳
	float Shadow;//�e�̔���
	float Bias;//�e�̃o�C�A�X	
	float Height;//�@���̍���	
	OBB HitObj;//�����蔻��X�e�[�^�X

	CObjMesh();
	virtual ~CObjMesh();	
	VOID SetSize(MyLibrary*);
	VOID draw(MyLibrary*);
	VOID Type(arc);
	VOID SetPare(const D3DXMATRIX* );	

	VOID SetHit(MyLibrary*);
	VOID HitMode(COLLISION_TYPE,COLLISION_BACK);
};