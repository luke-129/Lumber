#include <SFML/Graphics.hpp>
using namespace sf;
#include <iostream>

int main()
{
    /***********Texture and sprite logic*************/
    Texture backgroundTexture;
    backgroundTexture.loadFromFile("C:\\Users\\chasi\\source\\repos\\Lumber\\assets\\graphics\\background\\background.png");
    Sprite spriteBackground = Sprite(backgroundTexture);
    spriteBackground.setPosition(Vector2f(0, 0));

    Texture midgroundTexture;
    midgroundTexture.loadFromFile("C:\\Users\\chasi\\source\\repos\\Lumber\\assets\\graphics\\background\\midground.png");
    Sprite spriteMidground = Sprite(midgroundTexture);
    spriteMidground.setPosition(Vector2f(0, 0));

    Texture foregroundTexture;
    foregroundTexture.loadFromFile("C:\\Users\\chasi\\source\\repos\\Lumber\\assets\\graphics\\background\\foreground.png");
    Sprite spriteForeground = Sprite(foregroundTexture);
    spriteForeground.setPosition(Vector2f(0, 0));

    Texture midForegroundTexture;
    midForegroundTexture.loadFromFile("C:\\Users\\chasi\\source\\repos\\Lumber\\assets\\graphics\\background\\mid-foreground.png");
    Sprite spriteMidForeground = Sprite(midForegroundTexture);
    spriteMidForeground.setPosition(Vector2f(0, 0));

    Texture treeTexture;
    treeTexture.loadFromFile("C:\\Users\\chasi\\source\\repos\\Lumber\\assets\\graphics\\tree\\tree.png");
    Sprite spriteTree = Sprite(treeTexture);
    const float TREE_HORIZONTAL_POSITION{ 810 };
    const float TREE_VERTICAL_POSITION{ 0 };
    spriteTree.setPosition(Vector2f(TREE_HORIZONTAL_POSITION, TREE_VERTICAL_POSITION));
    spriteTree.scale(Vector2f(10, 35));
    
    Texture beeTexture;
    beeTexture.loadFromFile("C:\\Users\\chasi\\source\\repos\\Lumber\\assets\\graphics\\bee\\Bee-1.png");
    Sprite spriteBee = Sprite(beeTexture);
    spriteBee.scale(Vector2f(.5, .5));
    spriteBee.setPosition(Vector2f(TREE_HORIZONTAL_POSITION, TREE_VERTICAL_POSITION));

    bool beeActive = false;
    float beeSpeed = 0.f;

    Texture cloudTexture;
    cloudTexture.loadFromFile("C:\\Users\\chasi\\source\\repos\\Lumber\\assets\\graphics\\background\\clouds.png");
    Sprite spriteCloud = Sprite(cloudTexture);
    Sprite spriteCloudTwo = Sprite(cloudTexture);
    Vector2f initialCloudTwoPosition = Vector2f(1920, 0);
    spriteCloudTwo.setPosition(initialCloudTwoPosition);
    bool moveCloudleft = true;
    float cloudSpeed = 50.f;

    Clock clock;

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

        Time dt = clock.restart();

        //Setup the bee

        if (!beeActive)
        {
            srand((int)time(0));
            beeSpeed = (rand() % 200) + 200;
            //How high is the bee
            srand((int)time(0) * 10);
            float height = (rand() % 500) + 500;
            spriteBee.setPosition(Vector2f(2000, height));
            beeActive = true;
        }

        else
        {
            float beePositionX = spriteBee.getPosition().x;
            spriteBee.setPosition(Vector2f(beePositionX - beeSpeed * dt.asSeconds(), spriteBee.getPosition().y));


        }

        if (spriteBee.getPosition().x < -100)
        {
            // Set it up ready to be a whole new bee next frame
            beeActive = false;
        }

        // Cloud logic ---------------------

        

        if (spriteCloud.getPosition().x < -500)
            moveCloudleft = false;
        if (spriteCloudTwo.getPosition().x > 1500)
            moveCloudleft = true;

        std::cout << moveCloudleft;
        if (!moveCloudleft)
        {

            spriteCloud.setPosition(Vector2f(spriteCloud.getPosition().x + cloudSpeed * dt.asSeconds(), 0));
            spriteCloudTwo.setPosition(Vector2f(spriteCloudTwo.getPosition().x + cloudSpeed * dt.asSeconds(), 0));
        }

        else
        {
            spriteCloud.setPosition(Vector2f(spriteCloud.getPosition().x - cloudSpeed * dt.asSeconds(), 0));
            spriteCloudTwo.setPosition(Vector2f(spriteCloudTwo.getPosition().x - cloudSpeed * dt.asSeconds(), 0));
        }

        window.clear();
        
        window.draw(spriteCloud);
        window.draw(spriteCloudTwo);
        window.draw(spriteBackground);
        window.draw(spriteMidground);
        window.draw(spriteTree);
        window.draw(spriteMidForeground);
        window.draw(spriteBee);
        //window.draw(spriteForeground);
        window.display();
        
    }
}

