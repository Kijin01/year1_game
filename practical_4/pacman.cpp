#include "pacman.h"
#include "cmp_sprite.h"
#include "levelsystem.h"
#include "cmp_actor_movement.h"
#include "cmp_player_movement.h"
#include "cmp_enemy_ai.h"

#define GHOSTS_COUNT 4

using namespace std;
using namespace sf;

shared_ptr<Entity> player;
vector<shared_ptr<Entity>> ghosts;


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

	for (auto& g : ghosts) {
		if (length(g->getPosition() - player->getPosition()) < 30.0f) {
			respawn();
		}
	}
	 
	Scene::update(dt);
}

void GameScene::respawn() {
    player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
    player->GetCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(150.f);

    auto ghost_spawns = ls::findTiles(ls::ENEMY);
    for (auto& g : ghosts) {
        g->setPosition(ls::getTilePosition(ghost_spawns[rand() % GHOSTS_COUNT]));
        g->GetCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(100.f);
    }
}



void GameScene::load() {

    ls::loadLevelFile("res/pacman.txt", 25.f);

    {
        auto pl = make_shared<Entity>();
        auto s = pl->addComponent<ShapeComponent>();
        s->setShape<sf::CircleShape>(12.5f);
        s->getShape().setFillColor(Color::Yellow);
        s->getShape().setOrigin(Vector2f(12.5f, 12.5f));

		pl->addComponent<PlayerMovementComponent>();

        _ents.list.push_back(pl);
		player = pl;
    }

    const sf::Color ghost_cols[]{ {208, 62, 25},    // red Blinky
                                 {219, 133, 28},   // orange Clyde
                                 {70, 191, 238},   // cyan Inky
                                 {234, 130, 229} }; // pink Pinky

    for (int i = 0; i < GHOSTS_COUNT; ++i) {
        auto ghost = make_shared<Entity>();
        auto s = ghost->addComponent<ShapeComponent>();
        s->setShape<sf::CircleShape>(12.5f);
        s->getShape().setFillColor(ghost_cols[i % 4]);
        s->getShape().setOrigin(Vector2f(12.5f, 12.5f));

        ghost->addComponent<EnemyAIComponent>();

        _ents.list.push_back(ghost);
        ghosts.push_back(ghost);
    }

    respawn();
}

void GameScene::render() {
    ls::Render(Renderer::getWindow()); 
    Scene::render();
}
