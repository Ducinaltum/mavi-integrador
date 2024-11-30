#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;
#pragma once

class ShootableEntity
{
private:
	const float m_targetHeight = 64.0f;
	Sprite * m_sprite;
	Texture * m_texture;
	float m_elapsedTime;
	float m_duration;
	bool m_isEnemy;
	bool m_isActive;
	bool m_shouldHaunt;

public:
	ShootableEntity(std::string path, bool isEnemy, float initialDuration)
	{
		float sizeRatio = 0;
		m_elapsedTime = 0;
		m_shouldHaunt = false;
		m_isEnemy = isEnemy;
		m_duration = initialDuration;
		m_isActive = false;
		m_sprite = new Sprite();
		m_texture = new Texture();
		m_texture->loadFromFile(path);
		m_sprite->setTexture(*m_texture);
		sizeRatio = m_targetHeight / m_texture->getSize().y;
		m_sprite->setScale(sizeRatio, sizeRatio);
		m_sprite->setOrigin((m_texture->getSize().x * sizeRatio) / 2.0f, m_targetHeight);
	}

	void Update(float dt, RenderWindow* rw)
	{
		m_elapsedTime += dt;
		if (m_elapsedTime >= m_duration)
		{
			if (m_isEnemy)
			{
				m_shouldHaunt = true;
			}
			Deactivate();
		}
	}

	Sprite* GetSprite()
	{
		return m_sprite;
	}

	bool CheckShoot(Vector2f mousePos) {
		return m_sprite->getGlobalBounds().contains(mousePos);
	}

	void Activate(Vector2f pos)
	{
		m_isActive = true;
		m_sprite->setPosition(pos);
		m_elapsedTime = 0;
	}

	void Deactivate()
	{
		m_isActive = false;
		m_elapsedTime = 0;
	}

	bool IsActive()
	{
		return m_isActive;
	}

	bool IsEnemy()
	{
		return m_isEnemy;
	}

	int ShouldHaunt()
	{
		if (m_shouldHaunt)
		{
			m_shouldHaunt = false;
			return true;
		}
		return false;
	}
};