#pragma once
//ヒットポイント
class HitPoint
{
private:
	//体力値
	int m_iHp;
public:
	//コンストラクタ
	HitPoint();
	//体力値を返す
	int HP();
	//体力の設定
	VOID Set(int);
	//回復
	VOID Recovery(int);
	//ダメージ
	VOID Damage(int);
	//死亡判定
	BOOL Dead();
	//生存判定
	BOOL ALive();

};