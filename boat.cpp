#include "boat.h"
#include "main.h"
#include <time.h>
#include <unistd.h>


Boat::Boat(float x_cor, float y_cor) {
    this->position = glm::vec3(x_cor, y_cor, 2);
    this->rotation = 90;
    this->cam_view = 1;
    this->in_air = 0;
    this->speedy = 0;
    this->score = 0;
    this->health = 300;
    this->lives = 3;
    this->is_boost = 0;
    this->flag = 0;
    this->level = 1;
    this->points = 0;

    color_t colors_boat[] = {
        COLOR_1,COLOR_2,COLOR_3,COLOR_1,COLOR_2,COLOR_3,COLOR_1,COLOR_2,COLOR_3,COLOR_1,COLOR_2,COLOR_3,COLOR_1,COLOR_BROWN ,
    };

    float t = 255.0f;

    color_t flag_colors_boat[] = {
        COLOR_NAVY,COLOR_YELLOW,COLOR_GREEN,
    };

        GLfloat vertex_buffer_data[] = {

          0.75, 0.2, -0.36 ,
          0.75, 0.2, 0.36,
          0.75 + 0.3, 0.2, 0,


            -0.75, 0, -0.3,
            -0.75, 0, 0.3,
            -0.75, 0.2, 0.36,
            -0.75, 0.2, 0.36,
            -0.75, 0, -0.3,
            -0.75, 0.2, -0.36,

            -0.75, 0, -0.3,
            0.75, 0, -0.3,
            -0.75, 0.2, -0.36,
            -0.75, 0.2, -0.36,
            0.75, 0.2, -0.36,
            0.75, 0, -0.3,

            -0.75, 0, 0.3,
            0.75, 0, 0.3,
            -0.75, 0.2, 0.36,
            -0.75, 0.2, 0.36,
            0.75, 0.2, 0.36,
            0.75, 0, 0.3,

            0.75, 0, -0.3,
            1.05 , 0, 0,
            0.75, 0.2, -0.36,
            0.75, 0.2, -0.36,
            1.05 , 0.2, 0,
            1.05, 0, 0,

            0.75, 0, 0.3,
            1.05, 0, 0,
            0.75, 0.2, 0.36,
            0.75, 0.2, 0.36,
            1.05, 0.2, 0,
            1.05, 0, 0,


            -0.75, 0, -0.3,
            -0.75, 0, 0.3,
            0.75, 0, 0.3,

            -0.75, 0, -0.3,
            0.75, 0, -0.3,
            0.75, 0, 0.3,

            0.75, 0, -0.3,
            0.75, 0, 0.3,
            1.05, 0, 0,
        };


        GLfloat colors_data[126];

        for(int i=0;i<14;i++) {
            colors_data[9*i+0] = float(colors_boat[i].r)/t,colors_data[9*i+1] = float(colors_boat[i].g)/t,colors_data[9*i+2] = float(colors_boat[i].b)/t;
            colors_data[9*i+3] = float(colors_boat[i].r)/t,colors_data[9*i+4] = float(colors_boat[i].g)/t,colors_data[9*i+5] = float(colors_boat[i].b)/t;
            colors_data[9*i+6] = float(colors_boat[i].r)/t,colors_data[9*i+7] = float(colors_boat[i].g)/t,colors_data[9*i+8] = float(colors_boat[i].b)/t;
        };

        GLfloat vertex_data1[]    = {
            0.135, 0, -0.015,
            0.135, 0, 0.015,
            0.135, 1.0, -0.015,
            0.135, 1.0, -0.015,
            0.135, 1.0, 0.015,
            0.135, 0, 0.015,

            0.165, 0, -0.015,
            0.165, 0, 0.015,
            0.165, 1.0, -0.015,
            0.165, 1.0, -0.015,
            0.165, 1.0, 0.015,
            0.165, 0, 0.015,

            0.165, 0, -0.015,
            0.135, 0, -0.015,
            0.135, 1.0, -0.015,
            0.135, 1.0, -0.015,
            0.165, 1.0, -0.015,
            0.165, 0, -0.015,

            0.165, 0, 0.015,
            0.135, 0, 0.015,
            0.135, 1.0, 0.015,
            0.135, 1.0, 0.015,
            0.165, 1.0, 0.015,
            0.165, 0, 0.015,

            0.135, 1.0, -0.015,
            0.135, 1.0, 0.015,
            0.165, 1.0, 0.015,
            0.135, 1.0, -0.015,
            0.165, 1.0, 0.015,
            0.165, 1.0, -0.015,
        };

        GLfloat vertex_data2[] = {
            0.135, 0.2 , -0.015,
            0.135, 1.0, -0.015,
            -0.865, 0.2, -0.015,
        };


        GLfloat flag_color_data[] = {
                float(flag_colors_boat[0].r)/t,
                float(flag_colors_boat[0].g)/t,
                float(flag_colors_boat[0].b)/t,
                float(flag_colors_boat[1].r)/t,
                float(flag_colors_boat[1].g)/t,
                float(flag_colors_boat[1].b)/t,
                float(flag_colors_boat[2].r)/t,
                float(flag_colors_boat[2].g)/t,
                float(flag_colors_boat[2].b)/t,
        };

        this->object1 = create3DObject(GL_TRIANGLES, 42, vertex_buffer_data, colors_data, GL_FILL);
        this->object2 = create3DObject(GL_TRIANGLES, 30, vertex_data1,COLOR_GREEN, GL_FILL);
        this->object3 = create3DObject(GL_TRIANGLES, 3, vertex_data2,flag_color_data, GL_FILL);
    }

void Boat::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
}

void Boat::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Boat::tick() {
  if(this->in_air)
  {
    if(this->position.y <= -1)
      {
        this->position.y = -0.999;
        this->in_air = 0;
        this->speedy = 0;
      }
    this->position.y += this->speedy;
    this->speedy -= 0.01;

  }

}

void Boat::wind_tick(int is_wind, int dir) {
    if(is_wind)
    {
      if(dir){
      this->position.x += 0.002;
      this->position.z -= 0.002;
      this->rotation+= 0.1;
      }
      else
      {
        this->position.x -= 0.004;
        this->position.z -= 0.004;
        this->rotation-= 0.5;
      }
    }
}

int Boat::get_score() {
  int lvl = this->level;
  return 25*lvl*(lvl-1) + this->score;
}



bounding_box_t Boat::bounding_box(){
  float x = this->position.x, y = this->position.y , z = this->position.z;
  bounding_box_t bbox = { x, y, z};
  return bbox;
}
