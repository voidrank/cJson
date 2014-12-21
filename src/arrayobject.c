#include <stdlib.h>

#include "JSON.h"

#define MIN_ARRAY_SIZE 2

static JsObject **array_calloc(size_t size){
    JsObject **item = (JsObject**)calloc(size, sizeof(JsObject*));
    return item;
}

JsObject *array_new(size_t var_size){
    size_t size = JsArray_Type.ob_basesize;
    JsArrayObject *obj = (JsArrayObject*)calloc(1, size);
    obj->ob_item = array_calloc(var_size);
    obj->type = &JsArray_Type;
    obj->ob_refcnt = 1;
    obj->ob_size = var_size;
    obj->allocated = 0;
    return (JsObject*)obj;
}

void array_destroy(JsObject *obj){
    register int i;
    JsArrayObject *arr_obj = (JsArrayObject*)obj;
    for ( i = 0; i < arr_obj->allocated; ++i){
        arr_obj->ob_item[i]->type->tp_destroy(arr_obj->ob_item[i]);
    }
    free(arr_obj->ob_item);
    free(arr_obj);
}

JsObject *CreateArray(void){
    JsArrayObject *obj = (JsArrayObject*)JsArray_Type.tp_new(MIN_ARRAY_SIZE);
    return (JsObject*)obj;
}

void AddItemToArray(JsObject *array, JsObject *item){
    JsArrayObject *arr_obj = (JsArrayObject*)array;
    if (arr_obj->allocated+1 > arr_obj->ob_size){
        JsObject **new_ob_item = calloc(arr_obj->ob_size<<1, sizeof(JsObject*));
        memcpy( new_ob_item, arr_obj->ob_item, arr_obj->ob_size*sizeof(JsObject*));
        free(arr_obj->ob_item);
        arr_obj->ob_item = new_ob_item;
        arr_obj->ob_size <<= 1;
    }
    arr_obj->ob_item[arr_obj->allocated] = item;
    ++arr_obj->allocated;
}

void ReplaceItemInArray(JsObject *obj, int which, JsObject *new_item){
    JsArrayObject *arr_obj = (JsArrayObject*)obj;
    if (which >= arr_obj->allocated){
        puts("out of range");
        return;
    }
    arr_obj->ob_item[which]->type->tp_destroy(arr_obj->ob_item[which]);
    arr_obj->ob_item[which] = new_item;
}

JsObject *DetachItemFromArray(JsObject *obj, int which){
    JsArrayObject *arr_obj = (JsArrayObject*)obj;
    if (which >= arr_obj->allocated){
        puts("out of range");
        return NULL;
    }
    JsObject *detached_item = arr_obj->ob_item[which];
    int i;
    for ( i = which; i < arr_obj->allocated-1; ++i){
        arr_obj->ob_item[i] = arr_obj->ob_item[i+1];
    }
    --arr_obj->allocated;
    arr_obj->ob_item[arr_obj->allocated] = 0;
    return detached_item;
}

void DeleteItemFromArray(JsObject *obj, int which){
    JsArrayObject *arr_obj = (JsArrayObject*)obj;
    if (which >= arr_obj->allocated){
        puts("out of range");
        return;
    }
    JsObject *to_del = DetachItemFromArray(obj, which);
    to_del->type->tp_destroy(to_del);
}

JsObject *GetItemInArray(JsObject *obj, int which){
    JsArrayObject *arr_obj = (JsArrayObject*)obj;
    if (which >= arr_obj->allocated){
        puts("out of range");
        return NULL;
    }
    return arr_obj->ob_item[which];
}
