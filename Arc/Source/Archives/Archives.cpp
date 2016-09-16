#include "main.h" 
Archive::Archive()
{
}
//------------------------------------------------
//ファイル重複の確認
//------------------------------------------------
BOOL Archive::NonRepet( TCHAR* Name )
{
	unsigned int i;
	for(i = 0; i < datas.size(); i++)
	{
		//同じ名前が存在する場合FALSE
		if(_tcscmp(Name,datas[i].name) == 0)
		{
			return FALSE;
		}
	}
	return TRUE;
}
//-------------------------------------------------
//拡張子とファイル名を逆にして.を_に変換
//-------------------------------------------------
VOID Archive::Dot_to_Under(TCHAR* Name)
{
	TCHAR FlName[MAX_PATH];
	TCHAR ExName[MAX_PATH];
	unsigned int len = _tcslen(Name);
	unsigned int i;
	for(i = len; i > 1; i--)
	{
		if(Name[i] == '.')
		{
			_stprintf_s(ExName,MAX_PATH,_T("%s"),Name + i);
			Name[i] = '\0';
			_stprintf_s(FlName,MAX_PATH,_T("%s"),Name);
			_stprintf_s(Name,MAX_PATH,_T("%s_%s"),ExName + 1,FlName);
			return;
		}
	}
}
//------------------------------------------------
//ファイルの列挙
//------------------------------------------------
VOID Archive::EnumFiles(TCHAR* Fold)
{
	//指定したフォルダの後ろに\*.*をつける
	TCHAR FoldName[MAX_PATH] = _T("");
	_stprintf_s(FoldName,MAX_PATH,_T("%s\\*.*"),Fold);
	//ファイルを列挙
	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile(FoldName,&fd);		
	//フォルダ発見
	if(hFind != INVALID_HANDLE_VALUE)
	{
		//ファイルの検索
		while(FindNextFile(hFind,&fd))
		{
			if(_tcscmp(_T("."),fd.cFileName) != 0 && _tcscmp(_T(".."),fd.cFileName) != 0)
			{
				//フォルダの場合
				if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					//フォルダ内を検索
					TCHAR NextFold[MAX_PATH] = _T("");
					_stprintf_s(NextFold,MAX_PATH,_T("%s\\%s"),Fold,fd.cFileName);
					//フォルダ内のフォルダも列挙
					EnumFiles(NextFold);
				}
				else
				{	
					//同名のファイルが登録されてない場合
					if(NonRepet( fd.cFileName ) ==TRUE)
					{					
						//システムファイルは除外
						if(_tcscmp(fd.cFileName,_T("Thumbs.db")) != 0)
						{
							Sleep(2);
							//アーカイブファイルに書き込み
							Data dat;//コピー用
							_stprintf_s(dat.path,MAX_PATH,_T("%s\\%s"),Fold,fd.cFileName);//パス
							_stprintf_s(dat.name,MAX_PATH,_T("%s"),fd.cFileName);//名前
							dat.size  = fd.nFileSizeLow;//サイズ
							datas.push_back(dat);//追加
						}
					}
				}
			}
		}
	}
	else
	{
		TCHAR DTxt[MAX_PATH] = _T("");
		_stprintf_s(DTxt,MAX_PATH,_T("\n\n%s\nを開けません\n\n"),Fold);
		CDebug().Debug(DTxt);
	}
	//ファイルを閉じる
	FindClose(hFind);
}
//------------------------------------------------
//拡張子の列挙
//------------------------------------------------
VOID Archive::EnumExt()
{
	Ext l_Ext;
	unsigned int i;
	unsigned int j;
	unsigned int k;
	unsigned int len = 0;
	BOOL check = FALSE;
	for( i = 0; i < datas.size(); i++ )
	{		
		len = _tcsclen(datas[i].name);
		for( j = len; j > 1; j-- )
		{
			if( datas[i].name[j] == '.' )
			{
				_stprintf_s(l_Ext.name,MAX_PATH,_T("%s"),datas[i].name + j);
				check = TRUE;
				for( k = 0; k < ext.size(); k++ )
				{
					//拡張子がリストに存在する場合
					if( _tcscmp( ext[k].name,l_Ext.name ) == NULL )
					{
						ext[k].num++;
						check = FALSE;
						break;
					}
				}
				//拡張子リストにない場合登録
				if( check == TRUE )
				{
					ext.push_back(l_Ext);
					ext[ext.size() - 1].num++;
				}
				//最後のドットなのでループ終了
				break;						
			}
		}
	}
}

//------------------------------------------------
//拡張子ごとにソート
//------------------------------------------------
VOID Archive::ExtSort()
{
	std::vector<Data> datas1;

	unsigned int j;
	unsigned int i;
	for(i = 0; i < ext.size(); i++)
	{
		for(j = 0; j < datas.size(); j++)
		{
			//指定した拡張子がある場合
			if(_tcsstr(datas[j].name,ext[i].name) != 0)
			{
				Data dt;
				dt.size = datas[j].size;
				_stprintf_s(dt.name,_T("%s"),datas[j].name);
				_stprintf_s(dt.path,_T("%s"),datas[j].path);
				datas1.push_back(dt);
		
			}
		}
	}
	//データを入れ替える
	datas.swap(datas1);
}
//--------------------------------------------------
//ヘッダーファイルの作成
//--------------------------------------------------
VOID Archive::Header(TCHAR* name)
{
	FILE* fp;
	TCHAR FileName[MAX_PATH] = _T("");
	unsigned int i;
		
	if(_tfopen_s( &fp,name, _T("w") ) == 0)
	{
		//ヘッダーを書き込む
		_ftprintf_s(fp,	_T("#pragma once\n"));
		
		//Enumの作成
		_ftprintf_s(fp,	_T("enum arc\n{\n"));	
		for(i = 0; i < datas.size(); i++)
		{
			_stprintf_s( FileName,MAX_PATH,_T("%s"),datas[i].name );
			Dot_to_Under( FileName );
			_ftprintf_s(fp,_T("\t%s,\n"),FileName);
		}
		_ftprintf_s(fp,	_T("\tMAX_arc,\n};\n"));
		//クラス個別データ
		_ftprintf_s(fp,	_T("//アーカイブ個別データ-------------------\n"));
		_ftprintf_s(fp,_T("class arcFile\n")
			_T("{\n")
			_T("public:\n")
			_T("\tunsigned long size;\n")
			_T("\tunsigned long point;\n")
			_T("\tTCHAR name[MAX_PATH];\n")
			_T("\tarcFile()\n")
			_T("\t{\n")
			_T("\t\tsize = 0;\n")
			_T("\t\tpoint = 0;\n")
			_T("\t\t_stprintf_s(name,MAX_PATH,_T(\"\"));\n")
			_T("\t}\n")
			_T("\tVOID Set(TCHAR* Name,unsigned long Size,unsigned long Point)\n")
			_T("\t{\n")
			_T("\t\tsize = Size;\n")
			_T("\t\tpoint = Point;\n")
			_T("\t\t_stprintf_s(name,MAX_PATH,_T(\"%%s\"),Name);\n")
			_T("\t}\n")
			_T("};\n"));	
		//class本体
		_ftprintf_s(fp,
			_T("//classデータ------------------------------\n")
			_T("class Arc_Files\n")
			_T("{\n")
			_T("public:\n")
			_T("\tarcFile af[MAX_arc];\n")
			_T("\tArc_Files()\n")
			_T("\t{\n"));
		for(i = 0; i < datas.size(); i++)
		{
			_stprintf_s( FileName,MAX_PATH,_T("%s"),datas[i].name );
			Dot_to_Under( FileName );
			_ftprintf_s( fp,_T("\t\taf[%s].Set(_T(\"%s\"),%d,%d);\n"),
				FileName,
				datas[i].name,
				datas[i].size,
				datas[i].point
				);
		}
		_ftprintf_s(fp,
			_T("\t}\n")
			_T("};\n")
			
			);
		//ファイルクローズ
		fclose(fp);
	}
	else{CDebug().Debug(_T("ファイルオープン失敗\n"));}
}

//--------------------------------------------------
//datファイルを作成
//--------------------------------------------------
VOID Archive::CreateDat(TCHAR* name)
{
	FILE *FpArc;
	FILE *FpData;	
	unsigned int i;
	unsigned int j;
	unsigned int copy_byte = 0;
	unsigned long file_point	= 0;
	//アーカイブファイルを作成
	if(_tfopen_s( &FpArc,name, _T("w+b") ) == 0)
	{
		//ここに各ファイルの読み込みを書く
		for(i = 0; i < datas.size(); i++)
		{
			if(_tfopen_s(&FpData,datas[i].path,_T("r+b")) == 0)
			{
				// ファイルサイズ分だけ繰り返す
				for(j = 0; j < datas[i].size; j++)
				{
					if(fread( &copy_byte, 1, 1,FpData) != 1 ){CDebug().Debug(_T("ファイルリード失敗\n"));}
					if(fwrite( &copy_byte, 1, 1,FpArc) != 1 ){CDebug().Debug(_T("ファイル書き込み失敗\n"));}
				}
				//位置を設定
				datas[i].point = file_point;//位置
				file_point += datas[i].size;//ファイル位置を進める

				_tprintf_s(_T("%s:%d:%d\n"),datas[i].name,datas[i].point,datas[i].size);
			}
			else
			{
				TCHAR Debug[MAX_PATH];
				_stprintf_s(Debug,_T("Fail:Create%s"),datas[i].name);
				CDebug().Debug(Debug);
			}
			fclose(FpData);
		}		
		//ファイルを閉じる
		fclose(FpArc);	
	}
	else
	{
		CDebug().Debug(_T("\nファイルオープン失敗\n"));
	}
}
//--------------------------------------------------
//実行
//--------------------------------------------------
VOID Archive::Save()
{
	TCHAR Cur[MAX_PATH];
	TCHAR input[MAX_PATH];
	TCHAR out[MAX_PATH];	
	TCHAR save_name[MAX_PATH];
	TCHAR header_name[MAX_PATH];	
	GetCurrentDirectory(MAX_PATH,Cur);//カレントフォルダ
	_stprintf_s(input,MAX_PATH,_T("%s\\input"),Cur);	//inputフォルダ
	_stprintf_s(out,MAX_PATH,_T("%s\\out"),Cur);//outフォルダ
	_stprintf_s(save_name,MAX_PATH,_T("%s\\data.dat"),out);//datファイル
	_stprintf_s(header_name,MAX_PATH,_T("%s\\arc.h"),out);//ヘッダーファイル
	//ファイル読み込み
	EnumFiles(input);
	//拡張子列挙
	EnumExt();
	//拡張子ごとにソート
	ExtSort();
	//datファイルを作成
	CreateDat(save_name);
	//ヘッダーファイルの作成
	Header(header_name);
	//データを表示
	UINT i;
	for(i = 0; i < ext.size(); i++)
	{
		_tprintf_s(_T("%s:%d\n"),ext[i].name,ext[i].num);		 
	}
	
}

