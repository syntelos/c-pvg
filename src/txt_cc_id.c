/*
 * syntelos common text operators
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#include "txt_cc_id.h"
#include <string.h>

bool_t txt_cc_id_class(const char ch){

  return (('a' <= ch && 'z' >= ch) ||
	  ('A' <= ch && 'Z' >= ch) ||
	  ('0' <= ch && '9' >= ch));
}

size_t txt_cc_id_sz(const char *sp){
  size_t count = 0;
  if (null != sp){
    char ch = *sp;
    while (txt_cc_id_class(ch)){

      count += 1;
      sp += 1;
      ch = *sp;
    }
  }
  return count;
}

bool_t txt_cc_id_is(const char *sp){
  size_t z = txt_cc_id_sz(sp);
  if (0 < z){

    sp += z;

    return (0 == *sp);
  }
  return false;
}

bool_t txt_cc_id_not_class(const char ch){

  return (('a' > ch || 'z' < ch) &&
	  ('A' > ch && 'Z' < ch) &&
	  ('0' > ch && '9' < ch));
}

size_t txt_cc_id_not_sz(const char *sp){
  size_t count = 0;
  if (null != sp){
    char ch = *sp;
    while (txt_cc_id_not_class(ch)){

      count += 1;
      sp += 1;
      ch = *sp;
    }
  }
  return count;
}

bool_t txt_cc_id_not_is(const char *sp){
  size_t z = txt_cc_id_not_sz(sp);
  if (0 < z){

    sp += z;

    return (0 == *sp);
  }
  return false;
}

bool_t txt_cc_id_branch(const char *parent, const char *child){
  if (null != parent && null != child){

    size_t parent_len = strlen(parent);
    if (0 == strncmp(parent,child,parent_len)){

      size_t child_len = strlen(child);
      if ((parent_len+2) <= child_len && '/' == child[parent_len]){

	const char *child_brid = (child+parent_len+1);
	size_t child_brid_len = txt_cc_id_sz(child_brid);
	size_t membership = (parent_len+1+child_brid_len);

	return (membership == child_len);
      }
    }
  }
  return false;
}
