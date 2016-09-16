#pragma once
//===================================
//システムデータ
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
//システムデータセーブ
//===================================
class SystemSave
{
public:
	SystemSave();
	BOOL Save(SystemData*);
	BOOL Load(SystemData*);
	//フォルダ作成
	BOOL CreatFold(TCHAR*);
};