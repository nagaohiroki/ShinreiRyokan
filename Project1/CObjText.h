#pragma once

//文字
class CObjText
{
private:
	int MaxLen;//文字の最大数
	const D3DXMATRIX* Pare;//親オブジェクト	
	VOID Sdraw(MyLibrary*);//横書き
	VOID Ldraw(MyLibrary*);//縦書き	
	VOID UpdateMat();

public:
	D3DXVECTOR2 vol;
	TCHAR *txt;
	D3DXVECTOR3	objPos;// ビルボードの座標
	D3DXVECTOR3 objScal;//スケールの倍率
	D3DXVECTOR3 YPR;//ヨーピッチロール
	D3DXVECTOR4 MeshCol;
	D3DXMATRIX  mWorld;//行列結果
	BOOL drawSkip;//ドローをスキップする
	BOOL Length;//縦書きにするか
	int StrLen;//文字の描画数
	D3DXVECTOR2 intrval;//行間
	CObjText(); 
	VOID SetPare(const D3DXMATRIX* );
	VOID SetText(TCHAR*);
	VOID draw(MyLibrary*);
	int Max();

	//横の文字数
	int wN(MyLibrary*);
	//段落数
	int hN(MyLibrary*);

};
