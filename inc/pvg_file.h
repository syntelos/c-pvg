/*
 * page svg from text
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#ifndef _pvg_file_h
#define _pvg_file_h

#include "pvg_string.h"
/*
 * A tail array behaves is an integral allocated unit,
 * including registers for allocation, source, and copy.
 */
typedef struct {
  size_t alloc;
  size_t limit;
  off_t  ofset;
  char buffer[];
} pvg_file;

#define pvg_file_buffer(p) (char*)&(p->buffer[0])

/*
 * Derive any extant, explicit parent identity from argument
 * path expression.  Otherwise, null.
 */
char* pvg_directory_parent(const char*);
/*
 * Assure existance of directory, as existing or created.
 */
bool_t pvg_directory(const char*);
/*
 * Existing file content length, or zero.
 */
size_t pvg_file_size(const char*);
/*
 * Existing file content length, or zero.
 */
pvg_file* pvg_file_new(size_t);

void pvg_file_destroy(pvg_file*);

#define pvg_file_exists(fn) 0 != pvg_file_size(fn)
/*
 * Copy file content to object.
 */
pvg_file* pvg_file_read(const char*);
/*
 * Read line into string, counting but not copying line
 * terminals (NL '\n' 0x0A).
 */
bool_t pvg_readline(pvg_string*, pvg_file*);
/*
 * Copy object content to file.
 */
bool_t pvg_file_write(pvg_file*, const char*);

#endif
