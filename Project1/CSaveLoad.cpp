VOID CSaveLoad::CreateFold()
	{
		//�t�H���_�̍쐬
		TCHAR Cur[MAX_PATH] = _T("");
		TCHAR Path[MAX_PATH] = _T("");
		GetCurrentDirectory(MAX_PATH,Cur);//�J�����g�t�H���_
		_stprintf_s(Path,MAX_PATH,_T("%s\\text\\SaveData"),Cur);
		if (!CreateDirectory(Path, NULL))
		{
			CFile().Debug(_T("SaveFile�t�H���_�쐬���s,�������͂��łɃt�H���_�����݂��܂�\n"));
		}
	}