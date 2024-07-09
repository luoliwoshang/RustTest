#ifndef CSV_WRAPPER_H
#define CSV_WRAPPER_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

const char *read_csv(const char *file_path);

void free_string(char *s);

#endif /* CSV_WRAPPER_H */
