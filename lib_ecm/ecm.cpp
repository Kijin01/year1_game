#include "ecm.h"

using namespace std;
using namespace sf;

Entity::Entity()
	: _position({ 0, 0 }), _rotation(0), _alive(true), _visible(true), _fordeletion(false) {}

const sf::Vector2f & Entity::getPosition() const { return _position; }

void Entity::setPosition(const Vector2f &pos) { Entity::_position = pos; }

void Entity::update(const float dt) {
	for (auto c : _components) {
		c->update(dt);
	}
}

bool Entity::is_fordeletion() const { return _fordeletion; }

void Entity::render() {
	for (auto c : _components) {
		c->render();
	}
}