//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "MainMenu.cpp"

using namespace sf;
#pragma once
int main() {
	RenderWindow App(sf::VideoMode(800, 600, 32), "Integrador");
	GameState * gameState = new MainMenu(&App);
	while (App.isOpen())
	{
		Event evt;
		while (App.pollEvent(evt))
		{
			switch (evt.type)
			{
			case sf::Event::Closed:
				App.close();
				break;
			}
		}
		gameState->Update(&App);
		App.clear();
		gameState->Draw(&App);
		App.display();

		GameState * gs = gameState->CheckState();
		if (gs != NULL)
		{
			delete gameState;
			gameState = gs;
		}
		
	}
	return 0;
}