
/**************************************
 * 头文件包含
 **************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>

#include "main.h"
#include "json.h"
/**************************************
 * 宏定义
 **************************************/

/**************************************
 * 私有变量
 **************************************/

const char *DEFAULT_PROJ_PATH = " ";

extern char *optarg;
extern int optind, opterr, optopt;

/**************************************
 * 私有类型
 **************************************/

union Run
{
	struct {
		const char *env_name;
		const char *vsc_path;
		const char *ext_data;
		const char *dat_data;
		const char *prj_path;
	};
	const char *param[5];
};


/**************************************
 * 全局变量
 **************************************/
const char *RUN_HELP_CONTENT = "This is a run help";

static struct option RUN_OPTION_TABLE[] = {
	{"help", 		no_argument, 		NULL,	'h'},
    {"project",	    required_argument,	NULL,	'p'},
    {"env",	        required_argument,	NULL,	'e'},
	{0,				0, 					0,		 0 }
};

static char *RUN_OPTION_STRING = "hp:e:";


/**************************************
 * 私有函数 / 宏函数
 **************************************/



/**************************************
 * 程序入口
 **************************************/

int run_main(int argc, char const *argv[])
{
   	// init run param
	union Run run_param = {NULL};

	int opt_code = 0;
	int opt_index = 0;

	#define getopts() getopt_long( 						\
								(int)argc, 				\
								(char * const*)argv, 	\
								RUN_OPTION_STRING, 		\
								RUN_OPTION_TABLE, 		\
								&opt_index)
								
	/* get command param */
	while ((opt_code = getopts()) != EOF) 
	{
		switch (opt_code) 
		{
			case 'h':
                printf("%s\n", RUN_HELP_CONTENT);
				goto finished;
				break;
			case 'p':
				/* get project path */
				run_param.prj_path = optarg;
				break;
			case 'e':
				/* get env name */
				run_param.env_name = optarg;
				break;
			default:
				break;
		}
	}

	if (run_param.env_name == NULL) {
		goto finished;
	}
	
	if (run_param.prj_path == NULL) {
		run_param.prj_path = DEFAULT_PROJ_PATH;
	}

	run_param.vsc_path = json_get_vsc(setting_json);
	if (run_param.vsc_path == NULL) {
		goto finished;
	}

	struct Env *env = 
		json_get_env(setting_json, run_param.env_name);
	if(env == NULL){
		goto finished;
	}

	run_param.ext_data = env->ext_path;
	run_param.dat_data = env->dat_path;	


	// assert integrity of run_param
	for (int i = 0; i < 5; i++) {
		if(run_param.param[i] == NULL)  {
			printf("SOME THING WRONG!\n");
			goto finished;
		}
	}
	
	// run command
	char buf[1024];

	printf("code %s --extensions-dir %s --user-data-dir %s",
			run_param.prj_path,
			run_param.ext_data,
			run_param.dat_data);

	system(buf);

finished :

	if(env != NULL) {
		free(env);
	}

    return 0;
}


/* END */
