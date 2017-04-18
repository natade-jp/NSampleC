#!/bin/sh

# カレントディレクトリを記録
CURDIR=$PWD

# シェルスクリプトがおいてあるディレクトリを取得
DIRNAME=`dirname ${0}`
cd $DIRNAME
DIRNAME=`pwd`

# 一度キレイにしてからコンパイル
echo "コンパイルします。"
make clean
make
sleep 1

# 静的リンクしたものは、普通に実行できる
echo "静的リンクしたソフトを実行します。"
./exe_a
sleep 1

# 動的リンクしたものは、エラーが出るはず
# ./exe_so: error while loading shared libraries:
# libgetone_so.so: cannot open shared object file: No such file or directory
echo "動的リンクしたソフトを実行します。"
./exe_so
sleep 1

# 理由は、下記のコマンドを実行するとわかる
echo "動的リンクしたソフトが必要なライブラリを表示します。"
ldd ./exe_so
sleep 1

#$ ldd exe_so
#        linux-vdso.so.1 (0x7ee47000)
#        /usr/lib/arm-linux-gnueabihf/libarmmem.so (0x76fad000)
#        libgetone_so.so => not found
#        libstdc++.so.6 => /usr/lib/arm-linux-gnueabihf/libstdc++.so.6 (0x76ebe000)
#        libm.so.6 => /lib/arm-linux-gnueabihf/libm.so.6 (0x76e43000)
#        libgcc_s.so.1 => /lib/arm-linux-gnueabihf/libgcc_s.so.1 (0x76e16000)
#        libc.so.6 => /lib/arm-linux-gnueabihf/libc.so.6 (0x76cd5000)
#        /lib/ld-linux-armhf.so.3 (0x54b00000)

# つまり、共有ライブラリを置く場所がきまっており、その場所におかないといけない。
# 共有ライブラリは下記の場所におく
echo "共用ライブラリは下記のディレクトリを見に行きます。"
cat /etc/ld.so.conf
sleep 1

# おそらく、「/usr/local/lib」などが書いてあると思う。つまりそこにおけばいい。
# あるいは、環境変数 LD_LIBRARY_PATH ライブラリが書いてあるパスを通す
# ただし、LD_LIBRARY_PATH は一時的なものになる

# 以下、環境変数に通すスクリプト
echo "環境変数に追加します。"
RESULT=`echo $LD_LIBRARY_PATH | grep "$DIRNAME"`
RESULTLEN=${#RESULT}
if [ ${RESULTLEN} = "0" ]; then
	echo $DIRNAME "を追加します。"
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DIRNAME
	echo $LD_LIBRARY_PATH
else
	echo "すでに追加されています。"
	echo $LD_LIBRARY_PATH
fi

# 2度目は実行可能である
echo "動的リンクしたソフトを実行します。"
./exe_so

# カレントディレクトリに戻す
cd $CURDIR
