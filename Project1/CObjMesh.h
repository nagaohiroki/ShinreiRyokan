#pragma once
//メッシュ
class CObjMesh
{
private:
	std::vector<std::map<int,CTexture*>::iterator> itT,itNT;

int MdlType;// オブジェクトのモデルの種類
	MyLibrary* ML;
	VOID MeshDraw();
	VOID ShadowDraw();
	VOID UpdateMat();//行列を更新
	VOID SetSp();
	VOID SetObb();	
public:
	std::map<int,CModel*>::iterator itMod;
	
	D3DXVECTOR3	objPos;//座標
	D3DXVECTOR3 objScal;//スケールの倍率
	D3DXVECTOR3 YPR;//ヨーピッチロール
	D3DXVECTOR4 MeshCol;	
	D3DXVECTOR4 SpCol;//スペキュラーの色
	D3DXVECTOR4 BloomColor;//ライトブルーム
	D3DXMATRIX *mCustom;//行列を個別に設定する場合
	D3DXMATRIX  mWorld;//行列結果
	const D3DXMATRIX* Pare;//親オブジェクト 
	BOOL drawSkip;//ドローをスキップする
	BOOL ShadowFlag;//シャドウマップフラグ
	float SpColm;//スペキュラのあらさ
	float Amb;//アビエントカラーの明るさ
	float Shadow;//影の薄さ
	float Bias;//影のバイアス	
	float Height;//法線の高さ	
	OBB HitObj;//当たり判定ステータス

	CObjMesh();
	virtual ~CObjMesh();	
	VOID SetSize(MyLibrary*);
	VOID draw(MyLibrary*);
	VOID Type(arc);
	VOID SetPare(const D3DXMATRIX* );	

	VOID SetHit(MyLibrary*);
	VOID HitMode(COLLISION_TYPE,COLLISION_BACK);
};