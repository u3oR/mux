# ################################################
#                      工程
# ################################################
TARGET = mux-core

# 构建目录
BUILD_DIR = build

GCC_PATH := C:/mingw64-posix/bin/

CC := $(GCC_PATH)/gcc
LD := $(GCC_PATH)/gcc

# ################################################
#                    源文件
# ################################################

INCLUDE_DIRS = \
	-Ilib/cJSON

SOURCES = \
	test.c \
	main.c \
	json.c \
	command_run.c \
	command_info.c \
	command_clean.c \
	command_create.c \
	lib/cJSON/cJSON.c 


# ################################################
#                  构建可执行文件
# ################################################

BUILD_FLAG := MUX_MAIN
# BUILD_FLAG := MUX_TEST

CFLAGS  = $(INCLUDE_DIRS) -Wall -Wextra -g -D$(BUILD_FLAG)

# LDFLAGS = 


vpath %.c $(sort $(dir $(SOURCES)))

# list of objects
OBJECTS  =  $(addprefix $(BUILD_DIR)/,$(notdir $(SOURCES:.c=.o)))


$(BUILD_DIR)/%.o: %.c   Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS)  $< -o $@


$(TARGET): $(OBJECTS) Makefile
	$(LD) $(OBJECTS) $(LDFLAGS) -o $@

$(BUILD_DIR):
	mkdir $@	

#######################################
# 命令
#######################################

all: $(TARGET)

.PHONY : clean
clean:
	del /Q /F $(BUILD_DIR)
	del /Q /F $(TARGET).exe
# -rm -fR $(BUILD_DIR)

test:


# *** EOF ***