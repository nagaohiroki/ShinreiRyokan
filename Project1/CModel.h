#pragma once
//===================================================
//新しいアニメーションキー
//===================================================
class gt_Anim
{	
protected:
	typedef D3DXVECTOR3 _V;//長いから短く
	typedef D3DXVECTOR3 v;//長いから短く
	VOID s(int,v*,v*,v*,v*,v*,v*,v*,v*,v*,v*,v*,v*);
public:
	enum G_ANIM
	{	//GRが回転、GPが位置
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
	//キーの最大数
	int MaxKey();

};
//待機
class gt_Wait : public gt_Anim
{
public:	gt_Wait();
};
//歩き
class gt_Walk : public gt_Anim
{
public:	gt_Walk();
};
//走り
class gt_Run : public gt_Anim
{
public:	gt_Run();
};
//飲み
class gt_Drink : public gt_Anim
{
public:	gt_Drink();
};
//投げ
class gt_Throw : public gt_Anim
{
public:	gt_Throw();
};
//===================================================
//モデル
//===================================================
class gt_Model
{
private:	
	std::vector<CObjMesh*> all;
	//モーション
	std::vector<gt_Anim*> Anim; 
	VOID aSet(gt_Anim*,int);    
public:
	//食塩水
	CObjMesh drug;
	BOOL SoltFlag;
	//懐中電灯オック
	BOOL FlashLock;
	//懐中電灯フラグ
	BOOL FlashFlag;
	//懐中電灯
	flashlight fl;
	//各オブジェクト
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
	//描画許可
	BOOL drawSkip;
	//モーションをストップさせる
	BOOL Stop;
	//キーフレーム
	int KeyFrame;	
	//アニメーションの種類
	int MotionType;
	//モーションのスピード
	int speed;
	//モーションのスローモー
	int slow;
	gt_Model();
	virtual ~gt_Model();
	VOID Update(MyLibrary*);
	VOID Set(MyLibrary*);
	VOID draw(MyLibrary*);
	VOID MotionCreate(DebugButton*,MyLibrary *);
	VOID MeshCol(D3DXVECTOR4*);
	VOID SpcCol(D3DXVECTOR4*,float);
	int MaxKey(gt_Anim::Motion);//最大キー
	VOID DebugText(TCHAR*,int);
};

