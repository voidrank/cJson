#ifndef JSON_H
#define JSON_H

#include <string.h>
#include <stdio.h>

#define JsObject_HEAD \
    int ob_refcnt; \
    struct _typeobject *type;

#define JsObject_VAR_HEAD \
    int ob_refcnt; \
    struct _vartypeobject *type; \
    int ob_size;

#define JsObject_HEAD_INIT(x) 1, x



/* cJSON Types: */
#define JSON_FALSE  &JsFalse_Type
#define JSON_TRUE   &JsTrue_Type
#define JSON_NULL   &JsNull_Type
#define JSON_NUMBER &JsNum_Type
#define JSON_STRING &JsString_Type
#define JSON_ARRAY  &JsArray_Type
#define JSON_OBJECT &JsObject_Type



/* BASE OBJECT */
typedef struct _object {
    JsObject_HEAD
} JsObject;
typedef JsObject JSON;



/* binary function pointer */
typedef JsObject * (*newfunc)(void);
typedef JsObject * (*varnewfunc)(size_t var_size);
typedef void (*destroyfunc)(JsObject*);

/* new object function */
extern JsObject *num_new(void);
extern JsObject *string_new(size_t var_size);
extern JsObject *array_new(size_t var_size);
extern JsObject *entry_new(void);
extern JsObject *object_new(size_t var_size);

/* destroy object function */
extern void intern_destroy(JsObject *obj);
extern void num_destroy(JsObject *obj);
extern void string_destroy(JsObject *obj);
extern void array_destroy(JsObject *obj);
extern void entry_destroy(JsObject *obj);
extern void object_destroy(JsObject *obj);

/* hash */
extern unsigned int hash(JsObject *obj);
extern unsigned int strhash(char *str);

/* NULL OBJECT */
typedef struct {
    JsObject_HEAD
} JsNullObject;

/* TRUE OBJECT */
typedef struct{
    JsObject_HEAD
} JsTrueObject;

/* FALSE OBJECT */
typedef struct{
    JsObject_HEAD
} JsFalseObject;

/* NUMBER OBJECT */
typedef struct {
    JsObject_HEAD
    double ob_ival;
} JsNumObject;

/* BASE VAR LENGTH OBJECT */
typedef struct {
    JsObject_VAR_HEAD
} JsVarObject;

/* STRING OBJECT */
typedef struct {
    // notice that, I use malloc(or my own malloc function)
    // to get a block free memory, so the length of ob_sval 
    // should be unnoticed
    JsObject_VAR_HEAD
    size_t ob_hash;
    char *ob_sval;
} JsStringObject;

/* ARRAY OBJECT */
typedef struct {
    JsObject_VAR_HEAD
    int allocated; // the size of the memory block
    JsObject **ob_item;  // array block
} JsArrayObject;

/* JSON OBJECT Entry */
typedef struct{
    JsObject_HEAD
    size_t me_hash;
    JsObject *key;
    JsObject *me_value;
} JsEntryObject;

/* JsOBJECT */
typedef struct {
    JsObject_VAR_HEAD
    size_t ma_fill;
    size_t ma_mask;
    JsEntryObject **ma_table;
} JsObjectObject;



/* JSON TYPE OBJECT */
typedef struct _typeobject{
    JsObject_HEAD
    char *tp_name; // type name
    size_t ob_size;
    newfunc tp_new;
    destroyfunc tp_destroy;
}JsType_Object;

typedef struct _vartypeobject{
    JsObject_HEAD
    char *tp_name;
    size_t ob_basesize;
    varnewfunc tp_new;
    destroyfunc tp_destroy;
}JsVarType_Object;


/* JsTYPE TYPE */
extern JsType_Object JsType_Type;
/* NULL TYPE */
extern JsType_Object JsNull_Type;
/* FALSE TYPE */
extern JsType_Object JsFalse_Type;
/* TRUE TYPE */
extern JsType_Object JsTrue_Type;
/* NUMBER TYPE */
extern JsType_Object JsNum_Type;
/* STRING TYPE */
extern JsVarType_Object JsString_Type;
/* ARRAY TYPE */
extern JsVarType_Object JsArray_Type;
/* JsEntry TYPE */
extern JsType_Object JsEntry_Type;
/* JsOBJECT TYPE */
extern JsVarType_Object JsObject_Type;



//Singleton Pattern
extern JsNullObject    JsNULL;
extern JsFalseObject   JsFALSE;
extern JsTrueObject    JsTRUE;



extern void PrintJSON(JSON *item);
extern void PrintJSONToFile(JSON *item,  char *file_name);


/* Create */
extern JSON *CreateNULL(void);
extern JSON *CreateTrue(void);
extern JSON *CreateFalse(void);
extern JSON *CreateBool(int b);
extern JSON *CreateNumber(double num);
extern JSON *CreateString(char *string);
extern JSON *CreateArray(void);
extern JSON *CreateObject(void);


/* Insert */
extern void InsertItemToObject(JsObject *obj, char *key, JsObject *value);

/* Append */
extern void AddItemToArray(JSON *array, JSON *item);
extern void AddItemToObject(JSON *object, char *key, JSON *value);



/* Update */
extern void ReplaceItemInArray(JSON *array, int which, JSON *new_item);
extern void ReplaceItemInObject(JSON *object,  char *key, JSON *new_value);



/* Remove/Delete */
extern JSON *DetachItemFromArray(JSON *array, int which);
extern void DeleteItemFromArray(JSON *array, int which);
extern JSON *DetachItemFromObject(JSON *object, char *key);
extern void DeleteItemFromObject(JSON *object,  char *key);

extern void DeleteJSON(JSON *item);



/* Duplicate */
extern JSON *Duplicate(JSON *item, int recurse);



/* Read */
extern JSON *GetItemInArray(JSON *array, int which);
extern JSON *GetItemInObject(JSON *object,  char *key);
extern JSON *GetItemInJSON(JSON *json,  char *path);

#endif
