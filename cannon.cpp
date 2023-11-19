#include "cannon.h"
#include "main.h"

Cannon::Cannon(float x, float z, float rotation) {
    this->position = glm::vec3(x, -1, z);
    this->rotation = rotation;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -0.1f,-0.1f,-0.1f, // triangle 1 : begin
        -0.1f,-0.1f, 0.1f,
        -0.1f, 0.1f, 0.1f, // triangle 1 : end

        0.1f, 0.1f,-0.1f, // triangle 2 : begin
        -0.1f,-0.1f,-0.1f,
        -0.1f, 0.1f,-0.1f, // triangle 2 : end

        0.1f,-0.1f, 0.1f,
        -0.1f,-0.1f,-0.1f,
        0.1f,-0.1f,-0.1f,

        0.1f, 0.1f,-0.1f,
        0.1f,-0.1f,-0.1f,
        -0.1f,-0.1f,-0.1f,

        -0.1f,-0.1f,-0.1f,
        -0.1f, 0.1f, 0.1f,
        -0.1f, 0.1f,-0.1f,

        0.1f,-0.1f, 0.1f,
        -0.1f,-0.1f, 0.1f,
        -0.1f,-0.1f,-0.1f,

        -0.1f, 0.1f, 0.1f,
        -0.1f,-0.1f, 0.1f,
        0.1f,-0.1f, 0.1f,

        0.1f, 0.1f, 0.1f,
        0.1f,-0.1f,-0.1f,
        0.1f, 0.1f,-0.1f,

        0.1f,-0.1f,-0.1f,
        0.1f, 0.1f, 0.1f,
        0.1f,-0.1f, 0.1f,

        0.1f, 0.1f, 0.1f,
        0.1f, 0.1f,-0.1f,
        -0.1f, 0.1f,-0.1f,

        0.1f, 0.1f, 0.1f,
        -0.1f, 0.1f,-0.1f,
        -0.1f, 0.1f, 0.1f,

        0.1f, 0.1f, 0.1f,
        -0.1f, 0.1f, 0.1f,
        0.1f,-0.1f, 0.1f
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_RED, GL_FILL);
}

void Cannon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.1f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Cannon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Cannon::tick() {
  float angle = ((rotation)*3.14)/180;
  float rad = 0.15;

  this->position.z -= rad*cos(angle);
  this->position.x -= rad*sin(angle);
}

bounding_box_t Cannon::bounding_box(){
  float x = this->position.x, y = this->position.y , z = this->position.z;
  bounding_box_t bbox = { x, y, z};
  return bbox;
}
