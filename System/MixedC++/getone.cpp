#include "getone.h"

// 「extern "C"」をつけることで、関数名をC言語用にする
// 付けない場合は、C++の機能で余計な関数名になる場合があり、
// この場合、コンパイル後の*.oファイルを、C言語上でリンクできない可能性がある

extern "C" int getone( void ) {
	return 1;
}
