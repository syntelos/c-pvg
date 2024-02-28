/*
 * syntelos common text operators
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#ifndef _txt_path_h
#define _txt_path_h

#include "syntelos.h"
#include "txt_string.h"
/*
 * Map code to content: a list of independent identifiers.
 */
txt_string* txt_path_expression(const char*);
/*
 * Map code to branch set hierarchy.  Subsets of expanding
 * membership: from the first identity; to the expression
 * set.  Trailing separators are excluded.  Leading
 * separators are included.
 */
txt_string* txt_path_hierarchy(const char*);

#endif
