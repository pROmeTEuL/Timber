#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    VideoMode vm(1920, 900);
    RenderWindow window(vm, "Timber", Style::Default);

    /*
    ******************************
             TEXTURILE
    ******************************
    */
    ///FUNDAL
    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");
    ///COPAC
    Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    ///ALBINA
    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    ///NORI
    Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");
    /*
    ******************************
             CONFIGURARI
    ******************************
    */
    ///FUNDAL
    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);
    ///COPAC
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, 0);
    ///ALBINA
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    bool beeActive = false;
    float beeSpeed = 0.0f;
    ///NORI
    Sprite spriteCloud0;
    Sprite spriteCloud1;
    Sprite spriteCloud2;
    spriteCloud0.setTexture(textureCloud);
    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud0.setPosition(0, 0);
    spriteCloud1.setPosition(0, 250);
    spriteCloud2.setPosition(0, 500);
    bool cloud0active = false;
    bool cloud1active = false;
    bool cloud2active = false;
    float cloud0speed = 0.0f;
    float cloud1speed = 0.0f;
    float cloud2speed = 0.0f;

    /*
    ******************************

    ******************************
    */

    Clock clock;

    /*
    ******************************
             BUCLA WHILE
    ******************************
    */
    while (window.isOpen()) {
        if(Keyboard::isKeyPressed(Keyboard::Escape)){
            window.close();
        }
        Time dt = clock.restart();
        if (!beeActive) {
            srand((int)time(0));
            beeSpeed = (rand() % 200) + 200;
            srand((int)time(0) * 10);
            float height = (rand() % 500) + 500;
            spriteBee.setPosition(2000, height);
            beeActive = true;
        }
        else {
            spriteBee.setPosition(
                        spriteBee.getPosition().x -
                        beeSpeed * dt.asSeconds(),
                        spriteBee.getPosition().y);
            if (spriteBee.getPosition().x < -100) {
                beeActive = false;
            }
        }
        if (!cloud0active) {
            srand((int)time(0) * 10);
            cloud0speed = (rand() % 200);
            srand((int)time(0) * 10);
            float height = rand() % 150;
            spriteCloud0.setPosition(-200, height);
            cloud0active = true;
        } else {
            spriteCloud0.setPosition(
                        spriteCloud0.getPosition().x +
                        (cloud0speed * dt.asSeconds()),
                        spriteCloud0.getPosition().y);
            if (spriteCloud0.getPosition().x > 1920) {
                cloud0active = false;
            }
        }
        if (!cloud1active) {
            srand((int)time(0) * 20);
            cloud1speed = (rand() % 200);
            srand((int)time(0) * 20);
            float height = rand() % 300 - 150;
            spriteCloud1.setPosition(-200, height);
            cloud1active = true;
        } else {
            spriteCloud1.setPosition(
                        spriteCloud1.getPosition().x +
                        (cloud1speed * dt.asSeconds()),
                        spriteCloud1.getPosition().y);
            if(spriteCloud1.getPosition().x > 1920) {
                cloud1active = false;
            }
        }
        if (!cloud2active) {
            srand((int)time(0) * 30);
            cloud2speed = (rand() % 200);
            srand((int)time(0) * 30);
            float height = rand() % 450 - 150;
            spriteCloud2.setPosition(-200, height);
            cloud2active = true;
        } else {
            spriteCloud2.setPosition(
                        spriteCloud2.getPosition().x +
                        cloud2speed * dt.asSeconds(),
                        spriteCloud2.getPosition().y);
            if (spriteCloud2.getPosition().x > 1920) {
                cloud2active = false;
            }
        }
        window.clear();
        window.draw(spriteBackground);
        window.draw(spriteCloud0);
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteTree);
        window.draw(spriteBee);
        window.display();
    }
    return 0;
}
