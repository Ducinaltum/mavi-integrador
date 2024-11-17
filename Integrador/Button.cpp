//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
//Inspired in https://en.sfml-dev.org/forums/index.php?topic=5950.0
class Button {
public:
    Button(sf::Texture* normal, sf::Texture* clicked, std::string, sf::Vector2f location);
    void checkClick(sf::Vector2f);
    void setState(bool);
    sf::Sprite* getSprite();
private:
    Sprite* normal;
    Sprite* clicked;
    Sprite* currentStateSprite;
    Text * text;
    bool current;
    RenderTexture* buttonTexture;
    Vector2f * targetSize;
};

Button::Button(sf::Texture* normalTexture, sf::Texture* clickedTexture, std::string words, sf::Vector2f location)
{
    normal = new Sprite();
    clicked = new Sprite();
    text = new Text();
    targetSize = new Vector2f(128, 128);
    normal->setTexture(*normalTexture);
    clicked->setTexture(*clickedTexture);
    currentStateSprite = normal;
    current = false;
    normal->setPosition(location);
    clicked->setPosition(location);
    text->setString(words);
    text->setPosition(location.x + 4, location.y + 4);
    text->setCharacterSize(14);
    buttonTexture = new RenderTexture();
    buttonTexture->create((int)targetSize->x, (int)targetSize->y);
}
void Button::checkClick(sf::Vector2f mousePos) {
    /*
    REDO
    if (mousePos.x > currentSpr->getPosition().x && mousePos.x < (currentSpr->getPosition().x + currentSpr->GetSize().x)) {
        if (mousePos.y > currentSpr->getPosition().y && mousePos.y < (currentSpr->getPosition().y + currentSpr->GetSize().y)) {
            setState(!current);
        }
    }
    */
}
void Button::setState(bool which) {
    current = which;
    if (current) 
    {
        currentStateSprite = clicked;
        return;
    }
    currentStateSprite = normal;
}

Sprite* Button::getSprite() {
    return currentStateSprite;
}


/*
    sf::Vector2i localPosition = sf::Mouse::getPosition(*app);
    sprite->setTexture(*tex);
    sprite->setOrigin(tex->getSize().x / 2, tex->getSize().y / 2);
    sprite->setPosition(localPosition.x, localPosition.y);
    texture->draw(*sprite);
    texture->display();
*/