# makefile

# コンパイルしたいファイル
Target = main.cpp

# フォルダ名を実行ファイル名にする
ExeName = $(lastword $(subst /, ,$(dir $(realpath $(Target)))))

$(ExeName) : $(Target)
	g++ -std=c++0x -Wall -o $(ExeName) $(Target)

.PHONY: clean
clean :
	rm -f $(ExeName)

