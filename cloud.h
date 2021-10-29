#ifndef CLOUD_H
#define CLOUD_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>

class Cloud : public sf::Sprite
{
public:
    Cloud();
    void move(sf::Time dt);

private:
    bool m_active = false;
    int m_speed;
    sf::Texture m_textureCloud;
};

#endif // CLOUD_H
