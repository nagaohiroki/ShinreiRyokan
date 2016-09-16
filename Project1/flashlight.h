#pragma once
class flashlight
{
	
	CObjMesh light;
public:
	CObjMesh flash;
	flashlight();
	VOID Set(MyLibrary*);
	VOID Update(MyLibrary*,BOOL);
	VOID draw(MyLibrary*);

};