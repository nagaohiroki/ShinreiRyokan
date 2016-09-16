#pragma once
//==========================================================
//���j���[
//==========================================================
class MenuPage
{
protected:
	virtual int Update(MenuMtrl*);
public:	
	MenuPage();
	virtual ~MenuPage();

	int MainUpdate(MenuMtrl*);	
	virtual VOID draw(MenuMtrl*);
};
//==========================================================
//���C�����j���[
//==========================================================
class MainPage : public MenuPage
{
public:
	MainPage();
	int Update(MenuMtrl*);
};
//==========================================================
//�A�C�e����
//==========================================================
class ItemPage : public MenuPage
{
	enum{ITEMMAX = 200};
	TCHAR t[ITEMMAX];

public:
	ItemPage();
	int Update(MenuMtrl* );
};
//==========================================================
//�Z�[�u
//==========================================================
class SavePage : public MenuPage
{
	int LoadNum;
	BOOL InfoClear;
	enum{FMMAX = 260};
	TCHAR t[FMMAX];
	FlagManager Fm[GameSave::MAX_SAVE];
	BOOL LoadSuc[GameSave::MAX_SAVE];
public:
	SavePage();
	int Update(MenuMtrl*);

};
//==========================================================
//�I�v�V����
//==========================================================
class SeekBer
{
	CObjFVF ber;
	CObjFVF mater;//���[�^�[	
	BOOL Hit2D(D3DXVECTOR2*,D3DXVECTOR2*,D3DXVECTOR2*);//FVF�̓����蔻��
	
public:
	BOOL Hold;//�N���b�N����
	SeekBer();
	//�V�[�N�̍X�V(ml,�ύX����l,�ʒu,�o�[�̃T�C�Y,�ŏ��l,�ő�l) 
	VOID update(MyLibrary*,float*,D3DXVECTOR2*,float,float,float);
	VOID draw(MyLibrary*);
	BOOL Hit(MyLibrary*);
};
class OptionPage : public MenuPage
{
	BOOL HoldPix;
	enum{tn = 1000};
	TCHAR t[tn];
	int k;
	SeekBer volume;
	SeekBer lum;
	//�𑜓x
	int PrePix;
	CObjFVF ber;
	CObjText PixelSize;
	AKey<float>	alpha;
	int Key;
public:
	OptionPage();
	int Update(MenuMtrl*);
	VOID draw(MenuMtrl*);
};
//==========================================================
//���j���[���
//==========================================================
class Menu
{
private:
	BOOL drawFlag;
	MenuMtrl mm;
	MainPage PgMain;//���C���y�[�W
	ItemPage PgItem;//�A�C�e����
	SavePage PgSave;//�Z�[�u
	OptionPage PgOption;//�ݒ�ύX
	std::vector<MenuPage*> vecPage;
public:
	Menu();
	VOID Set(MyLibrary*,FlagManager*);
	VOID CloseMenu();
	int Update(BOOL,BOOL,BOOL);
	VOID draw();
	VOID DebugText(TCHAR*,int);
};