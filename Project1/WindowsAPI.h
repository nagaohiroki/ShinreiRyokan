//====================================================================================================
//�E�B���h�E�Y�A�v���P�[�V�����̏�����
//====================================================================================================
#pragma once//�w�b�_�[�̏d���h�~
//���C���֐�
class D3DXMain
{
private:
	LPDIRECT3D9             m_pD3D;			// D3D�f�B�o�C�X�����̂���
	D3DPRESENT_PARAMETERS	m_D3DPParams;
	LPDIRECT3DDEVICE9       m_pD3DDevice;			// �����_�����O�f�B�o�C�X
	BOOL Lost;
	HRESULT ChangeW(HWND);//�E�B���h�E���[�h�̃t���X�N���[����؂�ւ���
	HRESULT CapsCheck();
public:
	RECT rect;
	Main main;
	D3DXMain();
	virtual ~D3DXMain();
	//�Q�[���̒��g
	HRESULT	SizeGet();
	HRESULT	InitDirect3D( HWND, HINSTANCE );//D3DX�Ƃ��̏�����
	HRESULT MsgLoop( HWND );//���b�Z�[�W���[�v
	HRESULT DeviceLost( HWND );
};



