#include "MyGame.h"
#include "../engine/EventEngine.h"
#include "../engine/custom/MyEngineSystem.h"
#include <functional>

MyGame::MyGame() : AbstractGame(), score(0), lives(3), numKeys(5), gameWon(false), box(5, 5, 30, 30) {
	TTF_Font * font = ResourceManager::loadFont("res/fonts/arial.ttf", 72);
	TTF_Font* uiFont = ResourceManager::loadFont("res/fonts/calibri.ttf", 24); 
	gfx->useFont(font);
	gfx->useUIFont(uiFont);
	gfx->setVerticalSync(true);

	// UI SETUP // 

	UIElement* resumeButton = new Button(-1, 175, 200, 50, "Resume", std::bind(&AbstractGame::runResume, this), SDL_COLOR_WHITE, SDL_COLOR_BLACK, SDL_COLOR_WHITE, SDL_COLOR_GRAY);
	UIElement* quitButton = new Button(-1, 250, 200, 50, "Quit", std::bind(&AbstractGame::quit, this), SDL_COLOR_WHITE, SDL_COLOR_BLACK, SDL_COLOR_WHITE, SDL_COLOR_GRAY);
	UIElement* checkBox = new Checkbox(-1, 400, 40, std::bind(&AbstractGame::changeEasterEgg, this), std::bind(&AbstractGame::changeEasterEgg, this), SDL_COLOR_AQUA, SDL_COLOR_WHITE, SDL_COLOR_GRAY);

	menuUIController.elements.insert(menuUIController.elements.end(), { resumeButton, quitButton, checkBox });

	// END UI SETUP // 

    for (int i = 0; i < numKeys; i++) {
        std::shared_ptr<GameKey> k = std::make_shared<GameKey>();
        k->isAlive = true;
        k->pos = Point2(getRandom(0, 750), getRandom(0, 550));
        gameKeys.push_back(k);
    }
}

MyGame::~MyGame() {

}

void MyGame::handleKeyEvents() {
	int speed = 3;

	if (eventSystem->isPressed(Key::W)) {
		velocity.y = -speed;
	}

	if (eventSystem->isPressed(Key::S)) {
		velocity.y = speed;
	}

	if (eventSystem->isPressed(Key::A)) {
		velocity.x = -speed;
	}

	if (eventSystem->isPressed(Key::D)) {
		velocity.x = speed;
	}

	if (eventSystem->isPressed(Key::P))
	{
		pause();
	}

	if (eventSystem->isPressed(Key::R))
	{
		resume();
	}
}

void MyGame::update() {
	box.x += velocity.x;
	box.y += velocity.y;

	for (auto key : gameKeys) {
		if (key->isAlive && box.contains(key->pos)) {
			score += 200;
			key->isAlive = false;
			numKeys--;
		}
	}

	velocity.x = 0;
    velocity.y = 0;

	if (numKeys == 0) {
		gameWon = true;
	}

	if (gameWon) {
		running = false; 
	}
}

void MyGame::render() {
	gfx->setDrawColor(SDL_COLOR_RED);
	gfx->drawRect(box);

	gfx->setDrawColor(SDL_COLOR_YELLOW);
	for (auto key : gameKeys)
        if (key->isAlive)
		    gfx->drawCircle(key->pos, 5);

	//gfx->drawFillButton(100, 100, 100, 100); 
}

void MyGame::renderUI() {
	gfx->setDrawColor(SDL_COLOR_AQUA);
	std::string scoreStr = std::to_string(score);
	gfx->drawText(scoreStr, 780 - scoreStr.length() * 50, 25);

	if (gameWon)
		gfx->drawText("YOU WON", 250, 500);
}

void MyGame::updatePauseMenu() {



}