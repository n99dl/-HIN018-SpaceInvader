#pragma once
#include <U_Math.h>
#include "Sprite2D.h"
#include "Entity.h"
#include "Item.h"
#include "Bullet.h"
#include "../ControlConfig.h"

class Player : public Entity
{
protected:
	int m_Hp;
	int m_Speed;
	int m_WeaponLevel;
	float m_AttackSpeed;
	void FixPosition();
	void ShootStraight();
	void ShootDouble();
	void ShootRear();
	float m_ShootTime;
	bool m_IsShooting;
public:
	Player();
	~Player();
	void Draw();
	void Update(float dt);
	void Move(int KeyPressed, float dt); 
	void MoveByMouse(int x, int y);
	void Shoot();
	void SetIsShooting(bool IsShooting);
	void PowerUp();
	void ConsumeItem(std::shared_ptr<Item> _Item);
	void DamageBy(std::shared_ptr<Bullet> _Bullet);
	int GetHp();
};

