/*
 * syntelos common text operators
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#include "txt_cc.h"
#include "txt_span_group.h"
#include <string.h>

bool_t txt_cc_group_class(const char ch){
  switch(ch){
  case '(':
  case ')':
  case '<':
  case '>':
  case '[':
  case ']':
  case '{':
  case '}':
  case ':':
    return true;
  default:
    return txt_cc_id_class(ch);
  }
}
size_t txt_cc_group_sz(const char *string){
  if (null != string){
    txt_span_group *sp;

    switch (*string){
    case '(':
    case '<':
    case '[':
    case '{':
      sp = txt_span_group_group_read(null,0,string,strlen(string));
      if (null != sp){
	size_t begin = sp->begin;
	size_t end = sp->end;

	txt_span_group_destroy(sp);

	if (0 == begin){
	  return end;
	}
      }
      break;
    default:
      return txt_cc_id_sz(string);
    }
  }
  return 0;
}
bool_t txt_cc_group_is(const char *sp){
  size_t z = txt_cc_group_sz(sp);
  if (0 < z){

    sp += z;

    return (0 == *sp);
  }
  return false;
}

bool_t txt_cc_group_not_class(const char ch){
  switch(ch){
  case '(':
  case ')':
  case '<':
  case '>':
  case '[':
  case ']':
  case '{':
  case '}':
  case ':':
    return false;
  default:
    return txt_cc_id_not_class(ch);
  }
}
size_t txt_cc_group_not_sz(const char *sp){
  size_t count = 0;
  if (null != sp){
    char ch = *sp;
    while (txt_cc_group_not_class(ch)){

      count += 1;
      sp += 1;
      ch = *sp;
    }
  }
  return count;
}
bool_t txt_cc_group_not_is(const char *sp){
  size_t z = txt_cc_group_not_sz(sp);
  if (0 < z){

    sp += z;

    return (0 == *sp);
  }
  return false;
}
