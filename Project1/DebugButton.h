#pragma once 
//=================================
//ボタン素材
//=================================
class MyButton
{
private:
	enum{TMAX = 100};
	int Mode;
	int TextX; 
	int TextY;
	float Size;
	float slide;
	D3DXVECTOR2 Pos;
	D3DXVECTOR2 Pos2;	
	D3DXVECTOR2 PreMPos;	
	CObjFVF mater;
	CObjFVF toggle;
	CObjFVF Move;
	//2D当たり判定
	BOOL Hit2D(CObjFVF*,float,float);
public:
	//テキスト
	TCHAR txt[TMAX];
	//コンストラクタ
	MyButton();
	//位置を指定
	VOID SetPos(float,float);
	//描画
	VOID draw(MyLibrary*);
	//テンプレート関数はクラス外、ヘッダー内で定義しなければならない(エラーを感知しない)
	//描画する
	template<class T>
	BOOL Set(MyLibrary* ml,TCHAR* Name,T* Now,T Min,T Max)
	{			
		D3DXVECTOR2 p  = ml->GV.mPos;
		float Mdl = Pos.y - 30.0f;
		float fNow = (float)*Now;
		float fMax = (float)Max;
		float fMin = (float)Min;
		float MaxMin = fMax - fMin;
		float alpha = 0.5f;
		//メーター
		mater.objPos    = D3DXVECTOR3(Pos.x + Size / 2.0f,Mdl,0.0f);
		mater.objScal   = D3DXVECTOR3(Size,5.0f,1.0f);
		mater.MeshCol   = D3DXVECTOR4(0.0f,0.0f,1.0f,0.5f);
		//移動バー
		Move.objPos		= D3DXVECTOR3(Pos.x+Size+15.0f,Mdl,0.0f); 
		Move.objScal	= D3DXVECTOR3(10.0f,10.0f,0.0f);
		Move.MeshCol	= D3DXVECTOR4(1.0f,1.0f,0.0f,alpha);		
		//トグル
		//最大値と最小値から現在値を0.0f~1.0fに変換
		float tog = ((fNow - fMin) / MaxMin) * Size;
		toggle.objPos	= D3DXVECTOR3(Pos.x + tog,Mdl,0.0f);
		toggle.objScal	= D3DXVECTOR3(10.0f,10.0f,1.0f);
		toggle.MeshCol	= D3DXVECTOR4(1.0f,1.0f,1.0f,alpha);
		//どの場所をクリックしていたかによってモード変更
		if(ml->C.Z.K())
		{
			if( Mode == 0 )
			{
				Mode = -1;				
				if(Hit2D(&Move,p.x,p.y))   {Mode = 1;}//移動バー
				if(Hit2D(&toggle,p.x,p.y)) {Mode = 2;}//トグル
			}
		}
		else{	Mode = 0;	} 		
	
		//モードによって命令を指定		
		//カーソル位置を記憶
		if(Mode == 0)
		{
			slide = tog;
			Pos2 = p - Pos; 
		}
		//位置の変更
		else if(Mode == 1)
		{
			Move.MeshCol.w = 1.0f;
			float cw = (float)ml->GV.ClientWidth * 0.5f;
			float ch = (float)ml->GV.ClientHeight * 0.5f;

			if(p.x <-cw){p.x =-cw;}
			if(p.x > cw){p.x = cw;}
			if(p.y <-ch){p.y =-ch;}
			if(p.y > ch){p.y = ch;}
			Pos = p - Pos2;
		}
		//トグルを動かす
		else if(Mode == 2)
		{
			toggle.MeshCol.w = 1.0f;
			float yp = fabsf(p.y - toggle.objPos.y);
			float y = 1.0f / yp;
			if(yp <= 10.0f){y = 1.0f;}
			toggle.MeshCol.x = y * 100.0f;
			slide -= (PreMPos.x - p.x) * y;
			*Now = (T)( MaxMin * slide / Size + fMin);
			if(*Now >= Max){*Now = Max;}
			if(*Now <= Min){*Now = Min;}	
		}
		PreMPos = p;		
		//テキスト設定
		float w  = (float)ml->GV.ClientWidth;
		float h  = (float)ml->GV.ClientHeight;	
		float sw  = (float)ml->GV.ScreenWidth;
		float sh  = (float)ml->GV.ScreenHeight;
		float w1 = (mater.objPos.x + 70.0f)*( sw / w ) + sw * 0.5f;;
		float h1 = sh * 0.5f - (mater.objPos.y + 8.0f ) * ( sh / h );
		TextX = (int)w1;
		TextY = (int)h1;
		_stprintf_s(txt,TMAX,Name,*Now);


	//	_stprintf_s(txt,TMAX,_T("%s\n%f,%f\n%f,%f"),txt,cw,ch,p.x,p.y);
		return TRUE;
	}
};

//=================================
//ボタンまとめ
//=================================
class DebugButton
{
private:	
	//ライブラリ
	MyLibrary* ml;
	//位置
	D3DXVECTOR2 Position;
	//個数
	size_t Num;
	//ボタン
	std::vector<MyButton> Button;
public:
	//コンストラクタ
	DebugButton();
	//ライブラリと位置のセット
	VOID Set(MyLibrary* ML,float x,float y);
	//描画
	VOID draw();
	//ボタンを生成
	template<class T>
	VOID DB(TCHAR* Name,T* Now,T Min,T Max);
};
//ボタンを生成
template<class T>
VOID DebugButton::DB(TCHAR* Name,T* Now,T Min,T Max)
{	
	if(ml == NULL){return;}
	//生成が出来たらパックする(これがないと毎ループ生成されてしまう)
 	if(Button.size() < Num + 1)
	{
		MyButton My;
		My.SetPos(Position.x,Position.y - (float)Num * 15.0f);
		Button.push_back(My);
	}	
	//ステータスを入力
	Button[Num].Set(ml,Name,Now,Min,Max);
	Num++;
}