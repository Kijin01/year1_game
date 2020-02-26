//cmp_enemy_ai.h
class EnemyAIComponent : public ActorMovementComponent {
protected:
  sf::Vector2f _direction;
  enum state {ROAMING, ROTATING, ROTATED };
  state _state;
...
}