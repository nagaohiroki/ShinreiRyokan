#pragma once//�w�b�_�[�̏d���h�~


//=============================================================================
//�t�H���g�֘A
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
	HRESULT Create(LPDIRECT3DDEVICE9);	//�ǂݍ���
	HRESULT Reset();					//���Z�b�g
	HRESULT Restore();					//���Z�b�g��̍č\�z
	VOID    draw(const TCHAR *);		//�`��
	VOID    draw(const TCHAR *,int,int);//�`��
};
