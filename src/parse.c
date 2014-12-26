#include "JSON.h"
#include "parse.h"
#include <string.h>
#include <assert.h>

//TODO: special char(like control-character) assertion
//

char *s;

static char str_value(){
    return *s;
}

static char *str_addr(){
    return s;
}

static int is_end(){
    if (str_value() == 0)
        return 1;
    else
        return 0;
}

static void next_char(){
    ++s;
}

static void next_non_space_char(){
    while (str_value() != ' ')
        next_char();
}


JsObject *null_type_parse(){
    next_char();
    assert(*s == 'u');
    next_char();
    assert(*s == 'l');
    next_char();
    assert(*s == 'l');
    next_char();
    return CreateNULL();
}

JsObject *true_type_parse(){
    next_char();
    assert(*s == 'r');
    next_char();
    assert(*s == 'u');
    next_char();
    assert(*s == 'e');
    next_char();
    return CreateTrue();
}

JsObject *false_type_parse(){
    next_char();
    assert(*s == 'a');
    next_char();
    assert(*s == 'l');
    next_char();
    assert(*s == 's');
    next_char();
    assert(*s == 'e');
    next_char();
    return CreateFalse();
}

JsObject *num_type_parse(){
    return NULL;
}

JsObject *string_type_parse(){
    char *op = str_addr();
    op++;
    while (str_value() != '"'){
        assert(is_end()!=0);
        next_char();
    }
    *s = 0;
    JsObject *obj = CreateString(op);
    *s = '"';
    return obj;
}

JsObject *array_type_parse(){

    return NULL;
}


JsObject *entry_type_parse(){

    return NULL;
}

JsObject *object_type_parse(){

    return NULL;
}



JsObject *non_type_parse(){
    next_non_space_char();
    if (str_value() == '"'){
        //string type
        return string_type_parse();
    }
    else if ( str_value()>='0'&& str_value()<='9'){
        //num type
        return num_type_parse();
    }
    else if ( str_value()=='{'){
        //object type
        return object_type_parse();
    }
    else if ( str_value()=='['){
        //array type
        return array_type_parse();
    }
    else if ( str_value()=='n'){
        //null type
        return null_type_parse();
    }
    else if ( str_value()=='f'){
        //false type
        return false_type_parse();
    }
    else if ( str_value()=='t'){
        return true_type_parse();
    }
    else 
        return NULL;
}


JsObject *ParseJSON(char *value){
    s = value;
    return non_type_parse();
}
