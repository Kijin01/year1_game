#include "scene.h"

using namespace std;
using namespace sf;

void Scene::render() {
	_ents.render();
}

void Scene::update(const double dt) {
	_ents.update(dt);
}

