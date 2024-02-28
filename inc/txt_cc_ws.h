/*
 * syntelos common text operators
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#ifndef _txt_cc_ws_h
#define _txt_cc_ws_h

#include "syntelos.h"
/*
 * Identifier CC := [a-zA-Z0-9]
 */
bool_t txt_cc_ws_class(const char);
size_t txt_cc_ws_sz(const char*);
bool_t txt_cc_ws_is(const char*);

bool_t txt_cc_ws_not_class(const char);
size_t txt_cc_ws_not_sz(const char*);
bool_t txt_cc_ws_not_is(const char*);

#endif
