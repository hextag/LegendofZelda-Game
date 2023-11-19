#include "gift.h"
#include "main.h"

Gift::Gift(float x_cor, float z_cor, color_t color, float height) {
    this->position = glm::vec3(x_cor, -1, z_cor);
    this->rotation = 0;
    speed = 1;
    float a = 0.3, b = 0.3, c = 0.2;
    float temp = b;
    b = height;

    float p = a/2, q = temp/2, r = c/2;
    static const GLfloat vertex_buffer_data_1[] = {
        -p,-q+b,-r, // triangle 1 : begin
        -p,-q+b, r,
        -p, q+b, r, // triangle 1 : end

        p, q+b,-r, // triangle 2 : begin
        -p,-q+b,-r,
        -p, q+b,-r, // triangle 2 : end

        p,-q+b, r,
        -p,-q+b,-r,
        p,-q+b,-r,

        p, q+b,-r,
        p,-q+b,-r,
        -p,-q+b,-r,

        -p,-q+b,-r,
        -p, q+b, r,
        -p, q+b,-r,

        p,-q+b, r,
        -p,-q+b, r,
        -p,-q+b,-r,

        -p, q+b, r,
        -p,-q+b, r,
        p,-q+b, r,

        p, q+b, r,
        p,-q+b,-r,
        p, q+b,-r,

        p,-q+b,-r,
        p, q+b, r,
        p,-q+b, r,

        p, q+b, r,
        p, q+b,-r,
        -p, q+b,-r,

        p, q+b, r,
        -p, q+b,-r,
        -p, q+b, r,

        p, q+b, r,
        -p, q+b, r,
        p,-q+b, r
    };

    this->object2 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data_1, color, GL_FILL);
}

void Gift::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object2);
}

void Gift::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Gift::tick() {
  // if(flag)
  //   this->position.y+=0.01;
  // else
  //   this->position.y-=0.01;
  // flag = 1-flag;
}

bounding_box_t Gift::bounding_box(){
  float x = this->position.x, y = this->position.y , z = this->position.z;
  bounding_box_t bbox = { x, y, z};
  return bbox;
}
