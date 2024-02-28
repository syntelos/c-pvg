/*
 * syntelos common text operators
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#include <string.h>
#include <stdlib.h>

#include "txt_span.h"

txt_span *txt_span_init(txt_span* state, off_t offset, const char *source, size_t length){

    if (null != source && 0 != length){

        if (null == state){

            state = calloc(1,sizeof(txt_span));
        }
        else {

            memset(state,0,sizeof(txt_span));
        }

        if (null != state){

            state->source = source;
            state->length = length;
            state->begin = offset;
            state->end = offset;
        }
    }
    return state;
}
void txt_span_destroy(txt_span* state){

    if (null != state){

        memset(state,0,sizeof(txt_span));
        free(state);
    }
}
char txt_span_target(char lhs){
    switch(lhs){
    case '<':
        return '>';
    case '[':
        return ']';
    case '{':
        return '}';
    case '(':
        return ')';
    default:
        return 0;
    }
}
txt_span_class txt_span_classification(char lhs){
    switch(lhs){
    case '<':
        return txt_span_class_object;
    case '[':
        return txt_span_class_vector;
    case '{':
        return txt_span_class_record;
    case '(':
        return txt_span_class_group;
    default:
        return txt_span_class_unknown;
    }
}
bool_t txt_span_read_close(txt_span *scope, off_t offset, const char *source, size_t length){
    if (null != scope && null != source && 0 != length){

        char lhs = txt_span_ascii(source[scope->begin]);
        char rhs = txt_span_target(lhs);

        if (0 != rhs){
            off_t nesting = 0;
            off_t ofs;

            for (ofs = (offset+1); ofs < length; ofs++){

                char co = txt_span_ascii(source[ofs]);

                if (rhs == co){

                    if (0 == nesting){

                        scope->class = txt_span_classification(lhs);

                        scope->end = (ofs+1);

                        return true;
                    }
                    else {

                        nesting -= 1;
                    }
                }
                else if (lhs == co){

                    nesting += 1;
                }
            }
        }
    }
    return false;
}
txt_span* txt_span_group_read(txt_span* state, off_t offset, const char *source, size_t length){
    if (null != source && 0 != length){

        bool_t new = (null == state);

        state = txt_span_init(state,offset,source,length);
        if (null != state){

            for (; offset < length; offset++){

                char co = txt_span_ascii(source[offset]);
                if (txt_span_is_open(co)){

                    state->end = offset;
                    state->begin = offset;

                    if (txt_span_read_close(state,offset,source,length)){

                        return state;
                    }
                }
                else if (txt_span_is_wspace(co)){

                    if (offset > state->begin){

                        state->end = offset;

                        return state;
                    }
                    else if (new){

                        free(state);

                        return null;
                    }
                    else {

                        return null;
                    }
                }
            }

            if (new){

                free(state);
            }
        }
    }
    return null;
}
