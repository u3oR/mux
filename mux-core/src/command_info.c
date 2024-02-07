
/**************************************
 * 头文件包含
 **************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>

#include "main.h"
#include "json.h"
/**************************************
 * 宏定义
 **************************************/


/**************************************
 * 私有类型
 **************************************/


/**************************************
 * 全局变量
 **************************************/
const char *INFO_HELP_CONTENT = "This is a info help";

static struct option INFO_OPTION_TABLE[] = {
	{"help", 		no_argument, 		NULL,	'h'},
	{"envs",		no_argument,	    NULL,	'e'},
	{0,				0, 					0,		 0 }
};

static char *INFO_OPTION_STRING = "he:";

/**************************************
 * 私有函数 / 宏函数
 **************************************/
#define print_info_help() printf("%s\n", INFO_HELP_CONTENT)
/**************************************
 * 程序入口
 **************************************/

int info_main(int argc, char const *argv[])
{

    if(argc < 2){
        print_info_help();
        goto finished;
    }

    int opt_code = 0;
	int opt_index = 0;

	#define getopts() getopt_long( \
						argc, \
						(char * const*)argv, \
						INFO_OPTION_STRING, \
						INFO_OPTION_TABLE, \
						&opt_index)

	while ((opt_code = getopts()) != EOF) 
	{
		switch (opt_code) 
		{
			case 'h':
                print_info_help();
				goto finished;
				break;
			case 'e':
				json_print_env(setting_json, optarg);
				goto finished;
				break;
			default:
				break;
		}
	}

	#undef getopts

finished :
    return 0;
}


/* END */
