#pragma once
//ゲーム用テキスト
class GameText
{
private:
	//int配列と文字列を持つ配列
	typedef std::vector<int> intvec;	
	typedef std::pair<TCHAR*,intvec> tp;
	std::vector<tp> str;
	//テキストオブジェクト
	CObjText txt;
	//バックグラウンド
	CObjFVF bg;
	//選択
	CObjFVF select;
	//ページ
	int Page;
	//選択
	int Flag;
	//文字送りのフラグ
	int Count;
	AKey<float> feed;
public:
	//コンストラクタ
	GameText();
	//シーンを適用
	VOID init(Scene*);
	//文字列を登録
	VOID s(TCHAR*);
	VOID s(TCHAR*,int);
	VOID s(TCHAR*,int,int);
	//テキスト開始
	VOID StartText(Personal*);
	//更新
	int Update(Personal*,MyLibrary*);
	//デバッグ
	VOID DebugText(TCHAR*,int);
	//テキストページ数
	int Max();
	
};