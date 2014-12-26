#include <stdlib.h>
#include <string.h>

#include "JSON.h"

#define MIN_OBJECT_SIZE 4


JsStringObject dummy_key = {
    JsObject_HEAD_INIT(&JsString_Type),
    0,
    0,
    "--dummy--"
};

JsEntryObject dummy = {
    JsObject_HEAD_INIT(&JsEntry_Type),
    0,
    (JsObject*)(&dummy_key),
    NULL
};

JsObject *entry_new(void){
    JsEntryObject *obj = calloc(1, sizeof(JsEntryObject));
    obj->type = &JsEntry_Type;
    obj->ob_refcnt = 1;
    return (JsObject*)obj;
}

void entry_destroy(JsObject *obj){
    if (obj == (JsObject*)&dummy) 
        return;
    JsEntryObject *ent_obj = (JsEntryObject*)obj;
    if (ent_obj->key != NULL){
        ent_obj->key->type->tp_destroy(ent_obj->key);
    }
    if (ent_obj->me_value != NULL){
        ent_obj->me_value->type->tp_destroy(ent_obj->me_value);
    }
    free(ent_obj);
}

JsObject *CreateEntry(JsObject *key, JsObject *value){
    JsEntryObject *ent = (JsEntryObject*)JsEntry_Type.tp_new();
    ent->key = key;
    ent->me_value = value;
    ent->me_hash = hash(key);;
    return (JsObject*)ent;
}

void DestroyEntry(JsObject *item){
    JsEntryObject *ent = (JsEntryObject*)item;
    if (ent != &dummy&& ent != NULL){
        ent->type->tp_destroy((JsObject*)ent);
    }
}


JsObject *object_new(size_t var_size){
    size_t size = JsObject_Type.ob_basesize;
    JsObjectObject *obj = (JsObjectObject*)calloc(1, size);
    obj->type = &JsObject_Type;
    obj->ob_refcnt = 1;
    obj->ma_fill = 0;
    obj->ma_mask = var_size - 1;
    obj->ob_size = var_size;
    obj->ma_table = (JsEntryObject**)calloc(var_size, sizeof(JsEntryObject*));
    return (JsObject*)obj;
}

void object_destroy(JsObject *obj){
    register int i;
    JsObjectObject *obj_obj = (JsObjectObject*)obj;
    for ( i = 0; i <= obj_obj->ma_mask; ++i)
        if (obj_obj->ma_table[i] != NULL&& obj_obj->ma_table[i] != &dummy){
            obj_obj->ma_table[i]->type->tp_destroy((JsObject*)(obj_obj->ma_table[i]));
        }
    free(obj_obj->ma_table);
    free(obj_obj);
}

JsObject *CreateObject(void){
    JsObjectObject *obj = (JsObjectObject*)JsObject_Type.tp_new(MIN_OBJECT_SIZE);
    return (JsObject*)obj;
}

int rich_compare(JsObject *obj0, JsObject *obj1){
    if (obj0->type != obj1->type)
        return 0;
    if (obj0->type == (JsType_Object*)(&JsString_Type)){
        JsStringObject *str_obj0 = (JsStringObject*)obj0;
        JsStringObject *str_obj1 = (JsStringObject*)obj1;
        if (str_obj0->ob_hash != str_obj1->ob_hash)
            return 0;
        if (strcmp(str_obj0->ob_sval, str_obj1->ob_sval) != 0)
            return 0;
        return 1;
    }
    else 
        return 0;
    //TODO:other types
}

static JsEntryObject **LookUpItemInObject(JsObject *obj, JsObject *item){
    JsObjectObject *obj_obj = (JsObjectObject*)obj;
    JsEntryObject *ins_obj = (JsEntryObject*)item;
    unsigned int perturb, hash = ins_obj->me_hash, mask = obj_obj->ma_mask, i = mask;
    printf("%lu ", ((i << 2) + i + perturb + 1)&mask);
    for (perturb = hash; (i&mask) != 0; perturb >>= 5) {
        i = (i << 2) + i + perturb + 1;
        printf("%d ", i&mask);
        JsEntryObject **p_ent_obj = &obj_obj->ma_table[i&mask];
        JsEntryObject *ent_obj = *p_ent_obj;
        if (ent_obj == NULL|| rich_compare(ent_obj->key, ins_obj->key)){
            puts("");
            return p_ent_obj;
        }
    }    
    // according to above algorithm,
    // this part can't be reached
    puts(GetStringValue(ins_obj->key));
    printf("%d %d\n", obj_obj->ma_mask, ins_obj->me_hash);
    
    printf("wrong branch\n");
    return NULL;
}

static void SetEntry(JsEntryObject **index, JsEntryObject *ins_item){
    DestroyEntry((JsObject*)(*index));
    *index = ins_item;
}

static void DirectInsertItemToObject(JsObject *obj, JsObject *item){
    JsObjectObject *obj_obj = (JsObjectObject*)obj;
    JsEntryObject **p_ent_obj = LookUpItemInObject(obj, item);
    SetEntry(p_ent_obj, (JsEntryObject*)item);
    ++obj_obj->ma_fill;
}

void InsertEntryToObject(JsObject *obj, JsObject *entry){
    JsEntryObject *ent_obj = (JsEntryObject*)entry;
    JsObjectObject *obj_obj = (JsObjectObject*)obj;
    if ((obj_obj->ma_fill+1)*3 >= (obj_obj->ob_size)*2){
        puts("enter41111");
        JsEntryObject **old_items = obj_obj->ma_table;
        int i;
        obj_obj->ma_table = (JsEntryObject**)calloc(((obj_obj->ob_size)<<1), sizeof(JsEntryObject*));
        obj_obj->ma_fill = 0;
        obj_obj->ob_size <<=1;
        obj_obj->ma_mask = obj_obj->ob_size-1;
        //copy
        for ( i = 0; i <= (obj_obj->ma_mask>>1); ++i)
            if (old_items[i] != NULL){
                DirectInsertItemToObject((JsObject*)obj_obj, (JsObject*)old_items[i]);
                if (*LookUpItemInObject((JsObject*)obj_obj, (JsObject*)old_items[i]) != old_items[i]){
                    puts("enter 8888");
                }
            }
        free(old_items);
    }
    DirectInsertItemToObject((JsObject*)obj_obj, (JsObject*)ent_obj);
}


void InsertItemToObject(JsObject *obj, char *key, JsObject *value){
    JsObject *ent_obj = CreateEntry(CreateString(key), value);
    return InsertEntryToObject(obj, ent_obj);
}

void AddItemToObject(JsObject *obj, char *key, JsObject *value){
    InsertItemToObject(obj, key, value);
}

void ReplaceItemInObject(JsObject *obj, char *key, JsObject *value){
    InsertItemToObject(obj, key, value);
}

JsObject* GetItemInObject(JsObject *obj, char *key){
    JsObject *key_obj = CreateString(key);
    JsObject *ent_obj = CreateEntry(key_obj, NULL);
    JsEntryObject *ret_obj = (*LookUpItemInObject(obj, ent_obj));
    if (ret_obj == NULL)
        return NULL;
    else
        return ret_obj->me_value;
}

JsObject *DetachItemFromObject(JsObject *obj, char *str){
    JsObject *ent_obj = CreateEntry(CreateString(str), NULL);
    JsEntryObject **ret_obj = LookUpItemInObject(obj, ent_obj);
    if ((*ret_obj) == &dummy|| (*ret_obj) == NULL){
        printf("enter %lu\n", ret_obj-((JsObjectObject*)obj)->ma_table);
        puts("enter 404");
        return NULL;
    }
    else{
        ent_obj = (*ret_obj)->me_value;
        *ret_obj = &dummy;
        return ent_obj;
    }
}

void DeleteItemFromObject(JsObject *obj, char *str){
    JsObject *ret_obj = DetachItemFromObject(obj, str);
    if (ret_obj != NULL){
        ret_obj->type->tp_destroy(ret_obj);
    }
}
