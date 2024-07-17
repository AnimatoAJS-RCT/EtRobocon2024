/******************************************************************************
 *  RandomWalker.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/02/07
 *  Implementation of the Class RandomWalker
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include <stdlib.h>
#include "Clock.h"

#include "RandomWalker.h"

// 定数宣言
const int RandomWalker::MIN_TIME = 5000 * 1000;   // 切り替え時間の最小値
const int RandomWalker::MAX_TIME = 15000 * 1000;  // 切り替え時間の最大値

/**
 * コンストラクタ
 * @param starter         スタータ
 * @param simpleTimer     タイマ
 */

RandomWalker::RandomWalker(const Starter* starter, SimpleTimer* simpleTimer)
  : mStarter(starter), mSimpleTimer(simpleTimer), mState(UNDEFINED)
{
  ev3api::Clock* clock = new ev3api::Clock();

  srand(clock->now());     // 乱数をリセットする
  generateCourseList();    // courseListを生成する。
  generateCourseList_2();  // courseList2を生成する。
  generateCourseList_3();  // courseList3を生成する。

  delete clock;
}

/**
 * ランダム走行する
 */
void RandomWalker::run()
{
  switch(mState) {
    case UNDEFINED:
      execUndefined();
      break;
    case WAITING_FOR_START:
      execWaitingForStart();
      break;
    case COURSE_RUNNING:
      execCourseRunning();
      break;
    case DIFFICULT_RUNNING:
      execDifficultRunning();
      break;
    case SHORTCUT_RUNNING:
      execShortcutRunning();
      break;
    case FINISHED:
      execFinished();
      break;
    default:
      break;
  }
}

/**
 * 乱数を取得する
 * @retrun 乱数
 */
int RandomWalker::getRandomTime()
{
  return MIN_TIME
         + static_cast<int>(static_cast<double>(rand()) * (MAX_TIME - MIN_TIME + 1.0)
                            / (1.0 + RAND_MAX));
}

/**
 * シーン変更処理
 */
void RandomWalker::modeChangeAction()
{
  mSimpleTimer->setTime(getRandomTime());
  mSimpleTimer->start();
}

void RandomWalker::generateCourseList()
{
  // ノーマルコースに必要なTracerインスタンスをcourseListに追加する
  if(IS_LEFT_COURSE) {  // Lコースの場合
    courseList.push_back(
        new ScenarioTracer(100, 40, 40));  // 初速が早いとブレるため少しだけ低速で走る
    courseList.push_back(
        new LineTracer(1300, BRIGHTNESS_TH, 90, LEFT_EDGE, PidGain(0.30, 0.12, 0.12)));
    courseList.push_back(new ScenarioTracer(1350, 100, 100));
    courseList.push_back(new ScenarioTracer(550, 100, 60));  // 第一カーブ
    courseList.push_back(
        new LineTracer(800, BRIGHTNESS_TH, 80, RIGHT_EDGE, PidGain(0.25, 0.04, 0.04)));
    courseList.push_back(new ScenarioTracer(700, 100, 100));
    courseList.push_back(new ScenarioTracer(590, 100, 60));  // 第二カーブ
    courseList.push_back(new ScenarioTracer(
        300, 100, 100));  // 青線でライントレースが狂うため少しシナリオトレースする
    courseList.push_back(
        new LineTracer(800, BRIGHTNESS_TH, 70, LEFT_EDGE, PidGain(0.24, 0.04, 0.04)));
    courseList.push_back(
        new LineTracer(300, BRIGHTNESS_TH, 60, LEFT_EDGE, PidGain(0.21, 0.04, 0.04)));
  } else {  // Rコースの場合
    courseList.push_back(
        new ScenarioTracer(100, 40, 40));  // 初速が早いとブレるため少しだけ低速で走るq
    courseList.push_back(
        new LineTracer(1300, BRIGHTNESS_TH, 90, RIGHT_EDGE, PidGain(0.30, 0.12, 0.12)));
    courseList.push_back(new ScenarioTracer(1350, 100, 100));
    courseList.push_back(new ScenarioTracer(550, 60, 100));  // 第一カーブ
    courseList.push_back(
        new LineTracer(800, BRIGHTNESS_TH, 80, LEFT_EDGE, PidGain(0.25, 0.04, 0.04)));
    courseList.push_back(new ScenarioTracer(680, 100, 100));
    courseList.push_back(new ScenarioTracer(590, 60, 100));  // 第二カーブ
    courseList.push_back(new ScenarioTracer(
        300, 100, 100));  // 青線でライントレースが狂うため少しシナリオトレースする
    courseList.push_back(
        new LineTracer(800, BRIGHTNESS_TH, 80, RIGHT_EDGE, PidGain(0.24, 0.04, 0.04)));
    courseList.push_back(
        new LineTracer(300, BRIGHTNESS_TH, 60, RIGHT_EDGE, PidGain(0.21, 0.04, 0.04)));
  }
}

void RandomWalker::generateCourseList_2()
{
  // 難所コースに必要なTracerインスタンスをcourseListに追加する
  if(IS_LEFT_COURSE) {  // ◆◆　Lコースの場合
    courseList2.push_back(new DifficultScenarioTracer(
        30, 1, 35, 35));  // ブロック押し１ 壁への最接近距離、１回の移動距離、左モーター、右モーター
    courseList2.push_back(new DifficultScenarioTracer(25, 1, 25,
                                                      25));  // ブロック押し２（低速）
    courseList2.push_back(new DifficultScenarioTracer(16, 1, 15,
                                                      15));  // ブロック押し３（超低速）

    courseList2.push_back(new ScenarioTracer(120, -40, -40));  // ブロック配置後、後進１
    courseList2.push_back(new ScenarioTracer(40, -20, -20));   // ブロック配置後、後進２

    courseList2.push_back(new ScenarioTracer(10, 10, 0));  // ゴール方向へ 右旋回１（低速）
    courseList2.push_back(new ScenarioTracer(120, 30, 0));  // ゴール方向へ右旋回２
    courseList2.push_back(new ScenarioTracer(10, 10, 0));  // ゴール方向へ 右旋回３（低速）
  } else {                                                 // ◆◆　Rコースの場合
    courseList2.push_back(new DifficultScenarioTracer(
        30, 1, 35, 35));  // ブロック押し１ 壁への最接近距離、１回の移動距離、左モーター、右モーター
    courseList2.push_back(new DifficultScenarioTracer(25, 1, 25,
                                                      25));  // ブロック押し２（低速）
    courseList2.push_back(new DifficultScenarioTracer(16, 1, 15,
                                                      15));  // ブロック押し３（低速）

    courseList2.push_back(new ScenarioTracer(112, -40, -40));  // ブロック配置後、後進１
    courseList2.push_back(new ScenarioTracer(40, -20, -20));   // ブロック配置後、後進２

    courseList2.push_back(new ScenarioTracer(10, 0, 10));  // ゴール方向へ 右旋回１（低速）
    courseList2.push_back(new ScenarioTracer(125, 0, 30));  // ゴール方向へ右旋回２
    courseList2.push_back(new ScenarioTracer(10, 0, 10));  // ゴール方向へ 右旋回３（低速）
  }
}

void RandomWalker::generateCourseList_3()
{
  // ショートカットコースに必要なTracerインスタンスをcourseList3に追加する
  if(IS_LEFT_COURSE) {                                      // ◆◆　Lコースの場合
    courseList3.push_back(new ScenarioTracer(50, 20, 20));  // ゴール方向へ直進（超低速）
    courseList3.push_back(new ScenarioTracer(50, 40, 40));  // ゴール方向へ直進（低速）
    courseList3.push_back(new ScenarioTracer(1900, 100, 100));  // ゴール方向へ直進（高速）
    courseList3.push_back(new ScenarioTracerWithLineCnt(500, 40, 40));  // ゴール方向へ直進（低速）
    courseList3.push_back(
        new ScenarioTracer(150, 0, 30));  // ゴール方向に旋回　右モーターのみ距離 動かし左 90度旋回
    courseList3.push_back(new ScenarioTracer(100, 20, 20));  // ゴール方向へ直進（超低速）
    courseList3.push_back(
        new LineTracer(1000, BRIGHTNESS_TH, 30, RIGHT_EDGE, PidGain(0.24, 0.04, 0.04)));

  } else {                                                  // ◆◆　Rコースの場合
    courseList3.push_back(new ScenarioTracer(50, 20, 20));  // ゴール方向へ直進（超低速）
    courseList3.push_back(new ScenarioTracer(50, 40, 40));  // ゴール方向へ直進（低速）
    courseList3.push_back(new ScenarioTracer(1900, 100, 100));  // ゴール方向へ直進（高速）
    courseList3.push_back(new ScenarioTracerWithLineCnt(500, 40, 40));  // ゴール方向へ直進（低速）
    courseList3.push_back(
        new ScenarioTracer(150, 30, 0));  // ゴール方向に旋回　左モーターのみ距離 動かし右 90度旋回
    courseList3.push_back(new ScenarioTracer(100, 20, 20));  // ゴール方向へ直進（超低速）
    courseList3.push_back(
        new LineTracer(1000, BRIGHTNESS_TH, 30, LEFT_EDGE, PidGain(0.24, 0.04, 0.04)));
  }
}

/**
 * 未定義状態の処理
 */
void RandomWalker::execUndefined()
{
  mState = WAITING_FOR_START;
}

/**
 * 開始待ち状態の処理
 */
void RandomWalker::execWaitingForStart()
{
  if(mStarter->isPushed()) {
    mState = COURSE_RUNNING;

    modeChangeAction();
  }
}

/**
 * ノーマルコースの走行状態の処理
 */
void RandomWalker::execCourseRunning()
{
  // int i = 1;
  for(const auto& tracer : courseList) {
    // courseListのインスタンスを順に実行していく
    tracer->run();
    // デバッグ用
    // printf("No.%d インスタンス終了\n", i++);
  }

  mState = DIFFICULT_RUNNING;
}

/**
 * 難所エリア走行状態の処理
 */
void RandomWalker::execDifficultRunning()
{
  /* TODO:
   * 難所エリア攻略に必要な走行インスタンスのリストを作ってそれのrun()を実行する。
   * やり方はノーマルコースと同様。
   */
  // int i = 1;
  for(const auto& tracer : courseList2) {
    // courseListのインスタンスを順に実行していく
    tracer->run();
    // デバッグ用
    // printf("DifficultRunning No.%d インスタンス終了\n", i++);
  }

  mState = SHORTCUT_RUNNING;
}

/**
 * ショートカット部走行状態の処理
 */
void RandomWalker::execShortcutRunning()
{
  /* TODO:
   * 難所エリア攻略に必要な走行インスタンスのリストを作ってそれのrun()を実行する。
   * やり方はノーマルコースと同様。
   */
  // int i = 1;
  for(const auto& tracer : courseList3) {
    // courseListのインスタンスを順に実行していく
    tracer->run();
    // デバッグ用
    // printf("ShortCutRunning No.%d インスタンス終了\n", i++);
  }

  mState = FINISHED;
}

void RandomWalker::execFinished()
{
  // シミュレータに終了を通知する
  Controller controller;
  controller.notifyCompleted();
}
