#pragma once//ヘッダーの重複防止
class fxManager
{
public:
	//本文
	VOID SetPass();
	VOID GandSampSet();
	fxManager()
	{		
		CreatefxFile();
		printf("OK\n");
		system("fxc.bat");
	
	}
	
	//グローバルを外部から読み込む
	VOID G_Set()
	{
		//結果
		string GlobalVal;
		//一列保存
		string buf;
		//ファイルを開く
		ifstream ifs("HLSL_Global.txt");		
		while(ifs && getline(ifs, buf)) 
		{
			GlobalVal += buf;
			GlobalVal += "\n";
		}
		size_t QPos = 0;
		size_t i=0;
		size_t size=GlobalVal.size();
		//?の数を数える
		for(i = 0; i < size; i++)
		{
			if(GlobalVal.c_str()[i] == '?')
			{
				QPos = i;
			}
		}
		//グローバル変数
		for(i = 0; i < QPos; i++)
		{
			Global += GlobalVal.c_str()[i];
		}
		//サンプラー
		for(i = QPos; i < size; i++)
		{
			Sampler += GlobalVal.c_str()[i];
		}
	}
	string out;//最終出力
private:
	string EffectPass;//エフェクトのパスを記録
	string Shader;//シェーダ本文構造体
	string PEnum;//アプリケーションで使うenum
	string Global;//グローバル変数
	string GEnum;//グローバル変数のenum
	string Sampler;//サンプラーステート
	//ファイルの作成
	VOID CreatefxFile()
	{
		//グローバル
	//	G_Set();
		GandSampSet();
		GlobalEnum();
		//パスをセット
		SetPass();
		//enumを用意
		EnumSet();
		//テクニックで囲む
		technique();
		//ファイルに保存
		ofstream ofs("main_hlsl.txt");
		ofs << out;		
	}
	//グローバル変数をenumにする
	VOID GlobalEnum()
	{
		GEnum="\n//グローバル変数\nnamespace prm\n{\n\tenum\n\t{\n";	
		size_t len = Global.size();
		size_t i=0;
		size_t first=0;//宣言の位置
		size_t nPos=0;//改行の位置
	
		size_t count=0;
		for(i = 0; i < len; i++)
		{
			if(count == 0)
			{
				if(Global.c_str()[i] == ' ')
				{
					first  = i;
					count  = 1;
				}
			}
			if(count == 1)
			{
				if(Global.c_str()[i] == ';' || Global.c_str()[i] == '[' || Global.c_str()[i] == '=')
				{
					string en;
					size_t j;
					GEnum +="\t\t";
					for(j = nPos + 1; j < first; j++)
					{
						en += Global.c_str()[j];
					}
					en +="_";
					for(j = first + 1; j < i; j++)
					{
						en += Global.c_str()[j];
					}
					GEnum +=en+",\n";
					count  = 2;					
				}
			}
			if(Global.c_str()[i] == '\n')
			{
				nPos = i;
				count = 0;
			}
		}
		GEnum += "\t\tPRM_MAX,\n\t};\n};\n*/\n";		
	}
	
	//パスの作成
	VOID Set(const char* name,string vs,string ps,string pipe)
	{
		Pass pass;//パス
		pass.Shader(name,vs,ps,pipe);
		PEnum += "\t\t" + pass.name + ",\n";
		pass.PassName(&EffectPass);
		Shader += pass.shader;
	}

	//Enumを用意する
	VOID EnumSet()
	{
		out += "\n/*\n//パス\nnamespace fx\n{\n\tenum Pass\n\t{\n" + PEnum +	"\t};\n};\n\n";
		out += GEnum;
		out += "#define init4x4 float4x4(\\\n"
			"1.0f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,\\\n"
			"0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f)\\\n\n";
		out += Global;
		out += Sampler;
		out += Shader;
	}
	//テクニック
	VOID technique()
	{
		out += 			
		"//=====================================================================================\n"
		"//technique\n"
		"//=====================================================================================\n"
		"technique TShader\n"
		"{\n"
			+ EffectPass +
		"}\n";
	}
};
