//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "MainMenu.cpp"

using namespace sf;
#pragma once
int main() {
	RenderWindow App(sf::VideoMode(1000, 1000, 32), "Integrador");
	//GameState * gameState = new MainMenu(&App);
	GameState * gameState = new Gameplay(&App);
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

		GameState * gs = gameState->CheckState(&App);
		if (gs != NULL)
		{
			delete gameState;
			gameState = gs;
		}
		
	}
	return 0;
}