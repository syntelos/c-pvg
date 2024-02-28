/*
 * interactive syntelos mechanical types
 * Copyright (C) 2024, John Pritchard, Syntelos
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * (LGPL and GPL) as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the LGPL
 * and GPL for more details.
 *
 * You should have received a copy of the LGPL and GPL along with this
 * program.  If not, see <http://www.gnu.org/licenses/>.
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
