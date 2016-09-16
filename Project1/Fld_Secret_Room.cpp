//====================================
//隠された部屋
//====================================
SecretRoom::SecretRoom(){}
VOID SecretRoom::Set()
{
	P->FM.FldType = FD_Secret;
	//ドア
	pDoor = NewObj(new ScDoor);
	pDoor->Ob()->objPos=D3DXVECTOR3(-4.86f,0.00f,-2.18f);
	pDoor->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);

	//部屋
	pRoom = NewObj(new Ev::drawObj);
	pRoom->Ob()->ShadowFlag=FALSE;
	pRoom->Ob()->Type(x_room);
	pRoom->Ob()->SpCol.w=50.0f;

	//ライト
	ML->E.Ls.Col = D3DXVECTOR4(0.5f,0.5f,0.5f,1.0f);
}
VOID SecretRoom::Update()
{

}
