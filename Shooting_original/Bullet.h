#pragma once
#include "BasicAbility.h"


const SizeF BULLET_CHR_SIZE{ 8, 17 }; //がぞうさいず
const SizeF BULLET_RECT_SIZE{ 8, 17 }; //当たり判定用のBBのサイズ
const double BULLET_MOVE_SPEED{ 300 }; //プレイヤーの弾の動作スピード
const Vec2 BULLET_INIT_POS{ -BULLET_CHR_SIZE * 2 };


class Bullet :
	public BasicAbility
{
	SizeF renderSize_;
	SizeF rectSize_;
public:
	Bullet(Texture& _tex, Vec2 _pos, Vec2 _dir, double _speed);
	Bullet(Texture& _tex) { tex_ = _tex; }
	Bullet(Vec2 _pos);
	Bullet();
	void SetRenderSize(SizeF _rendersize);
	void SetBBRectSize(SizeF _rectsize);
	void Update() override;
	void Draw() override;
};


