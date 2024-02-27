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

#define pvg_text_terminal(p) null != p && 0 == p->text.length

#define pvg_text_not_terminal(p) null != p && 0 != p->text.length
/*
 * An array of pvg_text blocks is null terminated.
 */
size_t pvg_text_count(pvg_text*);
/*
 * An array of pvg_text blocks is null terminated.
 */
pvg_text* pvg_text_append(pvg_text*,pvg_string*);

#endif
