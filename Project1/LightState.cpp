//===============================================
//ƒJƒƒ‰
//===============================================
Cam::Cam()
{
	Eye=D3DXVECTOR3(0.0f,0.0f,-5.0);
	At=D3DXVECTOR3(0.0f,0.0f,0.0f);
	Up=D3DXVECTOR3(0.0f,1.0f,0.0f);
	Pars=45.0f;
	wh=D3DXVECTOR2(1024.0f,768.0f);	
	Near = 0.1f;
	Far = 100.0f;
} 
VOID Cam::Init()
{
	Eye=D3DXVECTOR3(0.0f,0.0f,-5.0);
	At=D3DXVECTOR3(0.0f,0.0f,0.0f);
	Up=D3DXVECTOR3(0.0f,1.0f,0.0f);
	Pars=45.0f;
	wh=D3DXVECTOR2(1024.0f,768.0f);	
	Near = 0.1f;
	Far = 100.0f;

}
VOID Cam::Cast(const Cam* C)
{
	Eye.x  = C->Eye.x;
	Eye.y  = C->Eye.y;
	Eye.z  = C->Eye.z;
	At.x   = C->At.x;
	At.y   = C->At.y;
	At.z   = C->At.z;
	Up.x   = C->Up.x;
	Up.y   = C->Up.y;
	Up.z  = C->Up.z;
	wh.x   = C->wh.x;
	wh.y   = C->wh.y;
	Pars = C->Pars;
	Near = C->Near;
	Far = C->Far;

}

VOID Cam::CamSet(D3DXVECTOR3 *e,D3DXVECTOR3 *a)
{	
	Eye = *e;
	At  = *a;
}
