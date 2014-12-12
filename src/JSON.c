#include "JSON.h"
#include <string.h>

/* memory malloc */
static void *JSON_Mem_MALLOC(JSON_ssize_t nbytes){
    return (*JSON)malloc(nbytes);
}

static JSON_Num_Object *JSON_Num_New(void){
    JSON_Num_Object *obj = JSON_Mem_MALLOC(sizeof(JSON_Num_Object));
    obj = {
        JSON_Object_HEAD_INIT(&_json_number_type),
        0
    };
    return obj;
}

static JSON_String_Object *JSON_String_New(JSON_ssize_t length){
    JSON_String_Object *obj = JSON_Mem_MALLOC(sizeof(JSON_String_Object)+sizeof(char)*length);
    obj = {
        JSON_Object_HEAD_INIT(&_json_string_type),
        0
    };
    return obj;
}


JSON *CreateNULL(void){
    return (*JSON)&_NULL;
}

JSON *CreateTrue(void){
    return (*JSON)&_TRUE;
}

JSON *CreateFalse(void){
    return (*JSON)&_FALSE;
}

JSON *CreateBool(int b){
    if (b)
        return CreateTrue();
    else
        return CreateFalse();
}

JSON *CreateNumber(double num){
    JSON_Num_Object *obj = JSON_Num_New(JSON_NUMBER);
    obj->ob_ival = num;
    return (JSON*)obj;
}

JSON *CreateString(const char *string){
    int length = strlen(string);
    JSON_String_Object *obj = JSON_String_New(length);
    memcpy(obj->sval, string, sizeof(char)*length);
    obj->sval[length] = 0;
    //TODO: obj->ob_hash
    return (JSON*)obj;
}   
