main: libcjson.so JSON.h test.c
	clang test.c -L. -lcjson -Wall -g -o main

libcjson.so: typeobject.c nullobject.c trueobject.c falseobject.c \
	boolobject.c numobject.c stringobject.c arrayobject.c jsonobject.c JSON.h\
	parse.c parse.h
	clang typeobject.c nullobject.c trueobject.c falseobject.c \
		boolobject.c numobject.c stringobject.c arrayobject.c jsonobject.c \
		parse.c \
		-shared -fPIC -Wall -g -o libcjson.so


make clean:
	rm main libcjson.so
