//ship.cpp
#include "ship.h"
#include "game.h"
#include "bullet.h"

using namespace sf;
using namespace std;

Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite() {
    _exploded = false; //need to do this intially, since we dont want all of our ships be exploded from the start
    _sprite = ir;
    setTexture(spritesheet);
    setTextureRect(_sprite);
};

void Ship::Update(const float& dt) {
    
    if (_exploded) {
        _explosiontime -= dt;
    }
    if (_explosiontime <= 0.f) {
        setColor(Color(0, 0, 0, 0));	//make the ship transparent
    }
}

void Ship::Explode() {
    _exploded = true;
}

bool Ship::is_exploded() const {
    return _exploded;
}

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
    // Fire bullets
    // (each invader is not able to fire more than once in 4 seconds)
    static float firetime = 0.f;
    firetime -= dt;
    if (firetime <= 0 && rand() % 100 == 0 && !_exploded) {
        Bullet::Fire(getPosition(), true);
        firetime = 4.f + (rand() % 60);
    }
}


void Invader::Explode() {
    Ship::Explode();
    setTextureRect(IntRect(128, 32, 32, 32));
}

//Speed and direction
bool Invader::direction;
float Invader::speed;


//Player
Player::Player() : Ship(IntRect(160, 32, 32, 32)) {
    setOrigin(16, 16);
    setPosition({ gameWidth * .5f, gameHeight - 32.f });
}


int player = invaders_rows * invaders_columns;  //because it will always be the last ship in the vector

void Player::Explode() {
    Ship::Explode();
    setTextureRect(IntRect(0, 32, 32, 32));
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
    ships[player]->move(direction * speed * dt, 0);

    // Bullets
    
    static float firetime = 0.f;
    firetime -= dt;
    if (firetime <= 0 && Keyboard::isKeyPressed(Keyboard::F)) {
        Bullet::Fire(getPosition(), false);
        firetime = 0.7f;
    }
    
}



//Speed
float Player::speed;

