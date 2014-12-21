#include "JSON.h"

// Singleton Pattern
JsFalseObject   JsFALSE = {
    JsObject_HEAD_INIT(&JsFalse_Type)
};

JsObject *CreateFalse(void){
    return (JsObject*)&JsFALSE;
}

