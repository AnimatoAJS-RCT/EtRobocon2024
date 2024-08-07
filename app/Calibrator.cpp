#include "Calibrator.h"

Calibrator::Calibrator()
  : isLeftCourse(true), targetBrightness(100 / 2)
{
}

void Calibrator::run()
{
  // 左右ボタンでコースのLRを選択する
  selectCourse();

  // 黒と白の輝度を測定して目標輝度を求める
  measureTargetBrightness();

  // スタート合図が出るまで待機する
  waitForStart();
}


void Calibrator::selectCourse()
{
  bool _isLeftCourse = true;

  printf("コース選択");
  printf(">> Left Course");

  // 中央ボタンが押されたら確定する
  while(!controller.getEnterButton()) {
    // 左ボタンが押されたらLコースをセットする
    if(controller.getLeftButton() && !_isLeftCourse) {
      _isLeftCourse = true;
      printf(">> Left Course");
    }

    // 右ボタンが押されたらRコースをセットする
    if(controller.getRightButton() && _isLeftCourse) {
      _isLeftCourse = false;
      printf(">> Right Course");
    }

    controller.sleep();  // 10ミリ秒スリープ
  }

  isLeftCourse = _isLeftCourse;
  const char* COURSE = isLeftCourse ? "Left" : "Right";
  printf("\n%s Courseを走行します\n", COURSE);

  controller.sleep(1000);  // 1秒スリープ
}

void Calibrator::measureTargetBrightness()
{
  // 黒と白の輝度
  // TODO: 初期化の値は適当な値にしているため適切なものに置き換える
  int blackBrightness = 0;
  int whiteBrightness = 100;

  // 黒の上で中央ボタンを押して黒の輝度を取得する
  printf("黒線の上で中央ボタンを押してください\n");
  // 中央ボタンが押されるまで待機
  while(!controller.getEnterButton()) {
    controller.sleep();  // 10ミリ秒スリープ
  }
  blackBrightness = controller.getBrightness(); // 黒の輝度値を取得
  printf(">>黒の輝度値: %d\n", blackBrightness);
  controller.sleep(1000);  // 1秒スリープ

  // 白の上で中央ボタンを押して白の輝度を取得する
  printf("白線の上で中央ボタンを押してください\n");
  // 中央ボタンが押されるまで待機
  while(!controller.getEnterButton()) {
    controller.sleep();  // 10ミリ秒スリープ
  }
  whiteBrightness = controller.getBrightness(); // 白の輝度値を取得
  printf(">>白の輝度値: %d\n", whiteBrightness);
  controller.sleep(1000);  // 1秒スリープ

  // 黒と白の平均値を目標輝度とする
  targetBrightness = (whiteBrightness + blackBrightness) / 2;
  printf("\n目標輝度値: %d\n", targetBrightness);
}

void Calibrator::waitForStart()
{
  constexpr int startDistance = 5;  // 手などでスタート合図を出す距離[cm]

  // startDistance以内の距離に物体がない間待機する
  while(controller.getSSDistance() > startDistance) {
    controller.sleep();  // 10ミリ秒スリープ
  }
}

bool Calibrator::getIsLeftCourse()
{
  return isLeftCourse;
}

int Calibrator::getTargetBrightness()
{
  return targetBrightness;
}