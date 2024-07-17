#ifndef SCENARIO_TRACER_H
#define SCENARIO_TRACER_H

#include "Tracer.h"
#include "Mileage.h"

class ScenarioTracer : public Tracer {
 public:
  /**
   * コンストラクタ
   * @param _targetDistance 目標距離 0~
   * @param _leftPwm 左モータのPWM値 -100~100
   * @param _rightPwm 右モータのPWM値 -100~100
   */
  ScenarioTracer(double _targetDistance, int _leftPwm, int _rightPwm);

  /**
   * @brief ライントレースする
   */
  void run();

 private:
  double targetDistance;  // 目標距離 0~
  int leftPwm;            // 左モータのPWM値 -100~100
  int rightPwm;           // 右モータのPWM値 -100~100
};

#endif