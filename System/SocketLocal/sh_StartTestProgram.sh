#!/bin/sh

unlink /tmp/local_socket_test

echo "Enterキーを入力するとテストが始まります。"
echo "※テストが終わるまでCtrl+C 入力禁止"
read Wait

echo "サーバーを起動させます"
./SocketLocal -s &
echo "クライアントを起動させます"
./SocketLocal -c &

echo "Enterキーを入力すると終了します。"
read Wait

killall SocketLocal
