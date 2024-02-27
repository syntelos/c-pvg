/*
 * page svg from text
 * Copyright 2024 John Douglas Pritchard, Syntelos
 */
#include "pvg.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int usage(){
  fprintf(stderr,"usage: pvg <tgt> <src> [rm|tt] \n");
  return 1;
}

int main(int argc, char **argv){
  if (2 < argc){
    pvg_file *tgt = pvg_file_new(0x100000);
    pvg_text *src = pvg_text_read(argv[2]);

    char *style = "rm";
    if (3 < argc && 0 == strcmp("tt",argv[3])){
      style = "tt";
    }

    if (pvg_encode(tgt,src,style) && pvg_file_write(tgt,argv[1]),style){

      return 0;
    }
    else {
      return 1;
    }
  }
  else {
    return usage();
  }
}
