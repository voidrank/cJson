#include "JSON.h"

JsObject *CreateBool(int b){
    if (b)
        return CreateTrue();
    else
        return CreateFalse();
}

