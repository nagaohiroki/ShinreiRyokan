
/*
//パス
namespace fx
{
	enum Pass
	{
		Mesh,
		Mesh_Tex,
		Mesh_AlphaTex,
		Mesh_Bump,
		ShadowMap,
		ShadowAlphaMap,
		FVF,
		FVF_Tex,
		FVF_Tex_Point,
		FVF_Tex_One,
		Tone,
		GaussX,
		GaussY,
	};
};


//グローバル変数
namespace prm
{
	enum
	{
		float4x4_mW ,
		float4x4_mVP ,
		float4x4_mLight ,
		float4_vLightDir ,
		float4_vColor ,
		float3_vEyePos ,
		float4_SP ,
		float4_SBias ,
		float4_vFog ,
		float4_vFogColor ,
		int_vFogUse ,
		float4_PixelUV ,
		float4_BloomColor ,
		float3_CamPos ,
		float4_PLightDif ,
		float4_PLightPos ,
		float4_PLightVec ,
		texture_Tex,
		texture_ShadowTex,
		texture_NormalTex,
		float_w,
		float4_GaussMap ,
		PRM_MAX,
	};
};
*/
#define init4x4 float4x4(\
1.0f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,\
0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f)\


float4x4 mW =init4x4;//ワールドトランス
float4x4 mVP =init4x4;//ビュー*プロジェクト
float4x4 mLight =init4x4;//ライト視点の行列
float4 vLightDir =float4(0.0f,0.0f,0.0f,0.0f);//ライトの方向
float4 vColor =float4(0.0f,0.0f,0.0f,0.0f);//ライト＊メッシュの色
float3 vEyePos =float3(0.0f,0.0f,0.0f);//カメラの位置（ローカル座標系）
float4 SP =float4(0.0f,0.0f,0.0f,0.0f);//スペキュラ
float4 SBias =float4(0.0f,0.0f,0.0f,0.0f);//xにバイアスyに影の濃さ
float4 vFog =float4(0.0f,0.0f,0.0f,0.0f);//フォグ
float4 vFogColor =float4(0.0f,0.0f,0.0f,0.0f);//フォグの色
int vFogUse =0;//フォグのオンオフ
float4 PixelUV =float4(0.0f,0.0f,0.0f,0.0f);//ブラー
float4 BloomColor =float4(0.0f,0.0f,0.0f,0.0f); //ライトブルーム
float3 CamPos =float3(0.0f,0.0f,0.0f);//カメラの位置(ワールド) 
float4 PLightDif = float4(0.0f,0.0f,0.0f,0.0f);	//ポイントライトの色
float4 PLightPos = float4(0.0f,0.0f,0.0f,0.0f);	//ポイントライトの位置
float4 PLightVec = float4(0.0f,0.0f,0.0f,0.0f);	//スポットライトベクトルとwに射影角
texture Tex;//デカールテクスチャ
texture ShadowTex;//シャドウテクスチャ
texture NormalTex;//法線テクスチャ
float w[6] = {0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};//ガウスの重み
float4 GaussMap = float4(0.0f,0.0f,0.0f,0.0f);//ガウスのマップサイズ
sampler     Samp           = sampler_state{Texture = <Tex>;};      //デカールテクスチャ
sampler     ShadowTexSamp  = sampler_state{Texture = <ShadowTex>;};//シャドウマップテクスチャ
sampler     NormalSamp     = sampler_state{Texture = <NormalTex>;};//法線テクスチャ
//=====================================================================================
//Mesh
//=====================================================================================
struct Mesh_VS_INPUT
{
	float4 Pos : POSITION;
	float4 Normal : NORMAL;
};
struct Mesh_VS_OUTPUT
{
	float4 Pos : POSITION;
	float4 Color : COLOR0;
	float  Fog : FOG;
	float4 Depth : TEXCOORD0;
	float3 vLight : TEXCOORD1;
	float3 vEye : TEXCOORD2;
	float3 LclNormal : TEXCOORD3;
	float3 LclPos : TEXCOORD4;
};
struct Mesh_PS_OUTPUT
{
	float4 Color0 : COLOR0;
	float4 Color1 : COLOR1;
};
Mesh_VS_OUTPUT Mesh_VS(Mesh_VS_INPUT In)
{
	Mesh_VS_OUTPUT Out = (Mesh_VS_OUTPUT)0;

	//位置行列変換
	float4 Pos = mul(In.Pos, mW);
	Out.Pos  = mul(Pos, mVP);

	//ランバート反射
	Out.Color = vColor * max(vLightDir.w, dot(In.Normal,vLightDir));

	//鏡面反射
	Out.vLight = In.Normal.xyz;
	Out.vEye = vEyePos - In.Pos.xyz;

	//フォグ
	Out.Fog = vFog.x + Out.Pos.w  * vFog.y;

	//ポイントライト
	Out.LclPos = Pos;//位置
	Out.LclNormal = mul(float4(In.Normal.xyz,0.0f),(float3x3)mW);//法線ベクトル

	//シャドウマップ
	Out.Depth = mul(Pos, mLight);//深度を保存
	Out.Depth.x = ( Out.Depth.x + Out.Depth.w) * 0.5f;
	Out.Depth.y = (-Out.Depth.y + Out.Depth.w) * 0.5f;

	return Out;
}
Mesh_PS_OUTPUT Mesh_PS(Mesh_VS_OUTPUT In)
{
	Mesh_PS_OUTPUT Out = (Mesh_PS_OUTPUT)0;

	//ディフューズ
	Out.Color0 = In.Color;

	//影
	float4 Stex = float4(In.Depth.x,In.Depth.y,0.0f,In.Depth.w);
	float SM_Z	=tex2Dproj(ShadowTexSamp,Stex).x;
	float d = (In.Depth.z / In.Depth.w) - SBias.x;
	float shadow = (SM_Z < d) ? SBias.y : 1.0f;
	Out.Color0 *= shadow;

	//鏡面反射
	float3 N = normalize(In.vLight);//法線ベクトル
	float3 V = normalize(In.vEye);//視線ベクトル
	float3 H = normalize( vLightDir.xyz + V);//ハーフベクトル
	float4 S = pow(max(0.0f,dot(N,H)),SP.w) * SP;//鏡面反射
	Out.Color0 += S;

	//ポイントスポットライト
	float3 LV    = normalize(PLightPos.xyz - In.LclPos);//ライトベクトル
	float  gen   = PLightPos.w / length(PLightPos -  In.LclPos);//減衰
	float4 dif   = PLightDif * saturate(dot(  In.LclNormal ,LV ));//デフューズ
	float  Ldot  = saturate(dot(LV,PLightVec.xyz) - PLightVec.w);//スポットに納める
	float4 spc   = pow(max(0,saturate(dot( In.LclNormal,PLightVec.xyz) )),SP.w);//スペキュラ
	float4 Point = ( dif + spc ) * gen * Ldot;
	Out.Color0 += Point;

	//ブルーム
	Out.Color1 = ( S + Point ) * BloomColor;

	//アルファ
	Out.Color0.a = Out.Color1.a = vColor.a;

	return Out;
}
#define defPass_Mesh\
pass Mesh\
{\
	VertexShader	= compile vs_3_0 Mesh_VS();\
	PixelShader	= compile ps_3_0 Mesh_PS();\
	AlphaBlendEnable = TRUE;\
	SrcBlend = SRCALPHA;\
	DestBlend = INVSRCALPHA;\
	AddressU[0] = Wrap;\
	AddressV[0] = Wrap;\
	MinFilter[0] = LINEAR;\
	MagFilter[0] = LINEAR;\
	FogEnable =vFogUse;\
	FogVertexMode = Linear;\
	FogColor = vFogColor;\
	ZWRITEENABLE = TRUE;\
	CULLMODE = CCW;\
}\
//=====================================================================================
//Mesh_Tex
//=====================================================================================
struct Mesh_Tex_VS_INPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD;
	float4 Normal : NORMAL;
};
struct Mesh_Tex_VS_OUTPUT
{
	float4 Pos : POSITION;
	float4 Color : COLOR0;
	float  Fog : FOG;
	float2 Tex : TEXCOORD0;
	float4 Depth : TEXCOORD1;
	float3 vLight : TEXCOORD2;
	float3 vEye : TEXCOORD3;
	float3 LclNormal : TEXCOORD4;
	float3 LclPos : TEXCOORD5;
};
struct Mesh_Tex_PS_OUTPUT
{
	float4 Color0 : COLOR0;
	float4 Color1 : COLOR1;
};
Mesh_Tex_VS_OUTPUT Mesh_Tex_VS(Mesh_Tex_VS_INPUT In)
{
	Mesh_Tex_VS_OUTPUT Out = (Mesh_Tex_VS_OUTPUT)0;

	//位置行列変換
	float4 Pos = mul(In.Pos, mW);
	Out.Pos  = mul(Pos, mVP);

	//ランバート反射
	Out.Color = vColor * max(vLightDir.w, dot(In.Normal,vLightDir));

	//鏡面反射
	Out.vLight = In.Normal.xyz;
	Out.vEye = vEyePos - In.Pos.xyz;

	//フォグ
	Out.Fog = vFog.x + Out.Pos.w  * vFog.y;

	//ポイントライト
	Out.LclPos = Pos;//位置
	Out.LclNormal = mul(float4(In.Normal.xyz,0.0f),(float3x3)mW);//法線ベクトル

	//シャドウマップ
	Out.Depth = mul(Pos, mLight);//深度を保存
	Out.Depth.x = ( Out.Depth.x + Out.Depth.w) * 0.5f;
	Out.Depth.y = (-Out.Depth.y + Out.Depth.w) * 0.5f;

	//テクスチャ
	Out.Tex = In.Tex;

	return Out;
}
Mesh_Tex_PS_OUTPUT Mesh_Tex_PS(Mesh_Tex_VS_OUTPUT In)
{
	Mesh_Tex_PS_OUTPUT Out = (Mesh_Tex_PS_OUTPUT)0;

	//ディフューズ
	Out.Color0 = In.Color;

	//テクスチャ
	float4 T = tex2D(Samp, In.Tex);
	Out.Color0 *= T;

	//影
	float4 Stex = float4(In.Depth.x,In.Depth.y,0.0f,In.Depth.w);
	float SM_Z	=tex2Dproj(ShadowTexSamp,Stex).x;
	float d = (In.Depth.z / In.Depth.w) - SBias.x;
	float shadow = (SM_Z < d) ? SBias.y : 1.0f;
	Out.Color0 *= shadow;

	//鏡面反射
	float3 N = normalize(In.vLight);//法線ベクトル
	float3 V = normalize(In.vEye);//視線ベクトル
	float3 H = normalize( vLightDir.xyz + V);//ハーフベクトル
	float4 S = pow(max(0.0f,dot(N,H)),SP.w) * SP;//鏡面反射
	Out.Color0 += S;

	//ポイントスポットライト
	float3 LV    = normalize(PLightPos.xyz - In.LclPos);//ライトベクトル
	float  gen   = PLightPos.w / length(PLightPos -  In.LclPos);//減衰
	float4 dif   = PLightDif * saturate(dot(  In.LclNormal ,LV ));//デフューズ
	float  Ldot  = saturate(dot(LV,PLightVec.xyz) - PLightVec.w);//スポットに納める
	float4 spc   = pow(max(0,saturate(dot( In.LclNormal,PLightVec.xyz) )),SP.w);//スペキュラ
	float4 Point = ( dif + spc ) * gen * Ldot;
	Out.Color0 += Point;

	//ブルーム
	Out.Color1 = ( S + Point ) * BloomColor;

	//テクスチャアルファ
	Out.Color0.a = Out.Color1.a = vColor.a * T.a;

	return Out;
}
#define defPass_Mesh_Tex\
pass Mesh_Tex\
{\
	VertexShader	= compile vs_3_0 Mesh_Tex_VS();\
	PixelShader	= compile ps_3_0 Mesh_Tex_PS();\
	AlphaBlendEnable = TRUE;\
	SrcBlend = SRCALPHA;\
	DestBlend = INVSRCALPHA;\
	AddressU[0] = Wrap;\
	AddressV[0] = Wrap;\
	MinFilter[0] = LINEAR;\
	MagFilter[0] = LINEAR;\
	FogEnable =vFogUse;\
	FogVertexMode = Linear;\
	FogColor = vFogColor;\
	ZWRITEENABLE = TRUE;\
	CULLMODE = CCW;\
}\
//=====================================================================================
//Mesh_AlphaTex
//=====================================================================================
struct Mesh_AlphaTex_VS_INPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD;
	float4 Normal : NORMAL;
};
struct Mesh_AlphaTex_VS_OUTPUT
{
	float4 Pos : POSITION;
	float4 Color : COLOR0;
	float  Fog : FOG;
	float2 Tex : TEXCOORD0;
	float4 Depth : TEXCOORD1;
	float3 vLight : TEXCOORD2;
	float3 vEye : TEXCOORD3;
	float3 LclNormal : TEXCOORD4;
	float3 LclPos : TEXCOORD5;
};
struct Mesh_AlphaTex_PS_OUTPUT
{
	float4 Color0 : COLOR0;
	float4 Color1 : COLOR1;
};
Mesh_AlphaTex_VS_OUTPUT Mesh_AlphaTex_VS(Mesh_AlphaTex_VS_INPUT In)
{
	Mesh_AlphaTex_VS_OUTPUT Out = (Mesh_AlphaTex_VS_OUTPUT)0;

	//位置行列変換
	float4 Pos = mul(In.Pos, mW);
	Out.Pos  = mul(Pos, mVP);

	//ランバート反射
	Out.Color = vColor * max(vLightDir.w, dot(In.Normal,vLightDir));

	//鏡面反射
	Out.vLight = In.Normal.xyz;
	Out.vEye = vEyePos - In.Pos.xyz;

	//フォグ
	Out.Fog = vFog.x + Out.Pos.w  * vFog.y;

	//ポイントライト
	Out.LclPos = Pos;//位置
	Out.LclNormal = mul(float4(In.Normal.xyz,0.0f),(float3x3)mW);//法線ベクトル

	//シャドウマップ
	Out.Depth = mul(Pos, mLight);//深度を保存
	Out.Depth.x = ( Out.Depth.x + Out.Depth.w) * 0.5f;
	Out.Depth.y = (-Out.Depth.y + Out.Depth.w) * 0.5f;

	//テクスチャ
	Out.Tex = In.Tex;

	return Out;
}
Mesh_AlphaTex_PS_OUTPUT Mesh_AlphaTex_PS(Mesh_AlphaTex_VS_OUTPUT In)
{
	Mesh_AlphaTex_PS_OUTPUT Out = (Mesh_AlphaTex_PS_OUTPUT)0;

	//ディフューズ
	Out.Color0 = In.Color;

	//テクスチャ
	float4 T = tex2D(Samp, In.Tex);
	Out.Color0 *= T;

	//影
	float4 Stex = float4(In.Depth.x,In.Depth.y,0.0f,In.Depth.w);
	float SM_Z	=tex2Dproj(ShadowTexSamp,Stex).x;
	float d = (In.Depth.z / In.Depth.w) - SBias.x;
	float shadow = (SM_Z < d) ? SBias.y : 1.0f;
	Out.Color0 *= shadow;

	//鏡面反射
	float3 N = normalize(In.vLight);//法線ベクトル
	float3 V = normalize(In.vEye);//視線ベクトル
	float3 H = normalize( vLightDir.xyz + V);//ハーフベクトル
	float4 S = pow(max(0.0f,dot(N,H)),SP.w) * SP;//鏡面反射
	Out.Color0 += S;

	//ポイントスポットライト
	float3 LV    = normalize(PLightPos.xyz - In.LclPos);//ライトベクトル
	float  gen   = PLightPos.w / length(PLightPos -  In.LclPos);//減衰
	float4 dif   = PLightDif * saturate(dot(  In.LclNormal ,LV ));//デフューズ
	float  Ldot  = saturate(dot(LV,PLightVec.xyz) - PLightVec.w);//スポットに納める
	float4 spc   = pow(max(0,saturate(dot( In.LclNormal,PLightVec.xyz) )),SP.w);//スペキュラ
	float4 Point = ( dif + spc ) * gen * Ldot;
	Out.Color0 += Point;

	//ブルーム
	Out.Color1 = ( S + Point ) * BloomColor;

	//テクスチャアルファ
	Out.Color0.a = Out.Color1.a = vColor.a * T.a;

	return Out;
}
#define defPass_Mesh_AlphaTex\
pass Mesh_AlphaTex\
{\
	VertexShader	= compile vs_3_0 Mesh_AlphaTex_VS();\
	PixelShader	= compile ps_3_0 Mesh_AlphaTex_PS();\
	AlphaBlendEnable = TRUE;\
	SrcBlend = SRCALPHA;\
	DestBlend = INVSRCALPHA;\
	AddressU[0] = Wrap;\
	AddressV[0] = Wrap;\
	MinFilter[0] = LINEAR;\
	MagFilter[0] = LINEAR;\
	FogEnable =vFogUse;\
	FogVertexMode = Linear;\
	FogColor = vFogColor;\
	ZWRITEENABLE = FALSE;\
	CULLMODE = NONE;\
}\
//=====================================================================================
//Mesh_Bump
//=====================================================================================
struct Mesh_Bump_VS_INPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD;
	float4 Normal : NORMAL;
	float3 Tangent : TANGENT;
	float3 Binormal : BINORMAL;
};
struct Mesh_Bump_VS_OUTPUT
{
	float4 Pos : POSITION;
	float  Fog : FOG;
	float2 Tex : TEXCOORD0;
	float4 Depth : TEXCOORD1;
	float3 vLight : TEXCOORD2;
	float3 vEye : TEXCOORD3;
	float3 LclNormal : TEXCOORD4;
	float3 LclPos : TEXCOORD5;
};
struct Mesh_Bump_PS_OUTPUT
{
	float4 Color0 : COLOR0;
	float4 Color1 : COLOR1;
};
Mesh_Bump_VS_OUTPUT Mesh_Bump_VS(Mesh_Bump_VS_INPUT In)
{
	Mesh_Bump_VS_OUTPUT Out = (Mesh_Bump_VS_OUTPUT)0;

	//位置行列変換
	float4 Pos = mul(In.Pos, mW);
	Out.Pos  = mul(Pos, mVP);

	//鏡面反射用のベクトル
	float3 E = normalize(vEyePos - In.Pos.xyz);//視線ベクトル
	Out.vEye    =float3(dot(E,In.Tangent),dot(E,In.Binormal),dot(E,In.Normal));
	Out.vEye=normalize(Out.vEye);

	//ライトベクトル
	float3 L =vLightDir.xyz;
	Out.vLight=float3(dot(L,In.Tangent),dot(L,In.Binormal),dot(L,In.Normal));
	Out.vLight=normalize(Out.vLight);

	//フォグ
	Out.Fog = vFog.x + Out.Pos.w  * vFog.y;

	//ポイントライト
	Out.LclPos = Pos;//位置
	Out.LclNormal = mul(float4(In.Normal.xyz,0.0f),(float3x3)mW);//法線ベクトル

	//シャドウマップ
	Out.Depth = mul(Pos, mLight);//深度を保存
	Out.Depth.x = ( Out.Depth.x + Out.Depth.w) * 0.5f;
	Out.Depth.y = (-Out.Depth.y + Out.Depth.w) * 0.5f;

	//テクスチャ
	Out.Tex = In.Tex;

	return Out;
}
Mesh_Bump_PS_OUTPUT Mesh_Bump_PS(Mesh_Bump_VS_OUTPUT In)
{
	Mesh_Bump_PS_OUTPUT Out = (Mesh_Bump_PS_OUTPUT)0;

	//バンプマップ拡散反射
	float3 N = 2.0f * tex2D( NormalSamp,In.Tex).xyz - 1.0f;	// 法線マップからの法線
	float3 H = normalize(In.vLight + In.vEye);//ハーフベクトル
	Out.Color0 = vColor * max(vLightDir.w,dot(N,In.vLight));//拡散反射

	//テクスチャ
	float4 T = tex2D(Samp, In.Tex);
	Out.Color0 *= T;

	//影
	float4 Stex = float4(In.Depth.x,In.Depth.y,0.0f,In.Depth.w);
	float SM_Z	=tex2Dproj(ShadowTexSamp,Stex).x;
	float d = (In.Depth.z / In.Depth.w) - SBias.x;
	float shadow = (SM_Z < d) ? SBias.y : 1.0f;
	Out.Color0 *= shadow;

	//バンプマップ鏡面反射
	float4 S = pow(max(0.0f,dot(N,H)),SP.w) * SP;//鏡面反射
	Out.Color0 += S;

	//ポイントスポットライト
	float3 LV    = normalize(PLightPos.xyz - In.LclPos);//ライトベクトル
	float  gen   = PLightPos.w / length(PLightPos -  In.LclPos);//減衰
	float4 dif   = PLightDif * saturate(dot(  In.LclNormal ,LV ));//デフューズ
	float  Ldot  = saturate(dot(LV,PLightVec.xyz) - PLightVec.w);//スポットに納める
	float4 spc   = pow(max(0,saturate(dot( In.LclNormal,PLightVec.xyz) )),SP.w);//スペキュラ
	float4 Point = ( dif + spc ) * gen * Ldot;
	Out.Color0 += Point;

	//ブルーム
	Out.Color1 = ( S + Point ) * BloomColor;

	//テクスチャアルファ
	Out.Color0.a = Out.Color1.a = vColor.a * T.a;

	return Out;
}
#define defPass_Mesh_Bump\
pass Mesh_Bump\
{\
	VertexShader	= compile vs_3_0 Mesh_Bump_VS();\
	PixelShader	= compile ps_3_0 Mesh_Bump_PS();\
	AlphaBlendEnable = TRUE;\
	SrcBlend = SRCALPHA;\
	DestBlend = INVSRCALPHA;\
	AddressU[0] = Wrap;\
	AddressV[0] = Wrap;\
	MinFilter[0] = LINEAR;\
	MagFilter[0] = LINEAR;\
	FogEnable =vFogUse;\
	FogVertexMode = Linear;\
	FogColor = vFogColor;\
	ZWRITEENABLE = TRUE;\
	CULLMODE = CCW;\
	AddressU[2] = Wrap;\
	AddressV[2] = Wrap;\
	MinFilter[2] = LINEAR;\
	MagFilter[2] = LINEAR;\
}\
//=====================================================================================
//ShadowMap
//=====================================================================================
struct ShadowMap_VS_INPUT
{
	float4 Pos : POSITION;
};
struct ShadowMap_VS_OUTPUT
{
	float4 Pos : POSITION;
	float4 Depth : TEXCOORD0;
};
struct ShadowMap_PS_OUTPUT
{
	float4 Color0 : COLOR0;
};
ShadowMap_VS_OUTPUT ShadowMap_VS(ShadowMap_VS_INPUT In)
{
	ShadowMap_VS_OUTPUT Out = (ShadowMap_VS_OUTPUT)0;

	//シャドウマップ行列
	Out.Pos= mul(mul(In.Pos, mW), mLight);
	Out.Depth.xy =Out.Pos.zw;

	return Out;
}
ShadowMap_PS_OUTPUT ShadowMap_PS(ShadowMap_VS_OUTPUT In)
{
	ShadowMap_PS_OUTPUT Out = (ShadowMap_PS_OUTPUT)0;

	//深度を保存
	Out.Color0 = In.Depth.x / In.Depth.y;

	return Out;
}
#define defPass_ShadowMap\
pass ShadowMap\
{\
	VertexShader	= compile vs_3_0 ShadowMap_VS();\
	PixelShader	= compile ps_3_0 ShadowMap_PS();\
	ZWRITEENABLE = TRUE;\
	CULLMODE = CCW;\
}\
//=====================================================================================
//ShadowAlphaMap
//=====================================================================================
struct ShadowAlphaMap_VS_INPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD;
};
struct ShadowAlphaMap_VS_OUTPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD0;
	float4 Depth : TEXCOORD1;
};
struct ShadowAlphaMap_PS_OUTPUT
{
	float4 Color0 : COLOR0;
};
ShadowAlphaMap_VS_OUTPUT ShadowAlphaMap_VS(ShadowAlphaMap_VS_INPUT In)
{
	ShadowAlphaMap_VS_OUTPUT Out = (ShadowAlphaMap_VS_OUTPUT)0;

	//シャドウマップ行列
	Out.Pos= mul(mul(In.Pos, mW), mLight);
	Out.Depth.xy =Out.Pos.zw;

	//テクスチャ
	Out.Tex = In.Tex;

	return Out;
}
ShadowAlphaMap_PS_OUTPUT ShadowAlphaMap_PS(ShadowAlphaMap_VS_OUTPUT In)
{
	ShadowAlphaMap_PS_OUTPUT Out = (ShadowAlphaMap_PS_OUTPUT)0;

	//深度を保存
	Out.Color0.rgb = In.Depth.x / In.Depth.y;
	Out.Color0.a = tex2D(Samp, In.Tex).a;

	return Out;
}
#define defPass_ShadowAlphaMap\
pass ShadowAlphaMap\
{\
	VertexShader	= compile vs_3_0 ShadowAlphaMap_VS();\
	PixelShader	= compile ps_3_0 ShadowAlphaMap_PS();\
	AlphaBlendEnable = TRUE;\
	SrcBlend = SRCALPHA;\
	DestBlend = INVSRCALPHA;\
	ZWRITEENABLE = FALSE;\
	CULLMODE = NONE;\
	AddressU[0] = Wrap;\
	AddressV[0] = Wrap;\
	MinFilter[0] = LINEAR;\
	MagFilter[0] = LINEAR;\
}\
//=====================================================================================
//FVF
//=====================================================================================
struct FVF_VS_INPUT
{
	float4 Pos : POSITION;
};
struct FVF_VS_OUTPUT
{
	float4 Pos : POSITION;
	float  Fog : FOG;
};
struct FVF_PS_OUTPUT
{
	float4 Color0 : COLOR0;
};
FVF_VS_OUTPUT FVF_VS(FVF_VS_INPUT In)
{
	FVF_VS_OUTPUT Out = (FVF_VS_OUTPUT)0;

	//位置行列変換
	float4 Pos = mul(In.Pos, mW);
	Out.Pos  = mul(Pos, mVP);

	//フォグ
	Out.Fog = vFog.x + Out.Pos.w  * vFog.y;

	return Out;
}
FVF_PS_OUTPUT FVF_PS(FVF_VS_OUTPUT In)
{
	FVF_PS_OUTPUT Out = (FVF_PS_OUTPUT)0;

	//グローバルのカラーを直接使う
	Out.Color0 = vColor;
	return Out;
}
#define defPass_FVF\
pass FVF\
{\
	VertexShader	= compile vs_3_0 FVF_VS();\
	PixelShader	= compile ps_3_0 FVF_PS();\
	AlphaBlendEnable = TRUE;\
	SrcBlend = SRCALPHA;\
	DestBlend = INVSRCALPHA;\
	AddressU[0] = Clamp;\
	AddressV[0] = Clamp;\
	MinFilter[0] = LINEAR;\
	MagFilter[0] = LINEAR;\
}\
//=====================================================================================
//FVF_Tex
//=====================================================================================
struct FVF_Tex_VS_INPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD;
};
struct FVF_Tex_VS_OUTPUT
{
	float4 Pos : POSITION;
	float  Fog : FOG;
	float2 Tex : TEXCOORD0;
};
struct FVF_Tex_PS_OUTPUT
{
	float4 Color0 : COLOR0;
};
FVF_Tex_VS_OUTPUT FVF_Tex_VS(FVF_Tex_VS_INPUT In)
{
	FVF_Tex_VS_OUTPUT Out = (FVF_Tex_VS_OUTPUT)0;

	//位置行列変換
	float4 Pos = mul(In.Pos, mW);
	Out.Pos  = mul(Pos, mVP);

	//テクスチャ
	Out.Tex = In.Tex;

	//フォグ
	Out.Fog = vFog.x + Out.Pos.w  * vFog.y;

	return Out;
}
FVF_Tex_PS_OUTPUT FVF_Tex_PS(FVF_Tex_VS_OUTPUT In)
{
	FVF_Tex_PS_OUTPUT Out = (FVF_Tex_PS_OUTPUT)0;

	//外部のカラーを使う
	float4 T = tex2D(Samp,In.Tex);
	Out.Color0 = vColor * T;
	Out.Color0.a = vColor.a * T.a;
	return Out;
}
#define defPass_FVF_Tex\
pass FVF_Tex\
{\
	VertexShader	= compile vs_3_0 FVF_Tex_VS();\
	PixelShader	= compile ps_3_0 FVF_Tex_PS();\
	AlphaBlendEnable = TRUE;\
	SrcBlend = SRCALPHA;\
	DestBlend = INVSRCALPHA;\
	AddressU[0] = Clamp;\
	AddressV[0] = Clamp;\
	MinFilter[0] = LINEAR;\
	MagFilter[0] = LINEAR;\
}\
//=====================================================================================
//FVF_Tex_Point
//=====================================================================================
struct FVF_Tex_Point_VS_INPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD;
};
struct FVF_Tex_Point_VS_OUTPUT
{
	float4 Pos : POSITION;
	float  Fog : FOG;
	float2 Tex : TEXCOORD0;
};
struct FVF_Tex_Point_PS_OUTPUT
{
	float4 Color0 : COLOR0;
};
FVF_Tex_Point_VS_OUTPUT FVF_Tex_Point_VS(FVF_Tex_Point_VS_INPUT In)
{
	FVF_Tex_Point_VS_OUTPUT Out = (FVF_Tex_Point_VS_OUTPUT)0;

	//位置行列変換
	float4 Pos = mul(In.Pos, mW);
	Out.Pos  = mul(Pos, mVP);

	//テクスチャ
	Out.Tex = In.Tex;

	//フォグ
	Out.Fog = vFog.x + Out.Pos.w  * vFog.y;

	return Out;
}
FVF_Tex_Point_PS_OUTPUT FVF_Tex_Point_PS(FVF_Tex_Point_VS_OUTPUT In)
{
	FVF_Tex_Point_PS_OUTPUT Out = (FVF_Tex_Point_PS_OUTPUT)0;

	//外部のカラーを使う
	float4 T = tex2D(Samp,In.Tex);
	Out.Color0 = vColor * T;
	Out.Color0.a = vColor.a * T.a;
	return Out;
}
#define defPass_FVF_Tex_Point\
pass FVF_Tex_Point\
{\
	VertexShader	= compile vs_3_0 FVF_Tex_Point_VS();\
	PixelShader	= compile ps_3_0 FVF_Tex_Point_PS();\
	AlphaBlendEnable = TRUE;\
	SrcBlend = SRCALPHA;\
	DestBlend = INVSRCALPHA;\
	AddressU[0] = Clamp;\
	AddressV[0] = Clamp;\
	MinFilter[0] = POINT;\
	MagFilter[0] = POINT;\
}\
//=====================================================================================
//FVF_Tex_One
//=====================================================================================
struct FVF_Tex_One_VS_INPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD;
};
struct FVF_Tex_One_VS_OUTPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD0;
};
struct FVF_Tex_One_PS_OUTPUT
{
	float4 Color0 : COLOR0;
	float4 Color1 : COLOR1;
};
FVF_Tex_One_VS_OUTPUT FVF_Tex_One_VS(FVF_Tex_One_VS_INPUT In)
{
	FVF_Tex_One_VS_OUTPUT Out = (FVF_Tex_One_VS_OUTPUT)0;

	//位置行列変換
	float4 Pos = mul(In.Pos, mW);
	Out.Pos  = mul(Pos, mVP);

	//テクスチャ
	Out.Tex = In.Tex;

	return Out;
}
FVF_Tex_One_PS_OUTPUT FVF_Tex_One_PS(FVF_Tex_One_VS_OUTPUT In)
{
	FVF_Tex_One_PS_OUTPUT Out = (FVF_Tex_One_PS_OUTPUT)0;

	//外部のカラーを使う
	float4 T = tex2D(Samp,In.Tex);
	Out.Color0 = vColor * T;
	Out.Color0.a = vColor.a * T.a;
	Out.Color1 = Out.Color0 * BloomColor;
	return Out;
}
#define defPass_FVF_Tex_One\
pass FVF_Tex_One\
{\
	VertexShader	= compile vs_3_0 FVF_Tex_One_VS();\
	PixelShader	= compile ps_3_0 FVF_Tex_One_PS();\
	AlphaBlendEnable = TRUE;\
	SrcBlend =SRCALPHA;\
	DestBlend =ONE;\
	AddressU[0] = Clamp;\
	AddressV[0] = Clamp;\
	MinFilter[0] = LINEAR;\
	MagFilter[0] = LINEAR;\
	ZWRITEENABLE = FALSE;\
}\
//=====================================================================================
//Tone
//=====================================================================================
struct Tone_VS_INPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD;
};
struct Tone_VS_OUTPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD0;
};
struct Tone_PS_OUTPUT
{
	float4 Color0 : COLOR0;
};
Tone_VS_OUTPUT Tone_VS(Tone_VS_INPUT In)
{
	Tone_VS_OUTPUT Out = (Tone_VS_OUTPUT)0;

	//位置行列変換
	float4 Pos = mul(In.Pos, mW);
	Out.Pos  = mul(Pos, mVP);

	//テクスチャ
	Out.Tex = In.Tex;

	return Out;
}
Tone_PS_OUTPUT Tone_PS(Tone_VS_OUTPUT In)
{
	Tone_PS_OUTPUT Out = (Tone_PS_OUTPUT)0;

	//トーンマッピング
	float Exposure = 1.0f;
	float4 Tone = tex2D(Samp,In.Tex);
	float2 l=PixelUV.xy;
	Exposure=PixelUV.z;
	float Lp=(Exposure/l.r) * max(Tone.r,max(Tone.g,Tone.b));
	float LmSqr=(l.g * l.g)*(l.g * l.g);
	float Scl=( Lp * (1.0f + ( Lp / (LmSqr)))) / (1.0f+Lp);
	Tone.rgb*=Scl;
	Out.Color0 = Tone;

	return Out;
}
#define defPass_Tone\
pass Tone\
{\
	VertexShader	= compile vs_3_0 Tone_VS();\
	PixelShader	= compile ps_3_0 Tone_PS();\
	AddressU[0] = Clamp;\
	AddressV[0] = Clamp;\
	MinFilter[0] = LINEAR;\
	MagFilter[0] = LINEAR;\
}\
//=====================================================================================
//GaussX
//=====================================================================================
struct GaussX_VS_INPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD;
};
struct GaussX_VS_OUTPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD0;
};
struct GaussX_PS_OUTPUT
{
	float4 Color0 : COLOR0;
};
GaussX_VS_OUTPUT GaussX_VS(GaussX_VS_INPUT In)
{
	GaussX_VS_OUTPUT Out = (GaussX_VS_OUTPUT)0;

	//位置行列変換
	float4 Pos = mul(In.Pos, mW);
	Out.Pos  = mul(Pos, mVP);

	//テクスチャ
	Out.Tex = In.Tex;

	return Out;
}
GaussX_PS_OUTPUT GaussX_PS(GaussX_VS_OUTPUT In)
{
	GaussX_PS_OUTPUT Out = (GaussX_PS_OUTPUT)0;

	//ガウスX
	float2 uv[5];
	uv[0]=GaussMap.xz;
	//ガウス分布
	uv[1]=uv[0] * 2.0f;
	uv[2]=uv[0] * 3.0f;
	uv[3]=uv[0] * 4.0f;
	uv[4]=uv[0] * 5.0f;
	float4 GaussMap = tex2D(Samp,In.Tex)   * w[0];
	GaussMap+= tex2D(Samp,In.Tex - uv[0] ) * w[1];
	GaussMap+= tex2D(Samp,In.Tex - uv[1] ) * w[2];
	GaussMap+= tex2D(Samp,In.Tex - uv[2] ) * w[3];
	GaussMap+= tex2D(Samp,In.Tex - uv[3] ) * w[4];
	GaussMap+= tex2D(Samp,In.Tex - uv[4] ) * w[5];
	GaussMap+= tex2D(Samp,In.Tex + uv[0] ) * w[1];
	GaussMap+= tex2D(Samp,In.Tex + uv[1] ) * w[2];
	GaussMap+= tex2D(Samp,In.Tex + uv[2] ) * w[3];
	GaussMap+= tex2D(Samp,In.Tex + uv[3] ) * w[4];
	GaussMap+= tex2D(Samp,In.Tex + uv[4] ) * w[5];
	Out.Color0 = GaussMap;

	return Out;
}
#define defPass_GaussX\
pass GaussX\
{\
	VertexShader	= compile vs_3_0 GaussX_VS();\
	PixelShader	= compile ps_3_0 GaussX_PS();\
	AddressU[0] = Clamp;\
	AddressV[0] = Clamp;\
	MinFilter[0] = LINEAR;\
	MagFilter[0] = LINEAR;\
}\
//=====================================================================================
//GaussY
//=====================================================================================
struct GaussY_VS_INPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD;
};
struct GaussY_VS_OUTPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD0;
};
struct GaussY_PS_OUTPUT
{
	float4 Color0 : COLOR0;
};
GaussY_VS_OUTPUT GaussY_VS(GaussY_VS_INPUT In)
{
	GaussY_VS_OUTPUT Out = (GaussY_VS_OUTPUT)0;

	//位置行列変換
	float4 Pos = mul(In.Pos, mW);
	Out.Pos  = mul(Pos, mVP);

	//テクスチャ
	Out.Tex = In.Tex;

	return Out;
}
GaussY_PS_OUTPUT GaussY_PS(GaussY_VS_OUTPUT In)
{
	GaussY_PS_OUTPUT Out = (GaussY_PS_OUTPUT)0;

	//ガウスY
	float2 uv[5];
	uv[0]=GaussMap.zy;
	//ガウス分布
	uv[1]=uv[0] * 2.0f;
	uv[2]=uv[0] * 3.0f;
	uv[3]=uv[0] * 4.0f;
	uv[4]=uv[0] * 5.0f;
	float4 GaussMap = tex2D(Samp,In.Tex)   * w[0];
	GaussMap+= tex2D(Samp,In.Tex - uv[0] ) * w[1];
	GaussMap+= tex2D(Samp,In.Tex - uv[1] ) * w[2];
	GaussMap+= tex2D(Samp,In.Tex - uv[2] ) * w[3];
	GaussMap+= tex2D(Samp,In.Tex - uv[3] ) * w[4];
	GaussMap+= tex2D(Samp,In.Tex - uv[4] ) * w[5];
	GaussMap+= tex2D(Samp,In.Tex + uv[0] ) * w[1];
	GaussMap+= tex2D(Samp,In.Tex + uv[1] ) * w[2];
	GaussMap+= tex2D(Samp,In.Tex + uv[2] ) * w[3];
	GaussMap+= tex2D(Samp,In.Tex + uv[3] ) * w[4];
	GaussMap+= tex2D(Samp,In.Tex + uv[4] ) * w[5];
	Out.Color0 = GaussMap;

	return Out;
}
#define defPass_GaussY\
pass GaussY\
{\
	VertexShader	= compile vs_3_0 GaussY_VS();\
	PixelShader	= compile ps_3_0 GaussY_PS();\
	AddressU[0] = Clamp;\
	AddressV[0] = Clamp;\
	MinFilter[0] = LINEAR;\
	MagFilter[0] = LINEAR;\
}\
//=====================================================================================
//technique
//=====================================================================================
technique TShader
{
	defPass_Mesh
	defPass_Mesh_Tex
	defPass_Mesh_AlphaTex
	defPass_Mesh_Bump
	defPass_ShadowMap
	defPass_ShadowAlphaMap
	defPass_FVF
	defPass_FVF_Tex
	defPass_FVF_Tex_Point
	defPass_FVF_Tex_One
	defPass_Tone
	defPass_GaussX
	defPass_GaussY
}
