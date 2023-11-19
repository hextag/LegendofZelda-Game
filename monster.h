#include "main.h"

#ifndef MONSTER_H
#define MONSTER_H


class Monster {
public:
    Monster() {}
    Monster(float x, float y, int size);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    float l;
    bounding_box_t bounding_box();

private:
    VAO *object1;
    VAO *object2;
};

#endif // MONSTER_H
