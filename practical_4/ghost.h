#pragma once
#include "entity.h"

class Ghost : public Entity {
private:
	float _speed;
public:
	void update(float dt) override;
	Ghost();
	void render();
};