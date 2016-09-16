#pragma once
//==========================================================
//メニュー
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
//メインメニュー
//==========================================================
class MainPage : public MenuPage
{
public:
	MainPage();
	int Update(MenuMtrl*);
};
//==========================================================
//アイテム欄
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
//セーブ
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
//オプション
//==========================================================
class SeekBer
{
	CObjFVF ber;
	CObjFVF mater;//メーター	
	BOOL Hit2D(D3DXVECTOR2*,D3DXVECTOR2*,D3DXVECTOR2*);//FVFの当たり判定
	
public:
	BOOL Hold;//クリックした
	SeekBer();
	//シークの更新(ml,変更する値,位置,バーのサイズ,最小値,最大値) 
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
	//解像度
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
//メニュー画面
//==========================================================
class Menu
{
private:
	BOOL drawFlag;
	MenuMtrl mm;
	MainPage PgMain;//メインページ
	ItemPage PgItem;//アイテム欄
	SavePage PgSave;//セーブ
	OptionPage PgOption;//設定変更
	std::vector<MenuPage*> vecPage;
public:
	Menu();
	VOID Set(MyLibrary*,FlagManager*);
	VOID CloseMenu();
	int Update(BOOL,BOOL,BOOL);
	VOID draw();
	VOID DebugText(TCHAR*,int);
};