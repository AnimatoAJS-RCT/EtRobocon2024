#include "ScenarioTracer.h"
using namespace std;

ScenarioTracer::ScenarioTracer(double _targetDistance, int _leftPwm, int _rightPwm, colorid_t _stopColor)
  : targetDistance(_targetDistance), leftPwm(_leftPwm), rightPwm(_rightPwm), stopColor(_stopColor)
{
}

void ScenarioTracer::run()
{
  double initialDistance = 0;  // 実行前の走行距離
  double currentDistance = 0;  // 現在の走行距離

  // デバッグ用
  printf("ScenarioTracer(%lf, %d, %d): run()\n", targetDistance, leftPwm, rightPwm);

  // 両輪のpwm値が0の場合は終了する
  if(leftPwm == 0 && rightPwm == 0) {
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

  // 停止条件を満たすまで繰り返す
  // 停止条件：下記のいずれかを満たす
  //   - 走行距離が目標距離に到達する
  //   - カラーセンサーが停止条件の色を検知する
  bool termCondDist, termCondColor;
  termCondDist = abs(currentDistance - initialDistance) >= targetDistance;
  termCondColor = controller.getColorNumber() == stopColor;
  // デバッグ用
  if (termCondDist) {
    printf("ScenarioTracer: terminated by distance: %lf.\n", targetDistance);
  }
  if (termCondColor) {
    printf("ScenarioTracer: terminated by color: %d.\n", stopColor);
  }
  while(!termCondDist && !termCondColor) {
    controller.setRightPwm(rightPwm);
    controller.setLeftPwm(leftPwm);
    // 10ミリ秒待機
    controller.sleep();
    
    // 停止条件を判定
    currentDistance
        = Mileage::calculateMileage(controller.getRightCount(), controller.getLeftCount());
    termCondDist = abs(currentDistance - initialDistance) >= targetDistance;
    termCondColor = controller.getColorNumber() == stopColor;
    // デバッグ用
    if (termCondDist) {
      printf("ScenarioTracer: terminated by distance: %lf.\n", targetDistance);
    }
    if (termCondColor) {
      printf("ScenarioTracer: terminated by color: %d.\n", stopColor);
    }
  }
  // 両輪を停止する
  controller.stopMotor();
}