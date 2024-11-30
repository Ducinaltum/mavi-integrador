#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "MainMenu.cpp"
#include "Gameplay.cpp"
#include "GameOver.cpp"
#include "GameState.h"
using namespace sf;
#pragma once

enum class EState
{
	MainMenu,
	Gameplay,
	GameOver
};

int main() {

	EState state = EState::MainMenu;
	sf::Font font;
	font.loadFromFile("assets/Allan-Bold.ttf");
	RenderWindow App(sf::VideoMode(1000, 1000, 32), "Integrador");
	GameState* gameState = new MainMenu(&App, &font);
	//GameState * gameState = new Gameplay(&App, &font);
	//GameState * gameState = new GameOver(&App, &font, 10);
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
		if (gameState != NULL)
		{
			gameState->Update(&App);
		}
		App.clear();
		gameState->Draw(&App);
		App.display();

		if (gameState->CheckState())
		{
			switch (state)
			{
			case EState::MainMenu:
				delete gameState;
				gameState = new Gameplay(&App, &font);
				state = EState::Gameplay;
				break;
			case EState::Gameplay:
			{
				Gameplay* gp = dynamic_cast<Gameplay*>(gameState);
				int score = gp->GetScore();
				delete gameState;
				gameState = new GameOver(&App, &font, score);
				state = EState::GameOver;
				break;
			}
			case EState::GameOver:
				delete gameState;
				gameState = new MainMenu(&App, &font);
				state = EState::MainMenu;
				break;
			}
		}
	}
	return 0;
}

