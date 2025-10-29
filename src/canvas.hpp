#pragma once

#include <SFML/Graphics.hpp>
#include <stdint.h>

class Canvas : public sf::Drawable {
public:
    Canvas(const sf::Vector2u texSize);
    ~Canvas();

    void update(sf::Time deltaTime);
    void setParentWindow(sf::RenderWindow*);

    void gui();

private:
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    sf::RenderTexture m_texture;
    sf::Vector2u m_texSize;

    sf::RectangleShape m_shape;
    int m_brushSize;
    bool m_modeEraser;
    sf::CircleShape m_brushIndicator;
    sf::CircleShape m_brushShape;
    
    sf::RenderWindow* m_parentWindow;
};
