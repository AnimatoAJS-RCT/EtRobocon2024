#ifndef LINE_TRACER_H
#define LINE_TRACER_H

#include "Tracer.h"
#include "Mileage.h"
#include "Pid.h"

class LineTracer : public Tracer {
 public:
  /**
   * コンストラクタ
   * @param _targetDistance 目標距離 0~
   * @param _targetBrightness 目標輝度 0~100
   * @param _pwm PWM値 -100~100
   * @param _isLeftEdge エッジの左右判定(true:左エッジ, false:右エッジ)
   * @param _gain PIDゲイン
   * @param _stopColor 停止条件の色
   */
  LineTracer(double _targetDistance, int _targetBrightness, int _pwm, bool _isLeftEdge,
             const PidGain& _gain, colorid_t _stopColor = colorid_t::COLOR_NONE);

  /**
   * @brief ライントレースする
   */
  void run();

 private:
  double targetDistance;  // 目標距離 0~
  int targetBrightness;   // 目標輝度 0~100
  int pwm;                // PWM値 -100~100
  bool isLeftEdge;        // エッジの左右判定(true:左エッジ, false:右エッジ)
  PidGain gain;           // PIDゲイン
  colorid_t stopColor;    // 停止条件の色
};

#endif