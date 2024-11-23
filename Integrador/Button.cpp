//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
//Inspired in https://en.sfml-dev.org/forums/index.php?topic=5950.0
class Button {
private:
    Sprite* normal;
    Sprite* clicked;
    Sprite* currentStateSprite;
    Text* text;
    bool current;

public:
    Button(sf::Texture* normalTexture, sf::Texture* clickedTexture, std::string words, sf::Vector2f location, sf::Vector2f * targetSize)
    {
        normal = new Sprite();
        clicked = new Sprite();
        text = new Text();
        normal->setTexture(*normalTexture);
        clicked->setTexture(*clickedTexture);

        clicked->setScale(targetSize->x / normalTexture->getSize().x, targetSize->y / normalTexture->getSize().y);
        normal->setScale(targetSize->x / clickedTexture->getSize().x, targetSize->y / clickedTexture->getSize().y);

        currentStateSprite = normal;
        current = false;
        normal->setPosition(location);
        clicked->setPosition(location);
        text->setString(words);
        text->setPosition(location.x + 4, location.y + 4);
        text->setCharacterSize(14);
        text->setFillColor(sf::Color::Black);
    }
    bool checkClick(sf::Vector2f mousePos) {
        return currentStateSprite->getGlobalBounds().contains(mousePos);
    }
    void setState(bool which) {
        current = which;
        if (current)
        {
            currentStateSprite = clicked;
            return;
        }
        currentStateSprite = normal;
    }

    Sprite* getSprite() {
        return currentStateSprite;
    }
    Text* getText() {
        return text;
    }
};