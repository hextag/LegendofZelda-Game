#include "main.h"

#ifndef CANNON_H
#define CANNON_H


class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y, float rotation);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void wind_tick(int is_wind, int dir);
    double speedy;
    int score, health, lives;
    int in_air;
    int cam_view;
    int is_boost;
    bounding_box_t bounding_box();

private:
  VAO *object;
};

#endif // CANNON_H
