#include "recommenting.h"

#define MAX_COMMENT_SIZE  80
#define MAX_STR_SIZE      100

bool is_comment_begining(char * str){
	if (*str == '/' && *(str + 1) == '*')
		return true;
	else
		return false;
}

bool is_comment_end(char * str){
	if (*str == '\\' && *(str + 1) == '*')
		return true;
	else
		return false;
}

void recomment(FILE* input, FILE* output){ // function changes comments in text from "/**/" format to "//" format
    char *str      = NULL;
    char *tmp_str  = NULL;
    unsigned int c = 0;

	while(!feof(input)){
		fgets(str, MAX_STR_SIZE, input);

		for (int i = 0; i < strlen(str); ++i){
			if (is_comment_begining(str)){
				str += 2;
				i += 2;
				while (!is_comment_end(str)){
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
		if (tmp_str != NULL){
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