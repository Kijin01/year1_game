//player.cpp
#include "player.h"
#include "levelsystem.h"
using namespace sf;
using namespace std;


void Player::Update(double dt) {
  //Move in four directions based on keys
    sf::Vector2f directionXY = { 0.0f, 0.0f };

    

    if (Keyboard::isKeyPressed(Keyboard::Left) && ls::validmove(this->getPosition() - Vector2f{1.0f, 0.0f})) {
        directionXY.x--;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right) && ls::validmove(this->getPosition() + Vector2f{ 1.0f, 0.0f })) {
        directionXY.x++;
    }
    if (Keyboard::isKeyPressed(Keyboard::Down) && ls::validmove(this->getPosition() + Vector2f{ 0.0f, 1.0f })) {
        directionXY.y++;
    }
    if (Keyboard::isKeyPressed(Keyboard::Up) && ls::validmove(this->getPosition() - Vector2f{ 0.0f, 1.0f })) {
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

