# makefile

# 実行用
all: exe_a exe_so
	@echo done.

# 共有ライブラリ（動的ライブラリ）を使用してコンパイル
exe_so : main.cpp libgetone_so.so
	g++ -O0 -Wall -o exe_so main.cpp -L./ -lgetone_so

# 静的ライブラリを使用してコンパイル
exe_a : main.cpp libgetone_a.a
	g++ -O0 -Wall -o exe_a main.cpp -L./ -lgetone_a

# 静的ライブラリは、oファイルをアーカイブ化したものである
libgetone_a.a : getone.o
	ar r libgetone_a.a getone.o

# 共有ライブラリ（動的ライブラリ）は、0ファイルに -shared を付ければ作成できる
libgetone_so.so : getone.o
	g++ -shared getone.o -o libgetone_so.so

# コンパイルをして、オブジェクトファイルを作成する
getone.o : getone.cpp
	g++ -O0 -Wall -fPIC getone.cpp -c

.PHONY: clean
clean :
	@rm -f getone.o
	@rm -f libgetone_so.so
	@rm -f libgetone_a.a
	@rm -f exe_a
	@rm -f exe_so

