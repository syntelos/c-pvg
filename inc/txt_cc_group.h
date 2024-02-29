/*
 * syntelos common text operators
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#ifndef _txt_cc_group_h
#define _txt_cc_group_h

#include "syntelos.h"
/*
 * Group CC
 */
bool_t txt_cc_group_class(const char);
size_t txt_cc_group_sz(const char*);
bool_t txt_cc_group_is(const char*);

bool_t txt_cc_group_not_class(const char);
size_t txt_cc_group_not_sz(const char*);
bool_t txt_cc_group_not_is(const char*);

#endif
