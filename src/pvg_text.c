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
    if (null != text){
      pvg_string inl;
      while (pvg_file_readline(&inl,file)){

	text = pvg_text_append(text,&inl);
      }
      return text;
    }
  }
  return null;
}

pvg_text* pvg_text_new(){
  return calloc(1,sizeof(pvg_text));
}

bool_t pvg_text_terminal(pvg_text *record){
  return (null != record && 0 == record->text.length);
}

bool_t pvg_text_not_terminal(pvg_text *record){
  return (null != record && 0 != record->text.length);
}

size_t pvg_text_length(pvg_text *doc){
  if (null != doc){
    size_t count = 0;
    for (; pvg_text_not_terminal(doc); doc++){

      count += 1;
    }
    return count;
  }
  else {
    return 0;
  }
}

size_t pvg_text_count(pvg_text *doc){
  if (null != doc){
    size_t count = 1;
    for (; pvg_text_not_terminal(doc); doc++){

      count += 1;
    }
    return count;
  }
  else {
    return 0;
  }
}

pvg_text* pvg_text_append(pvg_text *oarray, pvg_string *line){
  if (null != oarray && null != line && 0 != line->length){
    size_t ocount = pvg_text_count(oarray);
    size_t ncount = (ocount+1);
    pvg_text *narray = calloc(ncount,sizeof(pvg_text));
    if (null != narray){
      size_t extant = (ocount*sizeof(pvg_text));
      memcpy(narray,oarray,extant);
      memset(oarray,0,extant);
      free(oarray);
      oarray = null;

      off_t rindex = (ocount-1);
      pvg_text *record = (narray+rindex);
      pvg_string *text = &(record->text);
      pvg_string *link = &(record->link);

      char *nl = (char*)line+line->length;
      char *ht = memchr(line,'\t',line->length);
      if (null != ht){
	char *src_text = (char*)line;
	ssize_t cnt_text = (ht-src_text);

	char *src_link = (ht+1);
	ssize_t cnt_link = (nl-src_link);

	memcpy(text,src_text,cnt_text);
	text->length = cnt_text;

	memcpy(link,src_link,cnt_link);
	link->length = cnt_link;

	return narray;
      }
      else {
	memcpy(text,line,line->length);
	text->length = line->length;

	return narray;
      }
    }
  }
  return oarray;
}
