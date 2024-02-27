/*
 * page svg from text
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#include "pvg_file.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char* pvg_directory_parent(const char *path){
  if (null != path){
    size_t len = strlen(path);
    off_t trm = (len-1);
    if (0 <= trm){
      off_t idx = -1;
      for (idx = trm; 0 <= idx; idx--){
	if ('/' == path[idx]){
	  len = idx;
	  if (0 < len){
	    char *re = calloc(1,len+1);
	    memcpy(re,path,len);
	    return re;
	  }
	}
      }
    }
  }
  return null;
}

bool_t pvg_directory(const char *dir){
  struct stat sb;
  if (0 == stat(dir,&sb) && S_IFDIR == (sb.st_mode & S_IFMT) ){
    /*
     * Pre-existing directory.
     */
    return true;
  }
  else if (0 == mkdir(dir,0755)){
    /*
     * Create named child directory within existing parent.
     */
    return true;
  }
  else {
    /*
     * Recursive creation from parent to child.
     */
    char *parent = pvg_directory_parent(dir);
    if (null != parent){
      bool_t created = pvg_directory(parent);
      
      free(parent);
      parent = null;

      if (created){
	return (0 == mkdir(dir,0755));
      }
      else {
	return false;
      }
    }
    else {
      return false;
    }
  }
}

size_t pvg_file_size(const char *file){
  if (null != file){
    struct stat sb;
    if (0 == stat(file,&sb)){

      return sb.st_size;
    }
  }
  return 0;
}

pvg_file* pvg_file_new(size_t size){
  if (0 < size){
    size_t count = (sizeof(pvg_file)+size);
    pvg_file *re = calloc(1,count);
    if (null != re){
      re->alloc = size;

      return re;
    }
  }
  return null;
}

pvg_file* pvg_file_read(const char *file){
  if (null != file){
    size_t file_size = pvg_file_size(file);
    if (0 < file_size){
      pvg_file *object = pvg_file_new(file_size);
      fd_t fd = open(file,O_RDONLY);
      if (-1 < fd){
	char *p = pvg_file_buffer(object);
	ssize_t z = object->alloc;
	ssize_t rd;
	size_t w = 0;
	while (0 < z && 0 < (rd = read(fd, p, z))){
	  p += rd;
	  z -= rd;
	  w += rd;
	}
	object->limit = w;

	close(fd);
	return object;
      }
      else {
	pvg_file_destroy(object);
      }
    }
  }
  return null;
}

void pvg_file_destroy(pvg_file *object){
  if (null != object){
    size_t size = (sizeof(pvg_file)+object->alloc);
    memset(object,0,size);
    free(object);
  }
}

bool_t pvg_file_write(pvg_file *object, const char *file){
  if (null != object && null != file && 0 < object->limit && object->limit <= object->alloc){
    fd_t fd = open(file,(O_WRONLY|O_CREAT|O_TRUNC),0644);
    if (-1 < fd){
      char *p = pvg_file_buffer(object);
      ssize_t z = object->limit;
      ssize_t wr;
      while (0 < z && 0 < (wr = write(fd,p,z))){
	p += wr;
	z -= wr;
      }
      close(fd);
      return true;
    }
  }
  return false;
}

bool_t pvg_readline(pvg_string *tgt, pvg_file *src){
  if (null != tgt && null != src){
    memset(tgt,0,sizeof(pvg_string));
    char *begin = src->buffer+src->ofset;
    char *end = src->buffer+src->limit;
    ssize_t len = (end-begin);

    if ('\n' == *begin){
      if (1 < len){
	src->ofset += 1;
	tgt->length = 1;
	return true;
      }
    }
    else {
      char *lend = strchr(begin,'\n');
      if (lend > begin){
	size_t count = (lend-begin);
	if (count < pvg_string_buffer_size){
	  memcpy(tgt,begin,count);
	  src->ofset += (count+1);
	  tgt->length = (count+1);
	  return true;
	}
      }
    }
  }
  return false;
}
