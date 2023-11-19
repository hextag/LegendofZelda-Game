#include "main.h"

#ifndef BOAT_H
#define BOAT_H


class Boat {
public:
    Boat() {}
    Boat(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    int get_score();
    void respawn(int spawn_counter);
    void wind_tick(int is_wind, int dir);
    double speedy;
    int score, health, lives;
    int in_air;
    int cam_view,points;
    int is_boost, level;
    int flag;
    bounding_box_t bounding_box();

private:
  VAO *object1;
  VAO *object2;
  VAO *object3;
};

#endif // BOAT_H
