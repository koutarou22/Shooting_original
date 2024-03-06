#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(Texture& _tex, Vec2 _pos, Vec2 _dir, double _speed)
{
	tex_ = _tex;
	renderSize_ = BULLET_CHR_SIZE;
	rectSize_ = BULLET_RECT_SIZE;
	pos_ = _pos;
	speed_ = _speed;
	SetCharaRect(rectSize_);
	moveDir_ = _dir;
	isAlive_ = false;
}

Bullet::Bullet(Vec2 _pos)
	:BasicAbility(BULLET_INIT_POS)
{
	renderSize_ = BULLET_CHR_SIZE;
	rectSize_ = BULLET_RECT_SIZE;
	pos_ = _pos;
	speed_ = BULLET_MOVE_SPEED;
	tex_ = TextureAsset(U"BULLET");
	SetCharaRect(rectSize_);
	moveDir_ = { 0, -1 };
	isAlive_ = true;
}

Bullet::Bullet()
	:BasicAbility(BULLET_INIT_POS)
{
	renderSize_ = BULLET_CHR_SIZE;
	rectSize_ = BULLET_RECT_SIZE;
	speed_ = BULLET_MOVE_SPEED;
	tex_ = TextureAsset(U"BULLET");
	SetCharaRect(rectSize_);
	moveDir_ = { 0, -1 };
	isAlive_ = true;
}

void Bullet::SetRenderSize(SizeF _rendersize)
{
	renderSize_ = _rendersize;
}

void Bullet::SetBBRectSize(SizeF _rectsize)
{
	rectSize_ = _rectsize;
}

void Bullet::Update()
{
	if (isAlive_) {
		pos_ = pos_ + moveDir_ * speed_ * Scene::DeltaTime();
		SetCharaRect(rectSize_);
	}
	else
		return;

	//画面の中に弾は存在するか
	if (!Scene::Rect().intersects(pos_))
	{
		isAlive_ = false;
		pos_ = BULLET_INIT_POS;
	}
}

void Bullet::Draw()
{
	if (isAlive_) {
		tex_.resized(renderSize_).drawAt(pos_);
		rect_.drawFrame(1, 1, Palette::Red);
	}
}
