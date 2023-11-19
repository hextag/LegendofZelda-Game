#include "monster.h"
#include "main.h"
#include <math.h>

Monster::Monster(float x_cor, float z_cor, int flag) {
    this->position = glm::vec3(x_cor, -1, z_cor);
    this->rotation = 0;

    static GLfloat vertex_buffer_data1[] = {
        0.25,0,0.432,
        0.5,0,0,
        0.375,1,0.22,

        0.25,0,-0.432,
        0.5,0,0,
        0.375,1,-0.22,

        -0.25,0,-0.432,
        0.25,0,-0.432,
        0,1,-0.432,

        -0.25,0,-0.432,
        -0.5,0,0,
        -0.375,1,-0.22,

        -0.5,0,0,
        -0.25,0,0.432,
        -0.375,1,0.22,

        -0.25,0,0.432,
        0.25,0,0.432,
        0,1,0.432,
    };

    static GLfloat vertex_buffer_data[] = {
        0.25*2,0*2,0.432*2,
        0.5*2,0*2,0*2,
        0.375*2,1*2,0.22*2,

        0.25*2,0*2,-0.432*2,
        0.5*2,0*2,0*2,
        0.375*2,1*2,-0.22*2,

        -0.25*2,0*2,-0.432*2,
        0.25*2,0*2,-0.432*2,
        0*2,1*2,-0.432*2,

        -0.25*2,0*2,-0.432*2,
        -0.5*2,0*2,0*2,
        -0.375*2,1*2,-0.22*2,

        -0.5*2,0*2,0*2,
        -0.25*2,0*2,0.432*2,
        -0.375*2,1*2,0.22*2,

        -0.25*2,0*2,0.432*2,
        0.25*2,0*2,0.432*2,
        0*2,1*2,0.432*2,
    };
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    color_t colors_boat1[] = {
        COLOR_8,COLOR_9,COLOR_10,COLOR_11,COLOR_12,COLOR_13,
    };
    color_t colors_boat[] = {
        COLOR_11,COLOR_BROWN,COLOR_11,COLOR_BROWN,COLOR_11,COLOR_BROWN,
    };

    GLfloat colors_data[126];
    float t = 255.0f;
    for(int i=0;i<6;i++) {
        colors_data[9*i+0] = float(colors_boat[i].r)/t,colors_data[9*i+1] = float(colors_boat[i].g)/t,colors_data[9*i+2] = float(colors_boat[i].b)/t;
        colors_data[9*i+3] = float(colors_boat[i].r)/t,colors_data[9*i+4] = float(colors_boat[i].g)/t,colors_data[9*i+5] = float(colors_boat[i].b)/t;
        colors_data[9*i+6] = float(colors_boat[i].r)/t,colors_data[9*i+7] = float(colors_boat[i].g)/t,colors_data[9*i+8] = float(colors_boat[i].b)/t;
    };

    GLfloat colors_data1[126];
    for(int i=0;i<6;i++) {
        colors_data1[9*i+0] = float(colors_boat1[i].r)/t,colors_data1[9*i+1] = float(colors_boat1[i].g)/t,colors_data1[9*i+2] = float(colors_boat1[i].b)/t;
        colors_data1[9*i+3] = float(colors_boat1[i].r)/t,colors_data1[9*i+4] = float(colors_boat1[i].g)/t,colors_data1[9*i+5] = float(colors_boat1[i].b)/t;
        colors_data1[9*i+6] = float(colors_boat1[i].r)/t,colors_data1[9*i+7] = float(colors_boat1[i].g)/t,colors_data1[9*i+8] = float(colors_boat1[i].b)/t;
    };
    if(!flag)
    this->object1 = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data1, colors_data, GL_FILL);
    else
    this->object1 = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data, colors_data1, GL_FILL);
}

void Monster::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
}

void Monster::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Monster::tick() {
  this->rotation += 2;
}

bounding_box_t Monster::bounding_box(){
  float x = this->position.x, y = this->position.y , z = this->position.z;
  bounding_box_t bbox = { x, y, z};
  return bbox;
}
