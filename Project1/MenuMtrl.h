#pragma once
enum MENU_PAGE
{
	MP_MAIN,
	MP_ITEM,
	MP_SAVE,
	MP_OPTION,
	MP_END,
};
//メニュー素材
class MenuMtrl
{
	int UpdateSelect();
	AKey<float>	alpha;
	
	//変更があった場合
	int PreSelect;
	int PreSp;
	enum SLCT_MAX{SMAX = 3};
	CObjSound slct[SMAX];
	
public:
	int Key;
	VOID SelectSE();
	//選択肢
	int Select;
	int SelectMode;
	//項目の選択
	int Sp;
	//入力待ち
	BOOL Wait;
	//参照オブジェクト
	BOOL Check;
	BOOL Cansel;
	BOOL Close;
	MyLibrary* ML;
	FlagManager* FM;	
	//現在ページ
	MENU_PAGE Page;
	//オブジェクト
	CObjText Title;//タイトル
	CObjText info;//説明
	CObjText Cell;//項目
	CObjText tSelect;//選択肢
	CObjText CtrlOpe;//操作説明

	//オブジェクト
	CObjFVF BackGround;//背景
	CObjFVF Choice;//選択
	CObjFVF bgBlackL;//文字バック
	CObjFVF bgBlackM;//文字バックM
	//選択肢
	CObjFVF SlctBg;//選択肢のバックグランド
	CObjFVF Slct;//選択肢のバックグランド
	//コンストラクタ
	MenuMtrl();
	//入力待ちのセット
	VOID SetWait();
	//セット
	VOID Set(MyLibrary*,FlagManager*);
	//更新
	VOID Update(BOOL,BOOL,BOOL);
	int UpdateMenu();
	
	//描画	
	VOID draw();
	//選択肢をセット
	VOID SetSelect();
	//選択肢の結果をかえす
	BOOL GetSelect(int);

	VOID Debug(TCHAR*,int);
};
