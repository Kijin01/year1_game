#include <SFML/Graphics.hpp>
#include <iostream>
#include "entity.h"
#include "player.h"
#include "levelsystem.h"

using namespace sf;
using namespace std;



float gameWidth = 800.0f;
float gameHeight = 600.0f;

Player* player;

void Reset() {};

void Load() {
	//Load the player
	player = new Player();

	player->setPosition({ 146.978, 133.754 });

	ls::loadLevelFile("res/maze_2.txt");

	// Print the level to the console
	for (size_t y = 0; y < ls::getHeight(); ++y) {
		for (size_t x = 0; x < ls::getWidth(); ++x) {
			cout << ls::getTile({ x, y });
		}
		cout << endl;
	}
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

	if (Keyboard::isKeyPressed(Keyboard::P)) {
		cout << player->getPosition();
	}


	player->Update(dt);
}

void Render(RenderWindow& window) {
	ls::Render(window);
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