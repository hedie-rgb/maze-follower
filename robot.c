#include "robot.h"

int count = 0;
int turned = 0;
int to_turn = 0;
int count_command_execution_duration = 0; //was count1
int fine_tune = 0;
int count_fine_tune = 0;
int count_to_30_left = 0;
int count_to_30_right = 0;
int count_to_45_right_turn = 0;
int count_to_45_left_turn = 0;

void setup_robot(struct Robot *robot, int start_x, int start_y){
    robot->x = start_x;
    robot->y = start_y;
    robot->true_x = start_x;
    robot->true_y = start_y;
    robot->width = ROBOT_WIDTH;
    robot->height = ROBOT_HEIGHT;
    robot->direction = 0;
    robot->angle = 0;
    robot->currentSpeed = 0;
    robot->crashed = 0;
    robot->auto_mode = 0;

    printf("Press arrow keys to move manually, or press arrow key to move automatically\n\n");
}
int robot_off_screen(struct Robot * robot){
    if(robot->x < 0 || robot-> y < 0){
        return 0;
    }
    if(robot->x > OVERALL_WINDOW_WIDTH || robot->y > OVERALL_WINDOW_HEIGHT){
        return 0;
    }
    return 1;
}

int checkRobotHitWall(struct Robot * robot, struct Wall * wall) {

    int overlap = checkOverlap(robot->x,robot->width,robot->y,robot->height,
                 wall->x,wall->width,wall->y, wall->height);

    return overlap;
}

int checkRobotHitWalls(struct Robot * robot, struct Wall_collection * head) {
   struct Wall_collection *ptr = head;
   int hit = 0;

   while(ptr != NULL) {
      hit = (hit || checkRobotHitWall(robot, &ptr->wall));
      ptr = ptr->next;
   }
   return hit;

}

int checkRobotReachedEnd(struct Robot * robot, int x, int y, int width, int height){

    int overlap = checkOverlap(robot->x,robot->width,robot->y,robot->height,
                 x,width,y,height);

    return overlap;
}

void robotCrash(struct Robot * robot) {
    robot->currentSpeed = 0;
    if (!robot->crashed)
        printf("Ouchies!!!!!\n\nPress space to start again\n");
    robot->crashed = 1;
}

void robotSuccess(struct Robot * robot, int msec) {
    robot->currentSpeed = 0;
    if (!robot->crashed){
        printf("Success!!!!!\n\n");
        printf("Time taken %d seconds %d milliseconds \n", msec/1000, msec%1000);
        printf("Press space to start again\n");
    }
    robot->crashed = 1;
}

int checkRobotSensor(int x, int y, int sensorSensitivityLength, struct Wall * wall)  {
    //viewing_region of sensor is a square of 2 pixels * chosen length of sensitivity
    int overlap = checkOverlap(x,2,y,sensorSensitivityLength,
                 wall->x,wall->width,wall->y, wall->height);

    return overlap;
}

int checkRobotSensorFrontCentreAllWalls(struct Robot * robot, struct Wall_collection * head) {
    struct Wall_collection *ptr, *head_store;
    int i;
    double xDir, yDir;
    int robotCentreX, robotCentreY, xTL, yTL;
    int score, hit;

    int sensorSensitivityLength =  floor(SENSOR_VISION/5);

    head_store = head;
    robotCentreX = robot->x+ROBOT_WIDTH/2;
    robotCentreY = robot->y+ROBOT_HEIGHT/2;
    score = 0;

    for (i = 0; i < 5; i++)
    {
        ptr = head_store;
        //xDir = round(robotCentreX+(ROBOT_WIDTH/2-2)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*sin((robot->angle)*PI/180));
        //yDir = round(robotCentreY+(ROBOT_WIDTH/2-2)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*cos((robot->angle)*PI/180));
        xDir = round(robotCentreX-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*sin((robot->angle)*PI/180));
        yDir = round(robotCentreY+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*cos((robot->angle)*PI/180));
        xTL = (int) xDir;
        yTL = (int) yDir;
        hit = 0;

        while(ptr != NULL) {
            hit = (hit || checkRobotSensor(xTL, yTL, sensorSensitivityLength, &ptr->wall));
            ptr = ptr->next;
        }
        if (hit)
            score = i;
    }
    return score;
}

int checkRobotSensorLeftAllWalls(struct Robot * robot, struct Wall_collection * head) {
    struct Wall_collection *ptr, *head_store;
    int i;
    double xDir, yDir;
    int robotCentreX, robotCentreY, xTL, yTL;
    int score, hit;
    int sensorSensitivityLength;

    head_store = head;
    robotCentreX = robot->x+ROBOT_WIDTH/2;
    robotCentreY = robot->y+ROBOT_HEIGHT/2;
    score = 0;
    sensorSensitivityLength =  floor(SENSOR_VISION/5);

    for (i = 0; i < 5; i++)
    {
        ptr = head_store;
        //xDir = round(robotCentreX+(-ROBOT_WIDTH/2)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*sin((robot->angle)*PI/180));
        //yDir = round(robotCentreY+(-ROBOT_WIDTH/2)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*cos((robot->angle)*PI/180));
        xDir = round(robotCentreX+(+ROBOT_WIDTH/2)*cos((robot->angle-90)*PI/180)-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*sin((robot->angle-90)*PI/180));
        yDir = round(robotCentreY+(+ROBOT_WIDTH/2)*sin((robot->angle-90)*PI/180)+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*cos((robot->angle-90)*PI/180));
        xTL = (int) xDir;
        yTL = (int) yDir;
        hit = 0;

        while(ptr != NULL) {
            hit = (hit || checkRobotSensor(xTL, yTL, sensorSensitivityLength, &ptr->wall));
            ptr = ptr->next;
        }
        if (hit)
            score = i;
    }
    return score;
}

int checkRobotSensorRightAllWalls(struct Robot * robot, struct Wall_collection * head) {
    struct Wall_collection *ptr, *head_store;
    int i;
    double xDir, yDir;
    int robotCentreX, robotCentreY, xTL, yTL;
    int score, hit;
    int sensorSensitivityLength;

    head_store = head;
    robotCentreX = robot->x+ROBOT_WIDTH/2;
    robotCentreY = robot->y+ROBOT_HEIGHT/2;
    score = 0;
    sensorSensitivityLength =  floor(SENSOR_VISION/5);

    for (i = 0; i < 5; i++)
    {
        ptr = head_store;
        //xDir = round(robotCentreX+(-ROBOT_WIDTH/2)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*sin((robot->angle)*PI/180));
        //yDir = round(robotCentreY+(-ROBOT_WIDTH/2)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*cos((robot->angle)*PI/180));
        xDir = round(robotCentreX+(-ROBOT_WIDTH/2)*cos((robot->angle+90)*PI/180)-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*sin((robot->angle+90)*PI/180));
        yDir = round(robotCentreY+(-ROBOT_WIDTH/2)*sin((robot->angle+90)*PI/180)+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*cos((robot->angle+90)*PI/180));
        xTL = (int) xDir;
        yTL = (int) yDir;
        hit = 0;

        while(ptr != NULL) {
            hit = (hit || checkRobotSensor(xTL, yTL, sensorSensitivityLength, &ptr->wall));
            ptr = ptr->next;
        }
        if (hit)
            score = i;
    }
    return score;
}

void robotUpdate(struct SDL_Renderer * renderer, struct Robot * robot){
    double xDir, yDir;

    int robotCentreX, robotCentreY, xTR, yTR, xTL, yTL, xBR, yBR, xBL, yBL;
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);

    /*
    //Other Display options:
    // The actual square which the robot is tested against (not so nice visually with turns, but easier
    // to test overlap
    SDL_Rect rect = {robot->x, robot->y, robot->height, robot->width};
    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &rect);
    */
    /*
    //Center Line of Robot. Line shows the direction robot is facing
    xDir = -30 * sin(-robot->angle*PI/180);
    yDir = -30 * cos(-robot->angle*PI/180);
    xDirInt = robot->x+ROBOT_WIDTH/2+ (int) xDir;
    yDirInt = robot->y+ROBOT_HEIGHT/2+ (int) yDir;
    SDL_RenderDrawLine(renderer,robot->x+ROBOT_WIDTH/2, robot->y+ROBOT_HEIGHT/2, xDirInt, yDirInt);
    */

    //Rotating Square
    //Vector rotation to work out corners x2 = x1cos(angle)-y1sin(angle), y2 = x1sin(angle)+y1cos(angle)
    robotCentreX = robot->x+ROBOT_WIDTH/2;
    robotCentreY = robot->y+ROBOT_HEIGHT/2;

    xDir = round(robotCentreX+(ROBOT_WIDTH/2)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2)*sin((robot->angle)*PI/180));
    yDir = round(robotCentreY+(ROBOT_WIDTH/2)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2)*cos((robot->angle)*PI/180));
    xTR = (int) xDir;
    yTR = (int) yDir;

    xDir = round(robotCentreX+(ROBOT_WIDTH/2)*cos((robot->angle)*PI/180)-(ROBOT_HEIGHT/2)*sin((robot->angle)*PI/180));
    yDir = round(robotCentreY+(ROBOT_WIDTH/2)*sin((robot->angle)*PI/180)+(ROBOT_HEIGHT/2)*cos((robot->angle)*PI/180));
    xBR = (int) xDir;
    yBR = (int) yDir;

    xDir = round(robotCentreX+(-ROBOT_WIDTH/2)*cos((robot->angle)*PI/180)-(ROBOT_HEIGHT/2)*sin((robot->angle)*PI/180));
    yDir = round(robotCentreY+(-ROBOT_WIDTH/2)*sin((robot->angle)*PI/180)+(ROBOT_HEIGHT/2)*cos((robot->angle)*PI/180));
    xBL = (int) xDir;
    yBL = (int) yDir;

    xDir = round(robotCentreX+(-ROBOT_WIDTH/2)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2)*sin((robot->angle)*PI/180));
    yDir = round(robotCentreY+(-ROBOT_WIDTH/2)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2)*cos((robot->angle)*PI/180));
    xTL = (int) xDir;
    yTL = (int) yDir;

    SDL_RenderDrawLine(renderer,xTR, yTR, xBR, yBR);
    SDL_RenderDrawLine(renderer,xBR, yBR, xBL, yBL);
    SDL_RenderDrawLine(renderer,xBL, yBL, xTL, yTL);
    SDL_RenderDrawLine(renderer,xTL, yTL, xTR, yTR);

    //Front Centre Sensor
    int sensor_sensitivity =  floor(SENSOR_VISION/5);
    int i;
    for (i = 0; i < 5; i++)
    {
        xDir = round(robotCentreX-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*sin((robot->angle)*PI/180));
        yDir = round(robotCentreY+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*cos((robot->angle)*PI/180));
        xTL = (int) xDir;
        yTL = (int) yDir;

        SDL_Rect rect = {xTL, yTL, 2, sensor_sensitivity};
        SDL_SetRenderDrawColor(renderer, 80+(20*(5-i)), 80+(20*(5-i)), 80+(20*(5-i)), 255);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);
    }

    //Left Sensor
    for (i = 0; i < 5; i++)
    {
        xDir = round(robotCentreX+(+ROBOT_WIDTH/2)*cos((robot->angle-90)*PI/180)-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*sin((robot->angle-90)*PI/180));
        yDir = round(robotCentreY+(+ROBOT_WIDTH/2)*sin((robot->angle-90)*PI/180)+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*cos((robot->angle-90)*PI/180));
        xTL = (int) xDir;
        yTL = (int) yDir;

        SDL_Rect rect = {xTL, yTL, 2, sensor_sensitivity};
        SDL_SetRenderDrawColor(renderer, 80+(20*(5-i)), 80+(20*(5-i)), 80+(20*(5-i)), 255);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);
    }

    //Right Sensor
    for (i = 0; i < 5; i++)
    {
        xDir = round(robotCentreX+(-ROBOT_WIDTH/2)*cos((robot->angle+90)*PI/180)-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*sin((robot->angle+90)*PI/180));
        yDir = round(robotCentreY+(-ROBOT_WIDTH/2)*sin((robot->angle+90)*PI/180)+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*cos((robot->angle+90)*PI/180));
        xTL = (int) xDir;
        yTL = (int) yDir;

        SDL_Rect rect = {xTL, yTL, 2, sensor_sensitivity};
        SDL_SetRenderDrawColor(renderer, 80+(20*(5-i)), 80+(20*(5-i)), 80+(20*(5-i)), 255);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);
    }

        //xDir = round(robotCentreX+(ROBOT_WIDTH/2-2)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*sin((robot->angle)*PI/180));
        //yDir = round(robotCentreY+(ROBOT_WIDTH/2-2)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*cos((robot->angle)*PI/180));
}



void robotMotorMove(struct Robot * robot, int crashed) {
    double x_offset, y_offset;
    if (crashed)
        robot->currentSpeed = 0;
    else {
        switch(robot->direction){
            case UP :
                robot->currentSpeed += DEFAULT_SPEED_CHANGE;
                if (robot->currentSpeed > MAX_ROBOT_SPEED)
                    robot->currentSpeed = MAX_ROBOT_SPEED;
                break;
            case DOWN :
                robot->currentSpeed -= DEFAULT_SPEED_CHANGE;
                if (robot->currentSpeed < -MAX_ROBOT_SPEED)
                    robot->currentSpeed = -MAX_ROBOT_SPEED;
                break;
            case LEFT :
                robot->angle = (robot->angle+360-DEFAULT_ANGLE_CHANGE)%360;
                break;
            case RIGHT :
                robot->angle = (robot->angle+DEFAULT_ANGLE_CHANGE)%360;
                break;
        }
    }
    robot->direction = 0;
    x_offset = (-robot->currentSpeed * sin(-robot->angle*PI/180));
    y_offset = (-robot->currentSpeed * cos(-robot->angle*PI/180));

    robot->true_x += x_offset;
    robot->true_y += y_offset;

    x_offset = round(robot->true_x);
    y_offset = round(robot->true_y);

    robot->x = (int) x_offset;
    robot->y = (int) y_offset;
}

void robotAutoMotorMove(struct Robot * robot, int front_centre_sensor, int left_sensor, int right_sensor) {

    //Improve algorithm
    //wall hugging to right wall
    if(count_to_30_left != 0) {
        if(count_to_30_left < 2) {
            robot->currentSpeed = 0; //don't move
            robot->direction = LEFT;
            count_to_30_left++;
        }
        else {
            count_to_30_left = 0;
        }
    }

    else if(count_to_30_right != 0) {
        if(count_to_30_right < 2) {
            robot->currentSpeed = 0; //don't move
            robot->direction = RIGHT;
            count_to_30_right++;
        }
        else {
            count_to_30_right = 0;
        }
    }
    //when set to turning, ensure turn 90 degrees without moving
    else if (count_to_45_right_turn != 0) {
        //turning by default is 3
        //when set to RIGHT/LEFT, turn 15 degrees each time
        //thus meaning, 3*15 = 45 degrees, turn 45 degree exactly here
        if(count_to_45_right_turn < 3) {
            robot->currentSpeed = 0; //don't move
            robot->direction = RIGHT;
            count_to_45_right_turn++;
        }
        else {
            count_to_45_right_turn = 0;
        }
    }
    //when set to turning, ensure turn 45 degrees without moving
    else if (count_to_45_left_turn != 0) {
        if(count_to_45_left_turn < 3) {
            robot->currentSpeed = 0; //don't move
            robot->direction = LEFT;
            count_to_45_left_turn++;
        }
        else {
            count_to_45_left_turn = 0;
        }
    }

    //when not turning on the spot
    //if sensing somethign in front
    else if (front_centre_sensor > 0) {
        //if very close, turn accordingly
        if(front_centre_sensor >= 3){
            if (right_sensor == 0){
                robot->currentSpeed = 0;
                robot->direction = RIGHT;
                count_to_45_right_turn++;
                //record a turn right command is given
                turned = 1;
            }else if (left_sensor == 0){
                robot->currentSpeed = 0;
                robot->direction = LEFT;
                count_to_45_left_turn++;
            }
        }else{
            //if too close, fine tune by turning 15
            if(right_sensor >= 3) {
                robot->currentSpeed = 0;
                robot->direction = LEFT;
            }
            else if(left_sensor >= 3) {
                robot->currentSpeed = 0;
                robot->direction = RIGHT;
            }
            else {
            //else, go straight
            robot -> direction == UP;
            robot->currentSpeed += DEFAULT_SPEED_CHANGE;
            if (robot->currentSpeed > .158* MAX_ROBOT_SPEED){
                robot->currentSpeed = .158* MAX_ROBOT_SPEED;
            }}
        }
    }
    //if front open
    else if (front_centre_sensor == 0){

        //if fine tune command is given, delay a bit
        if(fine_tune == 1) {
            robot -> direction == UP;
            robot->currentSpeed += DEFAULT_SPEED_CHANGE;
            if (robot->currentSpeed > .158* MAX_ROBOT_SPEED){
                robot->currentSpeed = .158* MAX_ROBOT_SPEED;
            }
            //clear any count when front is open, right is open
            
            fine_tune = 0;

            //clear all the counts
            count = 0;
            to_turn = 0;

        }

        //if touching right wall, go straight
        else if (right_sensor > 0){
                if(right_sensor >= 3) {
                    robot->currentSpeed = 0;
                    robot->direction = LEFT;
                }
                else if(left_sensor >= 3) {
                    robot->currentSpeed = 0;
                    robot->direction = RIGHT;
                }
                //if right a bit too far away, fine tune by turning right 15
                else if (right_sensor == 1){
                    robot->currentSpeed = 0;
                    robot->direction = RIGHT;
                    fine_tune = 1;
                }
            robot -> direction == UP;
            robot->currentSpeed += DEFAULT_SPEED_CHANGE;
            if (robot->currentSpeed > .158* MAX_ROBOT_SPEED){
                robot->currentSpeed = .158* MAX_ROBOT_SPEED;
            }
            //clear all the counts
            count = 0;
            count_command_execution_duration = 0;
        }

        //if one right turn command is given, moving forward longer before next check so passing the junction
        else if (turned == 1){
            robot -> direction == UP;
            robot->currentSpeed += DEFAULT_SPEED_CHANGE;
            if (robot->currentSpeed > .158* MAX_ROBOT_SPEED){
                robot->currentSpeed = .158* MAX_ROBOT_SPEED;
            }
            count_command_execution_duration++;
            if (count_command_execution_duration >= 5){
                turned = 0;
                count_command_execution_duration = 0;
            }
            //clear any count when front is open, right is open
            count = 0;
            to_turn = 0;
        }
        //when front is open, right is open
        else if (right_sensor == 0){
            //if asked to turn
            if (to_turn == 1){
                //printf("right spare, turning\n");
                robot->currentSpeed = 0;
                robot->direction = RIGHT;
                count_to_45_right_turn++;
                //reset to_turn, move to turned so walk further before next check
                to_turn = 0;
                turned = 1;
            }else{
                //printf("delay\n");
                //when sensed, don't turn yet
                //move forward a bit longer before asking to turn
                //so robot can pass junction wall or if it takes time to realise it is a corner etc
                robot -> direction == UP;
                robot->currentSpeed += DEFAULT_SPEED_CHANGE;
                if (robot->currentSpeed > .158* MAX_ROBOT_SPEED){
                    robot->currentSpeed = .158* MAX_ROBOT_SPEED;
                }
                //delay for 7 frames
                count++;
                if (count >= 5){
                    //printf("change turning\n");
                    to_turn = 1;
                    count = 0;
                }

            }
        }


    }

}