#ifndef __TEST_GAME_H__
#define __TEST_GAME_H__

#include "../engine/AbstractGame.h"

struct GameKey {
	Point2 pos;
	bool isAlive;
};

class MyGame : public AbstractGame {
	private:
		Rect box;
		Button button;

		//UIController uiController; 

		Vector2i velocity;

		std::vector<std::shared_ptr<GameKey>> gameKeys;

		/* GAMEPLAY */
		int score, numKeys, lives;
		bool gameWon;

		void handleKeyEvents();
		void update();
		void render();
		void renderUI();
		void updatePauseMenu(); 
		void showEasterEgg();
		void hideEasterEgg();
	public:
        MyGame();
		~MyGame();
};

#endif
