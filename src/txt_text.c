/*
 * syntelos common text operators
 * Copyright 2024 John Douglas Pritchard, Syntelos
 */
#include "txt_file.h"
#include "txt_text.h"
#include <stdlib.h>
#include <string.h>

txt_text* txt_text_read(const char *filename){
  txt_file *file = txt_file_read(filename);
  if (null != file){
    txt_text *text = txt_text_new();
    if (null != text){
      txt_string inl;
      while (txt_file_readline(&inl,file)){

	text = txt_text_append(text,&inl);
      }
      return text;
    }
  }
  return null;
}

txt_text* txt_text_new(){
  return calloc(1,sizeof(txt_text));
}

bool_t txt_text_terminal(txt_text *record){
  return (null != record && 0 == record->text.length);
}

bool_t txt_text_not_terminal(txt_text *record){
  return (null != record && 0 != record->text.length);
}

size_t txt_text_length(txt_text *doc){
  if (null != doc){
    size_t count = 0;
    for (; txt_text_not_terminal(doc); doc++){

      count += 1;
    }
    return count;
  }
  else {
    return 0;
  }
}

size_t txt_text_count(txt_text *doc){
  if (null != doc){
    size_t count = 1;
    for (; txt_text_not_terminal(doc); doc++){

      count += 1;
    }
    return count;
  }
  else {
    return 0;
  }
}

txt_text* txt_text_append(txt_text *oarray, txt_string *line){
  if (null != oarray && null != line && 0 != line->length){
    size_t ocount = txt_text_count(oarray);
    size_t ncount = (ocount+1);
    txt_text *narray = calloc(ncount,sizeof(txt_text));
    if (null != narray){
      size_t extant = (ocount*sizeof(txt_text));
      memcpy(narray,oarray,extant);
      memset(oarray,0,extant);
      free(oarray);
      oarray = null;

      off_t rindex = (ocount-1);
      txt_text *record = (narray+rindex);
      txt_string *text = &(record->text);
      txt_string *link = &(record->link);

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
