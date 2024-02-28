/*
 * syntelos common text operators
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#ifndef _txt_symbol_h
#define _txt_symbol_h

#include "syntelos.h"
/*
 * Symbolic register common to referential syntactic
 * operations in process heap memory (not mapped file
 * memory) employed by operational context.
 */
#define txt_symbol_size 0x100
typedef char txt_symbol[txt_symbol_size];
/*
 * Generic symbolic user common to referential symbolic
 * binding is defined by argument size to the binding
 * operator functions.
 */
typedef struct {
  txt_symbol source;
} txt_symbol_rec;
/*
 * Passive binding operator returns existing record,
 * otherwise null.  Arguments table, count, object
 * reference, and (record) size.  Returns record pointer
 * into argument table, otherwise null for error or not
 * found.
 */
ptr_t txt_symbol_record(ptr_t,size_t,const char*,size_t);
/*
 * Active binding operator returns new table (first record),
 * otherwise null.  Arguments table, count, object 
 * reference, and (record) size.  Returns null for error, 
 * otherwise argument (old) table or new table.
 */
ptr_t txt_symbol_table(ptr_t,size_t,const char*,size_t);
/*
 * Derive principal symbolic member from argument class.
 */
const char* txt_symbol_class(const char*);
/*
 * Clear and free type txt_symbol.
 */
void txt_symbol_free(ptr_t);
/*
 * Clear and free array of txt_symbol.
 */
void txt_symbol_array_free(ptr_t,size_t,size_t);

#endif
