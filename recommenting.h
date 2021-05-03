#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool is_comment_begining(char * str);
bool is_comment_end(char * str);

void recomment(FILE* input, FILE* output);