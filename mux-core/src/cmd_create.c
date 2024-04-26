
/**************************************
 * 头文件包含
 **************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "main.h"
/**************************************
 * 宏定义
 **************************************/


/**************************************
 * 私有类型
 **************************************/


/**************************************
 * 全局变量
 **************************************/
const char *CREATE_HELP_CONTENT = "This is a create help";

static struct option CREATE_OPTION_TABLE[] = {
	{"help", 		no_argument, 		NULL,	'h'},
	{"name",		required_argument,	NULL,	'n'},
    {"ext_path",	required_argument,	NULL,	'd'},
    {"dat_path",	required_argument,	NULL,	'e'},
	{0,				0, 					0,		 0 }
};

static char *CREATE_OPTION_STRING = "hnd:e:";


/**************************************
 * 私有函数 / 宏函数
 **************************************/

/**************************************
 * 程序入口
 **************************************/

int create_main(int argc, char const *argv[])
{
    int opt_code = 0;
	int opt_index = 0;

	#define getopts() getopt_long( \
                        argc, \
                        (char * const*)argv, \
						CREATE_OPTION_STRING, \
                        CREATE_OPTION_TABLE, \
                        &opt_index)

	while ((opt_code = getopts()) != EOF) 
	{
		switch (opt_code) 
		{
			case 'h':
                printf("%s\n", CREATE_HELP_CONTENT);
				goto finished;
				break;
			case 'n':

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
