#pragma once
//===================================
//アニメーション基盤
//===================================
class fish_anim
{
protected:
	typedef D3DXVECTOR3 v;
	VOID s(int,v*,v*,v*,v*,v*,v*,v*,v*,v*,v*);
public:
	//モーションの種類
	enum FISH_MOT
	{
		FM_WAIT,
		FM_WALK,
		FM_ATTACK,
		FM_DEATH,
	
		FM_EDIT,
	};
	//稼動部分
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
//各モーション
//===================================
//待機モーション
class fish_wait : public fish_anim
{
public:	fish_wait();
};
//歩行モーション
class fish_walk : public fish_anim
{
public:	fish_walk();
};
//攻撃モーション
class fish_attack : public fish_anim
{
public:	fish_attack();
};
//殺害モーション
class fish_death : public fish_anim
{
public:	fish_death();
};
//===================================
//魚モデル
//===================================
class Fish
{
	
	//モーション
	std::vector<fish_anim*> aBase;
	//モーション更新
	VOID AnimUpdate(fish_anim*,int);
public:
	//オブジェクトをまとめる
	std::vector<CObjMesh*> all;
	int HP;
	//描画
	BOOL drawSkip;
	//フレーム更新ストップ
	BOOL Stop;
	//モーションのスピード
	int speed;
	//モーションのスローモー
	int slow;
	//モーションタイプ
	int MotType;
	//フレーム
	int frame;
	//各パーツ
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
	//コンストラクタ
	Fish();
	//デストラクタ
	virtual ~Fish();
	//更新
	VOID Update(MyLibrary*);
	//描画
	VOID draw(MyLibrary*);
	//メッシュカラー
	VOID MeshCol(D3DXVECTOR4*);
	//ブルームカラー
	VOID Bloom(D3DXVECTOR4*);
	//スペキュラカラー
	VOID Sp(D3DXVECTOR4*,float);
	//デバッグ
	VOID DebugBtn(DebugButton*,MyLibrary*);
};
