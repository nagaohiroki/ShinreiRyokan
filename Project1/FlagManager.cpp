//======================================
//�e�d�|���̃t���O
//======================================
TrickFlag::TrickFlag()
{
	Init();
}
//������
VOID TrickFlag::Init()
{
	chairMove = 0;
	dinigDoor = 0;
	darts = 0;
	dartsbord = 0;
}
//======================================
//�G�t���O
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
//�t���O�Ǘ�
//======================================
FlagManager::FlagManager()
{
	Init();
}
//������
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

	//�A�C�e��
	for(int i = 0;i < ITEM_MAX; i++)
	{
		ItemGet[i] = FALSE;
		ItemGeted[i] = FALSE;

	
	}
}
//�|�W�V�����Z�b�g
VOID FlagManager::StaticPos(D3DXVECTOR3* p,float rot)
{
	Pos = *p;
	RotY = rot;
}

//���ݎ����̎擾
VOID FlagManager::SaveTime()
{
	time_t now;
	time(&now);
	localtime_s(&Local,&now);

	PlayTime += timeGetTime() - NTime;
	NTime = timeGetTime();

}
//�Z�[�u���ꂽ���Ԃ̎擾
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
	_stprintf_s(t,l,_T("�O��Z�[�u %d�N%d��%d��%d��%d��%d�b\n�v���C���� %02d : %02d : %02d")
						,Local.tm_year + 1900,Local.tm_mon + 1,Local.tm_mday
						,Local.tm_hour,Local.tm_min,Local.tm_sec
						,Hours,Minute,Second
						);

}
//�A�C�e��
//�A�C�e�����擾
VOID FlagManager::iGet(ITEM itm)
{
	ItemGeted[itm] = TRUE;
	ItemGet[itm] = TRUE;
}

//���O
VOID FlagManager::iRemove(ITEM itm)
{
	ItemGeted[itm] = FALSE;
	ItemGet[itm] = FALSE;
}

//�̂Ă�
VOID FlagManager::iRelease(ITEM itm)
{
	ItemGet[itm] = FALSE;
}
//���ݎ����Ă��邩�̃t���O
BOOL FlagManager::iGetFlag(ITEM itm)
{
	return ItemGet[itm];
}
//�ߋ��Ɏ����Ă������̃t���O
BOOL FlagManager::iGetedFlag(ITEM itm)
{
	return ItemGeted[itm];
}
//======================================
//�Z�[�u�f�[�^�Ǘ�
//======================================
GameSave::GameSave(){}
BOOL GameSave::Save(FlagManager* FM,int n)
{
	if(n > MAX_SAVE)
	{
		CFile().Debug(_T("overSaveNum\n"));
		return FALSE;
	}
	//�Z�[�u��������
	FM->SaveTime();
	
	TCHAR Cur[MAX_PATH]  = _T("");
	TCHAR Path[MAX_PATH] = _T("");
	TCHAR txt[100] = _T("");
	//�J�����g�ʒu�擾
	GetCurrentDirectory(MAX_PATH,Cur);
	//�t�H���_�쐬
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
	//�J�����g�ʒu�擾
	GetCurrentDirectory(MAX_PATH,Cur);
	//�t�H���_�쐬
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