#pragma once
//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "ShootableEntity.cpp"
#include <iostream>

class Gameplay : public GameState
{
private:
	int lives;
	int kills;
	float m_timeBetweenSpawns;
	float elapsedTime;
	Sprite* sBackground;
	Texture* tBackground;
	Sprite* sForeground;
	Texture* tForeground;
	Sprite* sCrosshair;
	Texture* tCrosshair;
	Vector2f* crosshairOffset;
	ShootableEntity* shootableEntities[12];
	Vector2f* spawnSpots[6];
	int* spawnSpots[6];
	sf::Time currentTime;
	sf::Clock clock;

public:
	Gameplay(RenderWindow* rw)
	{
		lives = 3;
		kills = 0;
		elapsedTime = 0;
		m_timeBetweenSpawns = 2.0f;


		sCrosshair = new Sprite();
		tCrosshair = new Texture();
		sBackground = new Sprite();
		tBackground = new Texture();
		sForeground = new Sprite();
		tForeground = new Texture();

		tCrosshair->loadFromFile("assets/crosshair.png");
		sCrosshair->setTexture(*tCrosshair);

		tBackground->loadFromFile("assets/mansion.jpg");
		sBackground->setTexture(*tBackground);

		tForeground->loadFromFile("assets/mansion_transparency.png");
		sForeground->setTexture(*tForeground);

		float ratio = (float)rw->getSize().x/ (float)tBackground->getSize().x;
		sBackground->setScale(ratio, ratio);
		sForeground->setScale(ratio, ratio);

		spawnSpots[0] = new Vector2f(554 * ratio, 683 * ratio);
		spawnSpots[1] = new Vector2f(554 * ratio, 516 * ratio);
		spawnSpots[2] = new Vector2f(303 * ratio, 683 * ratio);
		spawnSpots[3] = new Vector2f(303 * ratio, 516 * ratio);
		spawnSpots[4] = new Vector2f(787 * ratio, 683 * ratio);
		spawnSpots[5] = new Vector2f(787 * ratio, 516 * ratio);

		crosshairOffset = new Vector2f(tCrosshair->getSize().x / 2.0f, tCrosshair->getSize().y / 2.0f);
		for (int i = 0; i < 12; i++)
		{
			std::string path = "assets/characters/";
			path += i < 6 ? "innocent" : "enemy";
			path += std::to_string(i < 6 ? i : i - 6);
			path += ".png";
			bool isEnemy = i < 6;
			float initialDuration = 5.0f;
			shootableEntities[i] = new ShootableEntity(path, isEnemy, initialDuration);
		}
	}

	void Update(RenderWindow* rw) override
	{
		float deltaTime = clock.getElapsedTime().asSeconds();
		clock.restart();
		Vector2i mousePos = Mouse::getPosition(*rw);
		Vector2f fMousePos(mousePos.x, mousePos.y);
		sCrosshair->setPosition(mousePos.x - crosshairOffset->x, mousePos.y - crosshairOffset->y);
		for (int i = 0; i < 12; i++)
		{
			if (shootableEntities[i]->IsActive())
			{
				shootableEntities[i]->Update(deltaTime, rw);
				if (Mouse::isButtonPressed(Mouse::Button::Left))
				{
					if (shootableEntities[i]->CheckShoot(fMousePos))
					{
						if (shootableEntities[i]->IsEnemy())
						{
							kills++;
						}
						else
						{
							lives--;
						}
						shootableEntities[i]->Deactivate();
					}
				}
			}
		}
		elapsedTime += deltaTime;
		if (elapsedTime > m_timeBetweenSpawns)
		{
			elapsedTime = 0;
			//Vector2f pos(0, 0);
			Vector2f* pos = spawnSpots[rand() % 6];
			//Vector2f pos(rand() % rw->getSize().x, rand() % rw->getSize().y);
			int index = PickEntity();
			if (index != -1)
			{
				shootableEntities[index]->Activate(*pos);
			}
		}
	};

	virtual void Draw(RenderWindow* rw)override
	{
		rw->draw(*sBackground);
		for (int i = 0; i < 12; i++)
		{
			if (shootableEntities[i]->IsActive())
			{
				rw->draw(*shootableEntities[i]->GetSprite());
			}
		}
		rw->draw(*sForeground);
		rw->draw(*sCrosshair);
	}

	virtual GameState* CheckState(RenderWindow* rw) override
	{
		return NULL;
	}

	int PickEntity()
	{
		int iterations = 0;
		int index = rand() % 12;
		std::cout << index << std::endl;
		while (shootableEntities[index]->IsActive() && iterations < 5)
		{
			index += rand() % 12;
			index %= 12;
			iterations++;
		}
		return  iterations < 5 ? index : -1;
	}
};

