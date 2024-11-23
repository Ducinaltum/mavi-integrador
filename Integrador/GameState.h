#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

class GameState
{
public:
	virtual void Update(RenderWindow*  rw) = 0;
	virtual void Draw(RenderWindow* rw) = 0;
	virtual GameState * CheckState() = 0;

};