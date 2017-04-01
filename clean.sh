#!/bin/sh

# NSampleC clean.sh
# 全フォルダの実行ファイルを削除する

# カレントディレクトリを記録
CURDIR=$PWD

# シェルスクリプトがおいてあるディレクトリを取得
DIRNAME=`dirname ${0}`

echo "実行ファイルを削除します。"
echo "Enterキーを入力してください"
read Wait

# ディレクトリ内のファイルを洗い出す
for FILEPATH in `\find ${DIRNAME} -maxdepth 5 -type f`; do
	# ディレクトリを移動させる
	cd $CURDIR
	cd $DIRPATH
	
	#makefile があればmake cleanを実行する
	if [ -e makefile ]; then
		echo "clean -> " ${FILEPATH}
		make clean
	fi

#	# ファイルの形式が実行ファイルかどうかを確認する
#	RESULT=`file ${FILEPATH} | grep ": ELF"`
#	# 長さが0でなければ、実行ファイルなので削除する
#	RESULTLEN=${#RESULT}
#	if [ ${RESULTLEN} != "0" ]; then
#		echo "delete -> " ${FILEPATH}
#		rm ${FILEPATH}
#	fi
done

echo "実行ファイルの削除完了しました。"

# カレントディレクトリに戻す
cd $CURDIR
