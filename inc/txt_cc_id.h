/*
 * syntelos common text operators
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#ifndef _txt_cc_id_h
#define _txt_cc_id_h

#include "syntelos.h"
/*
 * Identifier CC := [a-zA-Z0-9]
 */
bool_t txt_cc_id_class(const char);
size_t txt_cc_id_sz(const char*);
bool_t txt_cc_id_is(const char*);

bool_t txt_cc_id_not_class(const char);
size_t txt_cc_id_not_sz(const char*);
bool_t txt_cc_id_not_is(const char*);
/*
 * Branch membership (A < B): A is a leading substring of B,
 * and B differs from A by a following path separator and
 * identifier.
 */
bool_t txt_cc_id_branch(const char*,const char*);

#endif
