#pragma once//�w�b�_�[�̏d���h�~
class fxManager
{
public:
	//�{��
	VOID SetPass();
	VOID GandSampSet();
	fxManager()
	{		
		CreatefxFile();
		printf("OK\n");
		system("fxc.bat");
	
	}
	
	//�O���[�o�����O������ǂݍ���
	VOID G_Set()
	{
		//����
		string GlobalVal;
		//���ۑ�
		string buf;
		//�t�@�C�����J��
		ifstream ifs("HLSL_Global.txt");		
		while(ifs && getline(ifs, buf)) 
		{
			GlobalVal += buf;
			GlobalVal += "\n";
		}
		size_t QPos = 0;
		size_t i=0;
		size_t size=GlobalVal.size();
		//?�̐��𐔂���
		for(i = 0; i < size; i++)
		{
			if(GlobalVal.c_str()[i] == '?')
			{
				QPos = i;
			}
		}
		//�O���[�o���ϐ�
		for(i = 0; i < QPos; i++)
		{
			Global += GlobalVal.c_str()[i];
		}
		//�T���v���[
		for(i = QPos; i < size; i++)
		{
			Sampler += GlobalVal.c_str()[i];
		}
	}
	string out;//�ŏI�o��
private:
	string EffectPass;//�G�t�F�N�g�̃p�X���L�^
	string Shader;//�V�F�[�_�{���\����
	string PEnum;//�A�v���P�[�V�����Ŏg��enum
	string Global;//�O���[�o���ϐ�
	string GEnum;//�O���[�o���ϐ���enum
	string Sampler;//�T���v���[�X�e�[�g
	//�t�@�C���̍쐬
	VOID CreatefxFile()
	{
		//�O���[�o��
	//	G_Set();
		GandSampSet();
		GlobalEnum();
		//�p�X���Z�b�g
		SetPass();
		//enum��p��
		EnumSet();
		//�e�N�j�b�N�ň͂�
		technique();
		//�t�@�C���ɕۑ�
		ofstream ofs("main_hlsl.txt");
		ofs << out;		
	}
	//�O���[�o���ϐ���enum�ɂ���
	VOID GlobalEnum()
	{
		GEnum="\n//�O���[�o���ϐ�\nnamespace prm\n{\n\tenum\n\t{\n";	
		size_t len = Global.size();
		size_t i=0;
		size_t first=0;//�錾�̈ʒu
		size_t nPos=0;//���s�̈ʒu
	
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
	
	//�p�X�̍쐬
	VOID Set(const char* name,string vs,string ps,string pipe)
	{
		Pass pass;//�p�X
		pass.Shader(name,vs,ps,pipe);
		PEnum += "\t\t" + pass.name + ",\n";
		pass.PassName(&EffectPass);
		Shader += pass.shader;
	}

	//Enum��p�ӂ���
	VOID EnumSet()
	{
		out += "\n/*\n//�p�X\nnamespace fx\n{\n\tenum Pass\n\t{\n" + PEnum +	"\t};\n};\n\n";
		out += GEnum;
		out += "#define init4x4 float4x4(\\\n"
			"1.0f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,\\\n"
			"0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f)\\\n\n";
		out += Global;
		out += Sampler;
		out += Shader;
	}
	//�e�N�j�b�N
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
