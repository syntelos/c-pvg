/*
 * page svg from text
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#ifndef _txt_file_h
#define _txt_file_h

#include "txt_string.h"
/*
 * A tail array behaves is an integral allocated unit,
 * including registers for allocation, source, and copy.
 */
typedef struct {
  size_t alloc;
  size_t limit;
  off_t  ofset;
  char buffer[];
} txt_file;

#define txt_file_buffer(p) (char*)&(p->buffer[0])

/*
 * Derive any extant, explicit parent identity from argument
 * path expression.  Otherwise, null.
 */
char* txt_directory_parent(const char*);
/*
 * Assure existance of directory, as existing or created.
 */
bool_t txt_directory(const char*);
/*
 * Existing file content length, or zero.
 */
size_t txt_file_size(const char*);
/*
 * Existing file content length, or zero.
 */
txt_file* txt_file_new(size_t);

void txt_file_destroy(txt_file*);

#define txt_file_exists(fn) 0 != txt_file_size(fn)
/*
 * Copy file content to object.
 */
txt_file* txt_file_read(const char*);
/*
 * Read line into string, counting but not copying line
 * terminals (NL '\n' 0x0A).
 */
bool_t txt_file_readline(txt_string*, txt_file*);
/*
 * Copy object content to file.
 */
bool_t txt_file_write(txt_file*, const char*);

#endif
