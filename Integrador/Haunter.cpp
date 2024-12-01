#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

#pragma once
class Haunter
{
private:
	bool m_isHaunting;
	float m_hauntDuration;
	float m_elapsedTime;
	Sprite* m_ghoulSprite;
	Texture* m_ghoulTexture;
	Sprite* m_damageSprite;
	Texture* m_damageTexture;
public:
	Haunter() {
		m_isHaunting = false;
		m_hauntDuration = 1;
		m_elapsedTime = FLT_MAX;
		m_ghoulSprite = new Sprite();
		m_ghoulTexture = new Texture();
		m_ghoulTexture->loadFromFile("assets/ghoul.png");
		m_damageSprite = new Sprite();
		m_damageTexture = new Texture();
		m_damageTexture->loadFromFile("assets/damage.png");

		m_ghoulSprite->setTexture(*m_ghoulTexture);
		m_damageSprite->setTexture(*m_damageTexture);

	}
	void Haunt()
	{
		m_elapsedTime = 0;
		m_isHaunting = true;
	}
	void Update(float dt)
	{
		if (m_elapsedTime < m_hauntDuration)
		{
			
			m_damageSprite->setColor(Color(255, 255, 255, 255 * sin(m_elapsedTime * 15)));
			m_ghoulSprite->setColor(Color(255, 255, 255, 255 * cos(m_elapsedTime * 15)));
			m_elapsedTime += dt;
		}
		else
		{
			m_isHaunting = false;
		}
	}
	void Draw(RenderWindow* rw)
	{
		if (m_isHaunting)
		{
			rw->draw(*m_ghoulSprite);
			rw->draw(*m_damageSprite);
		}
	};

	bool GetIsHaunting()
	{
		return m_isHaunting;
	}

};
