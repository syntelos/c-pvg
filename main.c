/*
 * page svg from text
 * Copyright 2024 John Douglas Pritchard, Syntelos
 */
#include "pvg.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int usage(){
  fprintf(stderr,"usage: pvg <tgt> <src>\n");
  return 1;
}

int main(int argc, char **argv){
  if (2 < argc){
    pvg_file *tgt = pvg_file_new(0x100000);
    pvg_file *src = pvg_file_read(argv[2]);

    return (pvg_encode(tgt,src) && pvg_file_write(tgt,argv[1]));
  }
  else {
    return usage();
  }
}
