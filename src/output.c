#include "JSON.h"
#include "output.h"
#include <string.h>
#include <stdio.h>

void PrintJSON(JsObject *item){
    if (item->type == &JsTrue_Type){
        printf("true");
    }
    else if (item->type == &JsFalse_Type){
        printf("false");
    }
    else if (item->type == &JsNull_Type){
        printf("null");
    }
    else if (item->type == &JsNum_Type){
        printf("%.9f", ((JsNumObject*)item)->ob_ival);
    }
    else if (item->type == ((JsType_Object*)&JsString_Type)){
        printf("\"");
        printf("%s", GetStringValue(item));
        printf("\"");
    }
    else if (item->type == ((JsType_Object*)&JsArray_Type)){
        printf("[");
        int n = GetItemTotalInArray(item);
        for (int i = 0; i < n-1; ++i){
            PrintJSON(GetItemInArray(item, i));
            printf(",");
        }
        if (n>0)
            PrintJSON(GetItemInArray(item, n-1));
        printf("]");
    }
    else if (item->type==((JsType_Object*)&JsObject_Type)){
        printf("{");
        int first = 1;
        int ct = 0;
        JsObjectObject *obj = (JsObjectObject*)item;
        for (int i = 0; i < obj->ma_mask; ++i)
            if (obj->ma_table[i] != NULL&& obj->ma_table[i] != &dummy){
                if (first!=0)
                    first = 0;
                else
                    printf(",");
                ++ct;
                PrintJSON(obj->ma_table[i]->key);
                printf(":");
                PrintJSON(obj->ma_table[i]->me_value);
            }
        printf("}");
        printf("%d\n", ct);
    }
}

