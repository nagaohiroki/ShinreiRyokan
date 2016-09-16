#pragma once


//パーティクル
class CParticl
{
public:	
	float timeLine;//タイムライン
	float OverTime;//消滅までの時間
	D3DXVECTOR3 randVec;//粒子を散らす	
	D3DXVECTOR3 objPos;
	D3DXVECTOR3 objScal;
	float alpha;
	CParticl();
};
class CObjParticl
{
private:
	std::map<int,CTexture*>::iterator it;
	MyLibrary* ML;
	int TexType;
	D3DXMATRIX  mR;//回転の行列
	const D3DXMATRIX* Pare;//親オブジェクト 
	std::vector<CParticl> prt;
	//乱数を返す引数は乱数の範囲(最小範囲,最大範囲)
	float randf(float,float);
	//粒子ひとつの更新
	VOID Update(CParticl*);
public:
	D3DXVECTOR3	objPos;// ビルボードの座標
	D3DXVECTOR3 objScal;//スケールの倍率
	D3DXVECTOR3 YPR;//ヨーピッチロール
	D3DXVECTOR4 MeshCol;//メッシュの色
	D3DXVECTOR4 BloomColor;
	D3DXMATRIX  mWorld;//行列結果
	BOOL drawSkip;//ドローをスキップする
	float Height;//高さ
	float Ext;//広がり
	float Speed;//速度
	float PrtTime;//継続時間
	CObjParticl();
	virtual ~CObjParticl();
	VOID SetPare(const D3DXMATRIX* );
	VOID SetTex(arc);
	VOID draw(MyLibrary*);
};
