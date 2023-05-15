#include "MyEngineSystem.h"
#include <functional>


void UIController::updateUI(std::shared_ptr<EventEngine> evt) {
	for (UIElement* element : elements) {

		element->update(evt);

	}
}

void UIController::drawUI(std::shared_ptr<GraphicsEngine> gfx) {

	for (UIElement* element : elements) {
		element->draw(gfx); 
	}
}

void UIElement::update(std::shared_ptr<EventEngine> evt) {
 
}

void UIElement::draw(std::shared_ptr<GraphicsEngine> gfx) {

}

Checkbox::Checkbox(const int newX, const int newY, const int newWH, std::function<void()> run, std::function<void()> cancel, SDL_Color _mainColor, SDL_Color _activeColor, SDL_Color _hoverColor) {

	// Checkbox Dimensions
	x = newX;
	y = newY;
	w = newWH; 
	h = newWH; 

	// Center main box
	if (x == -1) { x = (DEFAULT_WINDOW_WIDTH / 2) - (w / 2); }
	if (y == -1) { y = (DEFAULT_WINDOW_HEIGHT / 2) - (h / 2); }

	// Inner Dimensions
	inW = w / 2;
	inH = h / 2; 
	inX = (x + w / 2) - inW / 2; 
	inY = (y + h / 2) - inH / 2; 

	mainColor = _mainColor; 
	activeColor = _activeColor; 
	hoverColor = _hoverColor;
	borderColor = SDL_COLOR_WHITE;

	checkboxRect = new SDL_Rect{ x, y, w, h };
	selectedRect = new SDL_Rect{ inX, inY, inW, inH };

	runFunction = run;
	cancelFunction = cancel;
}; 

void Checkbox::update(std::shared_ptr<EventEngine> evt) {
	Point2 mousePos = evt->getMousePos(); 
	SDL_Rect mousePosRect = { mousePos.x, mousePos.y, 1, 1 }; 

	if (SDL_HasIntersection(checkboxRect, &mousePosRect)) {
		isMouseOver = true;

		if (evt->leftButton == true) { // If the mouse button has been clicked AND mouse has intersection with rect

				switch (isActive)
				{
				case true:
					cancelFunction();
					isActive = false;
					break;
				case false:
					runFunction();
					isActive = true;
				default:
					break;
				}
		}
		evt->leftButton = false; // Return mouse click to false state so the click is only registered once
	}
	else {
		isMouseOver = false; 
	}
}


void Checkbox::draw(std::shared_ptr<GraphicsEngine> gfx) {

	if (isMouseOver == true) {
		gfx->setDrawColor(hoverColor);
	}
	else {
		gfx->setDrawColor(mainColor);
	}
	gfx->fillRect(checkboxRect);
	gfx->setDrawColor(borderColor);
	gfx->drawRect(checkboxRect);
	
	if (isActive) {
		gfx->setDrawColor(activeColor); 
		gfx->fillRect(selectedRect); 
	}

}

void Button::update(std::shared_ptr<EventEngine> evt) {

	Point2 mousePos = evt->getMousePos(); 
	SDL_Rect mousePosRect = { mousePos.x, mousePos.y, 1, 1 }; 

	if (SDL_HasIntersection(buttonRect, &mousePosRect))
	{
		isMouseOver = true; 
	
		if (evt->isPressed(BTN_LEFT))
		{
			// Calling button functionality
			buttonFunction();
		}

	}
	else { isMouseOver = false; }

}

Button::Button(int newX, int newY, int newW, int newH, std::string buttonText, std::function<void()> callback, SDL_Color _textColor, SDL_Color _mainColor, SDL_Color _borderColor, SDL_Color _hoverColor ) {
	x = newX; 
	y = newY; 
	w = newW; 
	h = newH; 

	elementText = buttonText; 

	textColor = _textColor; 
	mainColor = _mainColor;
	borderColor = _borderColor;
	hoverColor = _hoverColor; 

	// Center Button
	if (x == -1) { x = (DEFAULT_WINDOW_WIDTH / 2) - (w / 2); }
	if (y == -1) { y = (DEFAULT_WINDOW_HEIGHT / 2) - (h / 2); }

	buttonRect = new SDL_Rect { x, y, w, h }; 

	// Assign function passed in constructor to member variable
	buttonFunction = callback; 
}

void Button::draw(std::shared_ptr<GraphicsEngine> gfx) {
	
	// Select colour
	if (isMouseOver == true) {
		gfx->setDrawColor(hoverColor); 
	}
	else {
		gfx->setDrawColor(mainColor);
	}
	// Draw button layers
	gfx->fillRect(buttonRect);
	gfx->setDrawColor(borderColor); 
	gfx->drawRect(buttonRect); 
	gfx->setDrawColor(textColor);

	// Get text size
	const char* charText = elementText.c_str(); 
	int textW, textH; 
	TTF_SizeUTF8(gfx->getUIFont(), charText, &textW, &textH);
	// Draw text with centred position
	gfx->drawUIElementText(elementText, ((x + buttonRect->w/2) - (textW/2)), ((y + buttonRect->h/2) - (textH/2)));
}
