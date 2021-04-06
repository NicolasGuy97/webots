/*
 * Copyright 1996-2020 Cyberbotics Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>

#include <webots/keyboard.h>
#include <webots/motor.h>
#include <webots/robot.h>

#define TIME_STEP 32

static void step() {
  if (wb_robot_step(TIME_STEP) == -1) {
    wb_robot_cleanup();
    exit(EXIT_SUCCESS);
  }
}

// function to create a timer
static void passive_wait(double sec) {
  double start_time = wb_robot_get_time();
  do
    step();
  while (start_time + sec > wb_robot_get_time());
}

// function to show the different commands
static void show_commands() {
  printf("------------COMMANDS--------------\n");
  printf("Launch demo --> D\n");
  printf("Move joint1 --> A and Z\n");
  printf("Move joint2 --> Q and S\n");
  printf("Move joint3 --> W and X\n");
  printf("Move joint4 --> Y and U\n");
  printf("Move joint5 --> H and J\n");
  printf("Move joint6 --> B and N\n");
  printf("Open Close Gripper --> L or M\n");
  printf("Launch Pick and Place --> P\n");
  printf("----------------------------------\n");
}

int main(int argc, char **argv) {
  /* initialize Webots */
  wb_robot_init();   // init the robot
  command_manager(); // show commands

  // init of the Keyboard control
  int time_step = (int)wb_robot_get_basic_time_step();
  wb_keyboard_enable(time_step);

  //----------------------Init all the motors of the Ned---------------------
  WbDeviceTag motors[8];
  motors[1] = wb_robot_get_device("joint_1");
  motors[2] = wb_robot_get_device("joint_2");
  motors[3] = wb_robot_get_device("joint_3");
  motors[4] = wb_robot_get_device("joint_4");
  motors[5] = wb_robot_get_device("joint_5");
  motors[6] = wb_robot_get_device("joint_6");
  gripper[1] = wb_robot_get_device("joint_base_to_mors_1");
  gripper[2] = wb_robot_get_device("joint_base_to_mors_2");

  // set the motor velocity
  // first we make sure that every joints are at their initial positions
  wb_motor_set_position(motors[1], 0.0);
  wb_motor_set_position(motors[2], 0.0);
  wb_motor_set_position(motors[3], 0.0);
  wb_motor_set_position(motors[4], 0.0);
  wb_motor_set_position(motors[5], 0.0);
  wb_motor_set_position(motors[6], 0.0);
  wb_motor_set_position(gripper[1], 0.0);
  wb_motor_set_position(gripper[2], 0.0);

  // set the motors speed. Here we put 1 or 2 radian/second
  wb_motor_set_velocity(motors[1], 1.0);
  wb_motor_set_velocity(motors[2], 1.0);
  wb_motor_set_velocity(motors[3], 1.0);
  wb_motor_set_velocity(motors[4], 1.0);
  wb_motor_set_velocity(motors[5], 1.0);
  wb_motor_set_velocity(motors[6], 1.0);
  wb_motor_set_velocity(gripper[1], 1.0);
  wb_motor_set_velocity(gripper[2], 1.0);
  //--------------------------------------------------------------------------------

  // control with keyboard
  while (wb_robot_step(time_step) != -1) {

    int c = wb_keyboard_get_key(); // get the keyboard key
    switch (c) {
    case 'A':
      wb_motor_set_position(motors[1], -1.5);
      printf("Move --> Joint1");
      break;

    case 'Z':
      wb_motor_set_position(motors[1], 1.5);
      printf("Move --> Joint1");
      break;

    case 'Q':
      printf("Move --> Joint2");
      wb_motor_set_position(motors[2], -0.5);
      break;

    case 'S':
      printf("Move --> Joint2");
      wb_motor_set_position(motors[2], 0.5);
      break;

    case 'W':
      printf("Move --> Joint3");
      wb_motor_set_position(motors[3], -0.5);
      break;

    case 'X':
      printf("Move --> Joint3");
      wb_motor_set_position(motors[3], 0.5);
      break;

    case 'Y':
      printf("Move --> Joint4");
      wb_motor_set_position(motors[4], -1);
      break;

    case 'U':
      printf("Move --> Joint4");
      wb_motor_set_position(motors[4], 1);
      break;

    case 'H':
      printf("Move --> Joint5");
      wb_motor_set_position(motors[5], -1.4);
      break;

    case 'J':
      printf("Move --> Joint5");
      wb_motor_set_position(motors[5], 1.4);
      break;

    case 'B':
      printf("Move --> Joint6");
      wb_motor_set_position(motors[6], 1.5);
      break;

    case 'N':
      printf("Move --> Joint6");
      wb_motor_set_position(motors[6], -1.5);
      break;

    case 'L':
      printf("Open Gripper");
      wb_motor_set_position(gripper[1], 0.01);
      wb_motor_set_position(gripper[2], 0.01);
      break;

    case 'M':
      printf("Close Gripper");
      wb_motor_set_position(gripper[1], 0.0);
      wb_motor_set_position(gripper[2], 0.0);
      break;

    case 'D': // demo

      wb_motor_set_velocity(motors[1], 1.0);
      wb_motor_set_velocity(motors[2], 1.0);
      wb_motor_set_velocity(motors[3], 1.0);

      wb_motor_set_position(motors[1], 1.5);
      wb_motor_set_position(gripper[1], 0.01);
      wb_motor_set_position(gripper[2], 0.01);
      passive_wait(1.5);
      wb_motor_set_position(motors[1], 0.0);
      passive_wait(1.5);
      wb_motor_set_position(motors[2], 0.5);
      passive_wait(0.7);
      wb_motor_set_position(motors[2], 0.0);
      passive_wait(0.7);
      wb_motor_set_position(motors[1], -0.5);
      wb_motor_set_position(motors[4], 1.45);
      passive_wait(1.5);
      wb_motor_set_position(motors[4], 0.0);
      passive_wait(1.5);
      wb_motor_set_position(motors[5], -1.0);
      passive_wait(0.7);
      wb_motor_set_position(motors[5], 0.0);
      passive_wait(1.0);
      wb_motor_set_position(motors[3], 0.0);
      wb_motor_set_position(motors[1], 0.0);
      passive_wait(0.5);
      wb_motor_set_position(motors[6], 1.5);
      passive_wait(1.0);
      wb_motor_set_position(motors[6], 0);
      passive_wait(1.0);
      wb_motor_set_position(gripper[1], 0);
      wb_motor_set_position(gripper[2], 0);
      passive_wait(0.5);
      wb_motor_set_position(gripper[1], 0.01);
      wb_motor_set_position(gripper[2], 0.01);
      break;

    case 'P': // pick and place

      wb_motor_set_velocity(motors[1], 0.5);
      wb_motor_set_velocity(motors[2], 0.5);
      wb_motor_set_velocity(motors[3], 0.5);

      wb_motor_set_position(motors[1], 1.5);
      wb_motor_set_position(motors[2], 0.70);
      wb_motor_set_position(gripper[1], 0.01);
      wb_motor_set_position(gripper[2], 0.01);
      passive_wait(4.2);
      wb_motor_set_position(motors[3], 0.5);
      passive_wait(1.2);
      wb_motor_set_position(gripper[1], 0.0);
      wb_motor_set_position(gripper[2], 0.0);
      passive_wait(1.5);
      wb_motor_set_position(motors[3], 0.3);
      passive_wait(1.2);
      wb_motor_set_position(motors[1], 0.0);
      passive_wait(5.0);
      wb_motor_set_position(motors[3], 0.5);
      passive_wait(0.5);
      wb_motor_set_position(gripper[1], 0.01);
      wb_motor_set_position(gripper[2], 0.01);
      passive_wait(0.5);
      wb_motor_set_position(motors[2], 0.0);
      wb_motor_set_position(motors[3], 0.0);
      break;
    }
  }

  wb_robot_cleanup();
  return 0;
}
