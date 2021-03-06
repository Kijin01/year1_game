#include <SFML/Graphics.hpp>
#include <iostream>
#include "pacman.h"
#include "system_renderer.h"
#include "scene.h"

using namespace sf;
using namespace std;


std::shared_ptr<Scene> gameScene;
std::shared_ptr<Scene> menuScene;
std::shared_ptr<Scene> activeScene;



void Load() {
	// Load Scene-Local Assets
	gameScene.reset(new GameScene());
	menuScene.reset(new MenuScene());
	gameScene->load();
	menuScene->load();
	// Start at main menu
	activeScene = gameScene;
	
}

void Update(RenderWindow &window) {
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	activeScene->update(dt);
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}
	// Quit via ESC Key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

}

void Render(RenderWindow &window) {
	activeScene->render();
	//flush to screen
	Renderer::render();

}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PacMan");
	Renderer::initialise(window);
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}