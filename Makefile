.PHONY : clean all compile

# 컴파일러 설정
# 크로스 컴파일 사용시 아래코드 주석해제
CC := aarch64-linux-gnu-gcc
# 일반 host 컴퓨터에서 사용시 아래 코드 주석해제
#CC := gcc

CFLAGS = -Ilib
SRC := $(wildcard src/*.c)
HDR := $(wildcard lib/*.h)
OBJ := $(SRC:.c=.o)

# 실행파일 이름 설정
TARGET = test

# all 타겟에서 clean과 compile을 순서대로 실행
all: clean compile

# compile 타겟은 $(TARGET) 빌드를 수행
compile: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

# .o 파일과 실행 파일을 삭제하는 clean 타겟
clean:
	rm -f $(OBJ) $(TARGET)
