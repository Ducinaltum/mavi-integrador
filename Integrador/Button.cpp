#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;
#pragma once

//Inspired in https://en.sfml-dev.org/forums/index.php?topic=5950.0
class Button {
private:
    Sprite* m_sprite;
    Text* m_text;

public:
    Button(sf::Texture* normalTexture, sf::Texture* clickedTexture, Font * font, std::string words, sf::Vector2f location, sf::Vector2f * targetSize)
    {
        m_sprite = new Sprite();
        m_text = new Text();

        m_text->setFont(*font);
        m_text->setString(words);
        m_text->setPosition(location.x + 16, location.y + 8);
        m_text->setCharacterSize(46);
        m_text->setFillColor(sf::Color::Black);

        m_sprite->setTexture(*normalTexture);
        m_sprite->setScale(targetSize->x / clickedTexture->getSize().x, targetSize->y / clickedTexture->getSize().y);
        m_sprite->setPosition(location);
    }

    bool checkClick(sf::Vector2f mousePos) {
        return m_sprite->getGlobalBounds().contains(mousePos);
    }

    Sprite* getSprite() {
        return m_sprite;
    }

    Text* getText() {
        return m_text;
    }
};