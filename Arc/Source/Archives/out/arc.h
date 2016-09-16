#pragma once
enum arc
{
	txt_test,
	MAX_arc,
};
//アーカイブ個別データ-------------------
class arcFile
{
public:
	unsigned long size;
	unsigned long point;
	TCHAR name[MAX_PATH];
	arcFile()
	{
		size = 0;
		point = 0;
		_stprintf_s(name,MAX_PATH,_T(""));
	}
	VOID Set(TCHAR* Name,unsigned long Size,unsigned long Point)
	{
		size = Size;
		point = Point;
		_stprintf_s(name,MAX_PATH,_T("%s"),Name);
	}
};
//classデータ------------------------------
class Arc_Files
{
public:
	arcFile af[MAX_arc];
	Arc_Files()
	{
		af[txt_test].Set(_T("test.txt"),0,0);
	}
};
