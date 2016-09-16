VOID CSaveLoad::CreateFold()
	{
		//フォルダの作成
		TCHAR Cur[MAX_PATH] = _T("");
		TCHAR Path[MAX_PATH] = _T("");
		GetCurrentDirectory(MAX_PATH,Cur);//カレントフォルダ
		_stprintf_s(Path,MAX_PATH,_T("%s\\text\\SaveData"),Cur);
		if (!CreateDirectory(Path, NULL))
		{
			CFile().Debug(_T("SaveFileフォルダ作成失敗,もしくはすでにフォルダが存在します\n"));
		}
	}