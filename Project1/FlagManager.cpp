//======================================
//各仕掛けのフラグ
//======================================
TrickFlag::TrickFlag()
{
	Init();
}
//初期化
VOID TrickFlag::Init()
{
	chairMove = 0;
	dinigDoor = 0;
	darts = 0;
	dartsbord = 0;
}
//======================================
//敵フラグ
//======================================
EnemyFlag::EnemyFlag(){Init();}
VOID EnemyFlag::Init()
{
	HP = 5;
	mode = 0;
	rot = 0.0f;
	pos = D3DXVECTOR3(0.0f,0.35f,0.0f);
	Level = 0;
}

//======================================
//フラグ管理
//======================================
FlagManager::FlagManager()
{
	Init();
}
//初期化
VOID FlagManager::Init()
{
	Door = 0;
	Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	RotY = 0.0f;
	FldType = FD_TestRoom;
	PlayTime = 0;
	NTime = timeGetTime();
	EventFlag = TL_INTRO_START;
	trick.Init();
	enemy.Init();

	//アイテム
	for(int i = 0;i < ITEM_MAX; i++)
	{
		ItemGet[i] = FALSE;
		ItemGeted[i] = FALSE;

	
	}
}
//ポジションセット
VOID FlagManager::StaticPos(D3DXVECTOR3* p,float rot)
{
	Pos = *p;
	RotY = rot;
}

//現在時刻の取得
VOID FlagManager::SaveTime()
{
	time_t now;
	time(&now);
	localtime_s(&Local,&now);

	PlayTime += timeGetTime() - NTime;
	NTime = timeGetTime();

}
//セーブされた時間の取得
VOID FlagManager::LoadTime()
{
	NTime = timeGetTime();
}
VOID FlagManager::ShowData(TCHAR *t,int l)
{

	int	sec  = (int)PlayTime / 1000;
	int	Second = sec % 60; 
	int	Minute = sec / 60 % 60;
	int	Hours  = sec / 60 / 60;
	_stprintf_s(t,l,_T("前回セーブ %d年%d月%d日%d時%d分%d秒\nプレイ時間 %02d : %02d : %02d")
						,Local.tm_year + 1900,Local.tm_mon + 1,Local.tm_mday
						,Local.tm_hour,Local.tm_min,Local.tm_sec
						,Hours,Minute,Second
						);

}
//アイテム
//アイテムを取得
VOID FlagManager::iGet(ITEM itm)
{
	ItemGeted[itm] = TRUE;
	ItemGet[itm] = TRUE;
}

//除外
VOID FlagManager::iRemove(ITEM itm)
{
	ItemGeted[itm] = FALSE;
	ItemGet[itm] = FALSE;
}

//捨てる
VOID FlagManager::iRelease(ITEM itm)
{
	ItemGet[itm] = FALSE;
}
//現在持っているかのフラグ
BOOL FlagManager::iGetFlag(ITEM itm)
{
	return ItemGet[itm];
}
//過去に持っていたかのフラグ
BOOL FlagManager::iGetedFlag(ITEM itm)
{
	return ItemGeted[itm];
}
//======================================
//セーブデータ管理
//======================================
GameSave::GameSave(){}
BOOL GameSave::Save(FlagManager* FM,int n)
{
	if(n > MAX_SAVE)
	{
		CFile().Debug(_T("overSaveNum\n"));
		return FALSE;
	}
	//セーブした時間
	FM->SaveTime();
	
	TCHAR Cur[MAX_PATH]  = _T("");
	TCHAR Path[MAX_PATH] = _T("");
	TCHAR txt[100] = _T("");
	//カレント位置取得
	GetCurrentDirectory(MAX_PATH,Cur);
	//フォルダ作成
	SystemSave().CreatFold(Cur);
	_stprintf_s(Path,MAX_PATH,_T("%s\\SaveData\\SaveData%d.dat"),Cur,n + 1);
	if(CSaveLoad().Save(Path,FM) == FALSE)
	{
		_stprintf_s(txt,100,_T("failed:SaveData%d\n"),n + 1);		
		return FALSE;
	}
	_stprintf_s(txt,100,_T("SaveData%d\n"),n + 1);

	CFile().Debug(txt);
	return TRUE;
}
BOOL GameSave::Load(FlagManager* FM,int n)
{
	if(n > MAX_SAVE)
	{
		CFile().Debug(_T("overLoadNum\n"));
		return FALSE;
	}
	TCHAR Cur[MAX_PATH]  = _T("");
	TCHAR Path[MAX_PATH] = _T("");
	TCHAR txt[100] = _T("");
	//カレント位置取得
	GetCurrentDirectory(MAX_PATH,Cur);
	//フォルダ作成
	SystemSave().CreatFold(Cur);

	_stprintf_s(Path,MAX_PATH,_T("%s\\SaveData\\SaveData%d.dat"),Cur,n + 1);
	if(CSaveLoad().Load(Path,FM) == FALSE)
	{
		_stprintf_s(txt,100,_T("failed:LoadData%d\n"),n + 1);
		return FALSE;
	}
	_stprintf_s(txt,100,_T("LoadData%d\n"),n + 1);

	CFile().Debug(txt);
	
	FM->LoadTime();
	return TRUE;	
}