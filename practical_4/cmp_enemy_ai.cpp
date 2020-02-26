#include "cmp_enemy_ai.h"
#include "levelsystem.h"

using namespace sf;
using namespace std;

static const Vector2i directions[] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};

EnemyAIComponent::EnemyAIComponent(Entity* p)
    : _direction(directions[(rand() % 4)]), _state(ROAMING), ActorMovementComponent(p) {}

void EnemyAIComponent::update(double dt) {
  //amount to move
  const auto mva = (float)(dt * _speed); 
  //Curent position
  const Vector2f pos = _parent->getPosition();
  //Next position
  const Vector2f newpos = pos + _direction * mva;
  //Inverse of our current direction
  const Vector2i baddir = -1 * Vector2i(_direction);
  //Random new direction
  Vector2i newdir = directions[(rand() % 4)];
  
 switch (_state) {
   case ROAMING:
     if (ls::getTileAt(newpos) == ls::WALL)// Wall in front or at waypoint
     {
       //start rotate
         _state = ROTATING;
     } else {
       //keep moving
         move(_direction * mva);

     }
     break;
    
   case ROTATING:
       while (
           //Don't reverse
           newdir == baddir
           // and Don't pick a direction that will lead to a wall
          || ls::getTileAt(pos + (Vector2f(newdir) * 25.0f)) == ls::WALL
        ) {
           // pick new direction
           newdir = directions[rand() % 4];
        }
     _direction = Vector2f(newdir);
     _state = ROTATED;
     break;
      
   case ROTATED:
     //have we left the waypoint?
     if (LevelSystem::getTileAt(pos) != LevelSystem::WAYPOINT) {
        _state = ROAMING; //yes
     }
     move(_direction * mva); //No
     break;

 }
 ActorMovementComponent::update(dt);
}