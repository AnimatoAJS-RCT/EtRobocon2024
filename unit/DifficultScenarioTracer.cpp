/******************************************************************************
 *  DifficultScenarioTracer.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2023/09/23
 *  Definition of the Class DifficultScenarioTracer
 *  Author: Toshiyuki Takahashi
 *  Copyright (c) 2023 AJS Inc.
 *****************************************************************************/
#include "DifficultScenarioTracer.h"
using namespace std;

DifficultScenarioTracer::DifficultScenarioTracer(int _wallDistance, double _targetDistance,
                                                 int _leftPwm, int _rightPwm)
  : wallDistance(_wallDistance),
    targetDistance(_targetDistance),
    leftPwm(_leftPwm),
    rightPwm(_rightPwm)
{
}

void DifficultScenarioTracer::run()
{
  int distance = 255;  // 計測した距離　格納用

  // 壁との距離が　wall_distance以内に近づくまで、前進フェーズ
  while(distance > wallDistance) {
    // 距離を測定して表示し続ける
    // 反射値を測って変数に格納
    Controller controller;
    // 文字配列に読み取った値を格納する
    distance = controller.getSSDistance();
    // デバッグ用
    printf("DISTANCE:%d\n", distance);
    // 移動
    ScenarioTracer st(targetDistance, leftPwm, rightPwm);
    st.run();
  }
}