#pragma once
#include "BasicAbility.h"


class Bullet;

const int EnemyInLine{ 8 };
const int EnemyLines{ 5 };
const int EnemyNum{ EnemyInLine * EnemyLines };
const int ENEMY_CHR_SIZE{ 48 }; 
const double ENEMY_RECT_SIZE{ 45 };
const double ENEMY_MOVE_SPEED{ ENEMY_CHR_SIZE/1  }; //プレイヤーの動作スピード
const double ENEMY_BULLET_SPEED{ 250 }; //敵弾の動作スピード
const Vec2 ENEMY_BULLET_DIR{ 0,1 };//敵の弾の移動方向


class Enemy :
	public BasicAbility
{
	Bullet* gun_;
public:
	Enemy(Vec2 _pos);
	Enemy();
	void Shot();
	void FlipMove() { moveDir_ = -moveDir_; }
	void MoveDown();
	void Update() override;
	void Draw() override;
	void Reset();

	
	Bullet* GetGun() { return gun_; }

};



