//===================================================
//�O���e�L�X�g
//===================================================
CFile::CFile()
{	
}
//�㏑��
VOID CFile::txt(const TCHAR* filename,const TCHAR* text)
{
	const TCHAR* F_FILE = _T(".\\text\\");
	TCHAR strFile[260];
	_stprintf_s(strFile,260,_T("%s%s"),F_FILE,filename);
	FILE *fp;
	if(_tfopen_s(&fp,strFile,_T("w"))==0)
	{
		_ftprintf_s(fp,_T("%s"),text);
		fclose(fp);
	}
	else
	{
		TCHAR Out[MAX_PATH] = _T("");
		_stprintf_s(Out,MAX_PATH,_T("failopen:%s\n"),strFile);
		Debug(Out);
	}
	
}
//�ǉ��L�q
VOID CFile::atxt(const TCHAR* filename,const TCHAR* text)
{
	const TCHAR* F_FILE = _T(".\\text\\");
	TCHAR strFile[260];
	_stprintf_s(strFile,260,_T("%s%s"),F_FILE,filename);
	FILE *fp;
	if(_tfopen_s(&fp,strFile,_T("a"))==0)
	{
		_ftprintf_s(fp,_T("%s"),text);
		fclose(fp);
	}
	else
	{
		TCHAR Out[MAX_PATH] = _T("");
		_stprintf_s(Out,MAX_PATH,_T("failopen:%s\n"),strFile);
		Debug(Out);
	}
}
#ifdef MY_DEBUG
//�f�o�b�O�p�o��
VOID CFile::Debug(TCHAR* text)
{
	OutputDebugString(text);
}
#else
VOID CFile::Debug(TCHAR*)
{
}
#endif