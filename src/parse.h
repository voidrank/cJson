#ifdef PARSE_H
#define PARSE_H

#include "JSON.h"

JsObject *non_type_parse();
JsObject *null_type_parse();
JsObject *true_type_parse();
JsObject *false_type_parse();
JsObject *num_type_parse();
JsObject *string_type_parse();
JsObject *array_type_parse();
JsObject *entry_type_parse();
JsObject *object_type_parse();

/* Parse & Print */
extern JSON *ParseJSON( char *value);
extern JSON *ParseJSONFromFile( char *file_name);



#endif

