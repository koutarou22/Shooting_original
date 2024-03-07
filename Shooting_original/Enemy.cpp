#include "stdafx.h"
#include "Enemy.h"
#include "Bullet.h"

Enemy::Enemy(Vec2 _pos)
	:BasicAbility()
{
	pos_ = _pos;
	speed_ = ENEMY_MOVE_SPEED;
	tex_ = TextureAsset(U"ENEMY");
	SetCharaRect(SizeF{ ENEMY_RECT_SIZE, ENEMY_RECT_SIZE });
	moveDir_ = { 1, 0 };
	isAlive_ = true;
	Texture t{ TextureAsset(U"EBULLET") };
	gun_ = new Bullet(t);
	gun_->SetRenderSize(t.size());
	gun_->SetBBRectSize(t.size());
	gun_->SetSpeed(ENEMY_BULLET_SPEED);
	gun_->SetMoveDir(ENEMY_BULLET_DIR);
}

Enemy::Enemy()
	:BasicAbility()
{
	pos_ = Scene::Center();
	speed_ = ENEMY_MOVE_SPEED;
	tex_ = TextureAsset(U"ENEMY");
	SetCharaRect(SizeF{ ENEMY_RECT_SIZE, ENEMY_RECT_SIZE });
	moveDir_ = { 1, 0 };
	isAlive_ = true;
	Texture t = TextureAsset(U"EBULLET");
	gun_ = new Bullet(t);
	gun_->SetRenderSize(t.size());
	gun_->SetBBRectSize(t.size());
	gun_->SetSpeed(ENEMY_BULLET_SPEED);
	gun_->SetMoveDir(ENEMY_BULLET_DIR);
}

void Enemy::Reset()
{
	pos_ = Scene::Center();
	speed_ = ENEMY_MOVE_SPEED;
	moveDir_ = { 1, 0 };
	isAlive_ = true;
	gun_->DeActivateMe();
}


void Enemy::Shot()
{
	if (gun_->isActive() == false)
	{
		gun_->SetPosition(pos_);//敵のポジションから発射
		gun_->ActivateMe();
		gun_->SetCharaRect(gun_->tex_.size());
	}
}

void Enemy::MoveDown()
{
	Vec2 yMoveVec = { 0, ENEMY_CHR_SIZE / 4 };
	pos_ = pos_ + yMoveVec;
}

void Enemy::Update()
{
	if (isAlive_) {
		pos_ = pos_ + moveDir_ * speed_ * Scene::DeltaTime();
		SetCharaRect({ ENEMY_RECT_SIZE, ENEMY_RECT_SIZE });
	}
	if (gun_->isActive())
		gun_->Update();
}

void Enemy::Draw()
{

	if (isAlive_) {
		tex_.resized(ENEMY_CHR_SIZE).drawAt(pos_);
		//rect_.drawFrame(1, 1, Palette::Red);

	    if (gun_->isActive())
	    {
		   gun_->Draw();
		   //gun_->rect_.drawFrame(1, 1, Palette::Red);
	    }
	}
}
