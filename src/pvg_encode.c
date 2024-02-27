/*
 * page svg from text
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#include "pvg.h"
#include "pvg_page.h"
#include <stdio.h>

bool_t pvg_encode(pvg_file *tgt, pvg_text *src, char *style){
  char *tgt_p = tgt->buffer;
  size_t tgt_z = tgt->alloc;
  size_t output = 0;
  ssize_t wr;
  uint32_t idx;
  /*
   * Head
   */
  for (idx = 0; idx < page_head_count; idx++){
    wr = snprintf(tgt_p, tgt_z, "%s\n", page_head[idx]);
    if (0 < wr){
      tgt_p += wr;
      tgt_z -= wr;
      output += wr;
    }
    else {
      break;
    }
  }
  /*
   * Body
   */
  size_t x = pvg_page_x0, y = pvg_page_y0;
  size_t line = 1;
  pvg_string class;
  char *class_p = (char*)&class;
  class.length = sprintf(class_p,"%s",style);

  size_t count = pvg_text_count(src);
  for (idx = 0; idx < count; idx++, src++){
    if (0 != src->link.length){
      if (1 == line){
	class.length = sprintf(class_p,"%s ti ln",style);
	line += 1;
      }
      else {
	class.length = sprintf(class_p,"%s ln",style);
	line += 1;
      }
      wr = snprintf(tgt_p, tgt_z, "  <a href=\"%s\"><text x=\"%ld\" y=\"%ld\" class=\"%s\">%s</text></a>\n", (char*)&(src->link), x, y, class_p, (char*)&(src->text));
      if (0 < wr){
	tgt_p += wr;
	tgt_z -= wr;
	output += wr;
	y += pvg_page_lh;
      }
      else {
	break;
      }
    }
    else if (0 != src->text.length){
      if (1 == line){
	class.length = sprintf(class_p,"%s ti",style);
	line += 1;
      }
      else {
	class.length = sprintf(class_p,"%s",style);
	line += 1;
      }
      wr = snprintf(tgt_p, tgt_z, "  <text x=\"%ld\" y=\"%ld\" class=\"%s\">%s</text>\n", x, y, class_p, (char*)&(src->text));
      if (0 < wr){
	tgt_p += wr;
	tgt_z -= wr;
	output += wr;
	y += pvg_page_lh;
      }
      else {
	break;
      }
    }
    else {
    }
  }
  /*
   * Tail
   */
  for (idx = 0; idx < page_tail_count; idx++){
    wr = snprintf(tgt_p, tgt_z, "%s\n", page_tail[idx]);
    if (0 < wr){
      tgt_p += wr;
      tgt_z -= wr;
      output += wr;
    }
    else {
      break;
    }
  }
  tgt->limit = output;
  return true;
}
