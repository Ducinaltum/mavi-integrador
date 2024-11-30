#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Button.cpp"
#pragma once

class GameOver : public GameState
{
private:
	Text m_gameOver;
	Text m_score;
	Texture* m_buttonIdleTex;
	Texture* m_buttonPressedTex;
	Button* m_continueButton;
	Font* m_mainFont;
	bool goToMainMenu;

public:
	GameOver(RenderWindow* rw, Font* mainFont, int score)
	{
		goToMainMenu = false;
		Vector2f* targetSize = new Vector2f(512, 128);
		m_mainFont = mainFont;
		m_buttonIdleTex = new Texture();
		m_buttonPressedTex = new Texture();
		m_buttonIdleTex->loadFromFile("assets/cuad_red.png");
		m_buttonPressedTex->loadFromFile("assets/cuad_yellow.png");
		m_continueButton = new Button(m_buttonIdleTex, m_buttonPressedTex, mainFont, "MAIN MENU", *new Vector2f((rw->getSize().x / 2) - (targetSize->x / 4), 512), targetSize);
		m_gameOver.setFont(*m_mainFont);
		m_gameOver.setString("GAME OVER");
		m_gameOver.setCharacterSize(128);
		m_gameOver.setFillColor(sf::Color::Red);
		m_gameOver.setPosition((rw->getSize().x / 2) - (m_gameOver.getGlobalBounds().width / 2), 64);

		m_score.setFont(*m_mainFont);
		m_score.setString("Score: " + std::to_string(score));
		m_score.setCharacterSize(92);
		m_score.setFillColor(sf::Color::Red);
		m_score.setPosition((rw->getSize().x / 2) - (m_score.getGlobalBounds().width / 2), 256);
	}

	void Update(RenderWindow* rw) override
	{
		if (Mouse::isButtonPressed(Mouse::Button::Left))
		{
			Vector2f mousePos(Mouse::getPosition(*rw));
			if (m_continueButton->checkClick(mousePos))
			{
				goToMainMenu = true;
			}
		}
	};
	void Draw(RenderWindow* rw) override
	{
		rw->draw(*m_continueButton->getSprite());
		rw->draw(*m_continueButton->getText());
		rw->draw(m_gameOver);
		rw->draw(m_score);
	};

	bool CheckState() override
	{
		if (goToMainMenu)
		{
			return true;
		}
		return false;
	};



};