//===================================
//システムデータ
//===================================
SystemData::SystemData()
{
	Init();
}
VOID SystemData::Init()
{
	PixelMode = 0;
	Lum = 1.0f;
	Volume = 1.0f;
	First = 0;
	Best = 0;
}
VOID SystemData::InitOption()
{
	PixelMode = 0;
	Lum = 1.0f;
	Volume = 1.0f;
}

//===================================
//システムデータセーブ
//===================================
SystemSave::SystemSave(){}
//セーブ
BOOL SystemSave::Save(SystemData* s)
{
	TCHAR Cur[MAX_PATH]  = _T("");
	TCHAR Path[MAX_PATH] = _T("");
	GetCurrentDirectory(MAX_PATH,Cur);//カレント位置取得
	CreatFold(Cur);//フォルダ作成
	_stprintf_s(Path,MAX_PATH,_T("%s\\SaveData\\SystemData.dat"),Cur);
	if(CSaveLoad().Save(Path,s) == FALSE)
	{
		CFile().Debug(_T("FailSave:SystemData\n"));
		return FALSE;
	}
	CFile().Debug(_T("Save:SystemData\n"));
	return TRUE;
}
//ロード
BOOL SystemSave::Load(SystemData* s)
{
	TCHAR Cur[MAX_PATH]  = _T("");
	TCHAR Path[MAX_PATH] = _T("");
	GetCurrentDirectory(MAX_PATH,Cur);//カレント位置取得
	CreatFold(Cur);//フォルダ作成
	_stprintf_s(Path,MAX_PATH,_T("%s\\SaveData\\SystemData.dat"),Cur);
	if(CSaveLoad().Load(Path,s) == FALSE)
	{
		CFile().Debug(_T("FailLoad:SystemData\n"));
		return FALSE;
	}
	CFile().Debug(_T("Load:SystemData\n"));
	return TRUE;
}
//フォルダ作成
BOOL SystemSave::CreatFold(TCHAR *Cur)
{	
	TCHAR path[MAX_PATH] = _T("");
	_stprintf_s(path,MAX_PATH,_T("%s\\SaveData"),Cur);
	BOOL fold =	CreateDirectory( path, NULL );
	return fold;
}
