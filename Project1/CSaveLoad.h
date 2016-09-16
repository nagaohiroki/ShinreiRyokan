#pragma once

//セーブロード
class CSaveLoad
{
private:
public:
	CSaveLoad(){}
	//セーブ(ファイル名,ファイル)
	template<class T> 
	BOOL Save(TCHAR* SaveName,T* SData)
	{
		FILE* fp;
		if(_tfopen_s(&fp,SaveName,_T("wb")) == 0)
		{
			if(fwrite(SData,sizeof(T),1,fp) != 1)
			{
				fclose(fp);
				return FALSE;
			}
			fclose(fp);
		}
		else
		{
			return FALSE;
		}
		
		return TRUE;
	}
	//ロード(ファイル名,ファイル)
	template<class T> 
	BOOL Load(TCHAR* LoadName,T* LData)
	{
		FILE* fp;
		if(_tfopen_s(&fp,LoadName,_T("rb")) == 0)
		{
			fseek(fp,0,SEEK_SET);
			if(fread(LData,sizeof(T),1,fp) != 1)
			{
				fclose(fp);	
				return FALSE;

			}
			fclose(fp);	
		}
		else
		{
			return FALSE;
		}	
		return TRUE;
	}
	VOID CreateFold();
};