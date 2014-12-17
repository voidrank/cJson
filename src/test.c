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
    char const_test_string[] = "heheda";
    JsStringObject *obj = (JsStringObject*)CreateString(const_test_string);
    if (obj->type != &JsString_Type){
        puts("Str Object wrong type");
    }
    if (obj->type != JSON_STRING){
        puts("Str Object wrong type");
    }
    if (strcmp(obj->ob_sval, const_test_string) != 0){
        puts("Str wrong string value");
        puts(obj->ob_sval);
    }
    if (obj->ob_size != sizeof(char)*strlen(const_test_string)){
        puts("Str wrong ob_size");
    }
}

void test_array(){
    JsArrayObject *obj = (JsArrayObject*)CreateArray();
    if (obj->type != &JsArray_Type){
        puts("Array Object wrong type");
    }
    if (obj->type != JSON_ARRAY){
        puts("Array Object wrong type");
    }
    if (obj->ob_size != 2){
        puts("Array Object wrong ob_size");
    }
    JsObject *obj0 = CreateBool(1);
    JsObject *obj1 = CreateString("heheda");
    JsObject *obj2 = CreateNumber(233);
    AddItemToArray((JsObject*)obj, obj0);
    AddItemToArray((JsObject*)obj, obj1);
    AddItemToArray((JsObject*)obj, obj2);
    printf("%d\n", obj->allocated);
    if (obj->allocated != 3){
        puts("Wrong items counts");
    }
    if (obj->ob_item[0] != obj0){
        puts("obj0 address error");
    }
    if (obj->ob_item[1] != obj1){
        puts("obj1 address error");
    }
    if (obj->ob_item[2] != obj2){
        puts("obj2 address error");
    }
}

int main(){
    test_null();
    test_true();
    test_false();
    test_bool();
    test_int();
    test_string();
    test_array();
    // test l Object

    return 0;
}
