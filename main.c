#include <stdio.h>
#include <stdlib.h>

#define MAX_STR_NUMBER  300
#define MAX_STR_LEN 120
#define MAX_HEADER_NAMESIZE 30

typedef struct FILE_TEXT{
     unsigned int file_number;
     char filestr[MAX_STR_NUMBER][MAX_STR_LEN];
}FILE_TEXT;

void file_open(int n_headers, char** argv, FILE_TEXT** arr_filestructures){
	n_headers--;
	for (int i = 0; i < n_headers; i++){
	    int j = 0;
	    arr_filestructures[i]->file_number = i+1;
	    FILE* inp_file = fopen(argv[i+1], "rt");
	    while (!feof(inp_file)) {
            fgets(arr_filestructures[i]->filestr[j], MAX_STR_LEN, inp_file);
            j++;
        }
	}
	/*
	for (unsigned int i = 0; i < n_headers; ++i){
        FILE *inp_header_file = fopen(argv[i + 1], "wt");
        arr_filestructures[i]->file_number = i+1;
        for (int j = 0; j < MAX_STR_NUMBER; j++){
            *arr_filestructures[j]->filestr = (char*) malloc((MAX_STR_LEN * sizeof(char)));
        }
        while(!feof(inp_header_file)) {
             fgets(*arr_filestructures[i]->filestr, MAX_STR_LEN, inp_header_file);
             arr_filestructures[i]->filestr ++;
        }
	}
	 */
}

int main(int argc, char ** argv)
{
    FILE_TEXT** arr_filestructures = (FILE_TEXT**) malloc((argc-1) * sizeof(FILE_TEXT));
    for (int i = 0; i < argc-1; i++) {
        arr_filestructures[i] = (FILE_TEXT*) malloc(sizeof(FILE_TEXT));
    }
	file_open(argc, argv, arr_filestructures);
	return 0;
}