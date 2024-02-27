/*
 * page svg from text
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#ifndef _pvg_text_h
#define _pvg_text_h

#include "syntelos.h"
#include "pvg_string.h"
/*
 * PVG plain text line includes an optional tab url suffix.
 * 
 * An array of pvg_text blocks is null terminated.
 */
typedef struct {
  pvg_string text;
  pvg_string link;
} pvg_text;

pvg_text* pvg_text_read(const char*);
/*
 * An array of pvg_text blocks is null terminated.
 */
pvg_text* pvg_text_new();
/*
 * Array element is tail null.
 */
bool_t pvg_text_terminal(pvg_text*);
/*
 * Array element is not tail null.
 */
bool_t pvg_text_not_terminal(pvg_text*);
/*
 * An array of pvg_text blocks is null terminated.  Number
 * of records in array, exclusive of terminal.
 */
size_t pvg_text_length(pvg_text*);
/*
 * An array of pvg_text blocks is null terminated.  Number
 * of records in array, inclusive of terminal.
 */
size_t pvg_text_count(pvg_text*);
/*
 * An array of pvg_text blocks is null terminated.
 */
pvg_text* pvg_text_append(pvg_text*,pvg_string*);

#endif
