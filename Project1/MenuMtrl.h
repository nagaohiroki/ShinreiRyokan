#pragma once
enum MENU_PAGE
{
	MP_MAIN,
	MP_ITEM,
	MP_SAVE,
	MP_OPTION,
	MP_END,
};
//���j���[�f��
class MenuMtrl
{
	int UpdateSelect();
	AKey<float>	alpha;
	
	//�ύX���������ꍇ
	int PreSelect;
	int PreSp;
	enum SLCT_MAX{SMAX = 3};
	CObjSound slct[SMAX];
	
public:
	int Key;
	VOID SelectSE();
	//�I����
	int Select;
	int SelectMode;
	//���ڂ̑I��
	int Sp;
	//���͑҂�
	BOOL Wait;
	//�Q�ƃI�u�W�F�N�g
	BOOL Check;
	BOOL Cansel;
	BOOL Close;
	MyLibrary* ML;
	FlagManager* FM;	
	//���݃y�[�W
	MENU_PAGE Page;
	//�I�u�W�F�N�g
	CObjText Title;//�^�C�g��
	CObjText info;//����
	CObjText Cell;//����
	CObjText tSelect;//�I����
	CObjText CtrlOpe;//�������

	//�I�u�W�F�N�g
	CObjFVF BackGround;//�w�i
	CObjFVF Choice;//�I��
	CObjFVF bgBlackL;//�����o�b�N
	CObjFVF bgBlackM;//�����o�b�NM
	//�I����
	CObjFVF SlctBg;//�I�����̃o�b�N�O�����h
	CObjFVF Slct;//�I�����̃o�b�N�O�����h
	//�R���X�g���N�^
	MenuMtrl();
	//���͑҂��̃Z�b�g
	VOID SetWait();
	//�Z�b�g
	VOID Set(MyLibrary*,FlagManager*);
	//�X�V
	VOID Update(BOOL,BOOL,BOOL);
	int UpdateMenu();
	
	//�`��	
	VOID draw();
	//�I�������Z�b�g
	VOID SetSelect();
	//�I�����̌��ʂ�������
	BOOL GetSelect(int);

	VOID Debug(TCHAR*,int);
};
