#pragma once
//===========================================
//�t�B�[���h�̊��I�u�W�F�N�g
//===========================================
class Scene
{
private:
	//�f�o�b�O�p�ϐ�====
	//�G�f�B�^����
	int m_iHir;	
	//�C�x���g�̑I��
	int m_iEvent;
	CObjMesh HitEriaObj[6];
	//=================

	//Get�ŕԂ��q
	int m_iSelect;	
	//�q�I�u�W�F�N�g
	std::vector<Scene*> m_pChild;
	//���ʂ̓����蔻��
	std::vector<Plane> Pl;
	
	//�g��Ȃ��q���폜
	VOID DeleteField();
	//�O���I�u�W�F�N�g�Z�b�g
	VOID Main_Set(Personal*,MyLibrary*);
	//�X�V
	VOID Main_Update();	
	//3D�I�u�W�F�N�g�`��
	VOID Mat_draw();
	//2D�I�u�W�F�N�g�`��
	VOID UI_draw();
	//2�����킹���`��
	VOID Main_draw();
	//���C�����[�v
	VOID Main_Loop(DebugButton*);
	//�t�B�[���h��W�J
	VOID Main(Personal*,MyLibrary*,DebugButton*);
	//�{�^���f�o�b�O
	VOID Main_Debug(DebugButton*);
protected:		
	//�e�I�u�W�F�N�g
	Scene* m_pPare;	
 	//�Q�ƃI�u�W�F�N�g
	Personal  *P;	
	MyLibrary *ML;
	//���z�֐�
	virtual VOID Set();
	virtual VOID Update();
	virtual VOID draw();
	virtual VOID UI();
	virtual VOID DebugText(TCHAR*,int);
	virtual VOID DebugBtn(DebugButton*);
	virtual const TCHAR* name();//�N���X�̖��O	
	//�ǂ̓����蔻��
	VOID EriaHit(D3DXVECTOR3*,D3DXVECTOR3*);

	
	//�I�u�W�F�N�g�̎擾
	Scene* NewObj(Scene*);	
public:
	//�t�B�[���h�J��
	VOID FldChange(Scene*,D3DXVECTOR3*,float);
	//�q�b�g�I�u�W�F�N�g
	std::vector<CollObj*> HitObj;
	//�R���X�g���N�^
	Scene();
	//�f�X�g���N�^
	virtual ~Scene();	
	//�q��ǉ�
	VOID AddField(Scene*);
	//�I�΂ꂽ�q��W�J
	VOID Begin(Personal*,MyLibrary*,DebugButton*);
	//=================================================
	//EventOnly
	//=================================================
private:
	//�I�u�W�F�N�^�C�v�̑I��
	int m_iObjType;
	//�I�u�W�F�N�g�̎q��I��
	int m_iObjNum;
	//�I�u�W�F�N�g
	VOID Obj_Set(Personal*,MyLibrary*);
	VOID Obj_Update();
	VOID Obj_UI();
	VOID Obj_Draw();	
	VOID Obj_Debug(DebugButton*);	
protected:

public:		
	//���ʂ̓����蔻��
	std::vector<CObjMesh*> Msh;	
	std::vector<CObjFVF*> Fvf;
	std::vector<CObjFVF*> Ui;
	std::vector<CObjParticl*> Prt;
	std::vector<CObjSound*> Snd;
	std::vector<CObjText*> UiTxt;
	std::vector<CObjText*> Txt;
	//�����蔻��----------------------------------------
	//�����蔻��(�ڐG�̐���)
	BOOL HitObjFlag(size_t);
	//�I�u�W�F�N�g��Ԃ�
	CObjMesh* Ob();//�ŏ��̃I�u�W�F�N�g��Ԃ�	
	CObjMesh* Ob(int);//�ŏ��̃I�u�W�F�N�g��Ԃ�	


};