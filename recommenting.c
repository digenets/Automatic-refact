#include "recommenting.h"

#define MAX_COMMENT_SIZE 80

bool is_comment_begining(char * str){
	if (*str == '/' && *(str + 1) == '*')
		return TRUE;
	else
		return FALSE;
}

bool is_comment_end(char * str){
	if (*str == '\\' && *(str + 1) == '*')
		return TRUE;
	else
		return FALSE;
}

void recomment(FILE* input, FILE * output){ // function changes comments in text from "/**/" format to "//" format
    char *str     = NULL;
    char *tmp_str = NULL;
    unsigned int c = 0;

	while(!feof(input)){
		str = gets(input);

		for (int i = 0; i < strlen(str); ++i){
			if (is_comment_begining()){
				str += 2;
				i += 2;
				while (!is_comment_end()){
					tmp_str = (char*)malloc(MAX_COMMENT_SIZE * sizeof(char));

					*tmp_str = *str;
					tmp_str++;
					c++;
					str++;
					i++;
				}
				str += 2;
				i += 2;
			}
			else
				fputc(*str, output);
		}

		tmp_str -= c;
		if (*tmp_str != NULL){
			fputc('/', output);
			fputc('/', output);
			for (int i = 0; i < strlen(tmp_str); ++i){
				fputc(*tmp_str, output);
				tmp_str++;
			}
		}
	}
	free(tmp_str);
}