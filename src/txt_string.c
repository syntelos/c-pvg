/*
 * syntelos common text operators
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#include "txt_string.h"
#include <stdlib.h>
#include <string.h>

txt_string* txt_string_array(){
  return calloc(1,sizeof(txt_string));
}

txt_string* txt_string_array_create(const char *member){
    txt_string *array = calloc(2,sizeof(txt_string));
    if (null != array){
      size_t limit = (txt_string_buffer_size-1);
      size_t count = strlen(member);
      size_t size = min(count,limit);
      memcpy(array,member,size);
      array->length = count;
    }
    return array;
}

bool_t txt_string_empty(txt_string *object){
  return (null != object && 0 == object->length);
}

bool_t txt_string_not_empty(txt_string *object){
  return (null != object && 0 != object->length);
}

size_t txt_string_array_count(txt_string *array){
  if (null != array){
    size_t count = 1;
    for (; txt_string_not_empty(array); array++){

      count += 1;
    }
    return count;
  }
  else {
    return 0;
  }
}

size_t txt_string_array_length(txt_string *array){
  if (null != array){
    size_t count = 0;
    for (; txt_string_not_empty(array); array++){

      count += 1;
    }
    return count;
  }
  else {
    return 0;
  }
}

void txt_string_array_destroy(txt_string *array){
  if (null != array){
    size_t count = txt_string_array_count(array);
    size_t extent = count*sizeof(txt_string);
    memset(array,0,extent);
    free(array);
  }
}

txt_string* txt_string_array_insert(txt_string *oarray, const char *member){
  if (null != oarray){
    size_t ocount = txt_string_array_count(oarray);
    size_t ncount = (ocount+1);
    txt_string *narray = calloc(ncount,sizeof(txt_string));
    /*
     * Pre-existing state
     */
    {
      txt_string *target = (narray+1);
      txt_string *source = oarray;
      size_t extent = ocount*sizeof(txt_string);
      memcpy(target,source,extent);
    }
    /*
     * Insert novel state
     */
    {
      txt_string *record = narray;
      size_t limit = (txt_string_buffer_size-1);
      size_t count = strlen(member);
      size_t size = min(count,limit);
      memcpy(record,member,size);
      record->length = count;      
    }
    /*
     * Cleanup
     */
    {
      size_t extent = ocount*sizeof(txt_string);
      memset(oarray,0,extent);
      free(oarray);
    }
    return narray;
  }
  else {
    return txt_string_array_create(member);
  }
}

txt_string* txt_string_array_append(txt_string *oarray, const char *member){
  if (null != oarray){
    size_t ocount = txt_string_array_count(oarray);
    size_t ncount = (ocount+1);
    txt_string *narray = calloc(ncount,sizeof(txt_string));
    /*
     * Pre-existing state
     */
    {
      txt_string *target = narray;
      txt_string *source = oarray;
      size_t extent = ocount*sizeof(txt_string);
      memcpy(target,source,extent);
    }
    /*
     * Append novel state
     */
    {
      txt_string *record = (narray+ocount);
      size_t limit = (txt_string_buffer_size-1);
      size_t count = strlen(member);
      size_t size = min(count,limit);
      memcpy(record,member,size);
      record->length = count;      
    }
    /*
     * Cleanup
     */
    {
      size_t extent = ocount*sizeof(txt_string);
      memset(oarray,0,extent);
      free(oarray);
    }
    return narray;
  }
  else {
    return txt_string_array_create(member);
  }
}
