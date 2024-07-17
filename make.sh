#!/bin/sh

# 引数の数を取得
num_args="$#"

# シミュレータのルートディレクトリに移動
cd $ETROBO_ROOT

# 引数が3つの場合
if [ "$num_args" -eq 3 ]; then
    make "$1" app=EtRobocon2023 "$2" "$3"
else
    make app=EtRobocon2023 "$@"
fi
