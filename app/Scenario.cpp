/******************************************************************************
 *  Scenario.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/02/07
 *  Implementation of the Class Scenario
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "Scenario.h"

/**
 * コンストラクタ
 * @param scene 先頭シーン
 */
Scenario::Scenario(Scene* scene) : mTopScene(scene), mCurrentScene(scene) {}

/**
 * シーン追加
 * @param scene 追加シーン
 */
void Scenario::add(Scene* scene)
{
  if(mTopScene == 0) {
    mTopScene = scene;
  } else {
    Scene* s = mTopScene;
    while(s->next != top()) {
      s = s->next;
    }
    s->next = scene;
  }
  scene->next = top();
}

/**
 * 先頭シーン取得
 * @return 先頭シーン
 */
Scene* Scenario::top() const
{
  return mTopScene;
}

/**
 * 現在シーン取得
 * @return 現在シーン
 */
Scene* Scenario::current() const
{
  return mCurrentScene;
}

/**
 * 次のシーンへ進める
 * @return 実行シーン
 */
Scene* Scenario::next()
{
  if(mCurrentScene != 0) {
    mCurrentScene = mCurrentScene->next;
  } else {
    mCurrentScene = mTopScene;
  }
  return mCurrentScene;
}

/**
 * 現在シーンコマンド取得
 * @return コマンド
 */
SceneCommands Scenario::currentSceneCommand() const
{
  return (mCurrentScene == 0) ? GO_STRAIGHT : mCurrentScene->command;
}

/**
 * 現在シーン実行時間取得
 * @return 実行時間
 */
uint32_t Scenario::currentSceneTime() const
{
  return (mCurrentScene == 0) ? 0 : mCurrentScene->time;
}
