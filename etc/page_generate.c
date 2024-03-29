/*
 * page svg from text
 * Copyright 2024 John Douglas Pritchard, Syntelos
 */
#include "pvg.h"
#include "txt_file.h"
#include "txt_string.h"
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
  "",
  "#define pvg_page_lh 18",
  "#define pvg_page_em 6",
  "#define pvg_page_x0 30",
  "#define pvg_page_y0 50",
  "",
};
static const size_t target_head_count = 12;

static const char *target_tail[] = {
  "",
  "#endif"
};
static const size_t target_tail_count = 2;

size_t copy_page(char *buffer, size_t size, const char* source[], size_t source_len){
  if (null != buffer){
    char *bp = buffer;
    ssize_t bz = size;
    off_t idx, cnt;
    size_t output = 0;
    for (idx = 0, cnt = source_len; idx < cnt; idx++){
      int many = snprintf(bp,bz,"%s\n",source[idx]);
      if (0 < many && 0 < bz){
	bp += many;
	bz -= many;
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
bool_t readline(txt_string *io, const char* source, size_t source_len){
  if (null != io && null != source && 0 < source_len){
    memset(io,0,sizeof(txt_string));
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
	off_t index;
	size_t count = (end-begin);
	/* 
	 * memcpy(io,source,count)
	 */
	char *tgt = (char*)io;
	char *src = (char*)source;
	for (index = 0; index < count; index++){

	  if ('"' == *src){
	    *tgt++ = '\\';
	  }
	  *tgt++ = *src++;
	}
	io->length = (count+1);
	return true;
      }
    }
  }
  return false;
}

#define isbreak_string "  <text "
#define isbreak_string_length 8

bool_t isbreak(txt_string *io){
  return (0 == strncmp((const char*)io,isbreak_string,isbreak_string_length));
}

size_t encode_page(char *buffer, size_t size, const char* source, size_t source_len){
  size_t wr, line_count;

  char *bp = buffer;
  ssize_t bz = size;
  size_t output = 0;
  size_t count = 0;
  wr = snprintf(bp,bz,"static const char *page_head[] = {\n");
  bp += wr;
  bz -= wr;
  output += wr;
  txt_string line;
  txt_string *linep = (&line);
  const char *sp = source;
  size_t sz = source_len;
  while (readline(&line,sp,sz)){
    if (isbreak(linep)){
      sp += line.length;
      sz -= line.length;

      wr = snprintf(bp,bz,"};\n");
      bp += wr;
      bz -= wr;
      output += wr;

      wr = snprintf(bp,bz,"static const uint32_t page_head_count = %ld;\n",count);
      bp += wr;
      bz -= wr;
      output += wr;

      wr = snprintf(bp,bz,"static const char *page_tail[] = {\n");
      bp += wr;
      bz -= wr;
      output += wr;

      count = 0;
    }
    else {
      wr = snprintf(bp,bz,"  \"%s\",\n",(char*)linep);
      bp += wr;
      bz -= wr;
      output += wr;

      sp += line.length;
      sz -= line.length;

      count += 1;
    }
  }
  wr = snprintf(bp,bz,"};\n");
  bp += wr;
  bz -= wr;
  output += wr;

  wr = snprintf(bp,bz,"static const uint32_t page_tail_count = %ld;\n",count);
  bp += wr;
  bz -= wr;
  output += wr;

  return output;
}

int main(int argc, char **argv){
  char *source = "etc/page.svg";
  char *target = "inc/pvg_page.h";
  txt_file *out = txt_file_new(0x100000);
  if (null != out){
    char *bp = txt_file_buffer(out);
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
    txt_file *in = txt_file_read(source);
    if (null != in){
      char *source_svg = txt_file_buffer(in);
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
 
      if (txt_file_write(out,target)){

	return 0;
      }
    }
  }
  return 1;
}
