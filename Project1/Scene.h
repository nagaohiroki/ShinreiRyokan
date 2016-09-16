#pragma once
//===========================================
//フィールドの基底オブジェクト
//===========================================
class Scene
{
private:
	//デバッグ用変数====
	//エディタ項目
	int m_iHir;	
	//イベントの選択
	int m_iEvent;
	CObjMesh HitEriaObj[6];
	//=================

	//Getで返す子
	int m_iSelect;	
	//子オブジェクト
	std::vector<Scene*> m_pChild;
	//平面の当たり判定
	std::vector<Plane> Pl;
	
	//使わない子を削除
	VOID DeleteField();
	//外部オブジェクトセット
	VOID Main_Set(Personal*,MyLibrary*);
	//更新
	VOID Main_Update();	
	//3Dオブジェクト描画
	VOID Mat_draw();
	//2Dオブジェクト描画
	VOID UI_draw();
	//2つをあわせた描画
	VOID Main_draw();
	//メインループ
	VOID Main_Loop(DebugButton*);
	//フィールドを展開
	VOID Main(Personal*,MyLibrary*,DebugButton*);
	//ボタンデバッグ
	VOID Main_Debug(DebugButton*);
protected:		
	//親オブジェクト
	Scene* m_pPare;	
 	//参照オブジェクト
	Personal  *P;	
	MyLibrary *ML;
	//仮想関数
	virtual VOID Set();
	virtual VOID Update();
	virtual VOID draw();
	virtual VOID UI();
	virtual VOID DebugText(TCHAR*,int);
	virtual VOID DebugBtn(DebugButton*);
	virtual const TCHAR* name();//クラスの名前	
	//壁の当たり判定
	VOID EriaHit(D3DXVECTOR3*,D3DXVECTOR3*);

	
	//オブジェクトの取得
	Scene* NewObj(Scene*);	
public:
	//フィールド遷移
	VOID FldChange(Scene*,D3DXVECTOR3*,float);
	//ヒットオブジェクト
	std::vector<CollObj*> HitObj;
	//コンストラクタ
	Scene();
	//デストラクタ
	virtual ~Scene();	
	//子を追加
	VOID AddField(Scene*);
	//選ばれた子を展開
	VOID Begin(Personal*,MyLibrary*,DebugButton*);
	//=================================================
	//EventOnly
	//=================================================
private:
	//オブジェクタイプの選択
	int m_iObjType;
	//オブジェクトの子を選択
	int m_iObjNum;
	//オブジェクト
	VOID Obj_Set(Personal*,MyLibrary*);
	VOID Obj_Update();
	VOID Obj_UI();
	VOID Obj_Draw();	
	VOID Obj_Debug(DebugButton*);	
protected:

public:		
	//平面の当たり判定
	std::vector<CObjMesh*> Msh;	
	std::vector<CObjFVF*> Fvf;
	std::vector<CObjFVF*> Ui;
	std::vector<CObjParticl*> Prt;
	std::vector<CObjSound*> Snd;
	std::vector<CObjText*> UiTxt;
	std::vector<CObjText*> Txt;
	//当たり判定----------------------------------------
	//当たり判定(接触の是非)
	BOOL HitObjFlag(size_t);
	//オブジェクトを返す
	CObjMesh* Ob();//最初のオブジェクトを返す	
	CObjMesh* Ob(int);//最初のオブジェクトを返す	


};