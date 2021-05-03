#include <stdio.h>
#include <stdlib.h>

#define MAX_HEADER_NAMESIZE 30
void file_open(int n_headers, char** argv){
	n_headers--;
	
	char** filenames  = (char**) malloc(n_headers * sizeof(char*));
	FILE** incl_files = (FILE**) malloc(n_headers * sizeof(FILE*));

	for (unsigned int i = 0; i < n_headers; ++i){
		// incl_files[i] = (FILE*) malloc(sizeof(FILE));
		incl_files[i] = fopen(argv[i+1], "wt");
		if (incl_files[i] == NULL){
			printf("File open error");
			break;
		}
	}
}

int main(int argc, char ** argv)
{
	file_open(argc, argv);
	return 0;
}