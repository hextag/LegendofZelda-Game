#include "island.h"
#include "main.h"

Island::Island(float x, float y) {
    this->position = glm::vec3(x, y, -250);
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {

    -10000,-2,-10000, // triangle 1 : begin
    -10000,-2, 10000,
    -10000, 2, 10000, // triangle 1 : end

    10000, 2,-10000, // triangle 2 : begin
    -10000,-2,-10000,
    -10000, 2,-10000, // triangle 2 : end

    10000,-2, 10000,
    -10000,-2,-10000,
    10000,-2,-10000,

    10000, 2,-10000,
    10000,-2,-10000,
    -10000,-2,-10000,

    -10000,-2,-10000,
    -10000, 2, 10000,
    -10000, 2,-10000,

    10000,-2, 10000,
    -10000,-2, 10000,
    -10000,-2,-10000,

    -10000, 2, 10000,
    -10000,-2, 10000,
    10000,-2, 10000,

    10000, 2, 10000,
    10000,-2,-10000,
    10000, 2,-10000,

    10000,-2,-10000,
    10000, 2, 10000,
    10000,-2, 10000,

    10000, 2, 10000,
    10000, 2,-10000,
    -10000, 2,-10000,

    10000, 2, 10000,
    -10000, 2,-10000,
    -10000, 2, 10000,

    10000, 2, 10000,
    -10000, 2, 10000,
    10000,-2, 10000

    };

    static const GLfloat vertex_buffer_data1[] = {

    -100,-2,-100, // triangle 1 : begin
    -100,-2, 100,
    -100, 2, 100, // triangle 1 : end

    100, 2,-100, // triangle 2 : begin
    -100,-2,-100,
    -100, 2,-100, // triangle 2 : end

    100,-2, 100,
    -100,-2,-100,
    100,-2,-100,

    100, 2,-100,
    100,-2,-100,
    -100,-2,-100,

    -100,-2,-100,
    -100, 2, 100,
    -100, 2,-100,

    100,-2, 100,
    -100,-2, 100,
    -100,-2,-100,

    -100, 2, 100,
    -100,-2, 100,
    100,-2, 100,

    100, 2, 100,
    100,-2,-100,
    100, 2,-100,

    100,-2,-100,
    100, 2, 100,
    100,-2, 100,

    100, 2, 100,
    100, 2,-100,
    -100, 2,-100,

    100, 2, 100,
    -100, 2,-100,
    -100, 2, 100,

    100, 2, 100,
    -100, 2, 100,
    100,-2, 100

    };

    this->object = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data1, COLOR_8, GL_FILL);
}

void Island::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(2);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Island::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Island::tick() {
      this->rotation += speed;
}