#include "stdafx.h"
#include "Player.h"

extern std::vector<BasicAbility*> objList;

int Player::GetBlankBullet()
{
	for (int i = 0; i < PLAYER_MAX_BULLET_NUM; i++)
	{
		if (Gun_[i]->isAlive_ == false)
			return i;
	}
	return PLAYER_MAX_BULLET_NUM;
}

Player::Player()
	:BasicAbility()
{
	Vec2 chrMargin{ 0, Scene::Height() / 2 - PLAYER_CHR_SIZE };
	pos_ = Scene::Center() + chrMargin;
	speed_ = PLAYER_MOVE_SPEED;
	tex_ = TextureAsset(U"PLAYER");
	SetCharaRect(SizeF{ PLAYER_RECT_SIZE,PLAYER_RECT_SIZE });
	moveDir_ = { 0, 0 };
	isAlive_ = true;
}

void Player::Initialize()
{
	for (int i = 0; i < PLAYER_MAX_BULLET_NUM; i++)
	{
		Bullet* p = nullptr;
		p = new Bullet();
		Gun_.push_back(p); //Releaseでdeleteしてね
	}
}

void Player::Reset()
{
	
	Vec2 chrMargin{ 0, Scene::Height() / 2 - PLAYER_CHR_SIZE };
	pos_ = Scene::Center() + chrMargin;
	speed_ = PLAYER_MOVE_SPEED;
	tex_ = TextureAsset(U"PLAYER");
	SetCharaRect(SizeF{ PLAYER_RECT_SIZE,PLAYER_RECT_SIZE });
	moveDir_ = { 0, 0 };
	isAlive_ = true;

    for (auto& bullet : Gun_)
	{
		bullet->DeActivateMe();
	}
}

direction Player::GetDirection()
{
	if ((KeyUp | KeyW).pressed())
	{
		return UP;
	}
	else if ((KeyLeft | KeyA).pressed())
	{
		return LEFT;
	}
	else if ((KeyDown | KeyS).pressed())
	{
		return DOWN;
	}
	else if ((KeyRight | KeyD).pressed())
	{
		return RIGHT;
	}
	else
		return NONE;
}

void Player::Update()
{   //寿命短い変数は名前も少し適当でいいよ
	if (KeyB.down())
	{
		int num = GetBlankBullet();
		if (num != PLAYER_MAX_BULLET_NUM)
		{
			Gun_[num]->isAlive_ = true;
			Gun_[num]->SetPosition(pos_);
			//ここのpos_はプレイヤーの位置
		}
	}
	for (auto& theI : Gun_) {
		theI->Update();
	}

	direction d = GetDirection();
	switch (d)
	{
	case LEFT:
		moveDir_ = { -1.0, 0 };
		break;
	case RIGHT:
		moveDir_ = { 1.0, 0 };
		break;
	default:
		return;
	}
	pos_ = pos_ + speed_ * Scene::DeltaTime() * moveDir_;
	SetCharaRect(SizeF{ PLAYER_RECT_SIZE,PLAYER_RECT_SIZE });

	
}

void Player::Draw()
{
	if (isAlive_) {
		tex_.resized(PLAYER_CHR_SIZE).drawAt(pos_);
		//rect_.drawFrame(1, 1, Palette::Red);

		for (auto& theI : Gun_) {
			theI->Draw();
		}
	}
}
