#include "main.h"

#ifndef BOOST_H
#define BOOST_H


class Boost {
public:
    Boost() {}
    Boost(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int is_wind, int dir);
    double speed;
    bounding_box_t bounding_box();

private:
    VAO *object;
};

#endif // BOOST_H
