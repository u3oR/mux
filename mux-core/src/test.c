
#ifdef MUX_TEST

#include <stdio.h>
#include <string.h>
#include "cJSON.h"
#include "json.h"


int main(int argc, char const *argv[])
{
    // printf("Hello World\n");
    
    const char *env_name = "python";

    struct Env env;

    cJSON *json = json_parse_file("_settings.json");
    
    cJSON * env_array_obj = cJSON_GetObjectItem(json, "envs");
    // printf("%s\n", cJSON_Print(env_array_obj));

    int arr_size = cJSON_GetArraySize(env_array_obj);
    printf("arr_size = %d\n", arr_size);

    for (int i = 0; i < arr_size; i++)
    {
        cJSON *env_obj = cJSON_GetArrayItem(env_array_obj, i);
        // printf("%d, %s\n", i, cJSON_Print(env_obj));

        cJSON *obj_item = NULL;

        obj_item = cJSON_GetObjectItem(env_obj, "name");
        // printf("%d, %s\n", i, cJSON_Print(obj_item));

        if(strcmp(cJSON_GetStringValue(obj_item), env_name) != 0)
        {
            continue;
        }
        env.name = cJSON_GetStringValue(obj_item);

        obj_item = cJSON_GetObjectItem(env_obj, "ext_path");
        env.ext_path = cJSON_GetStringValue(obj_item);

        obj_item = cJSON_GetObjectItem(env_obj, "dat_path");
        env.dat_path = cJSON_GetStringValue(obj_item);

        obj_item = cJSON_GetObjectItem(env_obj, "ico_path");
        env.ico_path = cJSON_GetStringValue(obj_item);
        
        
        printf("name:%s\n", env.name);
        printf("ext_path:%s\n", env.ext_path);
        printf("dat_path:%s\n", env.dat_path);
        printf("ico_path:%s\n", env.ico_path);
    }

    cJSON_Delete(json);

    return 0;
}

#endif
