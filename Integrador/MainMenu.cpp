#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Button.cpp"
#pragma once
//#include "Gameplay.cpp"
using namespace sf;
#pragma once

class Gameplay;

class MainMenu : public GameState
{
private:
	bool m_goToGame;
	Sprite* m_background;
	Texture* m_backgroundTex;
	Texture* m_buttonIdleTex;
	Texture* m_buttonPressedTex;
	Button* m_playButton;
	Button* m_exitButton;
	Font* m_mainFont;
	Text m_title;
	Text m_instructions;

public:
	MainMenu(RenderWindow* rw, Font* mainFont)
	{
		m_mainFont = mainFont;
		m_goToGame = false;
		m_background = new Sprite();
		m_backgroundTex = new Texture();
		m_backgroundTex->loadFromFile("assets/mansion.jpg");
		m_background->setTexture(*m_backgroundTex);

		float ratio = (float)rw->getSize().x / (float)m_backgroundTex->getSize().x;
		m_background->setScale(ratio, ratio);

		m_buttonIdleTex = new Texture();
		m_buttonPressedTex = new Texture();
		m_buttonIdleTex->loadFromFile("assets/cuad_red.png");
		m_buttonPressedTex->loadFromFile("assets/cuad_yellow.png");

		Vector2f* targetSize = new Vector2f(512, 128);
		m_playButton = new Button(m_buttonIdleTex, m_buttonPressedTex, mainFont, "PLAY", *new Vector2f((rw->getSize().x / 2) - (targetSize->x / 4), 128 + 64), targetSize); //Esto debería ser /2, pero por alguna razón no funciona como corresponde
		m_exitButton = new Button(m_buttonIdleTex, m_buttonPressedTex, mainFont, "EXIT", *new Vector2f((rw->getSize().x / 2) - (targetSize->x / 4), 256 + 64), targetSize);
		m_title.setFont(*mainFont);
		m_title.setString("SPRUNKILL");
		m_title.setCharacterSize(92);
		m_title.setFillColor(sf::Color::Red);
		m_title.setPosition((rw->getSize().x / 2) - (m_title.getGlobalBounds().width / 2) , 64);		

		m_instructions.setFont(*mainFont);
		m_instructions.setString("Kill the ghouls, \nbut not the house human inhabitants\nPrepare your spirit\nyou can only endure\nthree times to see the death face to face");
		m_instructions.setCharacterSize(64);
		m_instructions.setFillColor(sf::Color::Red);
		m_instructions.setPosition((rw->getSize().x / 2) - (m_instructions.getGlobalBounds().width / 2), 512);		
	}

	void Update(RenderWindow* rw) override
	{
		if (Mouse::isButtonPressed(Mouse::Button::Left))
		{
			Vector2f mousePos(Mouse::getPosition(*rw));
			if (m_playButton->checkClick(mousePos))
			{
				m_goToGame = true;
			}
			else if (m_exitButton->checkClick(mousePos))
			{
				rw->close();
			}
		}
	}

	virtual void Draw(RenderWindow* rw)override
	{
		rw->draw(*m_background);
		rw->draw(*m_playButton->getSprite());
		rw->draw(*m_playButton->getText());
		rw->draw(*m_exitButton->getSprite());
		rw->draw(*m_exitButton->getText());
		rw->draw(m_title);
		rw->draw(m_instructions);
	}

	virtual bool CheckState() override
	{
		if (m_goToGame)
		{
			return true;
		}
		return false;
	}
};