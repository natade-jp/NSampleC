# makefile

# マクロに代入が可能である
# $(Target), ${Target} などで呼び出し可能である。
Target = main.cpp

# フォルダ名を実行ファイル名にする
# realpath	... 絶対パス化			/test1/test2/main.cpp
# dir		... ディレクトリ抽出	/test1/test2
# subst		... 文字列の置換		test1 test2
# lastword	... 最後のワード抽出	test2
ExeName = $(lastword $(subst /, ,$(dir $(realpath $(Target)))))

# よく利用されるマクロ名
# Cコンパイラに対する引数は下記が用いられる
#  CFLAGS = XXX
# C++コンパイラに対する引数は下記が用いられる
#  CXXFLAGS = XXX
# ライブラリのフォルダに対する引数は下記が用いられる
#  LDFLAGS = -L/test/test
CXXFLAGS = -O0 -lpthread -Wall

# ターゲット名 : 依存ファイル1, 依存ファイル2, ...
# 	コマンド1(かならずタブを左に入れる)
# 	コマンド2
# 	...
$(ExeName) : $(Target)
	g++ $(CXXFLAGS) -o $(ExeName) $(Target)
# 基本的に上記のように書いていく。
# make $(ExeName) で呼び出すか、
# make と書くと最初に書いたターゲットの make が呼び出される。
# 依存ファイルが1つも更新されていなければ、コマンドは実行されない
# ターゲット名の部分は、コマンドが実行された結果作成されるファイルを書くのが基本

# 例えば、ファイルを作らないこともできる。下記のcleanはその例
# 「make clean」で呼び出すことができる。
# ただし、cleanというファイルがあると困るので、
# 防止するために、「.PHONY: clean」と記述する。
.PHONY: clean
clean :
	rm -f $(ExeName)

# マクロはすでに定義されているものがある
# 「makefile test」で表示する
.PHONY: test
test :
# @を付けるとエコーバックされないのでつける
# C コンパイラ
	@echo $(CC)
# C++ コンパイラ
	@echo $(CXX)
# 削除コマンド
	@echo $(RM)
# ターゲット名
	@echo $@
