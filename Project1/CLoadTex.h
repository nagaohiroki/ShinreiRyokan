#pragma once
//テクスチャデータ
class CTexture
{
private:	
public:	
	//使用数
	int m_iCount;
	//テクスチャ
	LPDIRECT3DTEXTURE9 m_pTex;
	//コンストラクタ
	CTexture();
	//デストラクタ
	virtual ~CTexture();
	//作成
	HRESULT Create(int,LPDIRECT3DDEVICE9,Arc_Files*,FILE*);
	//カウントを減らす1以下なら破棄
	int Release();	
};

class CTextureManager
{
	typedef std::map<int,CTexture*> mapc;
	
public:
	mapc tex;
	//コンストラクタ
	CTextureManager();
	//デストラクタ
	virtual ~CTextureManager();
	//テクスチャの読み込み(すでにある場合はカウントを増やす)
	HRESULT Load(int,LPDIRECT3DDEVICE9,Arc_Files*,FILE*);

	mapc::iterator load(int,LPDIRECT3DDEVICE9,Arc_Files*,FILE*);
	//カウントを減らす1以下なら破棄
	VOID Release(int);	
	//デバッグ
	VOID Debug(TCHAR*,int,Arc_Files*);
	//テクスチャを返す
	LPDIRECT3DTEXTURE9 Retex(int);
};
