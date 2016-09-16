#pragma once//ヘッダーの重複防止


//=============================================================================
//フォント関連
//=============================================================================
class CText
{
private:
	LPD3DXFONT   m_pFont;
public:
	int PosX;
	int PosY;
	D3DXVECTOR4 color;
	CText();
	virtual ~CText();
	HRESULT Create(LPDIRECT3DDEVICE9);	//読み込み
	HRESULT Reset();					//リセット
	HRESULT Restore();					//リセット後の再構築
	VOID    draw(const TCHAR *);		//描画
	VOID    draw(const TCHAR *,int,int);//描画
};
