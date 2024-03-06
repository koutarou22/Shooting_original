#include <Siv3D.hpp> // OpenSiv3D v0.6.10
#include "Player.h"
#include "Enemy.h"
#include "EnemyMaster.h"
#include "Bullet.h"
#include "Effect.h"


enum class State {
	TITLE,
	PLAY,
	CLEAR,
	GAMEOVER
};

State gameState = State::TITLE;
Rect StartButtonRect;

std::vector<BasicAbility*> objList;

void TitleUpdate() {
	if (KeySpace.pressed()) {
		gameState = State::PLAY;
	}
}

// 以下に、TitleDraw, ClearUpdate, ClearDraw, GameOverUpdate, GameOverDraw の定義を書く

void Main()
{
	// 初期化処理...

	Player* p = nullptr;
	p = new Player;
	p->Initialize();

	EnemyMaster* em = new EnemyMaster;
	em->InitializeEnemies();

	while (System::Update())
	{
		switch (gameState) {
		case State::TITLE:
			// タイトル画面の処理
			TitleUpdate();
			TitleDraw();
			break;
		case State::PLAY:
			// ゲーム画面の処理
			if (player == nullptr) {
				gameState = State::GAMEOVER;
			}
			else if (enemyMaster == nullptr) {
				gameState = State::CLEAR;
			}
			break;
		case State::CLEAR:
			// クリア画面の処理
			ClearUpdate();
			ClearDraw();
			break;
		case State::GAMEOVER:
			// ゲームオーバー画面の処理
			GameOverUpdate();
			GameOverDraw();
			break;
		}

		// 他の更新処理...
		PlayerVSEnemies(p, em);
		EnemiesVSPlayer(em, p);
		for (auto& theI : objList)
			theI->Update();

		//背景描画
		TextureAsset(U"BGIMAGE").resized(Scene::Size()).draw();
		for (auto& theI : objList)
			theI->Draw();
	}

	// 終了処理...
	//p->Release();
	for (auto& theI : objList)
		delete theI;
	objList.clear();
}




