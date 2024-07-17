#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ColorSensor.h"
#include "SonarSensor.h"
#include "Motor.h"
#include "Clock.h"
#include "etroboc_ext.h"
#include <algorithm>

class Controller {
 public:
  static const int MAX_PWM = 100;
  static const int MIN_PWM = -100;

  /**
   * コンストラクタ
   */
  Controller();

  /**
   * 輝度を取得
   * @return 反射光の強さ(0-100)
   */
  int getBrightness();

  /**
   * RGB値を取得
   * @return RGB値
   */
  rgb_raw_t getRawColor();

  /**
   * 左モータ角位置取得
   * @return 左モータ角位置[deg]
   */
  int getLeftCount();

  /**
   * 右モータ角位置取得
   * @return 右モータ角位置[deg]
   */
  int getRightCount();

  /**
   * 右モータのPWM値をセット
   */
  void setRightPwm(const int pwm);

  /**
   * 左モータのPWM値をセット
   */
  void setLeftPwm(const int pwm);

  /**
   * アームのモータを停止する
   */
  void stopMotor();

  /**
   * 自タスクスリープ（デフォルトは10ミリ秒）
   * @param milliSec スリープ時間(ミリ秒)
   */
  void sleep(int milliSec = 10);

  /**
   * シミュレータに競技終了の通知をする
   */
  void notifyCompleted();

// added T.Takahashi
  int getSSDistance();
  
 private:
  ev3api::ColorSensor colorSensor;
  ev3api::SonarSensor sonarSensor;
  ev3api::Motor leftWheel;
  ev3api::Motor rightWheel;
  ev3api::Motor armMotor;
  ev3api::Clock clock;

  /**
   * 入力されたPWM値を制約内のPWM値に直す
   * @param value 入力されたPWM値
   * @return 制約内のPWM値
   */
  int limitPwmValue(const int value);
};

#endif