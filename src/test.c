#include "JSON.h"
#include <stdio.h>

void test_null(void){
    JsObject *null_obj = CreateNULL();
    if (null_obj->type != &JsNull_Type){
        puts("Null Object wrong type");
    }
    if (null_obj->type != JSON_NULL){
        puts("Null Object wrong type");
    }
}

void test_false(void){
    JsObject *false_obj = CreateFalse();
    if (false_obj->type != &JsFalse_Type){
        puts("False Object wrong type");
    }
    if (false_obj->type != JSON_FALSE){
        puts("False Object wrong type");
    }
}

void test_true(void){
    JsObject *obj = CreateTrue();
    if (obj->type != &JsTrue_Type){
        puts("True Object wrong type");
    }
    if (obj->type != JSON_TRUE){
        puts("True Object wrong type");
    }
}

void test_int(){
    JsNumObject *obj = (JsNumObject*)CreateNumber(10);
    if (obj->type != &JsNum_Type){
        puts("Num Object wrong type");
    }
    if (obj->type != JSON_NUMBER){
        puts("Num Object wrong type");
    }
    if (obj->ob_ival != 10)
        puts("Num wrong value");
}


int main(){
    test_null();
    test_true();
    test_false();
    test_int();
    // test l Object

    return 0;
}
