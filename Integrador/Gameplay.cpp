#pragma once
//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameState.h"

class Gameplay : public GameState
{
private:
	int lives;
	int kills;
	Sprite* sBackground;
	Texture* tBackground;
	Sprite* sForeground;
	Texture* tForeground;
	Sprite* sCrosshair;
	Texture* tCrosshair;


public:
	Gameplay()
	{
		lives = 3;
		kills = 0;

		sCrosshair = new Sprite();
		tCrosshair = new Texture();
		tCrosshair->loadFromFile("assets/crosshair.png");
		sCrosshair->setTexture(*tCrosshair);
	}
	void Update(RenderWindow* rw) override
	{
		Vector2i mousePos = Mouse::getPosition(*rw);
		sCrosshair->setPosition(mousePos.x, mousePos.y);
		lives++;
	};

	virtual void Draw(RenderWindow* rw)override
	{
		rw->draw(*sCrosshair);
	}
	virtual GameState* CheckState() override
	{
		return NULL;
	}
};

