#include <stdlib.h>
#include <assert.h>

#include "JSON.h"

JsObject *string_new(size_t var_size){
    JsStringObject *obj = (JsStringObject*)calloc(1,JsString_Type.ob_basesize);
    obj->type = &JsString_Type;
    obj->ob_refcnt = 1;
    obj->ob_size = var_size;
    obj->ob_sval = (char*)calloc(var_size+1, sizeof(char));
    return (JsObject*)obj;
}

void string_destroy(JsObject *obj){
    JsStringObject *str_obj = (JsStringObject*)obj;
    free(str_obj->ob_sval);
    free(str_obj);
}

unsigned int hash(JsObject *obj) 
{ 
    if (obj->type == (JsType_Object*)(&JsString_Type)){
        JsStringObject *str_obj = (JsStringObject*)obj;
        char *str = str_obj->ob_sval;
        return strhash(str);
    }
    else if (obj->type == &JsNum_Type){
        JsNumObject *num_obj = (JsNumObject*)obj;
        unsigned int hash = num_obj->ob_ival * 131;
        if (hash == 0)
            hash -= 1;
        return hash;
    }
    else{
        return 0;
    }
} 

unsigned int strhash(char *str){
    register unsigned int seed = 131;
    register unsigned int hash = 0; 
    while (*str){ 
        hash = hash*seed+(*str++); 
    } 
    hash ^= seed * strlen(str);
    if (hash == 0) 
        hash -= 1;
    return hash;
}

JsObject *CreateString(char *string){
    size_t length = strlen(string);
    size_t var_size = length;
    JsStringObject *obj = (JsStringObject*)JsString_Type.tp_new(var_size);
    memcpy(obj->ob_sval, string, var_size);
    obj->ob_sval[length] = 0;
    obj->ob_hash = strhash(string);
    return (JsObject*)obj;
}   

char *GetStringValue(JsObject *obj){
    assert(obj->type == (JsType_Object*)&JsString_Type);
    return ((JsStringObject*)obj)->ob_sval;
}
