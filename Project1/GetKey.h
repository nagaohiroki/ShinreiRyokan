#pragma once
class GetKey
{
private:
	
	//�}�E�X���̈�
	RECT r;
public:
	//�}�E�X���g���Ă��邩�̃t���O
	BOOL MouseFlag;	
	int m_iActive;
	//�L�[�{�[�h�}�E�X�ǂ�����Ō�Ɏg������
	int k0m1;
	//�J�[�\���̈ړ����x
	POINT speed;
	//�J�[�\���̈ʒu
	POINT point;
	//�R���X�g���N�^
	GetKey();
	//�}�E�X�J�[�\���̕\��
	VOID MyShowCursor(BOOL);
	//�}�E�X�̃��[�h���w��
	VOID MouseMode(BOOL,HWND);
	//�}�E�X���[�h��؂�ւ���
	VOID MouseChenge(HWND);
	//�}�E�X���g�p���Ă��邩
	BOOL UseMouse();
	//�L�[�̎擾
	VOID getWAKey(BOOL,BOOL,HWND,int*);

	
};

