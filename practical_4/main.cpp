#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;


void Load() {
	
}

void Update(RenderWindow &window) {
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
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