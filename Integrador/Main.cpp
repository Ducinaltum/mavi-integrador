//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
	RenderWindow App(sf::VideoMode(800, 600, 32), "Integrador");
	while (App.isOpen())
	{
		Event evt;
		while (App.pollEvent(evt))
		{
			switch (evt.type)
			{
			case sf::Event::Closed:
				App.close();
				break;
			}
		}
		App.clear();

		App.display();
	}
	return 0;
}