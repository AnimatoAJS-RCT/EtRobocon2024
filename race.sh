#!/bin/sh

# 提出用ファイルを作成するスクリプト
# ./race.sh left/right のように使用する
cd $ETROBO_ROOT
make $@ sim up
# make import sim upをしていない場合ここで実行する（変更しない限り、一度実行すればok）
race zip $@ EtRobocon2023