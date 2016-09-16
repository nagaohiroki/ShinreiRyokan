#include "main.h"
VOID fxManager::GandSampSet()
{

	//GLOBAL
	Global =
		"\nfloat4x4 mW =init4x4;//ワールドトランス\n"
		"float4x4 mVP =init4x4;//ビュー*プロジェクト\n"
		"float4x4 mLight =init4x4;//ライト視点の行列\n"
		"float4 vLightDir =float4(0.0f,0.0f,0.0f,0.0f);//ライトの方向\n"
		"float4 vColor =float4(0.0f,0.0f,0.0f,0.0f);//ライト＊メッシュの色\n"
		"float3 vEyePos =float3(0.0f,0.0f,0.0f);//カメラの位置（ローカル座標系）\n"
		"float4 SP =float4(0.0f,0.0f,0.0f,0.0f);//スペキュラ\n"
		"float4 SBias =float4(0.0f,0.0f,0.0f,0.0f);//xにバイアスyに影の濃さ\n"
		"float4 vFog =float4(0.0f,0.0f,0.0f,0.0f);//フォグ\n"
		"float4 vFogColor =float4(0.0f,0.0f,0.0f,0.0f);//フォグの色\n"
		"int vFogUse =0;//フォグのオンオフ\n"
		"float4 PixelUV =float4(0.0f,0.0f,0.0f,0.0f);//ブラー\n"
		"float4 BloomColor =float4(0.0f,0.0f,0.0f,0.0f); //ライトブルーム\n"
		"float3 CamPos =float3(0.0f,0.0f,0.0f);//カメラの位置(ワールド) \n"
		"float4 PLightDif = float4(0.0f,0.0f,0.0f,0.0f);	//ポイントライトの色\n"
		"float4 PLightPos = float4(0.0f,0.0f,0.0f,0.0f);	//ポイントライトの位置\n"
		"float4 PLightVec = float4(0.0f,0.0f,0.0f,0.0f);	//スポットライトベクトルとwに射影角\n"
		"texture Tex;//デカールテクスチャ\n"
		"texture ShadowTex;//シャドウテクスチャ\n"
		"texture NormalTex;//法線テクスチャ\n"		
		"float w[6] = {0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};//ガウスの重み\n"
		"float4 GaussMap = float4(0.0f,0.0f,0.0f,0.0f);//ガウスのマップサイズ\n"


		
		;
	//SAMPLER
	Sampler =
		"sampler     Samp           = sampler_state{Texture = <Tex>;};      //デカールテクスチャ\n"
		"sampler     ShadowTexSamp  = sampler_state{Texture = <ShadowTex>;};//シャドウマップテクスチャ\n"
		"sampler     NormalSamp     = sampler_state{Texture = <NormalTex>;};//法線テクスチャ\n"
		;

}
//本文
VOID fxManager::SetPass()
{
	//バーテックスシェーダ----------------------------------------------------------------------------------------
	string vsPos =
		"\t//位置行列変換\n"
		"\tfloat4 Pos = mul(In.Pos, mW);\n"
		"\tOut.Pos  = mul(Pos, mVP);\n\n";
	string vsLambert=
		"\t//ランバート反射\n"
		"\tOut.Color = vColor * max(vLightDir.w, dot(In.Normal,vLightDir));\n\n";
	string vsPhong =
		"\t//鏡面反射\n"
		"\tOut.vLight = In.Normal.xyz;\n"
		"\tOut.vEye = vEyePos - In.Pos.xyz;\n\n";
	string vsFog =
		"\t//フォグ\n"
		"\tOut.Fog = vFog.x + Out.Pos.w  * vFog.y;\n\n";
	string vsPoint =
		"\t//ポイントライト\n"
		"\tOut.LclPos = Pos;//位置\n"
		"\tOut.LclNormal = mul(float4(In.Normal.xyz,0.0f),(float3x3)mW);//法線ベクトル\n\n";
	string vsShadow =
		"\t//シャドウマップ\n"
		"\tOut.Depth = mul(Pos, mLight);//深度を保存\n"
		"\tOut.Depth.x = ( Out.Depth.x + Out.Depth.w) * 0.5f;\n"
		"\tOut.Depth.y = (-Out.Depth.y + Out.Depth.w) * 0.5f;\n\n";
	string vsTex=
		"\t//テクスチャ\n"
		"\tOut.Tex = In.Tex;\n\n";
	string vsBumpPhong=
		"\t//鏡面反射用のベクトル\n"
		"\tfloat3 E = normalize(vEyePos - In.Pos.xyz);//視線ベクトル\n"
		"\tOut.vEye    =float3(dot(E,In.Tangent),dot(E,In.Binormal),dot(E,In.Normal));\n"
		"\tOut.vEye=normalize(Out.vEye);\n\n"
		"\t//ライトベクトル\n"
		"\tfloat3 L =vLightDir.xyz;\n"
		"\tOut.vLight=float3(dot(L,In.Tangent),dot(L,In.Binormal),dot(L,In.Normal));\n"
		"\tOut.vLight=normalize(Out.vLight);\n\n";
	string vsShadowMap=
		"\t//シャドウマップ行列\n"
		"\tOut.Pos= mul(mul(In.Pos, mW), mLight);\n"
		"\tOut.Depth.xy =Out.Pos.zw;\n\n";
	string vsSkinPos=
		"\t//スキン行列変換\n"
		"\tint4 IndexVector	= D3DCOLORtoUBYTE4(In.Indices);\n"
		"\tint 	Index[4]	= (int[4])IndexVector;\n"
		"\tfloat	Weight[4]	= (float[4])In.Weight;\n"
		"\tfloat	LBW	= 0.0f;\n"
		"\tfloat4 	Pos	= float4(0.0f,0.0f,0.0f,0.0f);\n"
		"\tint i;\n"
		"\tfor(i = 0; i < BoneNum - 1 ; i++)\n"
		"\t{\n"
		"\t\tLBW += Weight[i];\n"
		"\t\tPos  += mul(In.Pos,mWSM[Index[i]]) * Weight[i];\n"
		"\t}\n"
		"\tLBW	=  1.0f-LBW;\n"
		"\tPos 	+= (mul(In.Pos,mWSM[Index[BoneNum-1]]) * LBW);\n"
		"\tOut.Pos= mul(Pos,mVP);\n\n";
	string vsSkinShadowPos=
		"\t//スキンシャドウ行列変換\n"
		"\tint4 IndexVector	= D3DCOLORtoUBYTE4(In.Indices);\n"
		"\tint 	Index[4]	= (int[4])IndexVector;\n"
		"\tfloat	Weight[4]	= (float[4])In.Weight;\n"
		"\tfloat	LBW	= 0.0f;\n"
		"\tfloat4 	Pos	= float4(0.0f,0.0f,0.0f,0.0f);\n"
		"\tint i;\n"
		"\tfor(i = 0; i < BoneNum-1 ; i++)\n"
		"\t{\n"
		"\t\tLBW += Weight[i];\n"
		"\t\tPos  += mul(In.Pos,mSLP[Index[i]]) * Weight[i];\n"
		"\t}\n"
		"\tLBW	=  1.0f-LBW;\n"
		"\tPos 	+= (mul(In.Pos,mSLP[Index[BoneNum-1]]) * LBW);\n"
		"\tOut.Pos= mul(Pos, mLight);\n"
		"\tOut.Depth = Out.Pos;\n\n";

	string vsBicubic=
		"\t//バイキュービック\n"
		"\tfloat2 wh = float2(Bicubic.x,Bicubic.y);\n"
		"\tfloat w15 = Bicubic.w * 0.75f;\n"
		"\tfloat w05 = Bicubic.w * 0.25f;\n"
	
		"\tfloat2 T = In.Tex;\n"
		"\tOut.T0 = T + float2(-w15 / wh.x, w15 / wh.y);\n"
		"\tOut.T1 = T + float2(-w15 / wh.x, w05 / wh.y);\n"
		"\tOut.T2 = T + float2(-w15 / wh.x,-w05 / wh.y);\n"
		"\tOut.T3 = T + float2(-w15 / wh.x,-w15 / wh.y);\n"
		"\tOut.T4 = T + float2(-w05 / wh.x, w15 / wh.y);\n"
		"\tOut.T5 = T + float2(-w05 / wh.x, w05 / wh.y);\n"
		"\tOut.T6 = T + float2(-w05 / wh.x,-w05 / wh.y);\n"
		"\tOut.T7 = T + float2(-w05 / wh.x,-w15 / wh.y);\n"
		;



 
	//ピクセルシェーダ----------------------------------------------------------------------------------------
	string psPhong=
		"\t//鏡面反射\n"
		"\tfloat3 N = normalize(In.vLight);//法線ベクトル\n"
		"\tfloat3 V = normalize(In.vEye);//視線ベクトル\n"
		"\tfloat3 H = normalize( vLightDir.xyz + V);//ハーフベクトル\n"
		"\tfloat4 S = pow(max(0.0f,dot(N,H)),SP.w) * SP;//鏡面反射\n"
		"\tOut.Color0 += S;\n\n";
	string psBumpDif=
		"\t//バンプマップ拡散反射\n"
		"\tfloat3 N = 2.0f * tex2D( NormalSamp,In.Tex).xyz - 1.0f;	// 法線マップからの法線\n"
		"\tfloat3 H = normalize(In.vLight + In.vEye);//ハーフベクトル\n"
		"\tOut.Color0 = vColor * max(vLightDir.w,dot(N,In.vLight));//拡散反射\n\n";

	string psBumpDif2=
		"\t//視差マッピング\n"
		"\tfloat h = tex2D(NormalSamp, In.Tex ).a;\n"
		"\tfloat2 Tex = In.Tex + NormalHeight *  h * In.vEye.xy;\n"
		"\tfloat3 N = 2.0f * tex2D( NormalSamp,Tex).xyz - 1.0f;	// 法線マップからの法線\n"
		"\tfloat3 H = normalize(In.vLight + In.vEye);//ハーフベクトル\n"
		"\tOut.Color0 = vColor * max(vLightDir.w,dot(N,In.vLight));//拡散反射\n\n";
		;

	string psBumpPhong=
		"\t//バンプマップ鏡面反射\n"
		"\tfloat4 S = pow(max(0.0f,dot(N,H)),SP.w) * SP;//鏡面反射\n"
		"\tOut.Color0 += S;\n\n";	

	string psShadow=
		"\t//影\n"
		"\tfloat4 Stex = float4(In.Depth.x,In.Depth.y,0.0f,In.Depth.w);\n"
		"\tfloat SM_Z	=tex2Dproj(ShadowTexSamp,Stex).x;\n"
		"\tfloat d = (In.Depth.z / In.Depth.w) - SBias.x;\n"
		"\tfloat shadow = (SM_Z < d) ? SBias.y : 1.0f;\n"
		"\tOut.Color0 *= shadow;\n\n";
	string psTex=
		"\t//テクスチャ\n"
		"\tfloat4 T = tex2D(Samp, In.Tex);\n"
		"\tOut.Color0 *= T;\n\n";

	string psTexDif=
		"\t//テクスチャ\n"
		"\tfloat4 T = tex2D(Samp, In.Tex);\n"
		"\tOut.Color0 = T;\n\n";
	string psDiff=
		"\t//ディフューズ\n"
		"\tOut.Color0 = In.Color;\n\n";
	string psPoint=
		"\t//ポイントスポットライト\n"
		"\tfloat3 LV    = normalize(PLightPos.xyz - In.LclPos);//ライトベクトル\n"
		"\tfloat  gen   = PLightPos.w / length(PLightPos -  In.LclPos);//減衰\n"
		"\tfloat4 dif   = PLightDif * saturate(dot(  In.LclNormal ,LV ));//デフューズ\n"
		"\tfloat  Ldot  = saturate(dot(LV,PLightVec.xyz) - PLightVec.w);//スポットに納める\n"
		"\tfloat4 spc   = pow(max(0,saturate(dot( In.LclNormal,PLightVec.xyz) )),SP.w);//スペキュラ\n" 
		"\tfloat4 Point = ( dif + spc ) * gen * Ldot;\n"
		"\tOut.Color0 += Point;\n\n";		
	string psBloom=
		"\t//ブルーム\n"
		"\tOut.Color1 = ( S + Point ) * BloomColor;\n\n";

	string psColorDif=
		"\t//グローバルのカラーを直接使う\n"
		"\tOut.Color0 = vColor;\n";
		"\tOut.Color0.a = vColor.a;\n\n";

	string psAlpha=
		"\t//アルファ\n"
		"\tOut.Color0.a = In.Color.a;\n\n";
	string psTexAlpha=
		"\t//テクスチャアルファ\n"
		"\tOut.Color0.a = In.Color.a * T.a;\n\n";		
	
	string psAlpha2=
		"\t//アルファ\n"
		"\tOut.Color0.a = Out.Color1.a = vColor.a;\n\n";
	string psTexAlpha2=
		"\t//テクスチャアルファ\n"
		"\tOut.Color0.a = Out.Color1.a = vColor.a * T.a;\n\n";		
	string psShadowMap=
		"\t//深度を保存\n"
		"\tOut.Color0 = In.Depth.x / In.Depth.y;\n\n";
	string psShadowMapAlphaTex=
		"\t//深度を保存\n"
		"\tOut.Color0.rgb = In.Depth.x / In.Depth.y;\n"
		"\tOut.Color0.a = tex2D(Samp, In.Tex).a;\n\n";

	
	string psGaussX=
		"\t//ガウスX\n"
		"\tfloat2 uv[5];\n"
		"\tuv[0]=GaussMap.xz;\n";
	string psGaussY=
		"\t//ガウスY\n"
		"\tfloat2 uv[5];\n"
		"\tuv[0]=GaussMap.zy;\n";
	string psGaussMap = 
		"\t//ガウス分布\n"
		"\tuv[1]=uv[0] * 2.0f;\n"
		"\tuv[2]=uv[0] * 3.0f;\n"
		"\tuv[3]=uv[0] * 4.0f;\n"
		"\tuv[4]=uv[0] * 5.0f;\n"
		"\tfloat4 GaussMap = tex2D(Samp,In.Tex)   * w[0];\n"
		"\tGaussMap+= tex2D(Samp,In.Tex - uv[0] ) * w[1];\n"
		"\tGaussMap+= tex2D(Samp,In.Tex - uv[1] ) * w[2];\n"
		"\tGaussMap+= tex2D(Samp,In.Tex - uv[2] ) * w[3];\n"
		"\tGaussMap+= tex2D(Samp,In.Tex - uv[3] ) * w[4];\n"
		"\tGaussMap+= tex2D(Samp,In.Tex - uv[4] ) * w[5];\n"
		"\tGaussMap+= tex2D(Samp,In.Tex + uv[0] ) * w[1];\n"
		"\tGaussMap+= tex2D(Samp,In.Tex + uv[1] ) * w[2];\n"
		"\tGaussMap+= tex2D(Samp,In.Tex + uv[2] ) * w[3];\n"
		"\tGaussMap+= tex2D(Samp,In.Tex + uv[3] ) * w[4];\n"
		"\tGaussMap+= tex2D(Samp,In.Tex + uv[4] ) * w[5];\n"
		"\tOut.Color0 = GaussMap;\n\n";

	string psTone=
		"\t//トーンマッピング\n"
		"\tfloat Exposure = 1.0f;\n"
		"\tfloat4 Tone = tex2D(Samp,In.Tex);\n"
		"\tfloat2 l=PixelUV.xy;\n"
		"\tExposure=PixelUV.z;\n"
		"\tfloat Lp=(Exposure/l.r) * max(Tone.r,max(Tone.g,Tone.b));\n"	
		"\tfloat LmSqr=(l.g * l.g)*(l.g * l.g);\n"
		"\tfloat Scl=( Lp * (1.0f + ( Lp / (LmSqr)))) / (1.0f+Lp);\n"
		"\tTone.rgb*=Scl;\n"
		"\tOut.Color0 = Tone;\n\n";

	string psvColorTexAlpha=
		"\t//外部のカラーを使う\n"
		"\tfloat4 T = tex2D(Samp,In.Tex);\n"
		"\tOut.Color0 = vColor * T;\n"
		"\tOut.Color0.a = vColor.a * T.a;\n"
		;

	string psvColorTexAlphaBloom=
		"\t//外部のカラーを使う\n"
		"\tfloat4 T = tex2D(Samp,In.Tex);\n"
		"\tOut.Color0 = vColor * T;\n"
		"\tOut.Color0.a = vColor.a * T.a;\n"
		"\tOut.Color1 = Out.Color0 * BloomColor;\n"	;

	string psBicuvic=
		"\t//バイキュービックフィルタを作成\n"
		"\tfloat4 col00 = tex2D(Samp,In.T0);\n"
		"\tfloat4 col01 = tex2D(Samp,In.T1);\n"
		"\tfloat4 col02 = tex2D(Samp,In.T2);\n"
		"\tfloat4 col03 = tex2D(Samp,In.T3);\n"
		
		"\tfloat4 col10 = tex2D(Samp,In.T4);\n"
		"\tfloat4 col11 = tex2D(Samp,In.T5);\n"
		"\tfloat4 col12 = tex2D(Samp,In.T6);\n"
		"\tfloat4 col13 = tex2D(Samp,In.T7);\n"

		"\tfloat2 d2u = float2(Bicubic.z,0.0f);\n"	
		"\tfloat4 col20 = tex2D(Samp,In.T0 + d2u);\n"
		"\tfloat4 col21 = tex2D(Samp,In.T1 + d2u);\n"
		"\tfloat4 col22 = tex2D(Samp,In.T2 + d2u);\n"
		"\tfloat4 col23 = tex2D(Samp,In.T3 + d2u);\n"
	
		"\tfloat4 col30 = tex2D(Samp,In.T4 + d2u);\n"
		"\tfloat4 col31 = tex2D(Samp,In.T5 + d2u);\n"
		"\tfloat4 col32 = tex2D(Samp,In.T6 + d2u);\n"
		"\tfloat4 col33 = tex2D(Samp,In.T7 + d2u);\n"
#if 1
		"\tconst float4 w0 = float4( 0.0f, 1.0f, 0.0f, 0.0f);\n"
		"\tconst float4 w1 = float4(-1.0f, 0.0f, 1.0f, 0.0f);\n"
		"\tconst float4 w2 = float4( 2.0f,-2.0f, 1.0f,-1.0f);\n"
		"\tconst float4 w3 = float4(-1.0f, 1.0f,-1.0f, 1.0f);\n"
#else
		"\tconst float4 w0 = float4( 0.0, 1.0, 0.0, 0.0);\n"
		"\tconst float4 w1 = float4(-0.5, 0.0, 0.5, 0.0);\n"
		"\tconst float4 w2 = float4( 1.0,-2.5, 1.0,-0.5);\n"
		"\tconst float4 w3 = float4(-0.5, 1.5,-1.5, 0.5);\n"
#endif
		"\tfloat w05 = Bicubic.w * 0.25f;\n"
		"\tfloat2 fUV = (In.T6 + float2(w05/Bicubic.x,w05/Bicubic.y));\n"
		"\tfloat2 fUV2 = fUV * fUV;\n"
		"\tfloat2 fUV3 = fUV * fUV2;\n"
		"\tfloat4 u = fUV3.x * w3 + fUV2.x * w2 + fUV.x * w1 + w0;\n"
		"\tfloat4 v = fUV3.y * w3 + fUV2.y * w2 + fUV.y * w1 + w0;\n"


		"\tfloat4 col0 = u.x * col00 + u.y * col10 + u.z * col20 + u.w * col30;\n"
		"\tfloat4 col1 = u.x * col01 + u.y * col11 + u.z * col21 + u.w * col31;\n"
		"\tfloat4 col2 = u.x * col02 + u.y * col12 + u.z * col22 + u.w * col32;\n"
		"\tfloat4 col3 = u.x * col03 + u.y * col13 + u.z * col23 + u.w * col33;\n"
		"\tOut.Color0 = v.x * col0 + v.y * col1 + v.z * col2 + v.w * col3;\n"
		;

	string psWaveMap = 
		"\t//波マップの更新処理\n"
		"\tfloat4 Wave = tex2D(Samp,In.Tex);\n"
		"\tfloat H1 = tex2D(Samp,In.Tex + float2( WaveOffPos.x,0.0f)).r;\n"
		"\tfloat H2 = tex2D(Samp,In.Tex + float2(0.0f, WaveOffPos.y)).r;\n"
		"\tfloat H3 = tex2D(Samp,In.Tex + float2(-WaveOffPos.x,0.0f)).r;\n"
		"\tfloat H4 = tex2D(Samp,In.Tex + float2(0.0f,-WaveOffPos.y)).r;\n"
		"\tfloat V  = ((H1 + H2 + H3 + H4) * 0.25f - Wave.r) * WaveSpringHeight.x + Wave.g;\n"
		"\tfloat H  = Wave.r + V;\n"
		"\tif(distance(In.Tex,WaveOffPos.zw) < 0.005f ){ V += WaveSpringHeight.y; }\n"
		"\tOut.Color0 = float4(H,V,0.0f,0.0f);\n"
		;

	string psWaveBumpMap = 
		"\t//波の法線マップを作成\n"
		"\tfloat H1 = tex2D(Samp,In.Tex + float2( WaveOffPos.x,0.0f)).r;\n"
		"\tfloat H2 = tex2D(Samp,In.Tex + float2(0.0f, WaveOffPos.y)).r;\n"
		"\tfloat H3 = tex2D(Samp,In.Tex + float2(-WaveOffPos.x,0.0f)).r;\n"
		"\tfloat H4 = tex2D(Samp,In.Tex + float2(0.0f,-WaveOffPos.y)).r;\n"
		"\tfloat tu = 0.5f * (H3 - H1)  + 0.5f;\n"
		"\tfloat tv = 0.5f * (H4 - H2)  + 0.5f;\n"
		"\tOut.Color0 = float4(tu,tv,1.0f,tex2D(Samp,In.Tex).r * 0.5f + 0.5f);\n"
		;

	//パイプライン----------------------------------------------------------------------------------------
	string pipe="";
	string ppAlpha=
		"\tAlphaBlendEnable = TRUE;\\\n";
	string ppOne=
		"\tSrcBlend =SRCALPHA;\\\n"
		"\tDestBlend =ONE;\\\n";
	string ppSrcInv=
		"\tSrcBlend = SRCALPHA;\\\n"
		"\tDestBlend = INVSRCALPHA;\\\n";	
	string ppZTRUE=
		"\tZWRITEENABLE = TRUE;\\\n"
		"\tCULLMODE = CCW;\\\n";
	string ppZFALSE=
		"\tZWRITEENABLE = FALSE;\\\n"
		"\tCULLMODE = NONE;\\\n";
	string ppZWRITE=
		"\tZWRITEENABLE = FALSE;\\\n"
		;

	
	string ppClamp0=		
		"\tAddressU[0] = Clamp;\\\n"
		"\tAddressV[0] = Clamp;\\\n";

	string ppWrap0=		
		"\tAddressU[0] = Wrap;\\\n"
		"\tAddressV[0] = Wrap;\\\n";
	string ppWrap2=		
		"\tAddressU[2] = Wrap;\\\n"
		"\tAddressV[2] = Wrap;\\\n";

	string ppBorder0=		
		"\tAddressU[0] = Border;\\\n"
		"\tAddressV[0] = Border;\\\n";
	string ppLinear0=
		"\tMinFilter[0] = LINEAR;\\\n"
		"\tMagFilter[0] = LINEAR;\\\n";

	string ppLinear2=
		"\tMinFilter[2] = LINEAR;\\\n"
		"\tMagFilter[2] = LINEAR;\\\n";
	string ppPoint0=
		"\tMinFilter[0] = POINT;\\\n"
		"\tMagFilter[0] = POINT;\\\n";


	string ppFog=
		"\tFogEnable =vFogUse;\\\n"
		"\tFogVertexMode = Linear;\\\n"
		"\tFogColor = vFogColor;\\\n";
	
	//メッシュの描画
	Set("Mesh",
		vsPos  + vsLambert + vsPhong + vsFog + vsPoint + vsShadow,
		psDiff + psShadow + psPhong + psPoint  + psBloom+ psAlpha2,
		ppAlpha+ ppSrcInv + ppWrap0 + ppLinear0 + ppFog + ppZTRUE );
	Set("Mesh_Tex",
		vsPos  + vsLambert + vsPhong + vsFog + vsPoint + vsShadow + vsTex,
		psDiff + psTex + psShadow + psPhong + psPoint + psBloom + psTexAlpha2,
		ppAlpha+ ppSrcInv + ppWrap0 + ppLinear0  + ppFog + ppZTRUE );
	Set("Mesh_AlphaTex",
		vsPos  + vsLambert + vsPhong + vsFog + vsPoint + vsShadow + vsTex,
		psDiff + psTex + psShadow + psPhong + psPoint  + psBloom+ psTexAlpha2,
		ppAlpha+ ppSrcInv + ppWrap0 + ppLinear0  + ppFog + ppZFALSE);		
	Set("Mesh_Bump",
		vsPos  + vsBumpPhong + vsFog + vsPoint + vsShadow + vsTex,
		psBumpDif + psTex + psShadow + psBumpPhong + psPoint + psBloom + psTexAlpha2,
		ppAlpha+ ppSrcInv + ppWrap0 + ppLinear0  + ppFog + ppZTRUE+ ppWrap2 + ppLinear2 );
	//シャドウマップ
	Set("ShadowMap",vsShadowMap,psShadowMap,ppZTRUE);
	Set("ShadowAlphaMap",vsShadowMap + vsTex,psShadowMapAlphaTex,ppAlpha+ppSrcInv+ppZFALSE+ppWrap0 + ppLinear0 );		
	/*
	//スキンメッシュの描画
	Set("Mesh_Skin",
		vsSkinPos+ vsLambert + vsPhong + vsFog + vsPoint + vsShadow + vsTex,
		psDiff + psTex + psShadow + psPhong + psPoint + psBloom+ psTexAlpha2 ,
		ppAlpha+ ppSrcInv + ppWrap0 + ppLinear0  + ppFog + ppZTRUE );
	Set("Mesh_SkinShadow",vsSkinShadowPos,psShadowMap,ppZTRUE);
	*/
	//FVFの描画
	Set("FVF",
		vsPos + vsFog,
		psColorDif,
		ppAlpha + ppSrcInv + ppClamp0+ ppLinear0);
	Set("FVF_Tex",
		vsPos + vsTex + vsFog,
		psvColorTexAlpha,
		ppAlpha + ppSrcInv + ppClamp0 + ppLinear0
		);
		Set("FVF_Tex_Point",
		vsPos + vsTex + vsFog,
		psvColorTexAlpha,
		ppAlpha + ppSrcInv + ppClamp0 + ppPoint0
		);
	Set("FVF_Tex_One",
		vsPos + vsTex,
		psvColorTexAlphaBloom,
		ppAlpha + ppOne +ppClamp0+ ppLinear0 + ppZWRITE);

	//ポストエフェクト
	Set("Tone",vsPos + vsTex,psTone,ppClamp0+ ppLinear0);
	Set("GaussX",vsPos + vsTex,psGaussX + psGaussMap,ppClamp0 + ppLinear0);
	Set("GaussY",vsPos + vsTex,psGaussY + psGaussMap,ppClamp0 + ppLinear0);
/*
	Set("Bicubic",vsPos + vsBicubic,psBicuvic,ppClamp0 + ppPoint0);
	
	Set("Mesh_Bump2",
		vsPos  + vsBumpPhong + vsFog + vsPoint + vsShadow + vsTex,
		psBumpDif2 + psTex + psShadow + psBumpPhong + psPoint + psBloom + psTexAlpha2,
		ppAlpha+ ppSrcInv + ppWrap0 + ppLinear0  + ppFog + ppZTRUE+ ppWrap2 + ppLinear2 );

	//波
	Set("WaveMap",vsPos+ vsTex,psWaveMap,ppPoint0);
	Set("WaveBumpMap",vsPos+ vsTex,psWaveBumpMap,ppPoint0);
	Set("WaveBumpTex",vsPos+ vsTex + vsBumpPhong,psBumpDif2 + psBumpPhong,ppLinear0 + ppLinear2);

	*/

}