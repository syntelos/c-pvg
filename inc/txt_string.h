/*
 * syntelos common text operators
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#ifndef _txt_string_h
#define _txt_string_h

#include "syntelos.h"
/*
 * A fixed length buffer operates as a C string with a
 * length field.
 */
#define txt_string_buffer_size 0x100

typedef struct {
  char buffer[txt_string_buffer_size];
  size_t length;
} txt_string;

#endif
