#include <stdio.h>
#include <stdlib.h>
#include "filestructure.h"
#include "format_text.h"
#include "recommenting.h"


#define MAX_STR_NUMBER  150
#define MAX_STR_LEN 200

void fill_structure_field(FILE_TEXT** structure, int argc, char symb) {
    for (int i = 0; i < argc-1; i++){
        for (int j = 0; j < MAX_STR_NUMBER; j++) {
            for (int k = 0; k < MAX_STR_LEN; k++) {
                structure[i]->filestr[j][k] = symb;
            }
        }
    }
}
void file_open(int n_headers, char** argv, FILE_TEXT** arr_filestructures) {
    n_headers--;
    for (int i = 0; i < n_headers; i++) {
        int j = 0;
        arr_filestructures[i]->file_number = i + 1;
        FILE* inp_file = fopen(argv[i + 1], "rt");
        while (!feof(inp_file)) {
            fgets(arr_filestructures[i]->filestr[j], MAX_STR_LEN, inp_file);
            j++;
        }
        arr_filestructures[i]->file_str_number = j;
    }
}
int main(int argc, char** argv){
    FILE_TEXT** arr_filestructures = (FILE_TEXT**)malloc((argc - 1) * sizeof(FILE_TEXT*));

    for (int i = 0; i < argc - 1; i++) {
        arr_filestructures[i] = (FILE_TEXT*)malloc(sizeof(FILE_TEXT));
    }
    fill_structure_field(arr_filestructures, argc, '\0');

    file_open(argc, argv, arr_filestructures);
    recomment(arr_filestructures, argc-1);
    format_text(arr_filestructures, argc-1);
    return 0;
}
