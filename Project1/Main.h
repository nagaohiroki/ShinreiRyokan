#pragma once//�w�b�_�[�̏d���h�~

//=======================================================
//���C������
//=======================================================
class Main
{
private:
	//�f�o�b�O�p�̃{�^��
	DebugButton Db;
public:
	//�}�C���C�u����
	MyLibrary ML;
 private:
	//�v���C���[�I�u�W�F�N�g	
	Personal m_Psn;
	//�t�B�[���h�I�u�W�F�N�g
	Scene m_Scene;	
	//�������x�̌v��
	DWORD t_Time;	
	//���[�v�̌v��
	enum{Dnum=6};
	int loopNum;
	DWORD loop[Dnum];	
	
public:	
	//�R���X�g���N�^
	Main();
	//����
	HRESULT Create(LPDIRECT3DDEVICE9,HWND,HINSTANCE,BOOL*,BOOL*);	
	//���Z�b�g�O�̉��
	HRESULT Reset();
	//���Z�b�g��̎擾
	HRESULT Restore();
	//���C�����[�v
	VOID Render();	
};

