#include "LineTracer.h"
using namespace std;

LineTracer::LineTracer(double _targetDistance, int _targetBrightness, int _pwm, bool _isLeftEdge,
                       const PidGain& _gain)
  : targetDistance(_targetDistance),
    targetBrightness(_targetBrightness),
    pwm(_pwm),
    isLeftEdge(_isLeftEdge),
    gain(_gain)
{
}

void LineTracer::run()
{
  double initialDistance = 0;  // 実行前の走行距離
  double currentDistance = 0;  // 現在の走行距離
  int currentPid = 0;          // 現在のPID
  Pid pid(gain.kp, gain.ki, gain.kd, targetBrightness);
  int sign = isLeftEdge ? -1 : 1;  // エッジによってPID計算の符号を変える

  // pwm値が0の場合は終了する
  if(pwm == 0) {
    return;
  }
  // 目標距離が0以下の場合は終了する
  if(targetDistance <= 0) {
    return;
  }

  // 初期値を格納
  initialDistance
      = Mileage::calculateMileage(controller.getRightCount(), controller.getLeftCount());
  currentDistance = initialDistance;

  // 走行距離が目標距離に到達するまで繰り返す
  while(abs(currentDistance - initialDistance) < targetDistance) {
    currentDistance
        = Mileage::calculateMileage(controller.getRightCount(), controller.getLeftCount());
    currentPid = pid.calculatePid(controller.getBrightness()) * sign;

    int rightPwm, leftPwm;
    leftPwm = max(pwm + (int)currentPid, 0);
    rightPwm = max(pwm - (int)currentPid, 0);

    // デバッグ用
    // printf("PID: %d, leftPwm: %d, rightPwm: %d\n", currentPid, leftPwm, rightPwm);

    controller.setRightPwm(rightPwm);
    controller.setLeftPwm(leftPwm);
    // 10ミリ秒待機
    controller.sleep();
  }
  // 両輪を停止する
  controller.stopMotor();
}