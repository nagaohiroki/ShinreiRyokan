#pragma once//�w�b�_�[�̏d���h�~
//==========================================
//�t�H���g�e�N�X�`����o�^
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