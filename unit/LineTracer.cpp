#include "LineTracer.h"
using namespace std;

LineTracer::LineTracer(double _targetDistance, int _targetBrightness, int _pwm, bool _isLeftEdge,
                       const PidGain& _gain, colorid_t _stopColor)
  : targetDistance(_targetDistance),
    targetBrightness(_targetBrightness),
    pwm(_pwm),
    isLeftEdge(_isLeftEdge),
    gain(_gain),
    stopColor(_stopColor)
{
}

void LineTracer::run()
{
  double initialDistance = 0;  // 実行前の走行距離
  double currentDistance = 0;  // 現在の走行距離
  double currentPid = 0;          // 現在のPID
  Pid pid(gain.kp, gain.ki, gain.kd, targetBrightness, 2);
  int sign = isLeftEdge ? -1 : 1;  // エッジによってPID計算の符号を変える

  // デバッグ用
  printf("LineTracer(%lf, %d, %d, %s, PidGain(%lf, %lf, %lf)): run()\n", targetDistance, targetBrightness, pwm, isLeftEdge ? "True" : "False", gain.kp, gain.ki, gain.kd);

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

  // 停止条件を満たすまで繰り返す
  // 停止条件：下記のいずれかを満たす
  //   - 走行距離が目標距離に到達する
  //   - カラーセンサーが停止条件の色を検知する
  bool termCondDist, termCondColor;
  termCondDist = abs(currentDistance - initialDistance) >= targetDistance;
  termCondColor = controller.getColorNumber() == stopColor;
  // デバッグ用
  if (termCondDist) {
    printf("LineTracer: terminated by distance: %lf.\n", targetDistance);
  }
  if (termCondColor) {
    printf("LineTracer: terminated by color: %d.\n", stopColor);
  }
  while(!termCondDist && !termCondColor) {
    currentPid = pid.calculatePid(controller.getBrightness()) * sign;

    int rightPwm, leftPwm;
    leftPwm = min(max(pwm + (int)currentPid, 0), 100);
    rightPwm = min(max(pwm - (int)currentPid, 0), 100);

    // デバッグ用
    //printf("PID: %lf, leftPwm: %d, rightPwm: %d\n", currentPid, leftPwm, rightPwm);
    // FIXME:ファイル出力すると書き込みに時間がかかりすぎて走行結果に大きく影響する（書き込みの間、設定したPWMで車輪が動き続けるため）
    //FILE* file;  // ファイルポインタを宣言
    //file = fopen("/test.txt", "a");  // ファイルをオープン(名前の指定)
    //fprintf(file, "%lf\t%lf\t%d\t%d\n", controller.getBrightness(), currentPid, leftPwm,rightPwm);  // 書き込み
    //fclose(file);       // ファイルを閉じる

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
      printf("LineTracer: terminated by distance: %lf.\n", targetDistance);
    }
    if (termCondColor) {
      printf("LineTracer: terminated by color: %d.\n", stopColor);
    }
  }

  // 両輪を停止する
  controller.stopMotor();
}
