/*
 * syntelos common text operators
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#ifndef _txt_cc_xr_h
#define _txt_cc_xr_h

#include "syntelos.h"
/*
 * URI (XREF) CC
 */
bool_t txt_cc_xr_class(const char);
size_t txt_cc_xr_sz(const char*);
bool_t txt_cc_xr_is(const char*);

bool_t txt_cc_xr_not_class(const char);
size_t txt_cc_xr_not_sz(const char*);
bool_t txt_cc_xr_not_is(const char*);

#endif
