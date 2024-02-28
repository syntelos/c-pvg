/*
 * syntelos common text operators
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#include "txt_symbol.h"
#include "txt_cc_id.h"
#include <stdlib.h>
#include <string.h>

ptr_t txt_symbol_record(ptr_t table, size_t count, const char *ref, size_t size){
  if (null != table && 0 != count && null != ref && 0 != size){

    const char *symbol = txt_symbol_class(ref);
    size_t symbol_size = strlen(symbol)+1;

    int sign = 0;
    off_t index = (count>>1);
    ptr_t record = table+(index*size);
    /*
     * Partition search: scan the table between the lexical
     * median and boundary.  O(n/2) lookup.
     */
    while (0 <= index && index < count){

      int cmp = memcmp(record,symbol,symbol_size);
      if (0 == cmp){
	return record;
      }
      else if (cmp < 0){
	if (0 == sign){
	  sign = 1;
	  record += size;
	  index += 1;
	}
	else if (0 < sign){
	  record += size;
	  index += 1;
	}
	else {
	  return null;
	}
      }
      else {
	if (0 == sign){
	  sign = -1;
	  record -= size;
	  index -= 1;
	}
	else if (0 > sign){
	  record -= size;
	  index -= 1;
	}
	else {
	  return null;
	}
      }
    }
  }
  return null;
}

void txt_symbol_rec_swap(ptr_t *a, ptr_t *b, size_t size){
  txt_symbol_rec reg;
  memcpy(&reg,a,size);
  memcpy(a,b,size);
  memcpy(b,&reg,size);
}

ptr_t txt_symbol_table(ptr_t otable, size_t ocount, const char *ref, size_t size){
  if (null != txt_symbol_record(otable,ocount,ref,size)){
    return null;
  }
  else {
    const char *symbol = txt_symbol_class(ref);
    const size_t symbol_size = strlen(symbol)+1;

    size_t ncount = (ocount+1);
    txt_symbol_rec *ntable = (txt_symbol_rec*)calloc(ncount,size);
    if (null != ntable){
      if (0 != ocount){
	if (1 == ocount){
	  /*
	   * Primitive insertion sort
	   */
	  ptr_t otab = otable, ntab = ntable;
	  if (0 < memcmp(otab,symbol,symbol_size)){
	    memcpy(ntab,symbol,symbol_size);
	    ntab += size;
	    memcpy(ntab,otab,size);
	  }
	  else {
	    memcpy(ntab,otab,size);
	    ntab += size;
	    memcpy(ntab,symbol,symbol_size);
	  }
	  memset(otable,0,ocount*size);
	  free(otable);
	  otable = null;
	}
	else {
	  /*
	   * Simple insertion sort
	   */
	  off_t insertion = -1;
	  bool_t inserted = false;
	  {
	    off_t index;
	    ptr_t otab = otable, ntab = ntable;
	    for (index = 0; index < ocount; index++, otab += size, ntab += size){

	      if (inserted){
		memcpy(ntab,otab,size);
	      }
	      else if (0 < memcmp(otab,symbol,symbol_size)){
		inserted = true;
		insertion = index;
		memcpy(ntab,symbol,symbol_size);
		ntab += size;
		memcpy(ntab,otab,size);
	      }
	      else {
		memcpy(ntab,otab,size);
	      }
	    }
	    memset(otable,0,ocount*size);
	    free(otable);
	    otable = null;
	    if (!inserted){
	      /*
	       * Simple append order (no review).
	       */
	      memcpy(ntab,symbol,symbol_size);
	    }
	  }
	  /*
	   * Partition sort review of table order.
	   */
	  if (inserted){
	    off_t a = insertion, b = ncount, i, j;
	    ptr_t x, y;
	    for (i = (a+1); i < b; i++){
	      for (j = i; j > a; j--){
		x = (ntable+(j*size));
		y = (ntable+((j-1)*size));
		if (0 > memcmp(x,y,txt_symbol_size)){

		  txt_symbol_rec_swap(x,y,size);
		}
		else {
		  break;
		}
	      }
	    }
	  }
	}
      }
      else {
	memcpy(ntable,symbol,symbol_size);
      }
      return ntable;
    }
  }
  return null;
}

const char* txt_symbol_class(const char *object){
  if (null != object){
    size_t count = strlen(object);
    off_t index = (count-1);
    for (; 0 <= index; index--){
      if (txt_cc_id_not_class(object[index])){

	return &(object[index+1]);
      }
    }
  }
  return object;
}

void txt_symbol_free(ptr_t symbol){
  if (null != symbol){
    memset(symbol,0,txt_symbol_size);
    free(symbol);
  }
}

void txt_symbol_array_free(ptr_t array, size_t count, size_t size){
  if (null != array){
    memset(array,0,(count*size));
    free(array);
  }
}
