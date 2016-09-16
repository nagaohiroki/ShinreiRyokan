#pragma once//ヘッダーの重複防止

//=======================================================
//メイン処理
//=======================================================
class Main
{
private:
	//デバッグ用のボタン
	DebugButton Db;
public:
	//マイライブラリ
	MyLibrary ML;
 private:
	//プレイヤーオブジェクト	
	Personal m_Psn;
	//フィールドオブジェクト
	Scene m_Scene;	
	//処理速度の計測
	DWORD t_Time;	
	//ループの計測
	enum{Dnum=6};
	int loopNum;
	DWORD loop[Dnum];	
	
public:	
	//コンストラクタ
	Main();
	//生成
	HRESULT Create(LPDIRECT3DDEVICE9,HWND,HINSTANCE,BOOL*,BOOL*);	
	//リセット前の解放
	HRESULT Reset();
	//リセット後の取得
	HRESULT Restore();
	//メインループ
	VOID Render();	
};

