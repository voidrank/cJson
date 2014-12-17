#include "JSON.h"
#include <string.h>
#include <stdlib.h>

/*
 *  This part will manage intern object
 *  of json, including creatingw object,
 *  destoying object, memory management,
 */



#define MIN_ARRAY_SIZE 2



/* JsTYPE TYPE */
JsType_Object JsType_Type = {
    JsObject_HEAD_INIT(&JsType_Type),
    "json_type",
    0,
    0
};

JsType_Object JsVarType_Type = {
    JsObject_HEAD_INIT(&JsType_Type),
    "json_var_type",
    0,
    0
};

/* NULL TYPE */
JsType_Object JsNull_Type = {
    JsObject_HEAD_INIT(&JsType_Type),
    "json_null",
    sizeof(JsNullObject),
    0
};

/* FALSE TYPE */
JsType_Object JsFalse_Type = {
    JsObject_HEAD_INIT(&JsType_Type),
    "json_false",
    sizeof(JsFalseObject),
    0
};

/* TRUE TYPE */
JsType_Object JsTrue_Type = {
    JsObject_HEAD_INIT(&JsType_Type),
    "json_true",
    sizeof(JsTrueObject),
    0
};

/* NUMBER TYPE */
JsType_Object JsNum_Type = {
    JsObject_HEAD_INIT(&JsType_Type),
    "json_number",
    sizeof(JsNumObject),
    num_new,
};

/* STRING TYPE */
JsVarType_Object JsString_Type = {
    JsObject_HEAD_INIT(&JsVarType_Type),
    "json_string",
    sizeof(JsStringObject),
    string_new
};

/* ARRAY TYPE */
JsVarType_Object JsArray_Type = {
    JsObject_HEAD_INIT(&JsType_Type),
    "json_array",
    sizeof(JsArrayObject),
    array_new
};

/* JsOBJECT TYPE */
JsType_Object JsObject_Type = {
    JsObject_HEAD_INIT(&JsType_Type),
    "json_object"
};

//Singleton Pattern
JsNullObject    JsNULL = {
    JsObject_HEAD_INIT(&JsNull_Type)
};
JsFalseObject   JsFALSE = {
    JsObject_HEAD_INIT(&JsFalse_Type)
};
JsTrueObject    JsTRUE = {
    JsObject_HEAD_INIT(&JsTrue_Type)
};

// function

// NUll Object function
JsObject *CreateNULL(void){
    return (JsObject*)&JsNULL;
}


// True Object function
JsObject *CreateTrue(void){
    return (JsObject*)&JsTRUE;
}


// False Object function
JsObject *CreateFalse(void){
    return (JsObject*)&JsFALSE;
}


// Bool
JSON *CreateBool(int b){
    if (b)
        return CreateTrue();
    else
        return CreateFalse();
}


// Num object function
JsObject *num_new(void){
    JsNumObject *obj = (JsNumObject*)malloc(JsNum_Type.ob_size);
    obj->ob_refcnt = 1;
    obj->type = &JsNum_Type;
    obj->ob_ival = 0;
    return (JsObject*)obj;
}

JsObject *CreateNumber(double num){
    JsNumObject *obj = (JsNumObject*)JsNum_Type.tp_new();
    obj->ob_ival = num;
    return (JsObject*)obj;
}


// String object function
JsObject *string_new(size_t var_size){
    size_t size = var_size*sizeof(char) + JsString_Type.ob_basesize;
    JsStringObject *obj = (JsStringObject*)malloc(size);
    obj->type = &JsString_Type;
    obj->ob_refcnt = 1;
    obj->ob_size = var_size;
    return (JsObject*)obj;
}

JsObject *CreateString(const char *string){
    size_t length = strlen(string);
    size_t var_size = length;
    JsStringObject *obj = (JsStringObject*)JsString_Type.tp_new(var_size);
    memcpy(obj->ob_sval, string, var_size);
    obj->ob_sval[length] = 0;
    //TODO: obj->ob_hash
    return (JsObject*)obj;
}   

// Array object function
JsObject *array_new(size_t var_size){
    size_t size = var_size*sizeof(JsObject*) + JsString_Type.ob_basesize;
    JsArrayObject *obj = (JsArrayObject*)malloc(size);
    obj->type = &JsArray_Type;
    obj->ob_refcnt = 1;
    obj->ob_size = var_size;
    obj->allocated = 0;
    return (JsObject*)obj;
}

JsObject *CreateArray(void){
    JsArrayObject *obj = (JsArrayObject*)JsArray_Type.tp_new(MIN_ARRAY_SIZE);
    return (JsObject*)obj;
}

void AddItemToArray(JsObject *array, JsObject *item){
    JsArrayObject *arr_obj = (JsArrayObject*)array;
    if (arr_obj->allocated+1 > arr_obj->ob_size){
        JsArrayObject *new_arr_obj = (JsArrayObject*)JsArray_Type.tp_new(arr_obj->ob_size*2);
        memcpy(new_arr_obj->ob_item,  arr_obj->ob_item, arr_obj->ob_size);
        new_arr_obj->allocated = arr_obj->allocated;
        printf("%d %d\n", new_arr_obj->allocated, new_arr_obj->ob_size);
        //TODO: free old array object 
        arr_obj = new_arr_obj;
    }
    arr_obj->ob_item[arr_obj->allocated] = item;
    ++arr_obj->allocated;
}
