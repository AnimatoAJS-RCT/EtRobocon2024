#include "ScenarioTracerWithLineCnt.h"
using namespace std;

ScenarioTracerWithLineCnt::ScenarioTracerWithLineCnt(double _targetDistance, int _leftPwm,
                                                     int _rightPwm)
  : targetDistance(_targetDistance), leftPwm(_leftPwm), rightPwm(_rightPwm)
{
}

void ScenarioTracerWithLineCnt::run()
{
  double initialDistance = 0;  // 実行前の走行距離
  double currentDistance = 0;  // 現在の走行距離

  // 両輪のpwm値が0の場合は終了する
  if(leftPwm == 0 && rightPwm == 0) {
    return;
  }
  // 目標距離が0以下の場合は終了する
  if(targetDistance <= 0) {
    return;
  }
  printf("★カラー分岐待ち R<100\n");

  // 初期値を格納
  initialDistance
      = Mileage::calculateMileage(controller.getRightCount(), controller.getLeftCount());
  currentDistance = initialDistance;

  // 走行距離が目標距離に到達するまで繰り返す
  while(abs(currentDistance - initialDistance) < targetDistance) {
    currentDistance
        = Mileage::calculateMileage(controller.getRightCount(), controller.getLeftCount());
    controller.setRightPwm(rightPwm);
    controller.setLeftPwm(leftPwm);
    // 10ミリ秒待機
    controller.sleep();
    rgb_raw_t rgb = controller.getRawColor();
    printf("★R:%d, G:%d, B:%d\n", rgb.r, rgb.g, rgb.b);
    if(rgb.r < 110) {
      printf("カラー分岐\n");
      break;
    }
  }
  // 両輪を停止する
  controller.stopMotor();
}