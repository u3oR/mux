#ifndef MAIN_H
#define MAIN_H

/**************************************
 * 包含头文件
 **************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cJSON.h"

/**************************************
 * 宏开关
 **************************************/


/**************************************
 * 宏定义常量
 **************************************/

#define VERSION_MAJOR 0
#define VERSION_MINOR 1

/**************************************
 * 结构体定义
 **************************************/

/**************************************
 * 全局变量
 **************************************/
extern const char *FAULT_S;
extern const char *NOTE_S;

extern const char *DEFAULT_CONFIG_FILE;

extern cJSON* setting_json;
/**************************************
 * 函数声明 / 宏函数
 **************************************/

#if defined(__WIN64__) || defined(__WIN32__)
	#include <windows.h>
	#define set_cmd_utf8() SetConsoleCP(CP_UTF8);SetConsoleOutputCP(CP_UTF8)
#elif defined(__linux__)
	#define set_cmd_utf8() 
#endif


#define is_str_same(str1, str2) (strcmp(str1, str2) == 0)

int run_main(int argc, char const *argv[]);
int info_main(int argc, char const *argv[]);
int clean_main(int argc, char const *argv[]);
int create_main(int argc, char const *argv[]);


#endif
