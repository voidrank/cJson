#include "JSON.h"
#include "parse.h"
#include "output.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define eps 1e-8

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

void test_num(){
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
    if (obj->ob_hash == 0)
        printf("wrong hash func");
    JsObject *obj0 = CreateString("hehe");
    JsObject *obj1 = CreateString("heheda");
    JsObject *obj2 = CreateString("hehehe");
    if (obj1->type != obj0->type)
        printf("string wrong type");
    if (obj2->type != obj0->type)
        printf("string wrong type");
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
   

    JsObject *replaced_obj = CreateBool(1);
    ReplaceItemInArray((JsObject*)obj, 2, replaced_obj);
    if (obj->ob_item[2] != replaced_obj){
        puts("replace item error!");
    }
    // it will throw a exception
    printf("expected error(out of range): ");
    ReplaceItemInArray((JsObject*)obj, 3, replaced_obj);
    
    JsObject *detached_obj0 = DetachItemFromArray((JsObject*)obj, 1);
    if (detached_obj0 != obj1){
        puts("detach error");
    }
    printf("expected error(out of range): ");
    DeleteItemFromArray((JsObject*)obj, 2);
    printf("expected error(out of range): ");
    DetachItemFromArray((JsObject*)obj, 2);
    JsObject *detached_obj1 = DetachItemFromArray((JsObject*)obj, 1);
    if (detached_obj1 != replaced_obj){
        puts("detach array item error");
    }

    if (obj->ob_item[0] != GetItemInArray((JsObject*)obj, 0)){
        puts("get array item error");
    }
}

void test_object(){
    JsObject *obj0 = CreateBool(1);
    JsObject *obj1 = CreateNumber(2);
    JsObject *obj2 = CreateString("heheda");
    JsObject *obj_obj = CreateObject();
    InsertItemToObject(obj_obj, "heheda", obj0);
    InsertItemToObject(obj_obj, "hehehe", obj1);
    InsertItemToObject(obj_obj, "hahaha", obj2);
    if (GetItemInObject(obj_obj, "heheda") != obj0){
        printf("wrong read operation in jsonobject");
    }
    if (GetItemInObject(obj_obj, "hehehe") != obj1){
        printf("wrong read operation in jsonobject");
    }
    if (GetItemInObject(obj_obj, "heheha") != obj2){
        printf("expected error(wrong read operation in jsonobject): #(wrong read operation in jsonobject)\n");
    }
    
    if (DetachItemFromObject(obj_obj, "heheda") != obj0){
        printf("wrong detach operation in jsonobject\n");
    }
    if (DetachItemFromObject(obj_obj, "hehehe") != obj1){
        printf("wrong detach operation in jsonobject\n");
    }
    if (DetachItemFromObject(obj_obj, "hahaha") != obj2){
        printf("wrong detach operation in jsonobject\n");
    }
}

void test_parse_null(){
    JsObject *obj = ParseJSON("null");
    JsNumObject *null_obj = (JsNumObject*)obj;
    if (null_obj->type != &JsNull_Type)
        printf("wrong type\n");
}


void test_parse_true(){
    JsObject *obj = ParseJSON("true");
    JsNumObject *true_obj = (JsNumObject*)obj;
    if (true_obj->type != &JsTrue_Type)
        printf("wrong type\n");
}


void test_parse_false(){
    JsObject *obj = ParseJSON("false");
    JsNumObject *false_obj = (JsNumObject*)obj;
    if (false_obj->type != &JsFalse_Type)
        printf("wrong type\n");
}

void test_parse_number(){
    JsObject *obj = ParseJSON("123.123");
    JsNumObject *num_obj = (JsNumObject*)obj;
    if (num_obj->type != &JsNum_Type)
        printf("wrong type\n");
    if (abs(num_obj->ob_ival-123.123) > eps){
        puts("wrong number value.");
        printf("%.9f\n", num_obj->ob_ival);
    }
}


void test_parse_string(){
    JsObject *obj = ParseJSON("\"heheda\"");
    JsStringObject *str_obj = (JsStringObject*)obj;
    if (str_obj->type != &JsString_Type)
        printf("wrong type\n");
    if (strcmp(str_obj->ob_sval, "heheda") != 0){
        printf("wrong string value.\n");
        puts(str_obj->ob_sval);
    }
}

void test_parse_array(){
    JsObject *obj = ParseJSON("[\"hehe\", \"haha\"]");
    JsObject *obj0 = GetItemInArray(obj, 0);
    JsObject *obj1 = GetItemInArray(obj, 1);
    char *str0 = GetStringValue(obj0);
    char *str1 = GetStringValue(obj1);
    if (strcmp(str0, "hehe") != 0){
        printf("wrong array value: %s", str0);
    }
    if (strcmp(str1, "haha") != 0){
        printf("wrong array value: %s", str1);
    }
}

void test_parse_object(){
    JsObject *obj = ParseJSON("{ \"heheda\":\"papapa\"}");
    JsObject *str_obj = GetItemInObject(obj, "heheda");
    if (strcmp(GetStringValue(str_obj), "papapa") != 0){
        puts("wrong answer");
        puts(GetStringValue(str_obj));
    }
}

void test_parse_file(){
    JsObject *obj = ParseJSONFromFile("heheda.txt");
    PrintJSON(obj);
}

int main(){
    test_null();
    test_true();
    test_false();
    test_bool();
    test_num();
    test_string();
    test_array();
    test_object();

    //true
    /*
    test_parse_null();
    test_parse_true();
    test_parse_false();
    test_parse_number();
    test_parse_string();
    test_parse_array();
    test_parse_object();
    */

    //test file
    test_parse_file();
    return 0;
}
