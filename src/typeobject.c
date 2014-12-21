#include "JSON.h"
#include <string.h>
#include <stdlib.h>

/*
 *  This part will manage intern object
 *  of json, including creatingw object,
 *  destoying object, memory management,
 */


void intern_destroy(JsObject *obj){}

/* JsTYPE TYPE */
JsType_Object JsType_Type = {
    JsObject_HEAD_INIT(&JsType_Type),
    "json_type",
    0,
    0,
    0
};

JsType_Object JsVarType_Type = {
    JsObject_HEAD_INIT(&JsType_Type),
    "json_var_type",
    0,
    0,
    intern_destroy
};

/* NULL TYPE */
JsType_Object JsNull_Type = {
    JsObject_HEAD_INIT(&JsType_Type),
    "json_null",
    sizeof(JsNullObject),
    0,
    intern_destroy
};

/* FALSE TYPE */
JsType_Object JsFalse_Type = {
    JsObject_HEAD_INIT(&JsType_Type),
    "json_false",
    sizeof(JsFalseObject),
    0,
    intern_destroy
};

/* TRUE TYPE */
JsType_Object JsTrue_Type = {
    JsObject_HEAD_INIT(&JsType_Type),
    "json_true",
    sizeof(JsTrueObject),
    0,
    intern_destroy
};

/* NUMBER TYPE */
JsType_Object JsNum_Type = {
    JsObject_HEAD_INIT(&JsType_Type),
    "json_number",
    sizeof(JsNumObject),
    num_new,
    num_destroy
};

/* STRING TYPE */
JsVarType_Object JsString_Type = {
    JsObject_HEAD_INIT(&JsVarType_Type),
    "json_string",
    sizeof(JsStringObject),
    string_new,
    string_destroy
};

/* ARRAY TYPE */
JsVarType_Object JsArray_Type = {
    JsObject_HEAD_INIT(&JsType_Type),
    "json_array",
    sizeof(JsArrayObject),
    array_new,
    array_destroy
};

/* JsOBJECT TYPE */
JsType_Object JsEntry_Type = {
    JsObject_HEAD_INIT(&JsType_Type),
    "json_entry",
    sizeof(JsEntryObject),
    entry_new,
    entry_destroy
};

JsVarType_Object JsObject_Type = {
    JsObject_HEAD_INIT(&JsType_Type),
    "json_object",
    sizeof(JsObjectObject),
    object_new,
    object_destroy
};


