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
	Gameplay();
	void Update(RenderWindow rw) override;
};

Gameplay::Gameplay()
{
}

void Gameplay::Update(RenderWindow rw)
{
}
