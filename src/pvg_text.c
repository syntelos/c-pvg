/*
 * page svg from text
 * Copyright 2024 John Douglas Pritchard, Syntelos
 */
#include "pvg.h"
#include <stdlib.h>
#include <string.h>

pvg_text* pvg_text_read(const char *filename){
  pvg_file *file = pvg_file_read(filename);
  if (null != file){
    pvg_text *text = pvg_text_new();
    pvg_string inl;
    while (pvg_readline(&inl,file) && pvg_text_append(text,&inl)){
      continue;
    }
    return text;
  }
  else {
    return null;
  }
}

pvg_text* pvg_text_new(){
  return calloc(1,sizeof(pvg_text));
}

size_t pvg_text_count(pvg_text *doc){
  size_t count = 0;
  while (pvg_text_not_terminal(doc)){

    count += 1;
  }
  return count;
}

pvg_text* pvg_text_append(pvg_text *oarray, pvg_string *line){
  if (null != oarray && null != line){
    size_t ocount = pvg_text_count(oarray);
    size_t ncount = (ocount+2);
    pvg_text *narray = calloc(ncount,sizeof(pvg_text));
    if (null != narray){
      size_t extant = (ocount*sizeof(pvg_text));
      memcpy(narray,oarray,extant);
      memset(oarray,0,extant);
      free(oarray);
      oarray = null;
      {
	pvg_text *record = (narray+ocount);
	pvg_string *text = &(record->text);
	pvg_string *link = &(record->link);

	char *src_text = (char*)line;

	char *ht = memchr(line,'\t',line->length);
	if (null != ht){
	  char *nl = memchr(line,'\n',line->length);
	  ssize_t cnt_text = (ht-src_text);
	  char *src_link = (ht+1);
	  ssize_t cnt_link = (nl-src_link);

	  memcpy(text,src_text,cnt_text);
	  text->length = cnt_text;

	  memcpy(link,src_link,cnt_link);
	  link->length = cnt_link;
	}
	else {
	  char *nl = strchr(src_text,'\n');
	  ssize_t cnt_text = (nl-src_text);

	  memcpy(text,src_text,cnt_text);
	  text->length = cnt_text;
	}
      }
      return narray;
    }
  }
  return oarray;
}
