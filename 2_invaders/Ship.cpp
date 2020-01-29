//ship.cpp
#include "ship.h"
#include "game.h"

using namespace sf;
using namespace std;

Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite() {
    _sprite = ir;
    setTexture(spritesheet);
    setTextureRect(_sprite);
};

void Ship::Update(const float& dt) {}

//Define the ship deconstructor. 
//Although we set this to pure virtual, we still have to define it.
Ship::~Ship() = default;

//Inherit from the ship
Invader::Invader() : Ship() {}

//Invader
Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
    setOrigin(16, 16);
    setPosition(pos);
}

void Invader::Update(const float& dt) {
    Ship::Update(dt);

    move(dt * (direction ? 1.0f : -1.0f) * speed, 0);

    if ((direction && getPosition().x > gameWidth - 16) ||
        (!direction && getPosition().x < 16)) {
        direction = !direction;
        for (int i = 0; i < ships.size() - 1; ++i) {
            ships[i]->move(0, 24);
        }
    }
}

//Speed and direction
bool Invader::direction;
float Invader::speed;


//Player
Player::Player() : Ship(IntRect(160, 32, 32, 32)) {
    setOrigin(16, 16);
    setPosition({ gameWidth * .5f, gameHeight - 32.f });
}

void Player::Update(const float& dt) {
    Ship::Update(dt);
    // Movement
    float direction = 0.0f;
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        if (getPosition().x - 16 > 0)
            direction--;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        if (getPosition().x + 16 < gameWidth)
            direction++;
    }
    ships[invaders_rows * invaders_columns]->move(direction * speed * dt, 0);
}

//Speed
float Player::speed;

