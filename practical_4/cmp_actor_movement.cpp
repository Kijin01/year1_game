//"cmp_actor_movement.cpp"
#include "cmp_actor_movement.h"
#include <LevelSystem.h>

using namespace sf;

void ActorMovementComponent::update(double dt) {}

ActorMovementComponent::ActorMovementComponent(Entity* p)
    : _speed(100.0f), Component(p) {}

bool ActorMovementComponent::validMove(const sf::Vector2f& pos) {
  return (LevelSystem::getTileAt(pos) != LevelSystem::WALL);
}

void ActorMovementComponent::move(const sf::Vector2f& p) {
  auto pp = _parent->getPosition() + p;
  if (validMove(pp)) {
   ...
  }
}

void ActorMovementComponent::move(float x, float y) {
  move(Vector2f(x, y));
}
float ActorMovementComponent::getSpeed() const { ... }
void ActorMovementComponent::setSpeed(float speed) { ... }