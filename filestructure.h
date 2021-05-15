#pragma once

#define MAX_STR_NUMBER  150
#define MAX_STR_LEN 200
#define MAX_HEADER_NAMESIZE 30
#define MAX_HEADERS_NUMBER 10

typedef struct FILE_TEXT {
    unsigned int file_number;
    char filestr[MAX_STR_NUMBER][MAX_STR_LEN];
    unsigned int file_str_number;
}FILE_TEXT;

