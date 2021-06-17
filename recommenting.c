#include "recommenting.h"


#define MAX_STR_NUMBER  150
#define MAX_STR_LEN 200
#define MAX_COMMENT_SIZE 256


void str_fill(char* str, char symb){
    while (*str != '\0'){
        *str = symb;
        str ++;
    }
}

void str_writing(FILE_TEXT** arr_filestructures, int i, int j, char* tmp_str){
    if (strstr(arr_filestructures[i]->filestr[j], "//") != NULL){
        strcat(arr_filestructures[i]->filestr[j], tmp_str);
    }
    else{
        strcat(arr_filestructures[i]->filestr[j], "//");
        strcat(arr_filestructures[i]->filestr[j], tmp_str);
    }
}

void recomment(FILE_TEXT** arr_filestructures, int n_files) { // function changes comments in text from "/**/" format to "//" format
    int k = 0;
    char tmp_str[MAX_COMMENT_SIZE] = {'\0'};
    for (int i = 0; i < n_files; ++i){
        for (int j = 0; j < MAX_STR_NUMBER; ++j){
            k = 0;
            while (arr_filestructures[i]->filestr[j][k] != '\0') {
                if (arr_filestructures[i]->filestr[j][k] == '/' && arr_filestructures[i]->filestr[j][k + 1] == '*' && arr_filestructures[i]->filestr[j][k+2] != '*' && arr_filestructures[i]->filestr[j][k+3] != '/'){
                    delete_symb(arr_filestructures[i]->filestr[j], k);
                    delete_symb(arr_filestructures[i]->filestr[j], k);
                    if (strstr(arr_filestructures[i]->filestr[j], "*/") != NULL) { // если комментарий в одной строке
                        str_fill(tmp_str, '\0');

                        while (!(arr_filestructures[i]->filestr[j][k] == '*' &&
                                 arr_filestructures[i]->filestr[j][k + 1] == '/')) {
                            tmp_str[strlen(tmp_str)] = arr_filestructures[i]->filestr[j][k];
                            delete_symb(arr_filestructures[i]->filestr[j], k);
                        }
                        delete_symb(arr_filestructures[i]->filestr[j], k);
                        delete_symb(arr_filestructures[i]->filestr[j], k);
                        while (arr_filestructures[i]->filestr[j][strlen(arr_filestructures[i]->filestr[j])-1] == '\n'){
                            tmp_str[strlen(tmp_str)] = '\n';
                            arr_filestructures[i]->filestr[j][strlen(arr_filestructures[i]->filestr[j])-1] = '\0';
                        }
                        str_writing(arr_filestructures, i, j, tmp_str);
                    } else{
                        while (strstr(arr_filestructures[i]->filestr[j], "*/") == NULL) {
                            str_fill(tmp_str, '\0');
                            while (arr_filestructures[i]->filestr[j][k] != '\n' &&
                                   arr_filestructures[i]->filestr[j][k] != '\0') {
                                tmp_str[strlen(tmp_str)] = arr_filestructures[i]->filestr[j][k];
                                delete_symb(arr_filestructures[i]->filestr[j], k);
                            }
                            delete_symb(arr_filestructures[i]->filestr[j], k);
                            if (tmp_str[strlen(tmp_str)] != '\n')
                                tmp_str[strlen(tmp_str)] = '\n';
                            str_writing(arr_filestructures, i, j, tmp_str);
                            k = 0;
                            j++;
                        }
                        str_fill(tmp_str, '\0');
                        while (!(arr_filestructures[i]->filestr[j][k] == '*' &&
                                 arr_filestructures[i]->filestr[j][k + 1] == '/')) {
                            tmp_str[strlen(tmp_str)] = arr_filestructures[i]->filestr[j][k];
                            delete_symb(arr_filestructures[i]->filestr[j], k);
                        }
                        delete_symb(arr_filestructures[i]->filestr[j], k);
                        delete_symb(arr_filestructures[i]->filestr[j], k);
                        str_writing(arr_filestructures, i, j, tmp_str);
                        if (arr_filestructures[i]->filestr[j][strlen(arr_filestructures[i]->filestr[j])] != '\n'){
                            arr_filestructures[i]->filestr[j][strlen(arr_filestructures[i]->filestr[j])] = '\n';
                        }
                    }
                }
                else if (arr_filestructures[i]->filestr[j][k] == '/' && arr_filestructures[i]->filestr[j][k + 1] == '*' && arr_filestructures[i]->filestr[j][k+2] == '*' && arr_filestructures[i]->filestr[j][k+3] == '/') {
                    delete_symb(arr_filestructures[i]->filestr[j], k);
                    delete_symb(arr_filestructures[i]->filestr[j], k);
                    delete_symb(arr_filestructures[i]->filestr[j], k);
                    delete_symb(arr_filestructures[i]->filestr[j], k);
                    str_fill(tmp_str, '\0');
                    while (arr_filestructures[i]->filestr[j][k] != '\0' && arr_filestructures[i]->filestr[j][k] != '\n') {
                        if (arr_filestructures[i]->filestr[j][k] == '/' && arr_filestructures[i]->filestr[j][k+1] == '/'){
                            break;
                        }
                        tmp_str[strlen(tmp_str)] = arr_filestructures[i]->filestr[j][k];
                        k++;
                    }
                    while (arr_filestructures[i]->filestr[j][strlen(arr_filestructures[i]->filestr[j])-1] == '\n'){
                        tmp_str[strlen(tmp_str)] = '\n';
                        arr_filestructures[i]->filestr[j][strlen(arr_filestructures[i]->filestr[j])-1] = '\0';
                    }
                    str_writing(arr_filestructures, i, j, tmp_str);
                    if (arr_filestructures[i]->filestr[j][strlen(arr_filestructures[i]->filestr[j]) - 1] != '\n'){
                        arr_filestructures[i]->filestr[j][strlen(arr_filestructures[i]->filestr[j]) - 1] = '\n';
                    }
                }
                k++;
            }
        }
    }
}