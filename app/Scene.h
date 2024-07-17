/******************************************************************************
 *  Scene.h (for LEGO Mindstorms EV3)
 *  Created on: 2015/02/07
 *  Implementation of the Struct Scene
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef EV3_APP_SCENE_H_
#define EV3_APP_SCENE_H_

enum SceneCommands { GO_STRAIGHT = 0, TURN_LEFT, TURN_RIGHT };

struct Scene {
  SceneCommands command;
  int time;
  Scene* next;
};

#endif  // EV3_APP_SCENE_H_
