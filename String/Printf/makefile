# makefile

# コンパイルしたいファイル
Target = main.cpp

# フォルダ名を実行ファイル名にする
ExeName = $(lastword $(subst /, ,$(dir $(realpath $(Target)))))

$(ExeName) : $(Target)
	g++ -Wall -o $(ExeName) $(Target)

.PHONY: clean
clean :
	rm -f $(ExeName)

