#pragma once
//追尾アンカー
class Anchor
{
public:
	BOOL use;
	D3DXVECTOR3 Pos;
	Anchor* pNextAnc;
	Anchor();
};
//敵
class Enemy : public Scene
{
private:
	int flow;
	float speed;
	//首の向き
	float neck;
	float body;
	//線分の当たり判定
	BOOL Line;
	//パーティクル
	CObjParticl part;
	//BGM
	CObjSound bgm;
	//se
	CObjSound voice;
	//攻撃カウント
	BOOL AtFlag;
	int AtCount;
	D3DXVECTOR3 Atvec;
	//被弾中フラグ
	int Muteki;
	//魚
	Fish fish;
	//デバッグ表示用オブジェクト
	int annum;
	CObjMesh an;
	//敵が追いかけるアンカー
	Anchor* stalkAnc;
	//線分の端
	Anchor* EyeAnc;
	//見失う地点のアンカー
	std::vector<Anchor*> pAnc;
	//当たり判定用オブジェクト(フィールド)
	CObjMesh EriaHit;
	//弾当たり判定
	CObjMesh BulletHit;
	//強さ
	VOID Strength(int);
	//首振り
	VOID AngleNeck(float);
	//線分とエリアの当たり判定
	BOOL EyeHit(Segmet*);
	//敵を追う
	VOID ModeStalking();
	//敵を探す
	VOID ModeSearch();
	//死亡中
	VOID ModeDead();
	//当たり判定
	VOID ModeGameOver();
	//生存中
	VOID ModeHit();
	//攻撃
	VOID ModeAttack();
	//歩行
	VOID ModeManual();
	
public:
	enum MODE
	{
		MODE_CLEAR,
		MODE_SEARCH,
		MODE_STALK_ATTACK,
		MODE_STALK,
		MODE_GAMEOVER,
		MODE_DEAD,
		MODE_REMOVE,
		MODE_MANUAL,


	};
	Enemy();
	virtual ~Enemy();
	const TCHAR* name();
	VOID Set();
	VOID Update();
	VOID draw();
	VOID DebugText(TCHAR* ,int);
	VOID DebugBtn(DebugButton*);
};