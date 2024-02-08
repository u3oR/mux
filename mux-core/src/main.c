

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
#include "cJSON.h"
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

const char *FAULT_S = "FAULT";
const char *NOTE_S = "3oR";

const char *DEFAULT_CONFIG_FILE = "_settings.json";

struct {
	const char *name;
	
	enum COMMAND_ID
	{
		CMD_RUN = 0,
		CMD_INFO,
		CMD_INIT,
		CMD_CLEAN,
		CMD_CREATE,
		CMD_NONE,
	} id;
} COMMAND_TABLE[] = {
	{"run", CMD_RUN},
	{"info", CMD_INFO},
	{"init", CMD_INIT},
	{"clean", CMD_CLEAN},
	{"create", CMD_CREATE},
	{"none", CMD_NONE}
};

cJSON *setting_json = NULL;

const char *MAIN_HELP_CONTENT = "This is main help\n";

static struct option MAIN_OPTION_TABLE[] = {
	{"help", 		no_argument, 		NULL,	'h'},
	{"version",		no_argument,		NULL,	'v'},
	{0,				0, 					0,		 0 }
};
static char *MAIN_OPTION_STRING = "hv";

/**************************************
 * 私有函数 / 私有宏函数
 **************************************/

#define print_main_help() printf(MAIN_HELP_CONTENT)


static inline 
enum COMMAND_ID get_command_id(const char *cmd_name)
{
	int i = 0;

	for (i = 0; COMMAND_TABLE[i].id != CMD_NONE; i++)
	{
		if(is_str_same(COMMAND_TABLE[i].name, cmd_name))
		{
			break;
		}	
	}

	return COMMAND_TABLE[i].id;
}




/******************************************************
 * 程序入口
 ******************************************************/
#ifdef MUX_MAIN

int main(int argc, char const *argv[])
{
	/* 无参数 打印帮助信息 */
	if (argc < 2) 
	{
		print_main_help();
		goto finished;
	}
	
	/* 读取json配置 */
	// setting_json = NULL;
	setting_json = json_parse_file(DEFAULT_CONFIG_FILE);

	if (setting_json == NULL)
	{
		printf("%s: Some errors occured when opening %s.\n", \
				FAULT_S, DEFAULT_CONFIG_FILE);
		goto finished;
	}
	// printf(cJSON_Print(setting_json));
	

	/* 调用对应Command处理子程序 */
	int child_argc = argc - 1;
	char const **child_argv = (char const **)(&argv[1]);

	switch (get_command_id(argv[1]))
	{
		case CMD_RUN:
			run_main(child_argc, child_argv);
			goto finished;
		case CMD_INFO:
			info_main(child_argc, child_argv);
			goto finished;
		case CMD_CLEAN:
			clean_main(child_argc, child_argv);
			goto finished;
		case CMD_CREATE:
			create_main(child_argc, child_argv);
			goto finished;
		default:
			break;
	}

	/* 没有调用Command子程序, 处理主程序参数 */
	int opt_code = 0;
	int opt_index = 0;

	#define getopts() getopt_long( \
							(int)argc, 				\
							(char * const*)argv, 	\
							MAIN_OPTION_STRING, 	\
							MAIN_OPTION_TABLE, 		\
							&opt_index)

	while ((opt_code = getopts()) != EOF) 
	{
		switch (opt_code) 
		{
			case 'h':
				print_main_help();
				goto finished;
			case 'v':
				printf("version: %d.%d\n", \
					(int)VERSION_MAJOR, \
					(int)VERSION_MINOR);
				goto finished;
			default:
				break;
		}
	}

finished :

	if (setting_json != NULL)
	{
		cJSON_Delete(setting_json);
	}
	
	return 0;
}

#endif
/* END */
