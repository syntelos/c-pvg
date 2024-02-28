/*
 * syntelos common text operators
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#ifndef _txt_span_h
#define _txt_span_h

#include "syntelos.h"
/*
 */
typedef enum {
    txt_span_class_unknown = 0,
    txt_span_class_object  = '<',
    txt_span_class_record  = '{',
    txt_span_class_vector  = '[',
    txt_span_class_group   = '('

} txt_span_class;
/*
 */
typedef struct {

    const char *source;

    size_t length;

    txt_span_class class;

    off_t begin, end;

} txt_span;
/*
 * Re/initialize state of argument struct txt_span.
 */
txt_span* txt_span_init(txt_span*,off_t,const char*,size_t);
/*
 * Destroy argument struct span.
 */
void txt_span_destroy(txt_span*);
/*
 * Return matching pair terminal.
 */
char txt_span_target(char);
/*
 * Classify LHS character.
 */
txt_span_class txt_span_classification(char);
/*
 * Read source from offset into argument struct span.
 */
txt_span* txt_span_group_read(txt_span*,off_t,const char*,size_t);

#define txt_span_ascii(u8) (u8 & 0x7f)

#define txt_span_is_open(ch) (('(' == ch)||('<' == ch)||('[' == ch)||('{' == ch))

#define txt_span_is_close(ch) ((')' == ch)||('>' == ch)||(']' == ch)||('}' == ch))

#define txt_span_class_is_valid(cl) (txt_span_class_object == cl | txt_span_class_record == cl | txt_span_class_vector == cl | txt_span_class_group == cl)

#define txt_span_pointer(sp) (&(sp->source[sp->begin]))

#define txt_span_length(sp) (sp->end-sp->begin)

#define txt_span_is_wspace(ch) (('\a' == ch)||('\b' == ch)||('\t' == ch)||('\n' == ch)||('\v' == ch)||('\f' == ch)||('\r' == ch)||(' ' == ch))

#endif
