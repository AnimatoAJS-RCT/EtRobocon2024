#include "Pid.h"
#include <cstdio>
#include <numeric>

PidGain::PidGain(double _kp, double _ki, double _kd) : kp(_kp), ki(_ki), kd(_kd) {}

Pid::Pid(double _kp, double _ki, double _kd, double _targetValue, unsigned int _differenceRange)
  : gain(_kp, _ki, _kd), integral(0.0), targetValue(_targetValue), differenceRange(_differenceRange)
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
  //過去偏差数を超過する偏差の履歴を消す
  while (pastDeviations.size() > differenceRange) {
    pastDeviations.erase(pastDeviations.begin());
  }
  //今回の偏差を履歴に追加
  pastDeviations.push_back(currentDeviation);
  //偏差の履歴をもとに微分
  double difference;
  if (pastDeviations.size() <= differenceRange) {
    // 偏差の履歴の数が微分するのに足りない場合：D制御は0とする
    difference = 0;
  } else {
    // 偏差の履歴の数が微分するのに足りる場合：微分する
    double sum = std::accumulate(pastDeviations.begin(), pastDeviations.end(), 0.0);
    double ave = sum / (int)pastDeviations.size();
    difference = (ave - pastDeviations[0]) * ((int)pastDeviations.size() - 1) / 2 / delta;
  }

  // P制御の計算を行う
  double p = gain.kp * currentDeviation;
  // I制御の計算を行う
  double i = gain.ki * integral;
  // D制御の計算を行う
  double d = gain.kd * difference;

  // デバッグ用
  //printf("%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", targetValue,currentValue,currentDeviation,integral,difference,p,i,d,(p+i+d));
  //printf("CV: %lf, PID: %lf\n", currentValue, (p+i+d));
  // FIXME:ファイル出力すると書き込みに時間がかかりすぎて走行結果に大きく影響する（書き込みの間、設定したPWMで車輪が動き続けるため）
  //FILE *file;//ファイルポインタを宣言
  //file=fopen("/pid.csv","a");//ファイルをオープン(名前の指定)
  //fprintf(file,"%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", targetValue,currentValue,currentDeviation,integral,difference,p,i,d,(p+i+d));//書き込み
  //fclose(file);//ファイルを閉じる

  //操作量 = P制御 + I制御 + D制御
  return (p + i + d);
}