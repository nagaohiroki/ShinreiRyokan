#pragma once
//===================================================
//�V�����A�j���[�V�����L�[
//===================================================
class gt_Anim
{	
protected:
	typedef D3DXVECTOR3 _V;//��������Z��
	typedef D3DXVECTOR3 v;//��������Z��
	VOID s(int,v*,v*,v*,v*,v*,v*,v*,v*,v*,v*,v*,v*);
public:
	enum G_ANIM
	{	//GR����]�AGP���ʒu
		GR_NECK,
		GR_BODY,
		GR_BODY2,
		GP_BODY2,
		GR_L_NINO,
		GR_R_NINO,
		GR_L_HAND,
		GR_R_HAND,
		GR_L_MOMO,
		GR_R_MOMO,
		GR_L_ASI,
		GR_R_ASI,
		G_END,
	};
	enum Motion
	{
		Motion_Wait,
		Motion_Walk,
		Motion_Run,
		Motion_Drink,
		Motion_Throw,
		Motion_Edit,
	};
	AKey<D3DXVECTOR3> Ak[G_END];
	gt_Anim();
	//�L�[�̍ő吔
	int MaxKey();

};
//�ҋ@
class gt_Wait : public gt_Anim
{
public:	gt_Wait();
};
//����
class gt_Walk : public gt_Anim
{
public:	gt_Walk();
};
//����
class gt_Run : public gt_Anim
{
public:	gt_Run();
};
//����
class gt_Drink : public gt_Anim
{
public:	gt_Drink();
};
//����
class gt_Throw : public gt_Anim
{
public:	gt_Throw();
};
//===================================================
//���f��
//===================================================
class gt_Model
{
private:	
	std::vector<CObjMesh*> all;
	//���[�V����
	std::vector<gt_Anim*> Anim; 
	VOID aSet(gt_Anim*,int);    
public:
	//�H����
	CObjMesh drug;
	BOOL SoltFlag;
	//�����d���I�b�N
	BOOL FlashLock;
	//�����d���t���O
	BOOL FlashFlag;
	//�����d��
	flashlight fl;
	//�e�I�u�W�F�N�g
	CObjMesh Null;	
	CObjMesh neck;
	CObjMesh head;
	CObjMesh body;
	CObjMesh body2;
	CObjMesh L_nino;
	CObjMesh R_nino;
	CObjMesh L_hand;
	CObjMesh R_hand;
	CObjMesh L_momo;
	CObjMesh R_momo;
	CObjMesh L_asi;
	CObjMesh R_asi;
	//�`�拖��
	BOOL drawSkip;
	//���[�V�������X�g�b�v������
	BOOL Stop;
	//�L�[�t���[��
	int KeyFrame;	
	//�A�j���[�V�����̎��
	int MotionType;
	//���[�V�����̃X�s�[�h
	int speed;
	//���[�V�����̃X���[���[
	int slow;
	gt_Model();
	virtual ~gt_Model();
	VOID Update(MyLibrary*);
	VOID Set(MyLibrary*);
	VOID draw(MyLibrary*);
	VOID MotionCreate(DebugButton*,MyLibrary *);
	VOID MeshCol(D3DXVECTOR4*);
	VOID SpcCol(D3DXVECTOR4*,float);
	int MaxKey(gt_Anim::Motion);//�ő�L�[
	VOID DebugText(TCHAR*,int);
};

