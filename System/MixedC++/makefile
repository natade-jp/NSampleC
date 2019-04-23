# makefile

# 実行用
all: exe
	@echo done.

# リンクして実行ファイルを作成
exe : main.o getone.o
	gcc main.o getone.o -o exe

# C言語用でコンパイル
main.o : main.c
	gcc -O0 -Wall -c main.c

# C++言語用でコンパイル
getone.o : getone.cpp
	g++ -O0 -Wall -c getone.cpp

.PHONY: clean
clean :
	@rm -f main.o
	@rm -f getone.o
	@rm -f exe

