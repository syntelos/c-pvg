/*
 * page svg from text
 * Copyright 2024 John Douglas Pritchard, Syntelos
 */
#include "pvg.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static const char *target_head[] = {
  "/*",
  " * page svg from text",
  " * Copyright (C) 2024, John Pritchard, Syntelos",
  " */",
  "#ifndef _pvg_page_h",
  "#define _pvg_page_h",
  ""
};
static const size_t target_head_count = 9;

static const char *target_tail[] = {
  "",
  "#endif"
};
static const size_t target_tail_count = 2;

size_t copy_page(char *buffer, size_t size, const char* source[], size_t source_len){
  if (null != buffer){
    char *bp = buffer;
    off_t idx, cnt;
    ssize_t sz = size;
    size_t output = 0;
    for (idx = 0, cnt = source_len; idx < cnt; idx++){
      int many = snprintf(bp,sz,"%s\n",source[idx]);
      if (0 < many && 0 < sz){
	bp += many;
	sz -= many;
	output += many;
	continue;
      }
      else {
	break;
      }
    }
    return output;
  }
  else {
    return 0;
  }
}
/*
 * Counting but not copying line terminals.
 */
bool_t readline(pvg_string *io, const char* source, size_t source_len){
  if (null != io && null != source && 0 < source_len){
    memset(io,0,sizeof(pvg_string));
    if ('\n' == *source){
      if (1 < source_len){
	io->length = 1;
	return true;
      }
    }
    else {
      const char *begin = source;
      char *end = strchr(source,'\n');
      if (end > begin){
	size_t count = (end-begin);
	memcpy(io,source,count);
	io->length = (count+1);
	return true;
      }
    }
  }
  return false;
}

#define isbreak_string "  <text "
#define isbreak_string_length 8

bool_t isbreak(pvg_string *io){
  return (0 == strncmp((const char*)io,isbreak_string,isbreak_string_length));
}

size_t encode_page(char *buffer, size_t size, const char* source, size_t source_len){
  size_t wr, line_count;

  char *bp = buffer;
  ssize_t bz = size;
  size_t output = 0;
  wr = snprintf(bp,bz,"static const char *page_head = {\n");
  bp += wr;
  bz -= wr;
  pvg_string line;
  const char *sp = source;
  size_t sz = source_len;
  while (readline(&line,sp,sz)){
    if (isbreak(&line)){
      sp += line.length;
      sz -= line.length;

      wr = snprintf(bp,sz,"};\n");
      bp += wr;
      bz -= wr;
      output += wr;

      wr = snprintf(bp,bz,"static const char *page_tail = {\n");
      bp += wr;
      bz -= wr;
      output += wr;
    }
    else {
      wr = snprintf(bp,sz,"  \"%s\",\n",(char*)(&line));
      bp += wr;
      bz -= wr;
      output += wr;

      sp += line.length;
      sz -= line.length;
    }
  }
  wr = snprintf(bp,sz,"};\n");
  bp += wr;
  bz -= wr;
  output += wr;

  return output;
}

int main(int argc, char **argv){
  char *source = "etc/page.svg";
  char *target = "inc/pvg_page.h";
  pvg_file *out = pvg_file_new(0x100000);
  if (null != out){
    char *bp = pvg_file_buffer(out);
    size_t bz = out->alloc;
    size_t oz, bo = 0;
    /*
     * Write target head
     */
    oz = copy_page(bp,bz,target_head,target_head_count);
    bp += oz;
    bz -= oz;
    bo += oz;
    /*
     * Read target body
     */
    pvg_file *in = pvg_file_read(source);
    if (null != in){
      char *source_svg = pvg_file_buffer(in);
      size_t source_svg_len = in->limit;
      /*
       * Encode target body
       */
      oz = encode_page(bp,bz,source_svg,source_svg_len);
      bp += oz;
      bz -= oz;
      bo += oz;
      /*
       * Write target tail
       */
      oz = copy_page(bp,bz,target_tail,target_tail_count);
      bp += oz;
      bz -= oz;
      bo += oz;
      /*
       * Write target file
       */
      out->limit = bo;
 
      if (pvg_file_write(out,target)){

	return 0;
      }
    }
  }
  return 1;
}
