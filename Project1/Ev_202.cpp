//===================================
//電気
//===================================
const TCHAR *Denki202::name(){return _T("Denki202");}
Denki202::Denki202()
{
	//回転原点
	Msh.push_back(&pCube);
	pCube.Type(x_cube);
	pCube.objScal=D3DXVECTOR3(0.1f,0.1f,0.1f);
	pCube.ShadowFlag = FALSE;
	//ケーブル
	Msh.push_back(&pCable);
	pCable.Type(x_cube);
	pCable.ShadowFlag = FALSE;
	pCable.SetPare(&pCube.mWorld);
	pCable.objScal=D3DXVECTOR3(0.05f,0.8f,0.05f);
	pCable.objScal=vec3Ari().D3DXVec3Div(&pCable.objScal,&pCube.objScal);
	pCable.objPos=D3DXVECTOR3(0.0f,-2.0f,0.0f);
	pCable.MeshCol=D3DXVECTOR4(0.2f,0.2f,0.2f,1.0f);
	//電気本体
	Msh.push_back(&pDenki);
	pDenki.Type(x_denki);
	pDenki.SetPare(&pCable.mWorld);
	pDenki.objScal=vec3Ari().D3DXVec3Div(&pDenki.objScal,&pCube.objScal);
	pDenki.objScal=vec3Ari().D3DXVec3Div(&pDenki.objScal,&pCable.objScal);
	pDenki.objPos.y=-0.5f;
//	pDenki.ShadowFlag=FALSE;
	pDenki.HitMode(CT_OBB,CB_PLUS);


	//アニメーション
	frame = 0;
	rot.SetKey(0,D3DXVECTOR3(0.0f,0.0f,40.0f));
	rot.SetKey(20,D3DXVECTOR3(40.0f,0.0f,0.0f));
	rot.SetKey(40,D3DXVECTOR3(0.0f,0.0f,-40.0f));
	rot.SetKey(60,D3DXVECTOR3(-40.0f,0.0f,0.0f));
	rot.SetKey(80,D3DXVECTOR3(0.0f,0.0f,40.0f));
	power = 0.0f;

	//フラグ
	flag = 0;
	//懐中電灯
	fl.flash.SetPare(&pDenki.mWorld);
	fl.flash.objPos = D3DXVECTOR3(0.1f,0.3f,0.0f);
	fl.flash.YPR = D3DXVECTOR3(90.0f,0.0f,0.0f);
	fl.flash.ShadowFlag = FALSE;
	fl.flash.HitMode(CT_OBB,CB_NONE);
	//懐中電灯落下
	framefall = 0;
	//落下アニメーション
	r.SetKey(0,D3DXVECTOR3(90.0f,0.0f,0.0f));
	r.SetKey(20,D3DXVECTOR3(180.0f,45.0f,0.0f));
	r.SetKey(40,D3DXVECTOR3(270.0f,90.0f,0.0f));

	//テキスト
	text.init(this);
	text.s(_T("【懐中電灯】を拾った"));
	//当たり判定
	hitbox.Type(x_cube);
	hitbox.drawSkip = TRUE;
	hitbox.HitMode(CT_OBB,CB_NONE);
	Msh.push_back(&hitbox);

	//SE
	gon.Set(wav_step2);
	gon.m_b3DSound = TRUE;
	gon.Filter.Frequency = 0.110000f;
	gon.Filter.OneOverQ = 0.904000f;
	gon.Filter.Type = LowPassFilter;
	gon.m_fVol = 3.0f; 
	Snd.push_back(&gon);
}
VOID Denki202::Update()
{

	ML->E.Ls.EyePlus.y = 5.0f;
	//ダーツが当たると電気が揺れる
	frame++;
	if(frame > 80){frame = 0;}	
	pCube.YPR = rot.Val(frame) * power;
	if(power > 0.0){power -= 0.002f;}
	if(pDenki.HitObj.Reaction == 2 )
	{
		power += 0.2f;
		P->AtcBullet(&pDenki.mWorld);
	}
	//懐中電灯
	text.Update(P,ML);
	if(P->FM.iGetedFlag(ITEM_LIGHT)){return;}	
	fl.Update(ML,TRUE);
	if(flag == 0)
	{
		ML->E.PSL.dis = 2.0f;
		if(power > 0.6f){flag = 1;}
	}
	if(flag == 1)
	{
		fl.flash.SetPare(NULL);
		fl.flash.objScal = D3DXVECTOR3(1.0f,1.0f,1.0f);
		fl.flash.objPos = D3DXVECTOR3(fl.flash.mWorld._41,fl.flash.mWorld._42,fl.flash.mWorld._43);
		p.SetKey(0,fl.flash.objPos);
		p.SetKey(40,fl.flash.objPos - D3DXVECTOR3(0.0f,fl.flash.objPos.y - 0.05f,0.0f));//-0.15
		flag = 2;
	}
	if(flag == 2)
	{
		framefall++;
		if(framefall > 40)
		{
			//SE
			gon.Start(ML);
			flag = 3;
		}
		fl.flash.objPos = p.Val1(framefall);
		fl.flash.YPR  = r.Val1(framefall);
	}
	if(flag == 3)
	{
		if(hitbox.HitObj.Reaction == 1)
		if(P->Check)
		if(P->Mode != Personal::MODE_EVENT)
		{
			text.StartText(P);
			P->CheckSE(Personal::SE_ITEM);
			P->FM.iGet(ITEM_LIGHT);
		}
	}
}
VOID Denki202::draw()
{
	if(P->FM.iGetedFlag(ITEM_LIGHT)){return;}
	fl.draw(ML);
}

VOID Denki202::DebugText(TCHAR* t,int l)
{
	_stprintf_s(t,l,
		_T("%s\n")
		_T("power = %f\n")
		_T("flag = %d\n")
		_T("hit = %d\n")
		_T("item = %d\n")

		,t
		,power
		,flag
		,fl.flash.HitObj.Reaction
		,P->FM.iGetedFlag(ITEM_LIGHT)
		);
}
//===================================
//テキストバスルームが開かない
//===================================
const TCHAR *BathDoor202::name(){return _T("BathDoor202");}
BathDoor202::BathDoor202()
{
	//当たり判定
	hitbox.Type(x_cube);
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.drawSkip = TRUE;
	Msh.push_back(&hitbox);
	//鍵音
	gatya.Set(wav_keylock);
	gatya.m_b3DSound = TRUE;
	Snd.push_back(&gatya);
	//テキスト
	text.init(this);
	text.s(_T("扉がゆがんで開きそうに無い"));

}
VOID BathDoor202::Update()
{
	if(P->Mode != Personal::MODE_EVENT)
	if(hitbox.HitObj.Reaction == 1)
	if(P->Check)
	{
		text.StartText(P);
		gatya.Start(ML);

	}
	text.Update(P,ML);
}