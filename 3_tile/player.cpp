//player.cpp
#include "player.h"
using namespace sf;
using namespace std;

void Player::Update(double dt) {
  //Move in four directions based on keys
    sf::Vector2f directionXY = { 0.0f, 0.0f };

    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        directionXY.x--;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        directionXY.x++;
    }
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        directionXY.y++;
    }
    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        directionXY.y--;
    }

    move((float)dt * directionXY * _speed);
    Entity::Update(dt);
}

Player::Player()
    : _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
  _shape->setFillColor(Color::Magenta);
  _shape->setOrigin(Vector2f(25.f, 25.f));
}

void Player::Render(sf::RenderWindow &window) const {
  window.draw(*_shape);
}