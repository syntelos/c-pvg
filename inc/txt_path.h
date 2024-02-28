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
