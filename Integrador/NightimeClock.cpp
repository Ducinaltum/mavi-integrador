#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
#pragma once
class NightimeClock
{
private:
	float m_elapsedTime;
	float m_nightDurationInSeconds;
	bool m_hasNightEnded;
	Sprite* m_clockSprite;
	Sprite* m_needleSprite;
	Texture* m_clockTex;
	Texture* m_needleTex;

public:
	NightimeClock()
	{
		m_elapsedTime = 0;
		m_nightDurationInSeconds = 120;
		m_hasNightEnded = false;
		m_clockSprite = new Sprite();
		m_clockTex = new Texture();
		m_clockTex->loadFromFile("assets/clock.png");
		m_clockSprite->setTexture(*m_clockTex);
		m_needleSprite = new Sprite();
		m_needleTex = new Texture();
		m_needleTex->loadFromFile("assets/needle.png");
		m_needleSprite->setTexture(*m_needleTex);
	}

	void Update(float dt)
	{
		m_elapsedTime += dt;
		if (m_elapsedTime >= m_nightDurationInSeconds)
		{
			m_hasNightEnded = true;
		}
	}

	bool GetHasNigthEnded()
	{
		return m_hasNightEnded;
	}

	void Draw(RenderWindow* rw)
	{
		rw->draw(*m_clockSprite);
		rw->draw(*m_needleSprite);
	}
};
