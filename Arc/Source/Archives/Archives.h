#pragma once
//デバッグ
class CDebug
{
public:
	VOID Debug(TCHAR* text)
	{
		_tprintf_s(_T("%s\n"),text);
		OutputDebugString(text);
	}
};
//アーカイブ個別データ
class Data
{
public:
	TCHAR path[MAX_PATH];//ファイルパス
	TCHAR name[MAX_PATH];//ファイル名
	unsigned long point;//ファイルの位置
	unsigned long size;//ファイルサイズ
	Data()
	{
		_stprintf_s(path,MAX_PATH,_T(""));
		_stprintf_s(name,MAX_PATH,_T(""));
		point = 0;
		size = 0;	
	}
};
//拡張子データ
class Ext
{
public:	
	unsigned int num;//拡張子の個数
	TCHAR name[MAX_PATH];//拡張子の名前
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
	//ファイルを列挙
	VOID EnumFiles(TCHAR*);
	//重複を禁止
	BOOL NonRepet(TCHAR*);
	//.を_に変換し拡張子とファイル名を入れ替える
	VOID Dot_to_Under(TCHAR*);
	//拡張子の列挙
	VOID EnumExt();
	//拡張子を指定してソート
	VOID ExtSort();
	//datファイルを作成
	VOID CreateDat(TCHAR*);
	//ヘッダーファイル
	VOID Header(TCHAR*);
public:
	Archive();
	VOID Save();
	
};