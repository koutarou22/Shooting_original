#include "stdafx.h"
#include "EnemyMaster.h"
#include "Enemy.h"
#include <algorithm>


void EnemyMaster::SetEnemiesRect()
{
	float xmin = Scene::Width(), xmax = 0;
	float ymin = Scene::Height(), ymax = 0;
	for (auto& theI : enemies)
	{
		if (theI->isActive())
		{
			if (xmin > theI->pos_.x)
				xmin = theI->pos_.x;
			if (ymin > theI->pos_.y)
				ymin = theI->pos_.y;
			if (xmax <= theI->pos_.x)
				xmax = theI->pos_.x;
			if (ymax <= theI->pos_.y)
				ymax = theI->pos_.y;
		}
	}

	Vec2 adjustVal = { ENEMY_CHR_SIZE / 2, ENEMY_CHR_SIZE / 2 };
	rect_ = { {Vec2{xmin, ymin} - adjustVal}, xmax - xmin + ENEMY_CHR_SIZE, ymax - ymin + ENEMY_CHR_SIZE };
}



EnemyMaster::EnemyMaster()
	:BasicAbility(), timer_(ENEMY_SHOT_INTERVAL)
{
	SetSpeed(ENEMY_MOVE_SPEED);

}

EnemyMaster::~EnemyMaster()
{
}

void EnemyMaster::InitializeEnemies()
{
	//行、列分の敵キャラを生成
	//EnemyLinesは敵が何行存在するか→（行）
	//EnemyInLineは１行に敵が何匹居るか↓↓↓（列）
	for (int j = 0; j < EnemyLines; j++)
	{
		for (int i = 0; i < EnemyInLine; i++)
		{
			Enemy* e = new Enemy;
			enemies.push_back(e);
		}
	}

	const int W_MARGIN{ ENEMY_CHR_SIZE / 3 };
	const int H_MARGIN{ ENEMY_CHR_SIZE / 10 };
	const int CENTER = Scene::Width() / 4;
	
	for (int j = 0; j < EnemyLines; j++) {
		for (int i = 0; i < EnemyInLine; i++) {
			enemies[j * EnemyInLine + i]->speed_ = ENEMY_MOVE_SPEED;
			enemies[j * EnemyInLine + i]->pos_ 
				= Vec2{ i * (ENEMY_CHR_SIZE + H_MARGIN), j * (ENEMY_CHR_SIZE + W_MARGIN) }
			+ Vec2{ ENEMY_CHR_SIZE, ENEMY_CHR_SIZE } / 2 + Vec2{ CENTER, ENEMY_CHR_SIZE };
			enemies[j * EnemyInLine + i]->isAlive_ = true;
			enemies[j * EnemyInLine + i]->tex_ = TextureAsset(U"ENEMY");
			enemies[j * EnemyInLine + i]->moveDir_ = { 1.0, 0.0 };
			enemies[j * EnemyInLine + i]->SetCharaRect(Size{ ENEMY_CHR_SIZE, ENEMY_CHR_SIZE });
		}
	}

	speed_ = ENEMY_MOVE_SPEED; //全体枠の移動スピードも、エネミー個体と同じ
	SetEnemiesRect(); //全体枠自体の更新
	moveDir_ = { 1.0, 0.0 };//全体枠の移動方向も、エネミー個体と同じ



}

//今はキーボードで左右に敵が動いているけど、
//画面端まで敵がたどり着いたら、自動で向きをフリップ
//するように変更！
void EnemyMaster::Update()
{
	const float SWidth = Scene::Width();
	const float SHeight = Scene::Height();
	const float WMargin = 50;


	if (rect_.x <= WMargin || rect_.x + rect_.w >= SWidth - WMargin)
	{
		for (auto& theI : enemies) {
			theI->FlipMove();
			theI->MoveDown();
		}
	}

	for (auto& theI : enemies)
		theI->Update();

	SetEnemiesRect();//全体枠（黄色）を再設定

	if (timer_.IsTimeOver())
	{
		int num = Random(0, (int)(enemies.size() - 1));
		enemies[num]->Shot();

		timer_.ResetTimer();
	}
	else
		timer_.Update();

}


void EnemyMaster::Draw()
{
	for (auto& theI : enemies) {
		theI->Draw();
	}
}

