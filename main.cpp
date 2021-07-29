#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    VideoMode vm(1280, 720);
    RenderWindow fereastra(vm, "Timber", Style::Default);

    /*
    ******************************
             TEXTURILE
    ******************************
    */
    Texture texturaPeisaj;
    texturaPeisaj.loadFromFile("Peisaj.png");
    Sprite spritePeisaj;
    spritePeisaj.setTexture(texturaPeisaj);
    Texture texturaCopac;
    texturaCopac.loadFromFile("Copac.png");
    Sprite spriteCopac;
    spriteCopac.setTexture(texturaCopac);
    Texture texturaAlbina;
    texturaAlbina.loadFromFile("Albina.png");
    Sprite spriteAlbina;
    spriteAlbina.setTexture(texturaAlbina);

    /*
    ******************************
             CONFIGURARI
    ******************************
    */
    spritePeisaj.setPosition(0,0);
    spriteCopac.setPosition(550, 0);
    spriteAlbina.setPosition(100, 50);
    bool albinaActiva = false;
    float vitezaAlbinei = 0.0;

    /*
    ******************************
             BUCLA WHILE
    ******************************
    */
    while(fereastra.isOpen()){
        if(Keyboard::isKeyPressed(Keyboard::Escape)){
            fereastra.close();
        }
        fereastra.clear();
        fereastra.draw(spritePeisaj);
        fereastra.draw(spriteCopac);
        fereastra.draw(spriteAlbina);
        fereastra.display();
    }
    return 0;
}
