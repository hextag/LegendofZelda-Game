#include "enemy.h"
#include "main.h"

Enemy::Enemy(float x, float y, float z, float rotation) {
    this->position = glm::vec3(x, y, z);
    this->rotation = rotation;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    static const GLfloat vertex_buffer_data1[] = {
        -0.017, 0, 0.48,
        0.017, 0, 0.48,
        -0.017, 1, 0.48,

        -0.017, 0, 0.48,
        -0.017, 1, 0.48,
        0.017, 1, 0.48,

        0.017, 1, 0.48,
        0.017, 0, 0.48,
        0.017, 0, 0.45,

        0.017, 1, 0.48,
        0.017, 0, 0.45,
        0.017, 1, 0.45,

        0.017, 1, 0.45,
        -0.017, 1, 0.48,
        0.017, 1, 0.48,

        0.017, 1, 0.45,
        -0.017, 1, 0.48,
        -0.017, 1, 0.45,

        -0.017, 1, 0.45,
        0.017, 1, 0.45,
       -0.017, 0, 0.45,

        0.017, 1, 0.45,
       -0.017, 0, 0.45,
        0.017, 0, 0.45,

        -0.017, 1, 0.45,
        -0.017, 0, 0.45,
        -0.017, 1, 0.48,

        -0.017, 0, 0.45,
        -0.017, 1, 0.48,
        -0.017, 1, 0.45,

        -0.017, 0, 0.45,
        -0.017, 1, 0.48,
        -0.017, 0, 0.48,

        -0.017, 0, 0.48,
        0.017, 0, 0.48,
        0.017, 0, 0.45,

        -0.017, 0, 0.48,
        0.017, 0, 0.45,
        -0.017, 0, 0.45,
    };

    static const GLfloat vertex_buffer_data[] = {
      0.22, 0.15,0.67,
      0.12, -0.15,0.5,
      0.12, -0.15, -0.5,

      0.22, 0.15,0.67,
      0.12, -0.15, -0.5,
      0.22, 0.15, -0.5,

      -0.12, -0.15, -0.5,
      -0.22, 0.15, -0.67,
       0.12, -0.15, -0.5,

      -0.22, 0.15, -0.67,
      0.12, -0.15, -0.5,
      0.22, 0.15, -0.67,

      -0.22, 0.15, -0.67,
      -0.12, -0.15, -0.5,
      -0.22, 0.15, 0.67,

      -0.12, -0.15, -0.5,
      -0.22, 0.15, 0.67,
      -0.12, -0.15,0.5,

      -0.22, 0.15, 0.67,
      -0.12, -0.15,0.5,
      0.12, -0.15,0.5,

      -0.22, 0.15, 0.67,
      0.12, -0.15,0.5,
      0.22, 0.15, 0.67,

      0.22, 0.15, 0.67,
      0.22, 0.15, -0.67,
      -0.22, 0.15, -0.67,

      0.22, 0.15, 0.67,
      -0.22, 0.15, -0.67,
      -0.22, 0.15, 0.67,

      -0.12, -0.15,0.5,
      0.12, -0.15,0.5,
      -0.12, -0.15, -0.5,

      0.12, -0.15,0.5,
      -0.12, -0.15, -0.5,
      0.12, -0.15, -0.5,
    };
    float t = 255.0f;
    GLfloat colors_data[126];
    color_t colors_boat[] = {
        COLOR_1,COLOR_2,COLOR_3,COLOR_1,COLOR_2,COLOR_3,COLOR_1,COLOR_2,COLOR_3,COLOR_1,COLOR_2,COLOR_3,COLOR_1,COLOR_BROWN ,
    };

    for(int i=0;i<14;i++) {
        colors_data[9*i+0] = float(colors_boat[i].r)/t,colors_data[9*i+1] = float(colors_boat[i].g)/t,colors_data[9*i+2] = float(colors_boat[i].b)/t;
        colors_data[9*i+3] = float(colors_boat[i].r)/t,colors_data[9*i+4] = float(colors_boat[i].g)/t,colors_data[9*i+5] = float(colors_boat[i].b)/t;
        colors_data[9*i+6] = float(colors_boat[i].r)/t,colors_data[9*i+7] = float(colors_boat[i].g)/t,colors_data[9*i+8] = float(colors_boat[i].b)/t;
    };


    this->object1 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, colors_data, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data1, COLOR_RED, GL_FILL);
    }

void Enemy::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Enemy::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Enemy::tick() {
  float angle = ((this->rotation)*3.14)/180;

  this->position.z -= 0.005*cos(angle);
  this->position.x -= 0.005*sin(angle);
}

bounding_box_t Enemy::bounding_box(){
  float x = this->position.x, y = this->position.y , z = this->position.z;
  bounding_box_t bbox = { x, y, z};
  return bbox;
}
