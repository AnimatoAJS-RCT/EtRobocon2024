/******************************************************************************
 *  DifficultScenarioTracer.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2023/09/23
 *  Definition of the Class DifficultScenarioTracer
 *  Author: Toshiyuki Takahashi
 *  Copyright (c) 2023 AJS Inc.
 *****************************************************************************/
#ifndef DIFFICULTSCENARIOTRACER_H
#define DIFFICULTSCENARIOTRACER_H

#include "ScenarioTracer.h"
#include "Tracer.h"

class DifficultScenarioTracer : public Tracer {
 public:
  /**
   * コンストラクタ
   */
  /**
   * コンストラクタ
   * @param _wallDistance ブロックを置く場所の壁までの目標距離 0～
   * @param _targetDistance 目標距離 0~
   * @param _leftPwm 左モータのPWM値 -100~100
   * @param _rightPwm 右モータのPWM値 -100~100
   */
  DifficultScenarioTracer(int _wallDistance, double _targetDistance, int _leftPwm, int _rightPwm);

  /**
   * @brief 走行する抽象メソッド
   */
  void run();

 private:
  int wallDistance;       // ブロックを置く場所の壁までの目標距離 0～
  double targetDistance;  // 目標距離 0~
  int leftPwm;            // 左モータのPWM値 -100~100
  int rightPwm;           // 右モータのPWM値 -100~100
};

#endif