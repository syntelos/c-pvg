/*
 * syntelos common text operators
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#include "txt_cc_xr.h"
#include <string.h>

bool_t txt_cc_xr_class(const char ch){

  if (('a' <= ch && 'z' >= ch) ||
      ('A' <= ch && 'Z' >= ch) ||
      ('0' <= ch && '9' >= ch)){

    return true;
  }
  else {
    switch (ch){
    case '#':
    case '%':
    case '&':
    case '+':
    case '-':
    case '.':
    case '/':
    case ':':
    case '=':
    case '?':
    case '@':
    case '_':
    case '~':
      return true;
    default:
      return false;
    }
  }
}

size_t txt_cc_xr_sz(const char *sp){
  size_t count = 0;
  if (null != sp){
    char ch = *sp;
    while (txt_cc_xr_class(ch)){

      count += 1;
      sp += 1;
      ch = *sp;
    }
  }
  return count;
}

bool_t txt_cc_xr_is(const char *sp){
  size_t z = txt_cc_xr_sz(sp);
  if (0 < z){

    sp += z;

    return (0 == *sp);
  }
  return false;
}

bool_t txt_cc_xr_not_class(const char ch){

  if (('a' > ch || 'z' < ch) &&
      ('A' > ch && 'Z' < ch) &&
      ('0' > ch && '9' < ch)){

    return true;
  }
  else {
    switch (ch){
    case '#':
    case '%':
    case '&':
    case '+':
    case '-':
    case '.':
    case '/':
    case ':':
    case '=':
    case '?':
    case '@':
    case '_':
    case '~':
      return false;
    default:
      return true;
    }
  }
}

size_t txt_cc_xr_not_sz(const char *sp){
  size_t count = 0;
  if (null != sp){
    char ch = *sp;
    while (txt_cc_xr_not_class(ch)){

      count += 1;
      sp += 1;
      ch = *sp;
    }
  }
  return count;
}

bool_t txt_cc_xr_not_is(const char *sp){
  size_t z = txt_cc_xr_not_sz(sp);
  if (0 < z){

    sp += z;

    return (0 == *sp);
  }
  return false;
}
