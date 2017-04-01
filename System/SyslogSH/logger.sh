#!/bin/sh

# syslog の設定ファイルの場所は、次のうちのどちらか
# /etc/syslog.conf, /etc/rsyslog.conf
LOGSETTINGFILE=/etc/rsyslog.conf
echo "settings = " $LOGSETTINGFILE

# (/\w+)+/messages のワードを調べて、ファイルパスを調べる
# o ... マッチする部分を調べる
# e ... 正規表現を使用する
LOGFILE=`cat $LOGSETTINGFILE | grep -oe "\(/\w\+\)\+/messages"`
echo "logfile = " $LOGFILE

# バックグラウンドでログファイルを表示させる
tail -f $LOGFILE &

# ログファイルを書き込みする
# -p syslog.info 優先度の設定 (info のほかにも、debug や err 等がある)
# -t タグ名をともに記録する
logger -p syslog.info -t APPLICATION_NAME "data"

# 少し待つ
sleep 1

#終了
killall tail