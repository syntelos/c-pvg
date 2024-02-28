/*
 * syntelos common text operators
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#include "txt_cc_in.h"
#include "txt_cc_id.h"
#include "txt_cc_ws.h"
#include <stdlib.h>
#include <string.h>

bool_t txt_cc_in_append(txt_cc_in *mp, char *src, size_t begin, size_t end){
  if (null != mp && null != src){
    off_t len = (end-begin);
    if (0 < len){
      char *cid = calloc(1,len+1);
      if (null != cid){
	if (cid == memcpy(cid,&(src[begin]),len)){
	  size_t ocount = mp->count;
	  char **ovector = mp->vector;

	  size_t ncount = (mp->count+1);
	  char **nvector = calloc(ncount,sizeof(ptr_t));
	  if (null != ovector && 0 != ocount && nvector == memcpy(nvector,ovector,mp->count)){

	    nvector[mp->count] = cid;

	    memset(ovector,0,ocount*sizeof(ptr_t));
	    free(ovector);

	    mp->count = ncount;
	    mp->vector = nvector;
	  }
	  else {
	    nvector[0] = cid;

	    mp->count = ncount;
	    mp->vector = nvector;
	  }
	}
      }
    }
  }
  return false;
}

txt_cc_in* txt_cc_in_parse(char *expression){
  txt_cc_in *path = calloc(1,sizeof(txt_cc_in));
  if (null != path){

    size_t ofs = 0, len = strlen(expression);
    for (; ofs < len; ofs++){

      if (txt_cc_ws_class(expression[ofs])){

	continue;
      }
      else {

	size_t begin = ofs, end = ofs+txt_cc_ws_not_sz(expression+ofs);
	if (txt_cc_in_append(path,expression,begin,end)){

	  ofs = end;
	  continue;
	}
	else {
	  break;
	}
      }
    }
  }
  return path;
}

void txt_cc_in_free(txt_cc_in *mp){
  if (null != mp){
    size_t count = mp->count;
    char **vector = mp->vector;

    if (0 != count && null != vector){
      size_t ix = 0, iz = count;
      for (; ix < iz; ix++){

	char *substring = vector[ix];
	free(substring);
      }

      memset(vector,0,(count*sizeof(ptr_t)));
      free(vector);
    }
    memset(mp,0,sizeof(txt_cc_in));
    free(mp);
  }
}
