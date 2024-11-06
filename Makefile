.PHONY : clean all compile

CC ?= gcc
CFLAGS = -Ilib
SRC := $(wildcard src/*.c)
HDR := $(wildcard lib/*.h)
OBJ := $(SRC:.c=.o)

TARGET = gpio

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
