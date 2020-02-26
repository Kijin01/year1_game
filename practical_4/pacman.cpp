#include "pacman.h"
#include "cmp_sprite.h"
#include "levelsystem.h"

#define GHOSTS_COUNT 4

using namespace std;
using namespace sf;


void MenuScene::update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
        activeScene = gameScene;
    }

	Scene::update(dt);
	
}

void MenuScene::render() {
  Renderer::queue(&text);
  Scene::render();
}

void MenuScene::load() {
//Set up the text element here!
}

void GameScene::update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}
	 
	Scene::update(dt);
}

void GameScene::load() {

    {
        auto pl = make_shared<Entity>();

        auto s = pl->addComponent<ShapeComponent>();
        s->setShape<sf::CircleShape>(12.f);
        s->getShape().setFillColor(Color::Yellow);
        s->getShape().setOrigin(Vector2f(12.f, 12.f));

        _ents.list.push_back(pl);
    }

    const sf::Color ghost_cols[]{ {208, 62, 25},    // red Blinky
                                 {219, 133, 28},   // orange Clyde
                                 {70, 191, 238},   // cyan Inky
                                 {234, 130, 229} }; // pink Pinky

    for (int i = 0; i < GHOSTS_COUNT; ++i) {
        auto ghost = make_shared<Entity>();
        auto s = ghost->addComponent<ShapeComponent>();
        s->setShape<sf::CircleShape>(12.f);
        s->getShape().setFillColor(ghost_cols[i % 4]);
        s->getShape().setOrigin(Vector2f(12.f, 12.f));

        _ents.list.push_back(ghost);
    }
}

void GameScene::render() {
    ls::Render(Renderer::getWindow()); 
    Scene::render();
}
