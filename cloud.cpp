#include "cloud.h"


Cloud::Cloud()
{
    m_speed = 100 + rand() % 100;
    m_textureCloud.loadFromFile("graphics/cloud.png");
    setTexture(m_textureCloud);
    setPosition(rand() % 200, 0);
}

void Cloud::move(sf::Time dt)
{
    if (m_active) {
        const auto pos = getPosition();
        setPosition(pos.x + m_speed * dt.asSeconds(),  pos.y);
        if (pos.x > 1920)
            m_active = false;
    } else {
        m_speed = 100 + rand() % 100;
        float height = rand() % 300;
        setPosition(-200, height);
        m_active = true;
    }
}
