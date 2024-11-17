//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameState.h"


using namespace sf;
#pragma once
class MainMenu : public GameState
{
private:
	int currentIndex;
	Sprite* sBackground;
	Texture* tBackground;

public:
	MainMenu();
	void Update(RenderWindow rw) override;
};


MainMenu::MainMenu()
{
	currentIndex = 0;
	sBackground = new Sprite();
	tBackground = new Texture();
}

void MainMenu::Update(RenderWindow rw)
{
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		currentIndex++;
		currentIndex %= 3;
	}
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		currentIndex--;
		if (currentIndex < 0)
		{
			currentIndex += 3;
		}
		currentIndex %= 3;
	}
	if (Keyboard::isKeyPressed(Keyboard::Enter))
	{

	}
}
