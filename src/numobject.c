#include <stdlib.h>

#include "JSON.h"

JsObject *num_new(void){
    JsNumObject *obj = (JsNumObject*)calloc(1, JsNum_Type.ob_size);
    obj->ob_refcnt = 1;
    obj->type = &JsNum_Type;
    obj->ob_ival = 0;
    return (JsObject*)obj;
}

void num_destroy(JsObject *obj){
    free(obj);
}

JsObject *CreateNumber(double num){
    JsNumObject *obj = (JsNumObject*)JsNum_Type.tp_new();
    obj->ob_ival = num;
    return (JsObject*)obj;
}

