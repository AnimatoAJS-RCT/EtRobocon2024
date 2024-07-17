/******************************************************************************
 *  Scenario.h (for LEGO Mindstorms EV3)
 *  Created on: 2015/02/07
 *  Implementation of the Class Scenario
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef EV3_APP_SCENARIO_H_
#define EV3_APP_SCENARIO_H_

#include "ev3api.h"
#include "Scene.h"

class Scenario {
 public:
  explicit Scenario(Scene* scene);

  void add(Scene* scene);
  Scene* top() const;
  Scene* current() const;
  Scene* next();
  SceneCommands currentSceneCommand() const;
  uint32_t currentSceneTime() const;

 private:
  Scene* mTopScene;
  Scene* mCurrentScene;
};

#endif  // EV3_APP_SCENARIO_H_
