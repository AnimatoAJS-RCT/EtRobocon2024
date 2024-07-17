#include "Controller.h"

Controller::Controller()
  : colorSensor(PORT_2),
    sonarSensor(PORT_3),
    leftWheel(PORT_C),
    rightWheel(PORT_B),
    armMotor(PORT_A)
{
}

// 輝度を取得
// 参考: https://tomari.org/main/java/color/ccal.html
int Controller::getBrightness()
{
  // RGBモードと光センサモードを併用すると動作が悪くなるためRGBモードで取得する
  // 参考: https://qiita.com/kawanon868/items/5d52eb291c3f71af0419
  rgb_raw_t rgb = getRawColor();
  int brightness = std::max({ rgb.r, rgb.g, rgb.b }) * 100 / 255;  // 明度を取得して0-100に正規化
  return brightness;
}

// RGB値を取得
rgb_raw_t Controller::getRawColor()
{
  rgb_raw_t rgb;
  colorSensor.getRawColor(rgb);
  return rgb;
}

// 色を取得
/*int Controller::getColorNumber()
{
  int color;
  color = colorSensor.getColorNumber;
  return color;
}*/

// 左モータ角位置取得
int Controller::getLeftCount()
{
  return leftWheel.getCount();
}

// 右モータ角位置取得
int Controller::getRightCount()
{
  return rightWheel.getCount();
}

// 右モータのPWM値をセット
void Controller::setRightPwm(const int pwm)
{
  rightWheel.setPWM(limitPwmValue(pwm));
}

// 左モータのPWM値をセット
void Controller::setLeftPwm(const int pwm)
{
  leftWheel.setPWM(limitPwmValue(pwm));
}

// タイヤのモータを停止する
void Controller::stopMotor()
{
  leftWheel.stop();
  rightWheel.stop();
}

// 自タスクスリープ（デフォルトは10ミリ秒）
void Controller::sleep(int milliSec)
{
  // clock.sleep()はマイクロ秒指定なので，単位を合わせて呼び出す
  clock.sleep(milliSec * 1000);
}

int Controller::limitPwmValue(const int value)
{
  if(value > MAX_PWM) {
    return MAX_PWM;
  } else if(value < MIN_PWM) {
    return MIN_PWM;
  }
  return value;
}

void Controller::notifyCompleted()
{
  ETRoboc_notifyCompletedToSimulator();
}

// added T.Takahashi
int Controller::getSSDistance()
{
  return sonarSensor.getDistance();
}