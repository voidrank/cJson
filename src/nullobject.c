#include "JSON.h"

//Singleton Pattern
JsNullObject    JsNULL = {
    JsObject_HEAD_INIT(&JsNull_Type)
};

JsObject *CreateNULL(void){
    return (JsObject*)&JsNULL;
}

