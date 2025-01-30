#include <SFML/Graphics.hpp>
using namespace sf;
int main()
{
    Texture texture;
    texture.loadFromFile("C:\\Users\\chasi\\source\\repos\\Lumber\\assets\\graphics\\background\\0.png");
    Sprite spriteBackground = Sprite(texture);
    spriteBackground.setPosition(Vector2f(0, 0));
    
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.draw(spriteBackground);
        window.display();
        
    }
}
