#pragma once

#define MAX_STR_NUMBER  300
#define MAX_STR_LEN 120
#define MAX_HEADER_NAMESIZE 30

typedef struct FILE_TEXT {
    unsigned int file_number;
    char filestr[MAX_STR_NUMBER][MAX_STR_LEN];
    unsigned int file_str_number;
}FILE_TEXT;

