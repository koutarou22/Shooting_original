#pragma once
#include "BasicAbility.h"
#include <vector>
#include "CTIMER.h"

const int ENEMY_MAX_BULLET_NUM{ 10 };
const double ENEMY_SHOT_INTERVAL{ 1 };

using std::vector;
class Enemy;
class Bullet;

class EnemyMaster :
	public BasicAbility
{
	void SetEnemiesRect();
	CTIMER timer_;
public:
	EnemyMaster();
	~EnemyMaster();
	vector<Enemy*> enemies;
	void InitializeEnemies();
	void Update() override; 
	void Draw() override;
	void Reset();

};


