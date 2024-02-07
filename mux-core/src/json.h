#ifndef JSON_H
#define JSON_H

/**************************************
 * 包含头文件
 **************************************/
#include "cJSON.h"


/**************************************
 * 宏定义
 **************************************/


/**************************************
 * 结构体定义
 **************************************/

/* env config */
struct Env {
	char *name;
	char *ext_path;
	char *dat_path;
	char *ico_path;
};

/* json file  */
struct Config
{
	char *code_path;
	struct Env *envs;
};

/**************************************
 * 函数声明 / 宏函数
 **************************************/
cJSON* 
json_parse_file(const char* file_path);

char const * 
json_get_vsc(cJSON* json_object);

struct Env *
json_get_env(cJSON* json_object, const char* env_name);

int 
json_print_env(cJSON *json_object, const char *env_name);

int 
json_set_vsc(cJSON* json_object, const char* vsc_path);

int 
json_add_env(cJSON* json_object, struct Env *env);

int 
json_del_env(cJSON *json_root, const char *del_env_name);

int 
json_save_to_file(cJSON* json_object, const char* file_path);


#endif
