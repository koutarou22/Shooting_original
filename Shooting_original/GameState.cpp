#include "GameState.h"

GameState::GameState() : state(State::TITLE) {}

void GameState::Update(Player* player, EnemyMaster* enemyMaster) {
	switch (state) {
	case State::TITLE:
		// タイトル画面の処理
		TitleUpdate();
		TitleDraw();
		break;
	case State::PLAY:
		// ゲーム画面の処理
		if (player == nullptr) {
			state = State::GAMEOVER;
		}
		else if (enemyMaster == nullptr) {
			state = State::CLEAR;
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
}

void GameState::TitleUpdate() {
	if (KeySpace.pressed()) {
		state = State::PLAY;
	}
}

void GameState::TitleDraw() {
	Scene::SetBackground(ColorF(0.0, 0.5, 0.5));  // 背景色を設定
	String TitleStr = U"Invadershooting";
	String StartStr = U"Push Here to Start GAME";

	Point margin{ 3,3 };
	Point ajustSpace{ 0, -50 };
	Point startPoint = { Scene::Center().x, Scene::Center().y + 50 };
	FontAsset(U"TITLE_FONT")(TitleStr).drawAt(Scene::Center() + ajustSpace + margin, Palette::Lightslategray);
	FontAsset(U"TITLE_FONT")(TitleStr).drawAt(Scene::Center() + ajustSpace, Palette::Blueviolet);
	FontAsset(U"BUTTON_FONT")(StartStr).drawAt(TextStyle::Outline(0.2, Palette::Black),
										 startPoint + ajustSpace, Palette::White);

	StartButtonRect = FontAsset(U"BUTTON_FONT")(StartStr).drawAt(TextStyle::Outline(0.2, Palette::Black),
											 startPoint + ajustSpace, Palette::White).asRect();
}

void GameState::ClearUpdate() {
	if (KeySpace.pressed()) {
		state = State::TITLE;
	}
}

void GameState::ClearDraw() {
	Scene::SetBackground(ColorF(0.5, 0.5, 0.0));  // 背景色を設定
	String TitleStr = U"GAME CLEAR";
	String StartStr = U"Push Here to Continue";

	Point margin{ 3,3 };
	Point ajustSpace{ 0, -50 };
	Point startPoint = { Scene::Center().x, Scene::Center().y + 50 };
	FontAsset(U"TITLE_FONT")(TitleStr).drawAt(Scene::Center() + ajustSpace + margin, Palette::Lightslategray);
	FontAsset(U"TITLE_FONT")(TitleStr).drawAt(Scene::Center() + ajustSpace, Palette::Blueviolet);
	FontAsset(U"BUTTON_FONT")(StartStr).drawAt(TextStyle::Outline(0.2, Palette::Black),
										 startPoint + ajustSpace, Palette::White);

	StartButtonRect = FontAsset(U"BUTTON_FONT")(StartStr).drawAt(TextStyle::Outline(0.2, Palette::Black),
											 startPoint + ajustSpace, Palette::White).asRect();
}

void GameState::GameOverUpdate() {
	if (KeySpace.pressed()) {
		state = State::TITLE;
	}
}

void GameState::GameOverDraw() {
	Scene::SetBackground(ColorF(0.5, 0.0, 0.0));  // 背景色を設定
	String TitleStr = U"GAME OVER";
	String StartStr = U"Push Here to Restart GAME";

	Point margin{ 3,3 };
	Point ajustSpace{ 0, -50 };
	Point startPoint = { Scene::Center().x, Scene::Center().y + 50 };
	FontAsset(U"TITLE_FONT")(TitleStr).drawAt(Scene::Center() + ajustSpace + margin, Palette::Lightslategray);
	FontAsset(U"TITLE_FONT")(TitleStr).drawAt(Scene::Center() + ajustSpace, Palette::Blueviolet);
	FontAsset(U"BUTTON_FONT")(StartStr).drawAt(TextStyle::Outline(0.2, Palette::Black),
										 startPoint + ajustSpace, Palette::White);

	StartButtonRect = FontAsset(U"BUTTON_FONT")(StartStr).drawAt(TextStyle::Outline(0.2, Palette::Black),
											 startPoint + ajustSpace, Palette::White).asRect();
}
