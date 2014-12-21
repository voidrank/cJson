#include "JSON.h"

//Singleton Pattern
JsTrueObject    JsTRUE = {
    JsObject_HEAD_INIT(&JsTrue_Type)
};


JsObject *CreateTrue(void){
    return (JsObject*)&JsTRUE;
}

