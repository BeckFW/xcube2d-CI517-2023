#ifndef __MY_ENGINE_H__
#define __MY_ENGINE_H__

#include "../EngineCommon.h"
#include "../EventEngine.h"
#include "../GraphicsEngine.h"
#include <functional>
#include <vector>


class MyEngineSystem {
	friend class XCube2Engine;
	private:

	public:

};

// Add all functionality in UIElement class so it is generic. UIElement should not need to know what it is rendering
class UIElement {
public:
	int x, y, w, h;
	std::string elementText; 

	SDL_Color textColor, mainColor, borderColor, hoverColor, activeColor; 

	bool isMouseOver = false; 

	virtual void update(std::shared_ptr<EventEngine> evt);
	virtual void draw(std::shared_ptr<GraphicsEngine> gfx);
};

class Checkbox : public UIElement {
public:
	Checkbox() = default; 
	Checkbox(const int newX, const int newY, const int newWH, std::function<void()> run, std::function<void()> cancel, SDL_Color _mainColor, SDL_Color _activeColor, SDL_Color _hoverColor); 

	SDL_Rect* checkboxRect; 
	SDL_Rect* selectedRect;

	// Inner Rect Dimensions
	int inX, inY, inW, inH; 

	void update(std::shared_ptr<EventEngine> evt); 
	void draw(std::shared_ptr<GraphicsEngine> gfx);


	bool isActive = false; 

	std::function<void()> runFunction;
	std::function<void()> cancelFunction;
};

// Pass X, Y, W, H, Value, and a function using std::bind. For X or Y, pass -1 to center the button. 
class Button : public UIElement {

public:

	Button() = default;
	Button(const int newX, const int newY, const int newW, const int newH, std::string buttonText, std::function<void()> callback, SDL_Color _textColor, SDL_Color _mainColor, SDL_Color _borderColor, SDL_Color _hoverColor);
	SDL_Rect *buttonRect;

	void update(std::shared_ptr<EventEngine> evt);
	void draw(std::shared_ptr<GraphicsEngine> gfx);


	// Empty function pointer for button functionality (passed in constructor)
	std::function<void()> buttonFunction; 
};





class UIController {
public:
	
	// list of all the ui buttons
	std::vector<UIElement*> elements;

	// loops through the list and calls each object's update function
	void updateUI(std::shared_ptr<EventEngine> evt);
	void drawUI(std::shared_ptr<GraphicsEngine> gfx);

};



#endif