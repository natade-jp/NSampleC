#!/bin/sh

# NSampleC build.sh
# 全フォルダの実行ファイルを作成する

# カレントディレクトリを記録
CURDIR=$PWD

# シェルスクリプトがおいてあるディレクトリを取得
DIRNAME=`dirname ${0}`

echo "実行ファイルを作成します。"
echo "Enterキーを入力してください"
read Wait

# ディレクトリを検索
for DIRPATH in `\find ${DIRNAME} -maxdepth 5 -type d`; do
	# ディレクトリを移動させる
	cd $CURDIR
	cd $DIRPATH
	
	#makefile があればmakeを実行する
	if [ -e makefile ]; then
		echo "make -> " ${FILEPATH}
		make
	fi
done

echo "実行ファイルの作成しました。"

# カレントディレクトリに戻す
cd $CURDIR