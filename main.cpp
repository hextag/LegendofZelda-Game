#include "main.h"
#include "timer.h"
#include "ball.h"
#include "ocean.h"
#include "boat.h"
#include "rock.h"
#include "enemy.h"
#include "barrel.h"
#include <math.h>
#include "gift.h"
#include "cannon.h"
#include "monster.h"
#include "island.h"
#include "boost_object.h"
#include <cstring>
#include <string>
#include <sstream>


using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Boat boat;
Ocean ocean;
Rock rocks[1000];
Rock temp;
Enemy enemy[100];
Barrel barrels[1000];
Gift barrel_gifts[1000];
Gift gifts[1000];
Boost boosts[100];
int i, is_wind = 0, wind_counter = 0,dir = 0, boost_counter = 0,boat_cannon = 0;
Cannon cannons[100000];
Monster monsters[1000],boss;
int cannon_counter = 0, spawn_counter = 0, boss_monster = 0,boss_cannon = 0;
int  mons_killed = 0;
Gift gift_kill[1000];
int count_gift_kill = 0;
float rad = 1;
float ang = 0;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
Island island;
//int max = 1000, min = -1000;
int num = 50;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);


    // Eye - Location of camera. Don't change unless you are sure!!

   if(boat.cam_view == 1)
    {
      glm::vec3 eye (0, 0, 3);
      glm::vec3 target (0, 0, 0);
      glm::vec3 up (0, 1, 0);
      Matrices.view = glm::lookAt( eye, target, up );
    }

    else if(boat.cam_view == 2)
    {
        float angle = ((boat.rotation-90)*3.14)/180;

        glm::vec3 eye ( boat.position.x+2*sin(angle), boat.position.y+0.5 , boat.position.z+2*cos(angle));
        glm::vec3 target ( boat.position.x, boat.position.y+0.5, boat.position.z);
        glm::vec3 up (0, 1, 0);
        Matrices.view = glm::lookAt( eye, target, up );
    }

    else if(boat.cam_view == 3)
    {
      float angle = ((boat.rotation-90)*3.14)/180;

      glm::vec3 eye ( boat.position.x, boat.position.y+0.5 , boat.position.z);
      glm::vec3 target ( boat.position.x-2*sin(angle), boat.position.y+0.5, boat.position.z-2*cos(angle));
      glm::vec3 up (0, 1, 0);
      Matrices.view = glm::lookAt( eye, target, up );
    }

    else if(boat.cam_view == 4)
    {
      glm::vec3 eye ( boat.position.x, 14 , boat.position.z);
      glm::vec3 target ( boat.position.x, boat.position.y, boat.position.z);
      glm::vec3 up (0, 0, 1);
      Matrices.view = glm::lookAt( eye, target, up );
    }

    else if(boat.cam_view == 5)
    {
        glm::vec3 eye ( 2, 50 ,3);
        glm::vec3 target ( 2, 0, 3);
        glm::vec3 up (0, 0, 1);
        Matrices.view = glm::lookAt( eye, target, up );
    }

    if(boat.cam_view == 6)
     {
       glm::vec3 eye (50, 20, 0);
       glm::vec3 target (0, 0, 0);
       glm::vec3 up (-1, 1, 0);
       Matrices.view = glm::lookAt( eye, target, up );
     }

     if(boat.cam_view == 7)
      {
        float angl = (ang*3.14)/180;
        glm::vec3 eye (rad*cos(angl), 20, rad*sin(angl));
        glm::vec3 target (boat.position.x, boat.position.y, boat.position.z);
        glm::vec3 up (cos(angl), 1, sin(angl));
        Matrices.view = glm::lookAt( eye, target, up );
      }


    // Compute Camera matrix (view)
  //  Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model
    // Scene render
//    ball1.draw(VP);



    ocean.draw(VP);
    for(i=0;i<num;i++)
      rocks[i].draw(VP);

    for(i=0;i<num;i++)
      barrels[i].draw(VP);

    for(i=0;i<num;i++)
      gifts[i].draw(VP);

    for(i=0;i<num;i++)
      barrel_gifts[i].draw(VP);

    for(i=0;i<num;i++)
        enemy[i].draw(VP);

    for(i=0;i<num;i++)
      boosts[i].draw(VP);

    for(i=0;i<cannon_counter;i++)
        cannons[i].draw(VP);

    if(spawn_counter%2 == 0)
      boat.draw(VP);

      for(i=0;i<num;i++)
           monsters[i].draw(VP);

      if(boss_monster == 1)
          boss.draw(VP);

      for(i=0;i<count_gift_kill;i++)
        gift_kill[i].draw(VP);

  //    island.draw(VP);

}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int jump = glfwGetKey(window, GLFW_KEY_SPACE);
    int cam1 = glfwGetKey(window, GLFW_KEY_1);
    int cam2 = glfwGetKey(window, GLFW_KEY_2);
    int cam3 = glfwGetKey(window, GLFW_KEY_3);
    int cam4 = glfwGetKey(window, GLFW_KEY_4);
    int cam5 = glfwGetKey(window, GLFW_KEY_5);
    int cam6 = glfwGetKey(window, GLFW_KEY_6);
    int cam7 = glfwGetKey(window, GLFW_KEY_7);

    int ang_p = glfwGetKey(window, GLFW_KEY_A);
    int ang_n = glfwGetKey(window, GLFW_KEY_D);
    int rad_p = glfwGetKey(window, GLFW_KEY_W);
    int rad_n = glfwGetKey(window, GLFW_KEY_S);

    int boost = glfwGetKey(window, GLFW_KEY_B);
    int cannon = glfwGetKey(window, GLFW_KEY_C);

    if(ang_p)
      ang+=1.0;

    if(ang_n)
      ang-=1.0;

    if(rad_p)
      rad+=1;

    if(rad_n)
    {
      //if(rad>0)
      rad-=1;
    }
    if(boost)
      {
          boat.is_boost = 1;
      }

    if(cannon)
      {
        float angle = ((boat.rotation-90)*3.14)/180;
        if(boat_cannon>10)
          cannons[cannon_counter++] = Cannon(boat.position.x-sin(angle), boat.position.z-cos(angle), boat.rotation-90);
          boat_cannon = 1;
          cannon = 0;
      }



    if (up) {
        float angle = ((boat.rotation-90)*3.14)/180;
        float rad;
        if(boat.is_boost)
          rad = 0.15;
        else
          rad = 0.05;

        boat.position.z -= rad*cos(angle);
        boat.position.x -= rad*sin(angle);
    }

    if (right) {
        boat.rotation -= 0.5;
    }

    if (left) {
        boat.rotation += 0.5;
    }

    if (down) {
        float angle = ((boat.rotation-90)*3.14)/180;
        boat.position.z += 0.05*cos(angle);
        boat.position.x += 0.05*sin(angle);
    }
    if(jump)
      {
        boat.speedy = 0.05;
        boat.in_air = 1;
      }

    if(cam1){
      boat.cam_view = 1;
    }

    if(cam2){
      boat.cam_view = 2;
    }

    if(cam3){
      boat.cam_view = 3;
    }

    if(cam4){
      boat.cam_view = 4;
    }

    if(cam5){
      boat.cam_view = 5;
    }

    if(cam6){
      boat.cam_view = 6;
    }

    if(cam7){
      boat.cam_view = 7;
    }


}

void tick_elements() {
//    ball1.tick();
  //  camera_rotation_angle += 1;
  if(boat_cannon!=0)
    boat_cannon++;

  if(boat.score >= boat.level*50)
  {
    boat.level += 1;
    boat.score = 0;
  }

  if(boat.health == 0 || boat.lives == 0)
    {
      printf("GAME OVER\n Score : %d\nHealth : %d\nLives : %d\n",boat.score,boat.health,boat.lives);
      exit(0);
    }

for(i=0;i<num;i++)
  enemy[i].tick();

  boat.tick();

  for(i=0;i<num;i++)
  {
    if(detect_collision_rock(boat.bounding_box(), rocks[i].bounding_box()))
    {
      float angle = ((boat.rotation-90)*3.14)/180;
      boat.position.z += 2*cos(angle);
      boat.position.x += 2*sin(angle);
      boat.health -=10;
    }
  }

  for(i=0;i<num;i++)
  {
    if(detect_collision_barrel(boat.bounding_box(), barrels[i].bounding_box()))
    {
      if(barrel_gifts[i].position.y<2)
        boat.score += 20;
      barrel_gifts[i].position.y = 100;

    }
  }

  for(i=0;i<num;i++)
  {
    if(detect_collision_boat(boat.bounding_box(), enemy[i].bounding_box()))
    {
      float angle = ((boat.rotation-90)*3.14)/180;
      boat.position.z += 2*cos(angle);
      boat.position.x += 2*sin(angle);
      boat.health -=30;
    }
  }

  for(i=0;i<num;i++)
  {
    if(detect_collision_gift(boat.bounding_box(), gifts[i].bounding_box()))
    {
      boat.health +=30;
      gifts[i].position.z = rand()%1000;
    }
  }

  for(i=0;i<count_gift_kill;i++)
  {
    if(detect_collision_gift(boat.bounding_box(), gift_kill[i].bounding_box()))
    {
      boat.is_boost = 1;
      gift_kill[i].position.z = rand()%1000;
    }
  }

  for(i=0;i<num;i++)
  {
    if(detect_collision_boost(boat.bounding_box(), boosts[i].bounding_box()))
    {
      boat.is_boost = 1;
      boosts[i].position.z = rand()%1000;
    }
  }


  for(i=0;i<num;i++)
  {
    if(detect_collision_monster(boat.bounding_box(), monsters[i].bounding_box()))
    {
      boat.lives -= 1;
      monsters[i].position.z = rand()%1000;
      spawn_counter = 1;
      boat.position.x = 0;
      boat.position.z = 2;
      boat.rotation = 90;
    }
  }

  if(spawn_counter !=0 && spawn_counter<60)
    spawn_counter++;

  if(spawn_counter == 60)
    {
      spawn_counter = 0;
      boat.position.y = -0.999;
    }

    if(mons_killed > 3 && boss_monster == 0)
      {
        boss = Monster(boat.position.x + 1, boat.position.z - 3, 1);
        boss_monster = 1;
      }

  int j;
  for(i=0;i<cannon_counter;i++)
  {
    for(j=0;j<num;j++)
    {
      if(detect_collision_cannon(cannons[i].bounding_box(), monsters[j].bounding_box()))
      {
        gift_kill[count_gift_kill++] = Gift(monsters[j].position.x,monsters[j].position.z, COLOR_12, 0);

        boat.score+= 100;
        cannons[i].position.z = rand()%1000;
        cannons[i].position.y = 1000;
        monsters[j].position.z = rand()%1000;
        mons_killed += 1;
      }
    }
  }
    if(boss_monster == 1)
    {
      for(i=0;i<cannon_counter;i++)
      {
        if(detect_collision_boss(cannons[i].bounding_box(), boss.bounding_box()))
        {
          boss_cannon += 1;
          cannons[i].position.z = rand()%1000;
          cannons[i].position.y = 1000;
            if(boss_cannon == 3)
              {
                gift_kill[count_gift_kill++] = Gift(boss.position.x,boss.position.z, COLOR_11, 1);
                boat.score+= 300;
                boss.position.z = rand()%1000;
                boss.position.y = 1000;
                boss_monster = 2;

              }
        }
      }
    }
  for(i=0;i<cannon_counter;i++)
    cannons[i].tick();

  if(rand()%100==37 && is_wind==0)
      {
        is_wind = 1;
        dir = 1-dir;
      }
    boss.tick();

  if(is_wind)
    wind_counter++;

  if(wind_counter == 60)
    {
      wind_counter = 0;
      is_wind = 0;
    }
    boat.wind_tick(is_wind,dir);

  if(boost_counter<300 && boat.is_boost == 1)
    boost_counter++;

  if(boost_counter == 180)
  {
      boost_counter = 0;
      boat.is_boost = 0;
  }

    for(i=0;i<num;i++)
      rocks[i].tick(is_wind,dir);
//  printf("Boat => %f, %f , Rock=> %f, %f\n",boat.position.x,boat.position.z,temp.position.x,temp.position.z);
  for(i=0;i<num;i++)
    monsters[i].tick();
 }

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1 = Ball(0, 0, COLOR_RED);
    ocean = Ocean(0, -3);
    boat = Boat(0, -0.999);
    island = Island(0,-2.9);

    for(i=0;i<num;i++)
    {
      int x,y,z;
      int max = 100, min = -100;

      x = (rand() % (max + 1 - min)) + min;
      z = (rand() % (max + 1 - min)) + min;
      float angle = (rand() % (max + 1 - min)) + min;

      enemy[i] = Enemy(x,-1,z,angle);
    }

    for(i=0;i<num;i++)
    {
      int x,z;
      int max = 100, min = -100;

      x = (rand() % (max + 1 - min)) + min;
      z = (rand() % (max + 1 - min)) + min;

      rocks[i] = Rock(x,z);
    }

    for(i=0;i<num;i++)
    {
      int x,z;
      int max = 100, min = -100;

      x = (rand() % (max + 1 - min)) + min;
      z = (rand() % (max + 1 - min)) + min;

      barrels[i] = Barrel(x, z);
      barrel_gifts[i] = Gift(x, z, COLOR_PINK, 0.3);
    }

    for(i=0;i<num;i++)
    {
      int x,z;
      int max = 100, min = -100;
      x = (rand() % (max + 1 - min)) + min;
      z = (rand() % (max + 1 - min)) + min;

      gifts[i] = Gift(x, z, COLOR_6, 0.06);
    }

    for(i=0;i<num;i++)
    {
      int x,z;
      int max = 100, min = -100;
      x = (rand() % (max + 1 - min)) + min;
      z = (rand() % (max + 1 - min)) + min;

      boosts[i] = Boost(x, z);
    }

    for(i=0;i<num;i++)
    {
      int x,z;
      int max = 100, min = -100;
      x = (rand() % (max + 1 - min)) + min;
      z = (rand() % (max + 1 - min)) + min;

      monsters[i] = Monster(x, z, 0);
    }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1000;
    int height = 1200;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {

            string Result;
            stringstream convert;
            //cout << "nonedit score:" << score << endl;
            convert << boat.get_score();
            Result = convert.str();

            const char *one = "Score: ";
            const char *two = Result.c_str();
            const char *three = "   Health: ";
            const char *level = "   Level: ";
            string Result1;
            stringstream convert1;
            convert1 << boat.health;
            Result1 = convert1.str();

            string Result10;
            stringstream convert10;
            convert10 << boat.level;
            Result10 = convert10.str();
            const char *ten = Result10.c_str();

            const char *four = Result1.c_str();
            const char *five = "   Lives: ";
            string Result2;
            stringstream convert2;
            convert2 << boat.lives;
            Result2 = convert2.str();
            const char *six = Result2.c_str();
            string total( string(one) + two + string(three) + four + string(five) + six + string(level) + ten);
            glfwSetWindowTitle(window, total.c_str());

            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

// bool detect_collision(bounding_box_t a, bounding_box_t b) {
//     return (abs(a.x - b.x) * 2 < a.width+b.width) &&
//            (abs(a.y - b.y) * 2 < a.length+b.length) &&
//            (abs(a.z - b.z) * 2 < a.height+b.height);
// }

bool detect_collision_rock(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < 1) &&
           (abs(a.z - b.z) * 2 < 1);
}

bool detect_collision_barrel(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < 1) &&
          (a.y - b.y > 0.1 ) &&
           (abs(a.z - b.z) * 2 < 1);
}

bool detect_collision_boat(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < 2) &&
           (abs(a.z - b.z) * 2 < 2);
}

bool detect_collision_gift(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < 1) &&
           (abs(a.z - b.z) * 2 < 1);
}

bool detect_collision_boost(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < 0.6) &&
           (abs(a.z - b.z) * 2 < 0.6);
}

bool detect_collision_monster(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < 1.5) &&
           (abs(a.z - b.z) * 2 < 1.5);
}

bool detect_collision_cannon(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < 1.5) &&
           (abs(a.z - b.z) * 2 < 1.5);
}

bool detect_collision_boss(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < 1.5) &&
           (abs(a.z - b.z) * 2 < 1.5);
}


void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
//    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    Matrices.projection = glm::infinitePerspective(glm::radians(90.0f), 2.0f,0.1f);
}
