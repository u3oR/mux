
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
#include "lib/cJSON/cJSON.h"
#include "json.h"


/**************************************
 * 私有类型
 **************************************/


/**************************************
 * 全局变量
 **************************************/

/**************************************
 * 宏定义
 **************************************/

#define UNUSED(x) (void)(x)

/**************************************
 * 私有函数
 **************************************/

/**
 * @brief 读取json文件到内存
*/
static char* 
file_read(const char *filepath)
{
    FILE *fp = fopen(filepath, "r");

    if(fp == NULL) {
        printf("Unable to open file %s.\n", filepath);
        return NULL;
    }

    fseek(fp, 0, SEEK_END);

    long file_size = ftell(fp);

    char *message = (char *)malloc(file_size * sizeof(char));

    if(message == NULL) {
        printf("Fault:Unable to allocate memory for %s.\n", filepath);
        return NULL;
    }

    // init 
    memset(message, 0, file_size * sizeof(char));

    fseek(fp, 0, SEEK_SET);

    fread(message, sizeof(char), file_size, fp);

    fclose(fp);

    return message;
}



/**************************************
 * 函数定义
 **************************************/

cJSON *
json_parse_file(const char *filepath)
{
    char *file_buf = file_read(filepath);

    if(file_buf == NULL) {
        return NULL;
    }

    cJSON *json = cJSON_Parse(file_buf);

    free(file_buf);

    return json;
}



struct Env * 
json_get_env(cJSON* json_object, const char* env_name)
{

    struct Env *env = (struct Env *)malloc(sizeof(struct Env));
    
    if (env == NULL) {
        return NULL;
    }
    
    cJSON * env_array_obj = cJSON_GetObjectItem(json_object, "envs");

    if(env_array_obj == NULL) {
        return NULL;
    }

    int arr_size = cJSON_GetArraySize(env_array_obj);

    for (int i = 0; i < arr_size; i++)
    {
        cJSON *env_obj = cJSON_GetArrayItem(env_array_obj, i);
        
        cJSON *obj_item = NULL;

        obj_item = cJSON_GetObjectItem(env_obj, "name");
        if (strcmp(cJSON_GetStringValue(obj_item), env_name) != 0)
        {
            continue;
        }
        env->name = cJSON_GetStringValue(obj_item);
        
        obj_item = cJSON_GetObjectItem(env_obj, "ext_path");
        env->ext_path = cJSON_GetStringValue(obj_item);

        obj_item = cJSON_GetObjectItem(env_obj, "dat_path");
        env->dat_path = cJSON_GetStringValue(obj_item);
        
        obj_item = cJSON_GetObjectItem(env_obj, "ico_path");
        env->ico_path = cJSON_GetStringValue(obj_item);

        if (strcmp(cJSON_GetStringValue(obj_item), env_name) == 0)
        {
            break;
        }
    }

    return env;
}


char const * 
json_get_vsc(cJSON* json_object)
{
    char const *vsc_path_val = NULL;

    cJSON *vsc_obj = \
        cJSON_GetObjectItem(json_object,"vscode_path");

    if(vsc_obj == NULL)
        return NULL;

    vsc_path_val = cJSON_GetStringValue(vsc_obj);

    return vsc_path_val;
}


int 
json_set_vsc(cJSON* json_object, const char* vsc_path)
{
    UNUSED(vsc_path);
    UNUSED(json_object);

    // cJSON *obj = cJSON_CreateObject();
    
    return 0;
}


int 
json_add_env(cJSON* json_object, struct Env *env)
{
    UNUSED(env);
    UNUSED(json_object);

    return 0;
}



int 
json_del_env(cJSON* json_object, struct Env *env)
{
    UNUSED(env);
    UNUSED(json_object);

    return 0;
}



int 
json_save_to_file(cJSON* json_object, const char* file_path)
{
    UNUSED(file_path);
    UNUSED(json_object);


    return 0;
}


/* END */
