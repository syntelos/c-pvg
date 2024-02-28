/*
 * syntelos common text operators
 * Copyright (C) 2024, John Pritchard, Syntelos
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
