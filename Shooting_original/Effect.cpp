#include "stdafx.h"
#include "Effect.h"

ExplosionEffect::ExplosionEffect(Vec2 _pos)
	:BasicAbility(_pos)
{
	frames_ = { {EXPLOSION_RECT_SIZE.x * 0,EXPLOSION_RECT_SIZE.y * 0,EXPLOSION_RECT_SIZE},
			{EXPLOSION_RECT_SIZE.x * 1,EXPLOSION_RECT_SIZE.y * 0,EXPLOSION_RECT_SIZE},
			{EXPLOSION_RECT_SIZE.x * 2,EXPLOSION_RECT_SIZE.y * 0,EXPLOSION_RECT_SIZE},
			{EXPLOSION_RECT_SIZE.x * 0,EXPLOSION_RECT_SIZE.y * 1,EXPLOSION_RECT_SIZE},
			{EXPLOSION_RECT_SIZE.x * 1,EXPLOSION_RECT_SIZE.y * 1,EXPLOSION_RECT_SIZE},
			{EXPLOSION_RECT_SIZE.x * 2,EXPLOSION_RECT_SIZE.y * 1,EXPLOSION_RECT_SIZE},
			{EXPLOSION_RECT_SIZE.x * 0,EXPLOSION_RECT_SIZE.y * 2,EXPLOSION_RECT_SIZE},
			{EXPLOSION_RECT_SIZE.x * 1,EXPLOSION_RECT_SIZE.y * 2,EXPLOSION_RECT_SIZE},
			{EXPLOSION_RECT_SIZE.x * 2,EXPLOSION_RECT_SIZE.y * 2,EXPLOSION_RECT_SIZE} };
	frameNum = 0;
	pos_ = _pos;
	speed_ = 0;
	tex_ = TextureAsset(U"EXPLOSION");
	SetCharaRect(EXPLOSION_RECT_SIZE);
	moveDir_ = { 1, 0 };
	isAlive_ = true;
}

void ExplosionEffect::Draw()
{
	if (isAlive_) {
		tex_(frames_[frameNum]).resized(EXPLOSION_RECT_SIZE).drawAt(pos_);
		//rect_.drawFrame(1, 1, Palette::Red);
	}
}

void ExplosionEffect::Update()
{
	if (CTimer_.IsTimeOver()) {
		frameNum = (frameNum + 1);
		{
			if (frameNum >= MAX_FRAME_NUM) {
				frameNum = 0;
				DeActivateMe();
			}
		}
		CTimer_.ResetTimer();
	}
	else
		CTimer_.Update();
}


