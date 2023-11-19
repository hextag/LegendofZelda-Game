#include "barrel.h"
#include "main.h"

Barrel::Barrel(float x_cor, float z_cor) {
    this->position = glm::vec3(x_cor, -1, z_cor);
    this->rotation = 0;
    speed = 1;
    float a = 0.3, b = 0.3, c = 0.2;
    float temp = b;
    b = b/5;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -a,-b,-c, // triangle 1 : begin
        -a,-b, c,
        -a, b, c, // triangle 1 : end

        a, b,-c, // triangle 2 : begin
        -a,-b,-c,
        -a, b,-c, // triangle 2 : end

        a,-b, c,
        -a,-b,-c,
        a,-b,-c,

        a, b,-c,
        a,-b,-c,
        -a,-b,-c,

        -a,-b,-c,
        -a, b, c,
        -a, b,-c,

        a,-b, c,
        -a,-b, c,
        -a,-b,-c,

        -a, b, c,
        -a,-b, c,
        a,-b, c,

        a, b, c,
        a,-b,-c,
        a, b,-c,

        a,-b,-c,
        a, b, c,
        a,-b, c,

        a, b, c,
        a, b,-c,
        -a, b,-c,

        a, b, c,
        -a, b,-c,
        -a, b, c,

        a, b, c,
        -a, b, c,
        a,-b, c
    };
  //  b = temp;

    this->object1 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_YELLOW, GL_FILL);
}

void Barrel::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
}

void Barrel::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Barrel::tick() {
      this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t Barrel::bounding_box(){
  float x = this->position.x, y = this->position.y , z = this->position.z;
  bounding_box_t bbox = { x, y, z};
  return bbox;
}
