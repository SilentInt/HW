CC = gcc
LD = gcc
#SRCS = $(wildcard *.c)
OBJS = $(patsubst %c, %o, $(SRCS))
# -I指定头文件目录
INCLUDE = -I./include
# -L指定库文件目录，-l指定静态库名字(去掉文件名中的lib前缀和.a后缀)
LIB = -L./libs -lm
# 设置优化等级
CFLAGS =  -O2

TARGET = main

.PHONY:all clean

all: $(TARGET)
# 链接时候指定库文件目录及库文件名
$(TARGET): $(OBJS)
	$(LD) -o $@ $^ $(LIB)
 
# 编译时候指定头文件目录
%.o:%.c
	$(CC) -c $^ $(INCLUDE) $(CFLAGS) 

clean:
	rm -f $(OBJS) $(TARGET)
 
run: all
	./$(TARGET) 

runtb: all
	./$(TARGET) < $(TB)
