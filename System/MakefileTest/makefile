# makefile

# �}�N���ɑ�����\�ł���
# $(Target), ${Target} �ȂǂŌĂяo���\�ł���B
Target = main.cpp

# �t�H���_�������s�t�@�C�����ɂ���
# realpath	... ��΃p�X��			/test1/test2/main.cpp
# dir		... �f�B���N�g�����o	/test1/test2
# subst		... ������̒u��		test1 test2
# lastword	... �Ō�̃��[�h���o	test2
ExeName = $(lastword $(subst /, ,$(dir $(realpath $(Target)))))

# �悭���p�����}�N����
# C�R���p�C���ɑ΂�������͉��L���p������
#  CFLAGS = XXX
# C++�R���p�C���ɑ΂�������͉��L���p������
#  CXXFLAGS = XXX
# ���C�u�����̃t�H���_�ɑ΂�������͉��L���p������
#  LDFLAGS = -L/test/test
CXXFLAGS = -O0 -lpthread -Wall

# �^�[�Q�b�g�� : �ˑ��t�@�C��1, �ˑ��t�@�C��2, ...
# 	�R�}���h1(���Ȃ炸�^�u�����ɓ����)
# 	�R�}���h2
# 	...
$(ExeName) : $(Target)
	g++ $(CXXFLAGS) -o $(ExeName) $(Target)
# ��{�I�ɏ�L�̂悤�ɏ����Ă����B
# make $(ExeName) �ŌĂяo�����A
# make �Ə����ƍŏ��ɏ������^�[�Q�b�g�� make ���Ăяo�����B
# �ˑ��t�@�C����1���X�V����Ă��Ȃ���΁A�R�}���h�͎��s����Ȃ�
# �^�[�Q�b�g���̕����́A�R�}���h�����s���ꂽ���ʍ쐬�����t�@�C���������̂���{

# �Ⴆ�΁A�t�@�C�������Ȃ����Ƃ��ł���B���L��clean�͂��̗�
# �umake clean�v�ŌĂяo�����Ƃ��ł���B
# �������Aclean�Ƃ����t�@�C��������ƍ���̂ŁA
# �h�~���邽�߂ɁA�u.PHONY: clean�v�ƋL�q����B
.PHONY: clean
clean :
	rm -f $(ExeName)

# �}�N���͂��łɒ�`����Ă�����̂�����
# �umakefile test�v�ŕ\������
.PHONY: test
test :
# @��t����ƃG�R�[�o�b�N����Ȃ��̂ł���
# C �R���p�C��
	@echo $(CC)
# C++ �R���p�C��
	@echo $(CXX)
# �폜�R�}���h
	@echo $(RM)
# �^�[�Q�b�g��
	@echo $@