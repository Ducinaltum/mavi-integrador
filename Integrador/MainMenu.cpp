//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Button.cpp"
#include "Gameplay.cpp"
using namespace sf;
//#pragma once
class MainMenu : public GameState
{
private:
	bool goToGame;
	int currentIndex;
	Sprite* sBackground;
	Texture* tBackground;
	Texture* tButtonIdle;
	Texture* tButtonPressed;
	Button* playButton;
	Button* exitButton;

public:
	MainMenu(RenderWindow* rw)
	{
		goToGame = false;
		currentIndex = 0;
		sBackground = new Sprite();
		tBackground = new Texture();
		tButtonIdle = new Texture();
		tButtonPressed = new Texture();
		tButtonIdle->loadFromFile("assets/cuad_red.png");
		sBackground->setTexture(*tBackground);

		tButtonPressed->loadFromFile("assets/cuad_yellow.png");
		tBackground->loadFromFile("assets/cuad_blue.png");
		Vector2f* targetSize = new Vector2f(512, 128);
		playButton = new Button(tButtonIdle, tButtonPressed, "PLAY", *new Vector2f((rw->getSize().x / 2) - (targetSize->x / 4), 64), targetSize); //Esto debería ser /2, pero por alguna razón no funciona como corresponde
		exitButton = new Button(tButtonIdle, tButtonPressed, "EXIT", *new Vector2f((rw->getSize().x / 2) - (targetSize->x / 4), 128 + 64), targetSize);
	}

	void Update(RenderWindow* rw) override
	{
		if (Mouse::isButtonPressed(Mouse::Button::Left))
		{
			Vector2f mousePos(Mouse::getPosition(*rw));
			if (playButton->checkClick(mousePos))
			{
				goToGame = true;
			}
			else if (exitButton->checkClick(mousePos))
			{
				rw->close();
			}
		}
	}

	virtual void Draw(RenderWindow* rw)override
	{
		rw->draw(*sBackground);
		rw->draw(*playButton->getSprite());
		rw->draw(*exitButton->getSprite());
	}

	virtual GameState* CheckState() override
	{
		if (goToGame)
		{
			Gameplay* s = new Gameplay();
			return s;
		}
	}
};