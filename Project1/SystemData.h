#pragma once
//===================================
//�V�X�e���f�[�^
//===================================
class SystemData
{
public:
	DWORD First;
	DWORD Best;

	float Lum;
	float Volume;
	int PixelMode;
	SystemData();
	VOID Init();
	VOID InitOption();

};

//===================================
//�V�X�e���f�[�^�Z�[�u
//===================================
class SystemSave
{
public:
	SystemSave();
	BOOL Save(SystemData*);
	BOOL Load(SystemData*);
	//�t�H���_�쐬
	BOOL CreatFold(TCHAR*);
};