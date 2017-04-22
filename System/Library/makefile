# makefile

# ���s�p
all: exe_a exe_so
	@echo done.

# ���L���C�u�����i���I���C�u�����j���g�p���ăR���p�C��
exe_so : main.cpp libgetone_so.so
	g++ -O0 -Wall -o exe_so main.cpp -L./ -lgetone_so

# �ÓI���C�u�������g�p���ăR���p�C��
exe_a : main.cpp libgetone_a.a
	g++ -O0 -Wall -o exe_a main.cpp -L./ -lgetone_a

# �ÓI���C�u�����́Ao�t�@�C�����A�[�J�C�u���������̂ł���
libgetone_a.a : getone.o
	ar r libgetone_a.a getone.o

# ���L���C�u�����i���I���C�u�����j�́A0�t�@�C���� -shared ��t����΍쐬�ł���
libgetone_so.so : getone.o
	g++ -shared getone.o -o libgetone_so.so

# �R���p�C�������āA�I�u�W�F�N�g�t�@�C�����쐬����
getone.o : getone.cpp
	g++ -O0 -Wall -fPIC getone.cpp -c

.PHONY: clean
clean :
	@rm -f getone.o
	@rm -f libgetone_so.so
	@rm -f libgetone_a.a
	@rm -f exe_a
	@rm -f exe_so
