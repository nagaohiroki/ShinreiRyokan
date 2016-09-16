#pragma once//ヘッダーの重複防止
//==========================================
//フォントテクスチャを登録
//==========================================
class CString
{
private:
	typedef std::vector<CFontTex*> vFont;
	TCHAR FontName[LF_FACESIZE];
public:
	vFont cfont;
	int FontSize;
	CString();
	virtual ~CString();
	VOID SetFont(const TCHAR* ,int);
	VOID Reset();
	int FontSetCheck(LPDIRECT3DDEVICE9,const TCHAR*);
	CFontTex* SetFontTex(LPDIRECT3DDEVICE9,const TCHAR*);
	VOID Debug(TCHAR* ,int);
};