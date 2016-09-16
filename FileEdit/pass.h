#pragma once//�w�b�_�[�̏d���h�~

//#define initFloat4x4 float4x4(1.0, 0.0, 0.0, 0.0,  0.0, 1.0, 0.0, 0.0,  0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0)
class CharEdit
{
public:
	CharEdit(){}
	//�P��̌����L��
	BOOL Search(const char *A,const char *B)
	{
		size_t sizeA = strlen(A);
		size_t sizeB = strlen(B);
		size_t i	 = 0;
		size_t j	 = 0;
		for(i = 0; i < sizeA; i++)
		{
			if(A[i] == B[0])
			{				
				for(j = 0; j < sizeB; j++)
				{
					if( A[i+j] != B[j] ){ break;}
					if( j == sizeB - 1 ){ return TRUE;}
				}				
			}
		}
		return FALSE;
	}
	//�_�u���N�H�[�e�[�V�����ň͂�(���̃t�@�C����)
	VOID Dq(char *l)
	{
		//����
		string dq;
		//���ۑ�
		string buf;
		//�t�@�C�����J��
		ifstream ifs( l );		
		while(ifs && getline(ifs, buf)) 
		{
			//�_�u���N�H�[�e�[�V�����ł͂���
			dq += "\"";
			dq += buf;
			dq += "\"\n";      
		}
		//�t�@�C�����̌���_dq
		string str = l;
		str +="_dq.txt";
		//�t�@�C���ɕۑ�
		ofstream ofs(str.c_str());
		ofs << dq;
	}
};


class Pass
{
public: 
	int texcoord;//�e�N�X�R�[�h�̐�	
	string name;//����
	string pipe;//�p�C�v���C��
	string shader;//�\���� + �{��
	string vs_shader;//VS�{��
	string ps_shader;//VS�{��
	//�X�L�����b�V��
	string plus_vs_arg;//�o�[�e�b�N�X�V�F�[�_�̈����𑝂₷�ꍇ
	string plus_func;//�O���[�o���֐�

	string defPass;


	Pass( )
	{
		texcoord=0;
	}

	
	VOID Shader( const char* n ,string vs,string ps,string pi)
	{
		//�p�X�̖��O
		name = n;
		//�p�C�v���C��
		pipe=pi;
		//�o�[�e�b�N�X�V�F�[�_�{��
		vs_shader = vs;
		//�s�N�Z���V�F�[�_�{��
		ps_shader = ps;
		//�X�L�����b�V���̏ꍇ
		SkinShader();
		//�\���̂��쐬
		SeachInOut();
		//VS��PS�ƃp�X�̍쐬
		Shader_Main();
		
	}

	//�p�X�̖��O
	VOID PassName(string* str)
	{	
		*str += "\tdefPass_" + name + "\n";
	}
private: 
	
	string vsin_smn;//�ŏI�I��VS_IN�Z�}���e�B�N�X���i�[�����
	string vsout_smn;//�ŏI�I��VS_OUT�Z�}���e�B�N�X���i�[�����
	string psout_smn;//�ŏI�I��PS_OUT�Z�}���e�B�N�X���i�[�����

	
	//�o�[�e�b�N�X(�T���ϐ�,�\���̂ɃZ�b�g����Z�}���e�B�N�X)
	VOID v_plus(const char *call,const char *param)
	{		
		//�w�肳�ꂽ�P�ꂪ�������ꍇ
		if(CharEdit().Search(vs_shader.c_str(),call) == TRUE)
		{
			//���͍\���̂ɃZ�}���e�B�N�X��ǉ�
			if(CharEdit().Search(call,"In.")==TRUE)
			{
				//�Z�}���e�B�N�X���ɓo�^����Ȃ����
				if(CharEdit().Search(vsin_smn.c_str(),param) == FALSE)
				{
					vsin_smn += param;
				}
			}
			//�o�͍\���̂ɃZ�}���e�B�N�X��ǉ�		
			if(CharEdit().Search(call,"Out.")==TRUE)
			{
				//�o�̓Z�}���e�B�N�X���ɓo�^����Ȃ����
				if(CharEdit().Search(vsout_smn.c_str(),param) == FALSE)
				{
					if(CharEdit().Search(param,"TEXCOORD")==TRUE)
					{
						char texc[50]="";
						sprintf_s(texc,50,param,texcoord);
						texcoord++;
						vsout_smn += texc;
					}
					else
					{
						vsout_smn += param;
					}
				}
			}	
		}
	}
	//�s�N�Z��(�T���ϐ�,�\���̂ɃZ�b�g����Z�}���e�B�N�X)
	VOID p_plus(const char *call,const char *param)
	{
		//�w�肳�ꂽ�P�ꂪ�������ꍇ
		if(CharEdit().Search(ps_shader.c_str(),call) == TRUE)
		{
			//���͍\���̂ɃZ�}���e�B�N�X��ǉ�
			if(CharEdit().Search(call,"Out.")==TRUE)
			{
				//�o�̓Z�}���e�B�N�X���ɓo�^����Ȃ����
				if(CharEdit().Search(psout_smn.c_str(),param) == FALSE)
				{
					psout_smn+=param;
				}
			}

			if(CharEdit().Search(call,"In.")==TRUE)
			{
				//�o�̓Z�}���e�B�N�X���ɓo�^����Ȃ����
				if(CharEdit().Search(vsout_smn.c_str(),param) == FALSE)
				{
					if(CharEdit().Search(param,"TEXCOORD")==TRUE)
					{
						char texc[50]="";
						sprintf_s(texc,50,param,texcoord);
						texcoord++;
						vsout_smn += texc;
					}
					else
					{
						vsout_smn += param;
					}
					
				}
			}
		}
	}

	
	//�{��������Z�}���e�B�N�X��T��
	VOID SeachInOut()
	{
		//����VS�Z�}���e�B�N�X
		v_plus("In.Pos",			"\tfloat4 Pos : POSITION;\n");
		v_plus("In.Tex",			"\tfloat2 Tex : TEXCOORD;\n");
		v_plus("In.Normal",			"\tfloat4 Normal : NORMAL;\n");
		v_plus("In.Tangent",		"\tfloat3 Tangent : TANGENT;\n");
		v_plus("In.Binormal",		"\tfloat3 Binormal : BINORMAL;\n");
		v_plus("In.Color",			"\tfloat4 Color : COLOR0;\n");
		v_plus("In.PSize",			"\tfloat  PSize : PSIZE;\n");
		v_plus("In.Weight",			"\tfloat4 Weight : BLENDWEIGHT;\n");
		v_plus("In.Indices",		"\tfloat4 Indices : BLENDINDICES;\n");

		//�o��VS�Z�}���e�B�N�X,����PS�Z�}���e�B�N�X
		v_plus("Out.Pos",			"\tfloat4 Pos : POSITION;\n");
		v_plus("Out.PSize",			"\tfloat  PSize : PSIZE;\n");
		v_plus("Out.Color",			"\tfloat4 Color : COLOR0;\n");
		v_plus("Out.Fog",			"\tfloat  Fog : FOG;\n");
		v_plus("Out.Tex",			"\tfloat2 Tex : TEXCOORD%d;\n");
		v_plus("Out.Depth",			"\tfloat4 Depth : TEXCOORD%d;\n");
		v_plus("Out.vLight",		"\tfloat3 vLight : TEXCOORD%d;\n");
		v_plus("Out.vEye",			"\tfloat3 vEye : TEXCOORD%d;\n");
		v_plus("Out.LclNormal",		"\tfloat3 LclNormal : TEXCOORD%d;\n");
		v_plus("Out.LclPos",		"\tfloat3 LclPos : TEXCOORD%d;\n");

		v_plus("Out.T0",			"\tfloat2 T0 : TEXCOORD0;\n");
		v_plus("Out.T1",			"\tfloat2 T1 : TEXCOORD1;\n");
		v_plus("Out.T2",			"\tfloat2 T2 : TEXCOORD2;\n");
		v_plus("Out.T3",			"\tfloat2 T3 : TEXCOORD3;\n");
		v_plus("Out.T4",			"\tfloat2 T4 : TEXCOORD4;\n");
		v_plus("Out.T5",			"\tfloat2 T5 : TEXCOORD5;\n");
		v_plus("Out.T6",			"\tfloat2 T6 : TEXCOORD6;\n");
		v_plus("Out.T7",			"\tfloat2 T7 : TEXCOORD7;\n");


		//�o��PS�Z�}���e�B�N�X
		p_plus("Out.Color0","\tfloat4 Color0 : COLOR0;\n");
		p_plus("Out.Color1","\tfloat4 Color1 : COLOR1;\n");

		p_plus("In.T0",			"\tfloat2 T0 : TEXCOORD0;\n");
		p_plus("In.T1",			"\tfloat2 T1 : TEXCOORD1;\n");
		p_plus("In.T2",			"\tfloat2 T2 : TEXCOORD2;\n");
		p_plus("In.T3",			"\tfloat2 T3 : TEXCOORD3;\n");
		p_plus("In.T4",			"\tfloat2 T4 : TEXCOORD4;\n");
		p_plus("In.T5",			"\tfloat2 T5 : TEXCOORD5;\n");
		p_plus("In.T6",			"\tfloat2 T6 : TEXCOORD6;\n");
		p_plus("In.T7",			"\tfloat2 T7 : TEXCOORD7;\n");
	}

	//�\���̂Ɩ{��
	VOID Shader_Main()
	{
		//�e�\���̖̂��O
		string vs_input  = name + "_VS_INPUT";
		string vs_output = name + "_VS_OUTPUT";
		string ps_output = name + "_PS_OUTPUT";
		//�\���̓���
		shader=
			"//=====================================================================================\n"
			"//" + name + "\n"
			"//=====================================================================================\n"

			"struct "+ name + "_VS_INPUT\n"
			"{\n"
			+ vsin_smn +
			"};\n"

			"struct "+ name + "_VS_OUTPUT\n"
			"{\n"
			+ vsout_smn +
			"};\n"

			"struct "+ name + "_PS_OUTPUT\n"
			"{\n"
			+ psout_smn +
			"};\n"

			//�V�F�[�_�[�{��
			+vs_output + " " + name + "_VS(" + vs_input  + " In"+ plus_vs_arg+")\n"
			"{\n	"
			+ vs_output + " Out = (" + vs_output  +  ")0;\n\n"
			+ vs_shader +
			"\treturn Out;\n"
			"}\n" + plus_func 

			+ps_output + " " + name + "_PS("+ vs_output + " In)\n"
			"{\n\t"
			+ ps_output + " Out = (" + ps_output + ")0;\n\n"
			+ ps_shader +
			"\treturn Out;\n"
			"}\n";

		//VS�{����BoneNum���܂܂�Ă�����
		string vs;
		if(CharEdit().Search(vs_shader.c_str(),"BoneNum")==FALSE)
		{
			vs="\tVertexShader\t= compile vs_1_1 " + name +"_VS();\\\n";
		}
		else
		{
			vs="\tVertexShader = "+name+"_Skin[BNum];\\\n";
		}
		shader +=
			"#define defPass_"+name+"\\\n"
			"pass " + name + "\\\n"
			"{\\\n"
			+vs+
			"\tPixelShader\t= compile ps_2_0 " + name +"_PS();\\\n"
			+ pipe +
			"}\\\n";

	}
	//�X�L�����b�V��
	VOID SkinShader()
	{
		if(CharEdit().Search(vs_shader.c_str(),"BoneNum") == TRUE)
		{
			//VS�{����BoneNum���܂܂�Ă�����
			plus_vs_arg=",uniform int BoneNum";
			plus_func=
				"VertexShader " + name + "_Skin[4]={\n"
				"\tcompile vs_1_1 "+name+"_VS(1),\n"
				"\tcompile vs_1_1 "+name+"_VS(2),\n"
				"\tcompile vs_1_1 "+name+"_VS(3),\n"
				"\tcompile vs_1_1 "+name+"_VS(4),\n"
				"};\n"
				;
		}
	}

	
};