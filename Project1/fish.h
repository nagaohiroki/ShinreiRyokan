#pragma once
//===================================
//�A�j���[�V�������
//===================================
class fish_anim
{
protected:
	typedef D3DXVECTOR3 v;
	VOID s(int,v*,v*,v*,v*,v*,v*,v*,v*,v*,v*);
public:
	//���[�V�����̎��
	enum FISH_MOT
	{
		FM_WAIT,
		FM_WALK,
		FM_ATTACK,
		FM_DEATH,
	
		FM_EDIT,
	};
	//�ғ�����
	enum FISH_ACT
	{
		FAP_BODY2,
		FAR_BODY2,
		FAR_BODY,
		FAR_HEAD,
		FAR_L_NINO,
		FAR_R_NINO,
		FAR_L_HAND,
		FAR_R_HAND,
		FAR_L_ASI,
		FAR_R_ASI,
		FA_MAX,
	};
	AKey<D3DXVECTOR3> anim[FA_MAX];
	fish_anim();
	int MaxKey();
};
//===================================
//�e���[�V����
//===================================
//�ҋ@���[�V����
class fish_wait : public fish_anim
{
public:	fish_wait();
};
//���s���[�V����
class fish_walk : public fish_anim
{
public:	fish_walk();
};
//�U�����[�V����
class fish_attack : public fish_anim
{
public:	fish_attack();
};
//�E�Q���[�V����
class fish_death : public fish_anim
{
public:	fish_death();
};
//===================================
//�����f��
//===================================
class Fish
{
	
	//���[�V����
	std::vector<fish_anim*> aBase;
	//���[�V�����X�V
	VOID AnimUpdate(fish_anim*,int);
public:
	//�I�u�W�F�N�g���܂Ƃ߂�
	std::vector<CObjMesh*> all;
	int HP;
	//�`��
	BOOL drawSkip;
	//�t���[���X�V�X�g�b�v
	BOOL Stop;
	//���[�V�����̃X�s�[�h
	int speed;
	//���[�V�����̃X���[���[
	int slow;
	//���[�V�����^�C�v
	int MotType;
	//�t���[��
	int frame;
	//�e�p�[�c
	CObjMesh Null;
	CObjMesh head;
	CObjMesh body;
	CObjMesh body2;
	CObjMesh L_nino;
	CObjMesh R_nino;
	CObjMesh L_hand;
	CObjMesh R_hand;
	CObjMesh L_asi;
	CObjMesh R_asi;

	enum{RING_MAX = 5};
	CObjMesh Ring[RING_MAX];
	//�R���X�g���N�^
	Fish();
	//�f�X�g���N�^
	virtual ~Fish();
	//�X�V
	VOID Update(MyLibrary*);
	//�`��
	VOID draw(MyLibrary*);
	//���b�V���J���[
	VOID MeshCol(D3DXVECTOR4*);
	//�u���[���J���[
	VOID Bloom(D3DXVECTOR4*);
	//�X�y�L�����J���[
	VOID Sp(D3DXVECTOR4*,float);
	//�f�o�b�O
	VOID DebugBtn(DebugButton*,MyLibrary*);
};
