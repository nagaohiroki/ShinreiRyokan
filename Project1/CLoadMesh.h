#pragma once
//マテリアル
class CMtrl
{
private:
	//テクスチャの名前でテクスチャ番号を返す
	int ReTexNum(TCHAR*,Arc_Files* );
public:
	//モデル内のテクスチャの名前
	TCHAR TexName[MAX_PATH];
	//マテリアル
	D3DMATERIAL9 m_Mtrl;
	//テクスチャ番号
	int m_iTex;
	//法線テクスチャ番号
	int m_iNTex;
	//エフェクトパス
	int m_iTexPass;
	//コンストラクタ
	CMtrl();
	//テクスチャのナンバーを返す
	VOID SetTexNum(Arc_Files*);	
};
//モデル
class CModel
{
private:
	
	//マテリアル、テクスチャ、サイズの取得
	HRESULT LoadMtrl(LPD3DXBUFFER,LPDIRECT3DDEVICE9,Arc_Files*);	
	//法線マップの作成
	HRESULT SetNormal(LPDIRECT3DDEVICE9);
public:
	//使用数
	int	m_iCount;	
	
	//メッシュオブジェクト
	LPD3DXMESH	m_pMesh;	
	//マテリアルの数
	DWORD		m_dwMatNum;	
	//エフェクトパス
	int			TexPass;	
	//最大頂点
	D3DXVECTOR3	Max;
	//最小頂点
	D3DXVECTOR3	Min;
	//各半径
	D3DXVECTOR3	ren;
	//球の中心点
	D3DXVECTOR3	Center;
	//球の半径
	float		Sren;
	//マテリアル
	std::vector<CMtrl> m_pCMtrl;
	//コンストラクタ
	CModel();
	//デストラクタ
	virtual ~CModel();
	//モデルの読み込み
	HRESULT LoadModel(LPDIRECT3DDEVICE9,int,Arc_Files*,FILE*);	
	//モデルのカウント
	int Release();
};


class CModelManager
{
private:
	typedef std::map<int,CModel*> mapc;
	mapc Mod;
public:
	CModelManager();
	virtual ~CModelManager();
	mapc::iterator Load(int,LPDIRECT3DDEVICE9,Arc_Files*,FILE*);
	VOID Release(int);
	//デバッグ
	VOID Debug(TCHAR*,int,Arc_Files*);
};
