#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utilities.h"
#include "filestructure.h"

#define MAX_VARIABLE_SIZE 128
#define MAX_VAR_NUMBER 100

typedef struct {
    int type; // 1 - pascal 2 - snake 3 - camel 4 - simple 5 - CAPS
    unsigned int  inp_size;
    char name[MAX_VARIABLE_SIZE];
    char replacement[MAX_VARIABLE_SIZE];
}LINEAR_MAP;

void format_variables(FILE_TEXT** arr_filestructures, int n_files);
