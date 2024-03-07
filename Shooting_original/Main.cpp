# include <Siv3D.hpp> // OpenSiv3D v0.6.10

#include "Player.h"
#include "Enemy.h"
#include "EnemyMaster.h"
#include "Bullet.h"
#include "Effect.h"

enum GameState
{
	TITLE,
	PLAY,
	CLEAR,
	GAMEOVER
};

GameState state = GameState::TITLE;

namespace SIV3DMAIN
{
	void Initialize()
	{
		FontAsset::Register(U"font", FontMethod::MSDF, 48, Typeface::Bold);
		TextureAsset::Register(U"PLAYER", U"Player_.png");
		TextureAsset::Register(U"ENEMY", U"teki.png");
		TextureAsset::Register(U"BULLET", U"3.png");
		TextureAsset::Register(U"EBULLET", U"1.png");
		TextureAsset::Register(U"EXPLOSION", U"explosion.png");
		TextureAsset::Register(U"BGIMAGE", U"BackGround.jpg");
		FontAsset::Register(U"TITLE_FONT", FontMethod::SDF, 50, Typeface::Bold);
		FontAsset::Register(U"TITLE_MINI", FontMethod::SDF, 25, Typeface::Bold);
		FontAsset::Register(U"BUTTON_FONT", FontMethod::SDF, 30, Typeface::Mplus_Heavy);

		Window::Resize(1024, 768);
		// 背景の色を設定する | Set the background color
		Scene::SetBackground(ColorF{ 255, 255, 255 });
	}
}

std::vector<BasicAbility*> objList;

void PlayerVSEnemies(Player* p, EnemyMaster* em);
void EnemiesVSPlayer(EnemyMaster* em, Player* p);

void Main()
{
	SIV3DMAIN::Initialize();


	EnemyMaster* em = new EnemyMaster;
	em->InitializeEnemies();
	objList.push_back(em);

	Player* p = nullptr;
	p = new Player;
	p->Initialize();
	objList.push_back(p);

	bool allEnemiesInactive;  
	bool playerInactive;  

	while (System::Update())
	{
		switch (state)
		{
		case GameState::TITLE:

			Scene::SetBackground(ColorF{ 0.0, 0.0, 0.0 });
			FontAsset(U"TITLE_FONT")(U"ShootingGame2D").drawAt(Scene::Center(), Palette::White);
			if (KeyEnter.down())
			{
				state = GameState::PLAY;
			}
			break;

		case GameState::PLAY:

			PlayerVSEnemies(p, em);
			EnemiesVSPlayer(em, p);
			for (auto& theI : objList)
				theI->Update();

			//背景描画
			TextureAsset(U"BGIMAGE").resized(Scene::Size()).draw();
			for (auto& theI : objList)
				theI->Draw();

			
			allEnemiesInactive = true;
			for (auto& enemy : em->enemies) {
				if (enemy->isActive()) {
					allEnemiesInactive = false;
					break;
				}
			}

			
			playerInactive = !p->isActive();

			
			if (allEnemiesInactive) {
				state = GameState::CLEAR;
			}
			else if (playerInactive) {
				state = GameState::GAMEOVER;
			}

			break;

		case GameState::CLEAR:
			Scene::SetBackground(ColorF{ 0.0, 0.0, 0.0 });
			FontAsset(U"TITLE_FONT")(U"CLEAR!").drawAt(Scene::Center(), Palette::White);
			if (KeyEnter.down())
			{
				
				p->Reset();
				em->Reset();
				state = GameState::TITLE;
			}
			break;

		case GameState::GAMEOVER:
			Scene::SetBackground(ColorF{ 0.0, 0.0, 0.0 });
			FontAsset(U"TITLE_FONT")(U"GAMEOVER..").drawAt(Scene::Center(), Palette::White);
			if (KeyEnter.down())
			{
				p->Reset();
				em->Reset();
				state = GameState::TITLE;
			}
			break;

		default:
			break;
		}
	}

	//p->Release();
	for (auto& theI : objList)
		delete theI;
	objList.clear();
}

void PlayerVSEnemies(Player* p, EnemyMaster* em)
{
	for (auto& theJ : p->GetGunBullet())
	{
		if (!theJ->isActive())
			continue;
		for (auto& theI : em->enemies)
		{
			if (!theI->isActive())
				continue;
			if (theJ->IsMyRectHit(theI->GetCharaRect()))
			{
				ExplosionEffect* ef = new ExplosionEffect(theI->pos_);
				objList.push_back(ef);
				theJ->DeActivateMe();
				theI->DeActivateMe();
				theI->GetGun()->DeActivateMe();  
			}
		}
	}
}

void EnemiesVSPlayer(EnemyMaster* em, Player* p)
{
	for (auto& theI : em->enemies)
	{
		if (!theI->isActive())
			continue;
		Bullet* theJ = theI->GetGun();
		if (!theJ->isActive())
			continue;
		if (p->IsMyRectHit(theJ->GetCharaRect()))
		{
			ExplosionEffect* ef = new ExplosionEffect(p->pos_);
			objList.push_back(ef);
			theJ->DeActivateMe();
			p->DeActivateMe();
			for (auto& bullet : p->GetGunBullet())  
				bullet->DeActivateMe();
		}
	}
}
