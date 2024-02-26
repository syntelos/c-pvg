/*
 * page svg from text
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#ifndef _pvg_string_h
#define _pvg_string_h

#include "syntelos.h"
/*
 * A fixed length buffer operates as a C string with a
 * length field.
 */
#define pvg_string_buffer_size 0x100

typedef struct {
  char buffer[pvg_string_buffer_size];
  size_t length;
} pvg_string;

#endif
