#include "Pid.h"

PidGain::PidGain(double _kp, double _ki, double _kd) : kp(_kp), ki(_ki), kd(_kd) {}

Pid::Pid(double _kp, double _ki, double _kd, double _targetValue)
  : gain(_kp, _ki, _kd), preDeviation(0.0), integral(0.0), targetValue(_targetValue)
{
}

double Pid::calculatePid(double currentValue, double delta)
{
  // 0除算を避けるために0の場合はデフォルト周期0.01とする
  if(delta == 0) delta = 0.01;
  //現在の偏差を求める
  double currentDeviation = targetValue - currentValue;
  //積分の処理を行う
  integral += currentDeviation * delta;
  //微分の処理を行う
  double difference = (currentDeviation - preDeviation) / delta;
  //前回の偏差を更新する
  preDeviation = currentDeviation;

  // P制御の計算を行う
  double p = gain.kp * currentDeviation;
  // I制御の計算を行う
  double i = gain.ki * integral;
  // D制御の計算を行う
  double d = gain.kd * difference;

  //操作量 = P制御 + I制御 + D制御
  return (p + i + d);
}