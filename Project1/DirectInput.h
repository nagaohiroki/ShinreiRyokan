#pragma once//�w�b�_�[�̏d���h�~
//=============================================================================
//DirectInput�֘A
//===========================================================================

//�R���g���[���֘A
class DirectIn
{
private:	
	//�L�[���	
	int Key;
#ifdef USE_GAMEPAD
	JoyStick joy;
#endif
	//�}�E�X���[�h�̕ύX���X�L�b�v
	BOOL SkipMouse;
	//���b�N�������̃}�E�X�̏��
	BOOL LTMMode;
public:	
	//�}�E�X�L�[�{�[�h
	GetKey getkey;
	//�e�L�[
	Key_Set
	UP,
	DOWN,
	LEFT,
	RIGHT,
	W,
	A,
	S,
	D,
	X,
	Z,
	Q,
	E,
	C,
	V,
	Enter,
	Space,
	Ctrl,
	Back;

	DirectIn();
	HRESULT Create( HWND , HINSTANCE );//�C���v�b�g�̓ǂݍ���	
	VOID Update(HWND,BOOL,BOOL);
	VOID MouseLock(BOOL,HWND);


};