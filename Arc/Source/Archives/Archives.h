#pragma once
//�f�o�b�O
class CDebug
{
public:
	VOID Debug(TCHAR* text)
	{
		_tprintf_s(_T("%s\n"),text);
		OutputDebugString(text);
	}
};
//�A�[�J�C�u�ʃf�[�^
class Data
{
public:
	TCHAR path[MAX_PATH];//�t�@�C���p�X
	TCHAR name[MAX_PATH];//�t�@�C����
	unsigned long point;//�t�@�C���̈ʒu
	unsigned long size;//�t�@�C���T�C�Y
	Data()
	{
		_stprintf_s(path,MAX_PATH,_T(""));
		_stprintf_s(name,MAX_PATH,_T(""));
		point = 0;
		size = 0;	
	}
};
//�g���q�f�[�^
class Ext
{
public:	
	unsigned int num;//�g���q�̌�
	TCHAR name[MAX_PATH];//�g���q�̖��O
	Ext()
	{
		num = 0;
		_stprintf_s(name,MAX_PATH,_T(""));
	}
};
class Archive
{
private:
	std::vector<Data> datas;	
	std::vector<Ext> ext;
	//�t�@�C�����
	VOID EnumFiles(TCHAR*);
	//�d�����֎~
	BOOL NonRepet(TCHAR*);
	//.��_�ɕϊ����g���q�ƃt�@�C���������ւ���
	VOID Dot_to_Under(TCHAR*);
	//�g���q�̗�
	VOID EnumExt();
	//�g���q���w�肵�ă\�[�g
	VOID ExtSort();
	//dat�t�@�C�����쐬
	VOID CreateDat(TCHAR*);
	//�w�b�_�[�t�@�C��
	VOID Header(TCHAR*);
public:
	Archive();
	VOID Save();
	
};