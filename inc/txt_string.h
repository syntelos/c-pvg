/*
 * syntelos common text operators
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#ifndef _txt_string_h
#define _txt_string_h

#include "syntelos.h"
/*
 * A fixed length buffer operates as a C string with a
 * length field.  Typically employed as a stack variable,
 * and managed explicitly inline.  The array variation on
 * the theme is employed functionally.  The handling of
 * arrays is too complex for inlining.
 */
#define txt_string_buffer_size 0x100

typedef struct {
  char buffer[txt_string_buffer_size];
  size_t length;
} txt_string;
/*
 * Allocate empty string array.
 */
txt_string* txt_string_array();
/*
 * Allocate non-empty string array.
 */
txt_string* txt_string_array_create(const char*);
/*
 */
bool_t txt_string_empty(txt_string*);
/*
 */
bool_t txt_string_not_empty(txt_string*);
/*
 * Quantification of the membership of the string array,
 * inclusive of empty (null) terminal.
 */
size_t txt_string_array_count(txt_string*);
/*
 * Quantification of the non-empty (non-null) membership of
 * the string array, not inclusive of empty (null) terminal.
 */
size_t txt_string_array_length(txt_string*);
/*
 * Clear and free string object array.
 */
void txt_string_array_destroy(txt_string*);
/*
 * Prepend member to head of array.
 */
txt_string* txt_string_array_insert(txt_string*, const char*);
/*
 * Append member to tail of array.
 */
txt_string* txt_string_array_append(txt_string*, const char*);

#endif
