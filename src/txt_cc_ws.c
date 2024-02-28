/*
 * syntelos common text operators
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#include "txt_cc_ws.h"
#include <string.h>

bool_t txt_cc_ws_class(const char ch){
  switch (ch){
  case '\t':
  case '\r':
  case '\n':
  case ' ':
    return true;
  default:
    return false;
  }
}

size_t txt_cc_ws_sz(const char *sp){
  size_t count = 0;
  if (null != sp){
    char ch = *sp;
    while (txt_cc_ws_class(ch)){

      count += 1;
      sp += 1;
      ch = *sp;
    }
  }
  return count;
}

bool_t txt_cc_ws_is(const char *sp){
  size_t z = txt_cc_ws_sz(sp);
  if (0 < z){

    sp += z;

    return (0 == *sp);
  }
  return false;
}

bool_t txt_cc_ws_not_class(const char ch){

  return (0x21 <= ch && 0x7E >= ch);
}

size_t txt_cc_ws_not_sz(const char *sp){
  size_t count = 0;
  if (null != sp){
    char ch = *sp;
    while (txt_cc_ws_not_class(ch)){

      count += 1;
      sp += 1;
      ch = *sp;
    }
  }
  return count;
}

bool_t txt_cc_ws_not_is(const char *sp){
  size_t z = txt_cc_ws_sz(sp);
  if (0 < z){

    sp += z;

    return (0 == *sp);
  }
  return false;
}
