/*
 * syntelos common text operators
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#ifndef _txt_text_h
#define _txt_text_h

#include "syntelos.h"
#include "txt_string.h"
/*
 * TXT plain text line includes an optional tab url suffix.
 * 
 * An array of txt_text blocks is null terminated.
 */
typedef struct {
  txt_string text;
  txt_string link;
} txt_text;

txt_text* txt_text_read(const char*);
/*
 * An array of txt_text blocks is null terminated.
 */
txt_text* txt_text_new();
/*
 * Array element is tail null.
 */
bool_t txt_text_terminal(txt_text*);
/*
 * Array element is not tail null.
 */
bool_t txt_text_not_terminal(txt_text*);
/*
 * An array of txt_text blocks is null terminated.  Number
 * of records in array, exclusive of terminal.
 */
size_t txt_text_length(txt_text*);
/*
 * An array of txt_text blocks is null terminated.  Number
 * of records in array, inclusive of terminal.
 */
size_t txt_text_count(txt_text*);
/*
 * An array of txt_text blocks is null terminated.
 */
txt_text* txt_text_append(txt_text*,txt_string*);

#endif
