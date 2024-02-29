/*
 * syntelos common text operators
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#ifndef _txt_cc_h
#define _txt_cc_h

#include "syntelos.h"
/*
 * Character class operator types
 */
typedef bool_t (*txt_cc_class)(const char);
typedef size_t (*txt_cc_sz)(const char*);
typedef bool_t (*txt_cc_is)(const char*);

#include "txt_cc_id.h"
#include "txt_cc_ws.h"
#include "txt_cc_group.h"
#endif
