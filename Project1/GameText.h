#pragma once
//�Q�[���p�e�L�X�g
class GameText
{
private:
	//int�z��ƕ���������z��
	typedef std::vector<int> intvec;	
	typedef std::pair<TCHAR*,intvec> tp;
	std::vector<tp> str;
	//�e�L�X�g�I�u�W�F�N�g
	CObjText txt;
	//�o�b�N�O���E���h
	CObjFVF bg;
	//�I��
	CObjFVF select;
	//�y�[�W
	int Page;
	//�I��
	int Flag;
	//��������̃t���O
	int Count;
	AKey<float> feed;
public:
	//�R���X�g���N�^
	GameText();
	//�V�[����K�p
	VOID init(Scene*);
	//�������o�^
	VOID s(TCHAR*);
	VOID s(TCHAR*,int);
	VOID s(TCHAR*,int,int);
	//�e�L�X�g�J�n
	VOID StartText(Personal*);
	//�X�V
	int Update(Personal*,MyLibrary*);
	//�f�o�b�O
	VOID DebugText(TCHAR*,int);
	//�e�L�X�g�y�[�W��
	int Max();
	
};