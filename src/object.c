#include "JSON.h"
#include <string.h>
#include <stdlib.h>

/*
 *  This part will manage intern object
 *  of json, including creatingw object,
 *  destoying object, memory management,
 */



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
JsType_Object JsArray_Type = {
    JsObject_HEAD_INIT(&JsType_Type),
    "json_array",
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
    size_t size = var_size + JsString_Type.ob_size;
    JsStringObject *obj = (JsStringObject*)malloc(size);
    obj->type = &JsString_Type;
    obj->ob_refcnt = 1;
    return (JsObject*)obj;
}

JSON *CreateString(const char *string){
    size_t length = strlen(string);
    size_t var_size = length * sizeof(char);
    JsStringObject *obj = (JsStringObject*)JsString_Type.tp_new(var_size);
    memcpy(obj->ob_sval, string, var_size);
    obj->ob_sval[length] = 0;
    //TODO: obj->ob_hash
    return (JsObject*)obj;
}   
