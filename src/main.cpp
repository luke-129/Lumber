#include <SFML/Graphics.hpp>
#include <sstream>
using namespace sf;
#include <iostream>



void updateBranches(int seed);
const int NUM_BRANCHES = 6;


enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

int main()
{

    
    /***********Texture and sprite logic*************/

    // Branch

    Texture branchTexture;
    branchTexture.loadFromFile("C:\\Users\\chasi\\source\\repos\\Lumber\\assets\\graphics\\tree\\Branch.png");
    Sprite branches[NUM_BRANCHES] = { Sprite(branchTexture), Sprite(branchTexture), Sprite(branchTexture), Sprite(branchTexture), Sprite(branchTexture),Sprite(branchTexture) };
    for (int i = 0; i < NUM_BRANCHES; i++)
    {
        branches[i].scale(Vector2f(10,10));
        branches[i].setPosition(Vector2f( - 2000, -2000));
        // Set the sprite's origin to dead centre
        // We can then spin it round without changing its position
        branches[i].setOrigin(Vector2f(205, 20));
    }

    // Background
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

    int score = 0;

    // Text
    Font font;
    font.openFromFile("C:\\Users\\chasi\\source\\repos\\Lumber\\assets\\fonts\\PressStart2P-vaV7.ttf");

    Text messageText = Text(font, "");
    Text scoreText = Text(font, "");

    //Score
    scoreText.setString("0");
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(Color::White);
    scoreText.setFont(font);

    //Start of the game text
    messageText.setString("Press enter to start");
    messageText.setCharacterSize(50);
    messageText.setFillColor(Color::White);
    messageText.setFont(font);

    // Position the text
    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.getCenter());
    messageText.setPosition(Vector2f(1920 / 2, 1080 / 2));
    scoreText.setPosition(Vector2f(20, 20));

    

    Clock clock;

    //Time bar
    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition(Vector2f((1920 /2) - timeBarStartWidth / 2, 980));
    Time gameTimeTotal;
    float timeRemaining = 6.f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    bool bPaused = true;

    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);

    // Initial Window drawing logic
    window.clear();
    window.draw(spriteCloud);
    window.draw(spriteCloudTwo);
    window.draw(spriteBackground);
    window.draw(spriteMidground);
    window.draw(spriteTree);
    window.draw(spriteMidForeground);
    window.draw(spriteBee);
    //window.draw(spriteForeground);
    window.draw(messageText);
    window.display();
    
    updateBranches(1);

    updateBranches(2);

    updateBranches(3);

    updateBranches(4);

    updateBranches(5);


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
        {
            bPaused = false;
            score = 0;
            timeRemaining = 6;
        }


        // If the game is not paused
        if (!bPaused)
        {
            //Score
            std::stringstream ss;
            ss << "Score: " << score;
            scoreText.setString(ss.str());
                  

            // update the branch sprites

            for (int i = 0; i < NUM_BRANCHES; i++)

            {

                float height = i * 150;

                if (branchPositions[i] == side::LEFT)

                {

                    // Move the sprite to the left side

                    branches[i].setPosition(Vector2f(610, height));

                    // Flip the sprite round the other way

                    branches[i].setRotation(sf::Angle(sf::radians(120.f)));

                }

                else if (branchPositions[i] == side::RIGHT)

                {

                    // Move the sprite to the right side

                    branches[i].setPosition(Vector2f(1330, height));

                    // Set the sprite rotation to normal

                    branches[i].setRotation(Angle());

                }

                else

                {

                    // Hide the branch

                    branches[i].setPosition(Vector2f(3000, height));

                }

            }



            // Delta time
            Time dt = clock.restart();

            //Subtract from the amount of time remaining
            timeRemaining -= dt.asSeconds();
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));


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

            // Move the bee
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

            // Move cloud right
            if (!moveCloudleft)
            {

                spriteCloud.setPosition(Vector2f(spriteCloud.getPosition().x + cloudSpeed * dt.asSeconds(), 0));
                spriteCloudTwo.setPosition(Vector2f(spriteCloudTwo.getPosition().x + cloudSpeed * dt.asSeconds(), 0));
            }

            //Move cloud left
            else
            {
                spriteCloud.setPosition(Vector2f(spriteCloud.getPosition().x - cloudSpeed * dt.asSeconds(), 0));
                spriteCloudTwo.setPosition(Vector2f(spriteCloudTwo.getPosition().x - cloudSpeed * dt.asSeconds(), 0));
            }


            // Window drawing logic
            window.clear();
            window.draw(spriteCloud);
            window.draw(spriteCloudTwo);
            window.draw(spriteBackground);
            window.draw(spriteMidground);
            for (int i = 0; i < NUM_BRANCHES; i++)

            {

                window.draw(branches[i]);

            }

            window.draw(spriteTree);
            window.draw(spriteMidForeground);
            window.draw(spriteBee);
            //window.draw(spriteForeground);
            window.draw(scoreText);
            window.draw(timeBar);
            

            if (timeRemaining <= 0.0f) {
                // Pause the game
                bPaused = true;
                // Change the message shown to the player
                messageText.setString("Out of time!!");
                //Reposition the text based on its new size
                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.getCenter());
                messageText.setPosition(Vector2f(1920 / 2.0f, 1080 / 2.0f));
                window.draw(messageText);

            }


            window.display();

        }
        
        
    }
}

void updateBranches(int seed)
{
    // Move all the branches down one place

    for (int j = NUM_BRANCHES - 1; j > 0; j--) {

        branchPositions[j] = branchPositions[j - 1];

    }

    // Spawn a new branch at position 0

    // LEFT, RIGHT or NONE

    srand((int)time(0) + seed);

    int r = (rand() % 5);

    switch (r) {

    case 0:

        branchPositions[0] = side::LEFT;

        break;

    case 1:

        branchPositions[0] = side::RIGHT;

        break;

    default:

        branchPositions[0] = side::NONE;

        break;

    }

}
