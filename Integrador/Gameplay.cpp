#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "ShootableEntity.cpp"
#pragma once

class Gameplay : public GameState
{
private:
	int m_lives;
	int m_kills;
	float m_timeBetweenSpawns;
	float m_elapsedTime;
	float m_crosshairTargetSize;
	sf::Time m_currentTime;
	sf::Clock m_clock;
	Text* m_ghoulsCounter;
	Text* m_spiritCounter;
	Font* m_mainFont;

	Sprite* m_background;
	Texture* m_backgroundTex;
	Sprite* m_foreground;
	Texture* m_foregroundTex;
	Sprite* m_crosshair;
	Texture* m_crosshairTex;
	Vector2f* m_crosshairOffset;

	ShootableEntity* m_shootableEntities[12];
	Vector2f* m_spawnSpots[6];
	int* m_usedSpots[6];

public:
	Gameplay(RenderWindow* rw, Font* mainFont)
	{
		m_mainFont = mainFont;
		m_lives = 3;
		m_kills = 0;
		m_elapsedTime = 0;
		m_timeBetweenSpawns = 2.0f;
		for (int i = 0; i < 6; i++)
		{
			m_usedSpots[i] = new int(-1);
		}
		m_ghoulsCounter = new Text();
		m_ghoulsCounter->setFont(*m_mainFont);
		m_ghoulsCounter->setString("Ghouls killed : 0");
		m_ghoulsCounter->setCharacterSize(42);
		m_ghoulsCounter->setFillColor(sf::Color::Red);
		m_ghoulsCounter->setPosition(rw->getSize().x - m_ghoulsCounter->getGlobalBounds().width - 32, 32);

		m_spiritCounter = new Text();
		m_spiritCounter->setFont(*m_mainFont);
		m_spiritCounter->setString("Spirit : 3");
		m_spiritCounter->setCharacterSize(42);
		m_spiritCounter->setFillColor(sf::Color::Cyan);
		m_spiritCounter->setPosition(32, 32);

		m_crosshair = new Sprite();
		m_crosshairTex = new Texture();
		m_background = new Sprite();
		m_backgroundTex = new Texture();
		m_foreground = new Sprite();
		m_foregroundTex = new Texture();

		m_crosshairTargetSize = 32.0f;
		m_crosshairTex->loadFromFile("assets/crosshair.png");
		m_crosshair->setTexture(*m_crosshairTex);

		float crosshairRatio = m_crosshairTargetSize / (float) m_crosshairTex->getSize().x;
		m_crosshair->setScale(crosshairRatio, crosshairRatio);

		m_backgroundTex->loadFromFile("assets/mansion.jpg");
		m_background->setTexture(*m_backgroundTex);

		m_foregroundTex->loadFromFile("assets/mansion_transparency.png");
		m_foreground->setTexture(*m_foregroundTex);

		float bgRatio = (float)rw->getSize().x / (float)m_backgroundTex->getSize().x;
		m_background->setScale(bgRatio, bgRatio);
		m_foreground->setScale(bgRatio, bgRatio);

		m_spawnSpots[0] = new Vector2f(303 * bgRatio, 703 * bgRatio);
		m_spawnSpots[1] = new Vector2f(303 * bgRatio, 516 * bgRatio);
		m_spawnSpots[2] = new Vector2f(554 * bgRatio, 683 * bgRatio);
		m_spawnSpots[3] = new Vector2f(554 * bgRatio, 516 * bgRatio);
		m_spawnSpots[4] = new Vector2f(787 * bgRatio, 703 * bgRatio);
		m_spawnSpots[5] = new Vector2f(787 * bgRatio, 516 * bgRatio);

		m_crosshairOffset = new Vector2f(m_crosshairTargetSize / 2.0f, m_crosshairTargetSize / 2.0f);
		for (int i = 0; i < 12; i++)
		{
			std::string path = "assets/characters/";
			path += i < 6 ? "innocent" : "enemy";
			path += std::to_string(i < 6 ? i : i - 6);
			path += ".png";
			bool isEnemy = !(i < 6);
			float initialDuration = 5.0f;
			m_shootableEntities[i] = new ShootableEntity(path, isEnemy, initialDuration);
		}
	}

	void Update(RenderWindow* rw) override
	{
		float deltaTime = m_clock.getElapsedTime().asSeconds();
		m_clock.restart();
		Vector2i mousePos = Mouse::getPosition(*rw);
		Vector2f fMousePos((float)mousePos.x, (float)mousePos.y);
		m_crosshair->setPosition(mousePos.x - m_crosshairOffset->x, mousePos.y - m_crosshairOffset->y);
		for (int i = 0; i < 12; i++)
		{
			if (m_shootableEntities[i]->IsActive())
			{
				m_shootableEntities[i]->Update(deltaTime, rw);
				if (Mouse::isButtonPressed(Mouse::Button::Left))
				{
					if (m_shootableEntities[i]->CheckShoot(fMousePos))
					{
						if (m_shootableEntities[i]->IsEnemy())
						{
							m_kills++;
						}
						else
						{
							m_lives--;
						}
						m_shootableEntities[i]->Deactivate();
					}
				}
			}
			//if (shootableEntities[i]->ShouldHaunt())
			//{
			//
			//}
		}
		m_elapsedTime += deltaTime;
		if (m_elapsedTime > m_timeBetweenSpawns)
		{
			m_elapsedTime = 0;
			ClearSpots();
			int spot = GetUnusedSpot();
			if (spot != -1)
			{
				Vector2f* pos = m_spawnSpots[spot];
				int index = PickEntity();
				if (index != -1)
				{
					*m_usedSpots[spot] = index;
					m_shootableEntities[index]->Activate(*pos);
				}
			}
		}
		m_ghoulsCounter->setString("Ghouls killed : " + std::to_string(m_kills));
		m_spiritCounter->setString("Spirit: " + std::to_string(m_lives));
	};

	virtual void Draw(RenderWindow* rw)override
	{
		rw->draw(*m_background);
		for (int i = 0; i < 12; i++)
		{
			if (m_shootableEntities[i]->IsActive())
			{
				rw->draw(*m_shootableEntities[i]->GetSprite());
			}
		}
		rw->draw(*m_foreground);
		rw->draw(*m_crosshair);
		rw->draw(*m_ghoulsCounter);
		rw->draw(*m_spiritCounter);
	}

	virtual bool CheckState() override
	{
		if (m_lives <= 0)
		{
			return true;
		}
		return false;
	}

	int PickEntity()
	{
		int iterations = 0;
		int index = rand() % 12;
		while (m_shootableEntities[index]->IsActive() && iterations < 5)
		{
			index += rand() % 12;
			index %= 12;
			iterations++;
		}
		return  iterations < 5 ? index : -1;
	}

	void ClearSpots()
	{
		for (int i = 0; i < 6; i++)
		{
			int spotEntity = *m_usedSpots[i];
			if (spotEntity != -1)
			{
				spotEntity %= 12;
				if (!m_shootableEntities[spotEntity]->IsActive())
				{
					*m_usedSpots[i] = -1;
				}
			}
		}
	}

	int GetUnusedSpot()
	{
		int counter = 0;
		for (int i = 0; i < 6; i++)
		{
			if (*m_usedSpots[i] == -1)
			{
				counter++;
			}
		}
		if (counter == 0)
		{
			return -1;
		}
		int* availableSpots = new int[counter];
		int index = 0;
		for (int i = 0; i < 6; i++)
		{
			int spotEntity = *m_usedSpots[i];
			if (spotEntity == -1)
			{
				availableSpots[index] = i;
				index++;
			}
		}
		int selectedIndex = rand() % counter;
		int selectedSpot = availableSpots[rand() % counter];
		return selectedSpot;
	}

	int GetScore()
	{
		return m_kills - (m_lives * 2);
	}
};

