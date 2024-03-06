#include "stdafx.h"
#include "BasicAbility.h"

BasicAbility::BasicAbility(Vec2 _pos)//メンバイニシャライザ
	:pos_(_pos), isAlive_(false), speed_(0.0f), rect_({ 0,0,0,0 }), moveDir_({ 0,0 })
{

}
BasicAbility::BasicAbility()
{
	pos_ = { 0,0 };
	isAlive_ = false;
	speed_ = 0.0f;
	rect_ = { 0,0,0,0 };
	moveDir_ = { 0,0 };
}
void BasicAbility::SetCharaRect(SizeF _size)
{
	Vec2 adjustVal = { _size.x / 2.0, _size.y / 2.0 };
	rect_ = { pos_ - adjustVal, _size.x, _size.y };
}
void BasicAbility::SetPosition(Vec2 _pos)
{
	pos_ = _pos;
}
//とりあえず空
void BasicAbility::Update()
{
}
//とりあえず空
void BasicAbility::Draw()
{
	Print << U"GC Draw";
}

bool BasicAbility::IsMyRectHit(RectF _rect)
{
	float wAB = rect_.w / 2.0 + _rect.w / 2.0;
	float hAB = rect_.h / 2.0 + _rect.h / 2.0;
	float distx = abs(rect_.center().x - _rect.center().x);
	float disty = abs(rect_.center().y - _rect.center().y);
	if (wAB > distx && hAB > disty)
		return true;
	else
		return false;
}
