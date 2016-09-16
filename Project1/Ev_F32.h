#pragma once
namespace Ev
{
class FishGhost : public Scene
{
	Fish fish;
	int flag;
	int frame;
	AKey<D3DXVECTOR3> pos;
	AKey<float> alpha;

public:
	const TCHAR* name();
	FishGhost();
	VOID Set();
	VOID Update();
	VOID draw();
};
};