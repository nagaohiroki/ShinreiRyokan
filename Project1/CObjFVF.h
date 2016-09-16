#pragma once

//FVF
class CObjFVF
{
private:

	int TexType;//テクスチャの種類
	int Pass;//描画パス
	const D3DXMATRIX* Pare;//親オブジェクト
	MyLibrary* ML;
	VOID UpdateMat();
	std::map<int,CTexture*>::iterator it;
public:
	D3DXVECTOR3	objPos;// ビルボードの座標
	D3DXVECTOR3 objScal;//スケールの倍率
	D3DXVECTOR3 YPR;//ヨーピッチロール
	D3DXVECTOR4 MeshCol;//色	
	D3DXMATRIX  mWorld;//行列結果
	BOOL drawSkip;//ドローをスキップする
	CObjFVF();
	virtual ~CObjFVF();
	//テクスチャのセット
	VOID SetTex(arc);
	VOID SetTex(arc,fx::Pass);
	VOID SetPare(const D3DXMATRIX* );
	//描画	
	VOID draw(MyLibrary*);
	//インスタント描画
	VOID draw(MyLibrary*,LPDIRECT3DTEXTURE9,int);	

	//ミラー描画
	VOID drawMirror(MyLibrary*);	
}; 
