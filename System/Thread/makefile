# makefile

# コンパイルしたいファイル
Target = main.cpp

# フォルダ名を実行ファイル名にする
ExeName = $(lastword $(subst /, ,$(dir $(realpath $(Target)))))

# C++0x の機能の thread を使用しているが、pthread ライブラリを付けないとエラーが発生する
# pi@raspberrypi:~/git/NSampleC/System/Threads $ make
# g++ -O0 -std=c++0x -Wall -o Threads main.cpp
# /tmp/cc5skISF.o: 関数 `std::thread::thread<void* (&)(void*), Thread*>(void* (&)(void*), Thread*&&)' 内:
# main.cpp:(.text._ZNSt6threadC2IRFPvS1_EIP6ThreadEEEOT_DpOT0_[_ZNSt6threadC5IRFPvS1_EIP6ThreadEEEOT_DpOT0_]+0xd4): `pthread_create' に対する定義されていない参照 です
# collect2: error: ld returned 1 exit status
# makefile:10: recipe for target 'Threads' failed
# make: *** [Threads] Error 1

$(ExeName) : $(Target)
	g++ -O0 -lpthread -std=c++0x -Wall -o $(ExeName) $(Target)

.PHONY: clean
clean :
	rm -f $(ExeName)

