
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
const char *CLEAN_HELP_CONTENT = "This is a info help";

static struct option CLEAN_OPTION_TABLE[] = {
	{"help", 		no_argument, 		NULL,	'h'},
	{"env",			required_argument,  NULL,	'e'},
	{0,				0, 					0,		 0 }
};

static char *CLEAN_OPTION_STRING = "he:";

/**************************************
 * 私有函数 / 宏函数
 **************************************/
#define print_clean_help() printf("%s\n", CLEAN_HELP_CONTENT)
/**************************************
 * 程序入口
 **************************************/

int clean_main(int argc, char const *argv[])
{

    if(argc < 2){
        print_clean_help();
        goto finished;
    }

    int opt_code = 0;
	int opt_index = 0;

	#define getopts() getopt_long( \
                        argc, \
                        (char * const*)argv, \
						CLEAN_OPTION_STRING, \
                        CLEAN_OPTION_TABLE, \
                        &opt_index)

	while ((opt_code = getopts()) != EOF) 
	{
		switch (opt_code) 
		{
			case 'h':
                print_clean_help();
				goto finished;
			case 'e':
                json_del_env(setting_json, optarg);
				json_print_env(setting_json, "all");
				break;
			default:
				break;
		}
	}

finished:
    return 0;
}


/* END */
