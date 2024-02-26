#include "stdio.h"
#include "stdlib.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfxPrimitives.h"
#include "time.h"

#include "formulas.h"
#include "wall.h"
#include "robot.h"

#include "unistd.h"

int done = 0;


int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Renderer *renderer;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        return 1;
    }

    window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, 0);

    struct Robot robot;
    struct Wall_collection *head = NULL;
    int front_centre_sensor, left_sensor, right_sensor=0;
    clock_t start_time, end_time;
    int msec;
    int crashed = 0;

    int maze_number =3;

    // SETUP MAZE
    // You can create your own maze here. line of code is adding a wall.
    // You describe position of top left corner of wall (x, y), then width and height going down/to right
    // Relative positions are used (OVERALL_WINDOW_WIDTH and OVERALL_WINDOW_HEIGHT)
    // But you can use absolute positions. 10 is used as the width, but you can change this.

    //Basic narrower
    if(maze_number == 1) {
        insertAndSetFirstWall(&head, 1,  OVERALL_WINDOW_WIDTH/2+55, OVERALL_WINDOW_HEIGHT/2+100, 10, OVERALL_WINDOW_HEIGHT/2-100);
        insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/2-50, OVERALL_WINDOW_HEIGHT/2+100, 10, OVERALL_WINDOW_HEIGHT/2-100);
        insertAndSetFirstWall(&head, 3,  OVERALL_WINDOW_WIDTH/2-200, OVERALL_WINDOW_HEIGHT/2+100, 150, 10);
        insertAndSetFirstWall(&head, 4,  OVERALL_WINDOW_WIDTH/2-120, OVERALL_WINDOW_HEIGHT/2-130, 10, 235);
        insertAndSetFirstWall(&head, 5,  OVERALL_WINDOW_WIDTH/2-290, OVERALL_WINDOW_HEIGHT/2+10, 10, 250);
        insertAndSetFirstWall(&head, 6,  OVERALL_WINDOW_WIDTH/2-200, OVERALL_WINDOW_HEIGHT/2+100, 10, 160);
        insertAndSetFirstWall(&head, 7,  OVERALL_WINDOW_WIDTH/2-290, OVERALL_WINDOW_HEIGHT/2, 100, 10);
        insertAndSetFirstWall(&head, 8,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-205, 10, 210);
        insertAndSetFirstWall(&head, 9,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-215, 525, 10);
        insertAndSetFirstWall(&head, 10,  OVERALL_WINDOW_WIDTH/2+265, OVERALL_WINDOW_HEIGHT/2-205, 10, 310);
        insertAndSetFirstWall(&head, 11,  OVERALL_WINDOW_WIDTH/2+65, OVERALL_WINDOW_HEIGHT/2+100, 210, 10);
        insertAndSetFirstWall(&head, 12,  OVERALL_WINDOW_WIDTH/2+20, OVERALL_WINDOW_HEIGHT/2-130, 10, 165);
        insertAndSetFirstWall(&head, 13,  OVERALL_WINDOW_WIDTH/2+165, OVERALL_WINDOW_HEIGHT/2-130, 10, 165);
        insertAndSetFirstWall(&head, 14,  OVERALL_WINDOW_WIDTH/2+20, OVERALL_WINDOW_HEIGHT/2-130, 155, 10);
        insertAndSetFirstWall(&head, 15,  OVERALL_WINDOW_WIDTH/2+20, OVERALL_WINDOW_HEIGHT/2+35, 155, 10);
        setup_robot(&robot, OVERALL_WINDOW_WIDTH/2-245, OVERALL_WINDOW_HEIGHT/2+200);
    }
    //Basic
    else if (maze_number == 0) {
    insertAndSetFirstWall(&head, 1,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2, 10, OVERALL_WINDOW_HEIGHT/2);
    insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/2-100, OVERALL_WINDOW_HEIGHT/2+100, 10, OVERALL_WINDOW_HEIGHT/2-100);
    insertAndSetFirstWall(&head, 3,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2+100, 150, 10);
    insertAndSetFirstWall(&head, 4,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2, 150, 10);
    insertAndSetFirstWall(&head, 5,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-200, 10, 300);
    insertAndSetFirstWall(&head, 6,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2-100, 10, 100);
    insertAndSetFirstWall(&head, 7,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-200, 450, 10);
    insertAndSetFirstWall(&head, 8,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2-100, 250, 10);
    insertAndSetFirstWall(&head, 9,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2-200, 10, 300);
    insertAndSetFirstWall(&head, 10,  OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT/2-100, 10, 300);
    insertAndSetFirstWall(&head, 11,  OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT/2+200, OVERALL_WINDOW_WIDTH/2-100, 10);
    insertAndSetFirstWall(&head, 12,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2+100, OVERALL_WINDOW_WIDTH/2-100, 10);
    setup_robot(&robot, OVERALL_WINDOW_WIDTH/2-50, OVERALL_WINDOW_HEIGHT-50);
    }

    //Complex 1
    else if(maze_number == 2) {
    insertAndSetFirstWall(&head, 1,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2+50, 10, OVERALL_WINDOW_HEIGHT/2);
    insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/2-50, OVERALL_WINDOW_HEIGHT/2+100, 10, OVERALL_WINDOW_HEIGHT/2-100);
    insertAndSetFirstWall(&head, 3,  OVERALL_WINDOW_WIDTH/2-200, OVERALL_WINDOW_HEIGHT/2+100, 150, 10);
    insertAndSetFirstWall(&head, 4,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2+50, 150, 10);
    insertAndSetFirstWall(&head, 5,  OVERALL_WINDOW_WIDTH/2-200, OVERALL_WINDOW_HEIGHT/2-150, 10, 250);
    insertAndSetFirstWall(&head, 6,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2-100, 10, 50);
    insertAndSetFirstWall(&head, 14,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2-50, 100, 10);
    insertAndSetFirstWall(&head, 15,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2, 170, 10);
    insertAndSetFirstWall(&head, 13,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2, 10, 50);
    insertAndSetFirstWall(&head, 7,  OVERALL_WINDOW_WIDTH/2-200, OVERALL_WINDOW_HEIGHT/2-150, 350, 10);
    insertAndSetFirstWall(&head, 8,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2-100, 100, 10);
    insertAndSetFirstWall(&head, 16,  OVERALL_WINDOW_WIDTH/2+10, OVERALL_WINDOW_HEIGHT/2-100, 100, 10);
    insertAndSetFirstWall(&head, 17,  OVERALL_WINDOW_WIDTH/2-50, OVERALL_WINDOW_HEIGHT/2-100, 10, 60);
    insertAndSetFirstWall(&head, 18,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2-100, 10, 60);
    insertAndSetFirstWall(&head, 19,  OVERALL_WINDOW_WIDTH/2+10, OVERALL_WINDOW_HEIGHT/2-50, 95, 10);
    insertAndSetFirstWall(&head, 20,  OVERALL_WINDOW_WIDTH/2+15, OVERALL_WINDOW_HEIGHT/2, 5, 150);
    insertAndSetFirstWall(&head, 21,  OVERALL_WINDOW_WIDTH/2+50, OVERALL_WINDOW_HEIGHT/2, 10, 50);
    insertAndSetFirstWall(&head, 22,  OVERALL_WINDOW_WIDTH/2+15, OVERALL_WINDOW_HEIGHT/2+150, 90, 10);
    insertAndSetFirstWall(&head, 22,  OVERALL_WINDOW_WIDTH/2+105, OVERALL_WINDOW_HEIGHT/2+150, 10, 50);
    insertAndSetFirstWall(&head, 9,  OVERALL_WINDOW_WIDTH/2+150, OVERALL_WINDOW_HEIGHT/2-150, 10, 300);
    insertAndSetFirstWall(&head, 10,  OVERALL_WINDOW_WIDTH/2+105, OVERALL_WINDOW_HEIGHT/2-100, 5, 200);
    insertAndSetFirstWall(&head, 11,  OVERALL_WINDOW_WIDTH/2+105, OVERALL_WINDOW_HEIGHT/2+200, OVERALL_WINDOW_WIDTH/2-100, 10);
    insertAndSetFirstWall(&head, 12,  OVERALL_WINDOW_WIDTH/2+150, OVERALL_WINDOW_HEIGHT/2+150, OVERALL_WINDOW_WIDTH/2-100, 10);
    setup_robot(&robot, OVERALL_WINDOW_WIDTH/2-25, OVERALL_WINDOW_HEIGHT-50);
    }
    else if(maze_number == 3) {
        insertAndSetFirstWall(&head, 1,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2+120, 10, OVERALL_WINDOW_HEIGHT/4);
        insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/2-100, OVERALL_WINDOW_HEIGHT/2+120, 10, OVERALL_WINDOW_HEIGHT/4);
        for (float i = 0; i<8; i+=0.1){
            insertAndSetFirstWall(&head, i,  OVERALL_WINDOW_WIDTH/2+5*i*cos(i*PI/180), OVERALL_WINDOW_HEIGHT/2+120-50*i*sin(i*PI/180), 10, 10);
            insertAndSetFirstWall(&head, i,  OVERALL_WINDOW_WIDTH/2-100+5*i*cos(i*PI/180), OVERALL_WINDOW_HEIGHT/2+120-50*i*sin(i*PI/180), 10, 10);
        }
        float y = OVERALL_WINDOW_HEIGHT/2+120-50*7.9*sin(7.9*PI/180);
        float x = OVERALL_WINDOW_WIDTH/2+5*7.9*cos(7.9*PI/180);
        for (float i = 0; i<8; i+=0.1){
            insertAndSetFirstWall(&head, i,  x-5*i*cos(i*PI/180), y-50*i*sin(i*PI/180), 10, 10);
            insertAndSetFirstWall(&head, i,  x-5*i*cos(i*PI/180)-100, y-50*i*sin(i*PI/180), 10, 10);
        }
        float y2 = y-50*7.9*sin(7.9*PI/180);
        float x2 = x-5*7.9*cos(7.9*PI/180);
        for (float i = 0; i<8; i+=0.1){
            insertAndSetFirstWall(&head, i,  x2+5*i*cos(i*PI/180), y2-50*i*sin(i*PI/180), 10, 10);
            insertAndSetFirstWall(&head, i,  x2+5*i*cos(i*PI/180)-100, y2-50*i*sin(i*PI/180), 10, 10);
        }
        float y3 = y2-50*7.9*sin(7.9*PI/180);
        float x3 = x2+5*7.9*cos(7.9*PI/180);
        for (float i = 0; i < 8; i+=.1){
            insertAndSetFirstWall(&head, i,  x3-5*i*cos(i*PI/180), y3-50*i*sin(i*PI/180), 10, 10);
            insertAndSetFirstWall(&head, i,  x3-5*i*cos(i*PI/180)-100, y3-50*i*sin(i*PI/180), 10, 10);
        }
        float y4 = y3-50*7.9*sin(7.9*PI/180);
        float x4 = x3-5*7.9*cos(7.9*PI/180);
        for (float i = 0; i<8; i+=0.1){
            insertAndSetFirstWall(&head, i,  x4+5*i*cos(i*PI/180), y4-50*i*sin(i*PI/180), 10, 10);
            insertAndSetFirstWall(&head, i,  x4+5*i*cos(i*PI/180)-100, y4-50*i*sin(i*PI/180), 10, 10);
        }
        float y5 = y4-50*7.9*sin(7.9*PI/180);
        float x5 = x4+5*7.9*cos(7.9*PI/180);
        for (float i = 0; i < 8; i+=.1){
            insertAndSetFirstWall(&head, i,  x5-5*i*cos(i*PI/180), y5-50*i*sin(i*PI/180), 10, 10);
            insertAndSetFirstWall(&head, i,  x5-5*i*cos(i*PI/180)-100, y5-50*i*sin(i*PI/180), 10, 10);
        }
        float y6 = y5-50*7.9*sin(7.9*PI/180);
        float x6 = x5-5*7.9*cos(7.9*PI/180);
        for (float i = 0; i<6; i+=0.1){
            insertAndSetFirstWall(&head, i,  x6+5*i*cos(i*PI/180), y6-50*i*sin(i*PI/180), 10, 10);
            insertAndSetFirstWall(&head, i,  x6+5*i*cos(i*PI/180)-100, y6-50*i*sin(i*PI/180), 10, 10);
        }
        setup_robot(&robot, OVERALL_WINDOW_WIDTH/2-40, OVERALL_WINDOW_HEIGHT-40);
    }
    else if (maze_number == 4){
        insertAndSetFirstWall(&head, 1,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2, 10, OVERALL_WINDOW_HEIGHT/2);
        insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/2-100, OVERALL_WINDOW_HEIGHT/2, 10, OVERALL_WINDOW_HEIGHT/2);

    for (int i = 0; i < 100; i++){
        insertAndSetFirstWall(&head, i,
                              (i * 2)+OVERALL_WINDOW_WIDTH/2,
                              OVERALL_WINDOW_HEIGHT/2 - 130*sin(1.8*i * PI/180),
                              10, 10);
        insertAndSetFirstWall(&head, i,
                              (i * 4)+OVERALL_WINDOW_WIDTH/2-100,
                              OVERALL_WINDOW_HEIGHT/2 - 230*sin(1.8*i * PI/180),
                              10, 10);
    }
    double x2 = (99 * 2)+OVERALL_WINDOW_WIDTH/2;
    double x22 = (99 * 4)+OVERALL_WINDOW_WIDTH/2-100;
    double y2 = OVERALL_WINDOW_HEIGHT/2 - 130*sin(1.8*99 * PI/180);
    double y22 = OVERALL_WINDOW_HEIGHT/2 - 230*sin(1.8*99 * PI/180);

    insertAndSetFirstWall(&head, 1,  x2, y2, 10, OVERALL_WINDOW_HEIGHT/2);
    insertAndSetFirstWall(&head, 2,  x22, y22, 10, OVERALL_WINDOW_HEIGHT/2);
    setup_robot(&robot, OVERALL_WINDOW_WIDTH/2-50, OVERALL_WINDOW_HEIGHT-50);
    }
    else if(maze_number == 5) {
        insertAndSetFirstWall(&head, 1,  OVERALL_WINDOW_WIDTH/2-200, OVERALL_WINDOW_HEIGHT/2+120, 10, OVERALL_WINDOW_HEIGHT/4);
        insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/2-300, OVERALL_WINDOW_HEIGHT/2+120, 10, OVERALL_WINDOW_HEIGHT/4);
        for (float i = 0; i<8; i+=0.1){
            insertAndSetFirstWall(&head, i,  OVERALL_WINDOW_WIDTH/2+5*i*cos(i*PI/180)-200, OVERALL_WINDOW_HEIGHT/2+120-50*i*sin(i*PI/180), 10, 10);
            insertAndSetFirstWall(&head, i,  OVERALL_WINDOW_WIDTH/2-300+5*i*cos(i*PI/180), OVERALL_WINDOW_HEIGHT/2+120-50*i*sin(i*PI/180), 10, 10);
        }
        float y = OVERALL_WINDOW_HEIGHT/2+120-50*7.9*sin(7.9*PI/180);
        float x = OVERALL_WINDOW_WIDTH/2+5*7.9*cos(7.9*PI/180)-200;
        for (float i = 0; i<8; i+=0.1){
            insertAndSetFirstWall(&head, i,  x-5*i*cos(i*PI/180), y-50*i*sin(i*PI/180), 10, 10);
            insertAndSetFirstWall(&head, i,  x-5*i*cos(i*PI/180)-100, y-50*i*sin(i*PI/180), 10, 10);
        }
        for (int i = 0; i < 50; i++){
        insertAndSetFirstWall(&head, i,
                              (i * 2)+OVERALL_WINDOW_WIDTH/2-200,
                              OVERALL_WINDOW_HEIGHT/2 - 130*sin(1.8*i * PI/180),
                              10, 10);
        insertAndSetFirstWall(&head, i,
                              (i * 4)+OVERALL_WINDOW_WIDTH/2-300,
                              OVERALL_WINDOW_HEIGHT/2 - 230*sin(1.8*i * PI/180),
                              10, 10);
    }
    double x2 = (49 * 2)+OVERALL_WINDOW_WIDTH/2-200;
    double x22 = (49 * 4)+OVERALL_WINDOW_WIDTH/2-300;
    double y2 = OVERALL_WINDOW_HEIGHT/2 - 130*sin(1.8*49 * PI/180);
    double y22 = OVERALL_WINDOW_HEIGHT/2 - 230*sin(1.8*49 * PI/180);
    insertAndSetFirstWall(&head, 1,  x2, y2, 100, 10);
    insertAndSetFirstWall(&head, 2,  x22, y22, 100, 10);

    for (float i = 0; i<6; i+=0.1){
            insertAndSetFirstWall(&head, i,  x2+100+20*i*cos(i*PI/180), y2+150*i*sin(i*PI/180), 10, 10);
            insertAndSetFirstWall(&head, i,  x22+150+25*i*cos(i*PI/180)-70, y22+150*i*sin(i*PI/180), 10, 10);
        }

    float x3 = x2+100+20*5.9*cos(5.9*PI/180);
    float x32 = x22+150+25*5.9*cos(5.9*PI/180)-70;
    double y3 = y2+150*5.9*sin(5.9*PI/180);
    double y32 = y22+150*5.9*sin(5.9*PI/180);

    insertAndSetFirstWall(&head, 1,  x3, y3, 50, 10);
    insertAndSetFirstWall(&head, 2,  x32, y32, 100, 10);

    insertAndSetFirstWall(&head, 1,  x3+50, y3, 10, 300);
    insertAndSetFirstWall(&head, 2,  x32+100, y32, 10, 400);
        setup_robot(&robot, OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT-40);
    }
    else if(maze_number == 6) {
        insertAndSetFirstWall(&head, 1,  OVERALL_WINDOW_WIDTH/2-100, OVERALL_WINDOW_HEIGHT/2, 10, OVERALL_WINDOW_HEIGHT/4+120);
        insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/2-200, OVERALL_WINDOW_HEIGHT/2+120, 10, OVERALL_WINDOW_HEIGHT/4);

        insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/2-280, OVERALL_WINDOW_HEIGHT/2+120, 80, 10);
        insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/2-280, OVERALL_WINDOW_HEIGHT/2-100, 10, 220);

        insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/2-225, OVERALL_WINDOW_HEIGHT/2-25, 80, 10);

        insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/2-270, OVERALL_WINDOW_HEIGHT/2-100, 400, 10);
        insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/2-100, OVERALL_WINDOW_HEIGHT/2, 150, 10);

        for (int i = 0; i < 100; i++){
        insertAndSetFirstWall(&head, i,
                               OVERALL_WINDOW_WIDTH/2+130 + 150*sin(1.8*i * PI/180),
                              (i * 3)+OVERALL_WINDOW_HEIGHT/2-100,
                              10, 10);
        insertAndSetFirstWall(&head, i,
                              OVERALL_WINDOW_WIDTH/2 + 50 + 150*sin(1.8*i * PI/180),
                              (i * 1.5)+OVERALL_WINDOW_HEIGHT/2,
                              10, 10);
    }
    float x = OVERALL_WINDOW_WIDTH/2+130 + 150*sin(1.8*99 * PI/180);
    float x2 = OVERALL_WINDOW_WIDTH/2 + 50 + 150*sin(1.8*99 * PI/180);
    float y = (99 * 3)+OVERALL_WINDOW_HEIGHT/2-100;
    float y2 = (99 * 1.5)+OVERALL_WINDOW_HEIGHT/2;

    insertAndSetFirstWall(&head, 1,  x, y, 10, 50);
    insertAndSetFirstWall(&head, 2,  x2, y2, 10,150);

        setup_robot(&robot, OVERALL_WINDOW_WIDTH/2-155, OVERALL_WINDOW_HEIGHT-40);
    }
    updateAllWalls(head, renderer);

    SDL_Event event;
    while(!done){
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderClear(renderer);

        // printf("%f\n", robot.true_x);
        // printf("%f\n", robot.true_y);

        //Move robot based on user input commands/auto commands
        if (robot.auto_mode == 1)
            robotAutoMotorMove(&robot, front_centre_sensor, left_sensor, right_sensor);
        robotMotorMove(&robot, crashed);

        //Check if robot reaches endpoint. and check sensor values
        if (checkRobotReachedEnd(&robot, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT/2+100, 10, 100) && maze_number != 3){
            end_time = clock();
            msec = (end_time-start_time) * 10 / sysconf(_SC_CLK_TCK);
            robotSuccess(&robot, msec);
        }

        if(checkRobotReachedEnd(&robot, OVERALL_WINDOW_WIDTH/2-35, -50, 10, 100) && maze_number == 3){
            end_time = clock();
            msec = (end_time-start_time) * 10 / sysconf(_SC_CLK_TCK);
            robotSuccess(&robot, msec);
        }
        if(checkRobotReachedEnd(&robot, 579, 420, 10, 100) && maze_number == 4){
            end_time = clock();
            msec = (end_time-start_time) * 10 / sysconf(_SC_CLK_TCK);
            robotSuccess(&robot, msec);
        }
        else if(crashed == 1 || checkRobotHitWalls(&robot, head)){
            robotCrash(&robot);
            crashed = 1;
        }
        //Otherwise compute sensor information
        else {
            front_centre_sensor = checkRobotSensorFrontCentreAllWalls(&robot, head);
            if (front_centre_sensor>0)
                printf("Getting close on the centre. Score = %d\n", front_centre_sensor);

            left_sensor = checkRobotSensorLeftAllWalls(&robot, head);
            if (left_sensor>0)
                printf("Getting close on the left. Score = %d\n", left_sensor);

            right_sensor = checkRobotSensorRightAllWalls(&robot, head);
            if (right_sensor>0)
                printf("Getting close on the right. Score = %d\n", right_sensor);
        }
        robotUpdate(renderer, &robot);
        updateAllWalls(head, renderer);

        // Check for user input
        SDL_RenderPresent(renderer);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                done = 1;
            }
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            if(state[SDL_SCANCODE_UP] && robot.direction != DOWN){
                robot.direction = UP;
            }
            if(state[SDL_SCANCODE_DOWN] && robot.direction != UP){
                robot.direction = DOWN;
            }
            if(state[SDL_SCANCODE_LEFT] && robot.direction != RIGHT){
                robot.direction = LEFT;
            }
            if(state[SDL_SCANCODE_RIGHT] && robot.direction != LEFT){
                robot.direction = RIGHT;
            }
            if(state[SDL_SCANCODE_SPACE]){
                crashed = 0;
                setup_robot(&robot, OVERALL_WINDOW_WIDTH/2-50, OVERALL_WINDOW_HEIGHT-50);
            }
            if(state[SDL_SCANCODE_UP]){
                robot.auto_mode = 1;
                start_time = clock();
            }
        }

        SDL_Delay(120);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    printf("DEAD\n");
}