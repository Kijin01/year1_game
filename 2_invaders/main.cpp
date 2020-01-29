#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ship.h"
#include "game.h"
#include "bullet.h"





using namespace sf;
using namespace std;

//sfml stuff
sf::Texture spritesheet;
sf::Sprite invader;
std::vector<Ship*> ships;
Ship* playerShip;


void Reset() {
	// reset invaders movement
	Invader::direction = true;
	Invader::speed = 30.f;
	Player::speed = 160.f;
}


void Load() {
    if (!spritesheet.loadFromFile("res/invaders_sheet.png")) {
        cerr << "Failed to load spritesheet!" << std::endl;
    }

	for (int r = 0; r < invaders_rows; ++r) {
		// Note: IntRect(left, top, width, height)
		auto rect = IntRect(32 * r, 0, 32, 32);
		for (int c = 0; c < invaders_columns; ++c) {
			float leftMargin = gameWidth / 2 - 32 * invaders_columns / 2;
			float topMargin = 64.f;
			Vector2f position = { leftMargin + 32.f * c, topMargin + 32.f * r };
			auto inv = new Invader(rect, position);
			ships.push_back(inv);
		}
	}

	// Player
	auto player = new Player();
	playerShip = player;
	ships.push_back(player);
    
	Reset();
	

}

void Update(RenderWindow& window) {
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	// check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	// Quit Via ESC Key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	// Ships
	for (auto& s : ships) {
		s->Update(dt);
	}

	//bullets

	Bullet::Update(dt);

	if (playerShip->is_exploded()) {
		window.close();
	}

}

void Render(RenderWindow& window) {
    window.draw(invader);
	for (const auto s : ships) {
		window.draw(*s);
	}

	Bullet::Render(window);
}


int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "SPACE INVADERS");
	Load();
	
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}