/*
 * syntelos common text operators
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#ifndef _txt_cc_in_h
#define _txt_cc_in_h

#include "syntelos.h"

typedef struct {
  size_t count;
  char **vector;
} txt_cc_in;

txt_cc_in* txt_cc_in_parse(char*);

void txt_cc_in_free(txt_cc_in*);

#endif
