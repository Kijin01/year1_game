#include <SFML/Graphics.hpp>
#include <iostream>
#include "entity.h"
#include "player.h"

using namespace sf;
using namespace std;


float gameWidth = 800.0f;
float gameHeight = 600.0f;

Player* player;

void Reset() {};

void Load() {
	//Load the player
	player = new Player();
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

	player->Update(dt);
}

void Render(RenderWindow& window) {
	player->Render(window);
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "TILE ENGINE");
	Load();

	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}