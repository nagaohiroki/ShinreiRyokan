#pragma once
//================================
//外部ファイルとのアクセス
//================================
class CFile
{
private:	
public:
	CFile();
	VOID txt(const TCHAR*,const TCHAR*);//テキストファイル(ファイル名,テキスト);
	VOID atxt(const TCHAR*,const TCHAR*);//テキストファイル(ファイル名,テキスト);(テキストに書き足す)
	VOID Debug(TCHAR*);	

};

//Vec3算術
class vec3Ari
{
public:
	vec3Ari(){}
	//VEC3のxyzごとの乗
	D3DXVECTOR3 D3DXVec3Multi(D3DXVECTOR3* v1,D3DXVECTOR3* v2)
	{
		return D3DXVECTOR3(
			v1->x * v2->x,
			v1->y * v2->y,
			v1->z * v2->z);
	}
	//Vec3の除
	D3DXVECTOR3 D3DXVec3Div(D3DXVECTOR3* v1,D3DXVECTOR3* v2)
	{
		return D3DXVECTOR3(
			v1->x / v2->x,
			v1->y / v2->y,
			v1->z / v2->z);
	}
	//左上を(0,0)ワールド座標からスクリーン座標に変換(出力,ワールド位置,射影行列,スクリーン横サイズ,スクリーン縦サイズ)
	D3DXVECTOR3 D3DXVec3WtoS(D3DXVECTOR3* Out,D3DXVECTOR3 *Pos,D3DXMATRIX* mat,UINT w,UINT h)
	{
		//キャラのスクリーン座標
 		D3DXVECTOR4 out;
		D3DXVec4Transform(&out,&D3DXVECTOR4(Pos->x,Pos->y,Pos->z,1.0f),mat);
		out/=out.w;
		Out->x=(out.x+1.0f) * (w/2);
		Out->y=-(out.y-1.0f) * (h/2);
		Out->z=out.z;
		return *Out;
	}
	//中心を(0,0)ワールド座標からスクリーン座標に変換(出力,ワールド位置,射影行列,スクリーン横サイズ,スクリーン縦サイズ)
	D3DXVECTOR3 D3DXVec3WtoSCent(D3DXVECTOR3* Out,D3DXVECTOR3 *Pos,D3DXMATRIX* mat,UINT w,UINT h)
	{
		//キャラのスクリーン座標
 		D3DXVECTOR4 out;
		D3DXVec4Transform(&out,&D3DXVECTOR4(Pos->x,Pos->y,Pos->z,1.0f),mat);
		out /= out.w;
		Out->x = out.x * (w / 2);
		Out->y = out.y * (h / 2);
		Out->z = 0.0f;//out.z;
		return *Out;
	}
	//3ベクトルのもっとも多い値を返す
	float D3DXVec3Top(D3DXVECTOR3 *v)
	{
		if(v->x >= v->y)
		{
			if(v->x >= v->z){return v->x;}
		}
		else
		{
			if(v->y >= v->z){return v->y;}
		}
		return v->z;
	}

	//ベクトルをなす角で返す(出力,位置,注視点)
	D3DXVECTOR3 AtLookYpr(D3DXVECTOR3* out,D3DXVECTOR3* Eye,D3DXVECTOR3* At)
	{
		
		D3DXVECTOR3 vec(*At - *Eye);
		D3DXVECTOR3 vZ,vY;
		D3DXMATRIX mR;
		D3DXVec3Normalize(&vec,&vec);
		D3DXMatrixRotationY(&mR,atan2(vec.x,vec.z));
		D3DXVec3TransformCoord(&vY,&D3DXVECTOR3(0.0f,1.0f,0.0f),&mR);
		D3DXVec3TransformCoord(&vZ,&D3DXVECTOR3(0.0f,0.0f,1.0f),&mR);

		out->y=D3DXToDegree(atan2(vec.x,vec.z));
		out->x=D3DXToDegree(atan2(
			D3DXVec3Dot(&vZ,&vec),
			D3DXVec3Dot(&vY,&vec)));
		return *out;
	}
	//ベクトルをなす角で返す(出力,ベクトル)
	D3DXVECTOR3 AtLookYpr(D3DXVECTOR3* out,D3DXVECTOR3* vec)
	{
		D3DXVECTOR3 vZ,vY;
		D3DXMATRIX mR;
		D3DXMatrixRotationY(&mR,atan2(vec->x,vec->z));
		D3DXVec3TransformCoord(&vY,&D3DXVECTOR3(0.0f,1.0f,0.0f),&mR);
		D3DXVec3TransformCoord(&vZ,&D3DXVECTOR3(0.0f,0.0f,1.0f),&mR);

		out->y=D3DXToDegree(atan2(vec->x,vec->z));
		out->x=D3DXToDegree(atan2(
			D3DXVec3Dot(&vZ,vec),
			D3DXVec3Dot(&vY,vec)));
		return *out;
	}


};
//===================================================
//アニメーションキー
//===================================================
template<class T>
class AKey
{
private:
	typedef std::map<int,T> MapT;
	typedef std::pair<int,T> pT;
	//値を返す
	T ValA( int key )
	{
		//一致するキーがあれば直接出力
		MapT::iterator it = val.find(key);
		if( it != val.end() ){	return (*it).second;}
		//無ければ前後のキーを計算する
		MapT::iterator low = val.lower_bound(key);
		MapT::iterator high = low;
		--low;
		return (*low).second + ((*high).second - (*low).second) *
			   (float)(key - (*low).first) / (float)((*high).first - (*low).first);
	}	
public:	
	MapT val;
	AKey(){}
	//最終キー
	int MaxKey()
	{
		return val.rbegin()->first; 
	}	
	VOID DeleteKey(int k)
	{
		val.erase(k);
	}
	VOID DeleteAll()
	{
		val.clear();
	}
	//キーをセット
	VOID SetKey( int k,T v )
	{	
		val.insert(pT(k,v));
	}		
	//ループ
	T Val( int key )
	{
		return ValA(key % MaxKey());	
	}
	//ワンループ
	T Val1( int key )
	{
		if(key <= MaxKey() ){return ValA(key); }
		return ValA(MaxKey()); 
	}

};