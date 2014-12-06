#ifndef JSON_H
#define JSON_H



#define JSON_Object_HEAD \
    int ob_refcnt; \
    struct _typeobject *ob_type;

#define JSON_Object_VAR_HEAD \
    JSON_Object_HEAD \
    int ob_size;

#define JSON_Object_HEAD_INIT(x) 1, x



/* base type */
typedef unsigned int JSON_ssize_t;

/* cJSON Types: */
#define JSON_FALSE _json_false_type
#define JSON_TRUE _json_true_type
#define JSON_NULL _json_null_type
#define JSON_NUMBER _json_number_type
#define JSON_STRING _json_string_type
#define JSON_ARRAY _json_array_type
#define JSON_OBJECT _json_object_type



/* BASE OBJECT */
typedef struct _object {
    JSON_Object_HEAD
} JSON_Object;

typedef JSON_Object JSON;

/* NULL OBJECT */
typedef struct {
    JSON_Object_HEAD
} JSON_Null_Object;

/* TRUE OBJECT */
typedef struct{
    JSON_Object_HEAD
} JSON_True_Object;

/* FALSE OBJECT */
typedef struct{
    JSON_Object_HEAD
} JSON_False_Object;

/* NUMBER OBJECT */
typedef struct {
    JSON_Object_HEAD
    double ob_ival;
} JSON_Double_Object;

/* BASE VAR LENGTH OBJECT */
typedef struct {
    JSON_Object_VAR_HEAD
} JSON_Var_Object;

/* STRING OBJECT */
typedef struct {
    // notice that, I use malloc(or my own malloc function)
    // to get a block free memory, so the length of ob_sval 
    // should be unnoticed
    JSON_Object_VAR_HEAD
    int ob_hash;
    char ob_sval[1];
} JSON_String_Object;

/* ARRAY OBJECT */
typedef struct {
    JSON_Object_HEAD
    JSON **ob_item;  // a pointer to the head of a block of memory block
    int allocated; // the size of the memory block
} JSON_Array_Object;

/* JSON OBJECT Entry */
typedef struct{
    JSON_Object_HEAD
    JSON_ssize_t me_hash;
    JSON_Object *key;
    JSON_Object *me_value;
} JSON_Object_Entry_Object;

/* JSON_OBJECT */
typedef struct {
    JSON_Object_HEAD
    JSON_ssize_t ma_fill; // element num: Active + Dummy
    JSON_ssize_t ma_used; // element num: Active
    JSON_ssize_t ma_mask; // element num: All (2^x)
    JSON_Object_Entry_Object *ma_table; // memory pool
} JSON_Object_Object;



/* JSON TYPE OBJECT */
typedef struct _typeobject{
    JSON_Object_HEAD
    char *tp_name; // type name
}JSON_Type_Object;

/* JSON_BASE TYPE */
JSON_Type_Object _json_type_type = {
    JSON_Object_HEAD_INIT(&_json_type_type),
    "json_type"
};

/* FALSE TYPE */
JSON_Type_Object _json_false_type = {
    JSON_Object_HEAD_INIT(&_json_type_type),
    "json_flase"
};

/* TRUE TYPE */
JSON_Type_Object _json_true_type = {
    JSON_Object_HEAD_INIT(&_json_type_type),
    "json_true"
};

/* NULL TYPE */
JSON_Type_Object _json_null_type = {
    JSON_Object_HEAD_INIT(&_json_type_type),
    "json_null"
};

/* NUMBER TYPE */
JSON_Type_Object _json_number_type = {
    JSON_Object_HEAD_INIT(&_json_type_type),
    "json_number"
};

/* STRING TYPE */
JSON_Type_Object _json_string_type = {
    JSON_Object_HEAD_INIT(&_json_type_type),
    "json_string"
};

/* ARRAY TYPE */
JSON_Type_Object _json_array_type = {
    JSON_Object_HEAD_INIT(&_json_type_type),
    "json_array"
};

/* JSON_OBJECT TYPE */
JSON_Type_Object _json_object_type = {
    JSON_Object_HEAD_INIT(&_json_type_type),
    "json_object"
};



/* Parse & Print */
extern JSON *ParseJSON(const char *value);
extern JSON *ParseJSONFromFile(const char *file_name);

extern void PrintJSON(JSON *item);
extern void PrintJSONToFile(JSON *item, const char *file_name);



/* Create */
extern JSON *CreateNULL(void);
extern JSON *CreateTrue(void);
extern JSON *CreateFalse(void);
extern JSON *CreateBool(int b);
extern JSON *CreateNumber(double num);
extern JSON *CreateString(const char *string);
extern JSON *CreateArray(void);
extern JSON *CreateObject(void);



/* Append */
extern void AddItemToArray(JSON *array, JSON *item);
extern void AddItemToObject(JSON *object, const char *key, JSON *value);



/* Update */
extern void ReplaceItemInArray(JSON *array, int which, JSON *new_item);
extern void ReplaceItemInObject(JSON *object, const char *key, JSON *new_value);



/* Remove/Delete */
extern JSON *DetachItemFromArray(JSON *array, int which);
extern void *DeleteItemFromArray(JSON *array, int which);
extern JSON *DetachItemFromObject(JSON *object, const char *key);
extern void *DeleteItemFromObject(JSON *object, const char *key);

extern void DeleteJSON(JSON *item);



/* Duplicate */
extern JSON *Duplicate(JSON *item, int recurse);



/* Read */
extern JSON *GetItemInArray(JSON *array, int which);
extern JSON *GetItemInObject(JSON *object, const char *key);
extern JSON *GetItemInJSON(JSON *json, const char *path);



#endif
