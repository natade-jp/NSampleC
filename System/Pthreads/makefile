# makefile

# コンパイルしたいファイル
Target = main.cpp

# フォルダ名を実行ファイル名にする
ExeName = $(lastword $(subst /, ,$(dir $(realpath $(Target)))))

# lpthread を付けないとエラーが発生する
# g++ -O0 -Wall -o Thread main.cpp
# /tmp/ccW8MKoE.o: 関数 `Thread::iMakeThread()' 内:
# main.cpp:(.text._ZN6Thread11iMakeThreadEv[_ZN6Thread11iMakeThreadEv]+0x30): `pthread_create' に対する定義されていない参照です
# /tmp/ccW8MKoE.o: 関数 `Thread::stop()' 内:
# main.cpp:(.text._ZN6Thread4stopEv[_ZN6Thread4stopEv]+0x88): `pthread_join' に対する定義されていない参照です
# collect2: error: ld returned 1 exit status
# makefile:10: recipe for target 'Thread' failed

$(ExeName) : $(Target)
	g++ -O0 -lpthread -Wall -o $(ExeName) $(Target)

.PHONY: clean
clean :
	rm -f $(ExeName)

