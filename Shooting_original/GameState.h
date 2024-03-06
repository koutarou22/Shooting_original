#pragma once
#include "Player.h"
#include "EnemyMaster.h"

class GameState {
public:
	enum class State {
		TITLE,
		PLAY,
		CLEAR,
		GAMEOVER
	};

	GameState();
	void Update(Player* player, EnemyMaster* enemyMaster);
	void TitleUpdate();
	void TitleDraw();
	void ClearUpdate();
	void ClearDraw();
	void GameOverUpdate();
	void GameOverDraw();

private:
	State state;
	Rect StartButtonRect;
};
