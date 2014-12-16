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

void test_bool(void){
    JsObject *obj = CreateBool(1);
    if (obj->type != &JsTrue_Type){
        puts("Bool(True) Object wrong type");
    }
    if (obj->type != JSON_TRUE){
        puts("Bool(True) OBject wrong type");
    }
    obj = CreateBool(0);
    if (obj->type != &JsFalse_Type){
        puts("Bool(False) Object wrong type");
    }
    if (obj->type != JSON_FALSE){
        puts("Bool(False) OBject wrong type");
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

void test_string(){
    JsStringObject *obj = (JsStringObject*)CreateString("heheda");
    if (obj->type != &JsString_Type){
        puts("Str Object wrong type");
    }
    if (obj->type != JSON_STRING){
        puts("Str Object wrong type");
    }
    if (strcmp(obj->ob_sval, "heheda") != 0){
        puts("Str wrong string value");
        puts(obj->ob_sval);
    }
}


int main(){
    test_null();
    test_true();
    test_false();
    test_bool();
    test_int();
    test_string();
    // test l Object

    return 0;
}
