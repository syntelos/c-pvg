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
#include "txt_path.h"
#include "txt_cc_id.h"
#include <stdlib.h>
#include <string.h>

txt_string* txt_path_array_append(txt_string *path, const char *expression, size_t begin, size_t end){
  ssize_t length = (end-begin);
  if (0 < length){
    size_t limit = (txt_string_buffer_size-1);
    size_t count = length;
    size_t size = min(count,limit);
    char *substring = calloc(1,size+1);

    memcpy(substring,(expression+begin),count);

    path = txt_string_array_append(path,substring);

    free(substring);
  }
  return path;
}

txt_string* txt_path_expression(const char *expression){
  txt_string *path = null;
  if (null != expression){

    size_t ofs = 0, len = strlen(expression);
    for (; ofs < len; ofs++){

      if (txt_cc_id_not_class(expression[ofs])){

	continue;
      }
      else {
	size_t begin = ofs, end = ofs+txt_cc_id_sz(expression+ofs);

	path = txt_path_array_append(path,expression,begin,end);

	ofs = end;
      }
    }
  }
  return path;
}

txt_string* txt_path_hierarchy(const char *expression){
  txt_string *path = null;
  if (null != expression){

    size_t begin = 0, end = 0;
    size_t ofs = 0, len = strlen(expression);
    for (; ofs < len; ofs++){

      if (txt_cc_id_not_class(expression[ofs])){
	end = ofs;

	path = txt_path_array_append(path,expression,begin,end);

	begin = end;
	ofs = begin;
      }
    }
  }
  return path;
}
