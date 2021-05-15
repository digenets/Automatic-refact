#pragma once
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "filestructure.h"
#include "utilities.h"

bool is_open_paranthesis_next(char* str, int position);
bool is_close_paranthesis_previous(char* str, int position);
void symb_insert(char* str, int position, char symb);
void tmp_symb_insert(char* str, int position, char symb);
void format_text(FILE_TEXT** arr_filestructures, int nFiles);

