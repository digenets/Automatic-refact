#include "format_text.h"
#include <stdio.h>

bool is_open_paranthesis_next(char* str, int position){
    if (str[position] == '(')
        return true;
    else if (str[position] == ' '){
        while (str[position] == ' '){
            position++;
        }
        if (str[position] == '('){
            return true;
        }
        else
            return false;
    }
    else return false;
}

bool is_close_paranthesis_previous(char* str, int position){
    position--;
    while (str[position] == ' ' || str[position] == '\n'){
        position--;
    }
    if (str[position] == ')')
        return true;
    else
        return false;
}

bool is_close_figures_next(char* str, int i){
    for (int j = i; j < strlen(str); j++){
        if (str[j] == '{'){
            return false;
        }
        else if (str[j] == '}'){
            return true;
        }
    }
    return false;
}

void symb_insert(char* str, int position, char symb){
    position += 1;
    char tmp_str[MAX_STR_LEN] = {'\0'};
    int k = 0;
    for (int i = position; i < strlen(str); i++){
        tmp_str[k] = str[i];
        k++;
    }
    for (int i = position; i < strlen(str); i++){
        str[i] = '\0';
    }
    strcat(str, " ");
    strcat(str, tmp_str);
    str[position] = symb;
}

void tmp_symb_insert(char* str, int position, char symb){
    int tmp = position;
    while (position < strlen(str) - 1){
        str[position + 1] = str[position];
        position++;
    }
    str[tmp] = symb;
}

void format_text(FILE_TEXT** arr_filestructures, int nFiles){
    int nSpaces = 0;
    int nesting = 0;

    char file_text[MAX_HEADERS_NUMBER][MAX_STR_LEN * MAX_STR_NUMBER] = {'\0'};
    for (int i = 0; i < nFiles; i++){ // символы в одной строке
        for (int j = 0; j < MAX_STR_NUMBER; j++){
           strcat(file_text[i], arr_filestructures[i]->filestr[j]);
        }
    }
    for (int i = 0; i < nFiles; i++){
        nesting = 0;
        char tmp_str[MAX_STR_LEN * MAX_STR_NUMBER] = {'\0'};
        for (int j = 0; j < MAX_STR_LEN * MAX_STR_NUMBER - 1; j++){ // пробелы рядом со знаками арифметики
            if (file_text[i][j] == '+' && file_text[i][j+1] != '+' && file_text[i][j-1] != '+' && file_text[i][j+1] != '=' ||
                file_text[i][j] == '-' && file_text[i][j+1] != '-' && file_text[i][j-1] != '-' && file_text[i][j+1] != '=' ||
                file_text[i][j] == '*' && file_text[i][j+1] != '='||

                file_text[i][j] == '/' && file_text[i][j+1] !='/' &&
                file_text[i][j-1] != '/' && file_text[i][j-1] != '*' &&
                file_text[i][j+1] != '*'  && file_text[i][j+1] != '='||

                file_text[i][j] == '=' && file_text[i][j-1] != '+' && file_text[i][j-1] != '-' && file_text[i][j-1] != '*' && file_text[i][j-1] != '/' ||
                file_text[i][j] == '<' ||
                file_text[i][j] == '>')
            {
                if (file_text[i][j-1] != ' '){
                    symb_insert(file_text[i], j-1, ' ');
                }
                if (file_text[i][j+1] != ' '){
                    symb_insert(file_text[i], j+1, ' ');
                }
            }
        }
        for (int j = 0; j < strlen(file_text[i]) - 3; j++){
            if (file_text[i][j] == 'f' && file_text[i][j+1] == 'o' && file_text[i][j+2] == 'r' && is_open_paranthesis_next(file_text[i], j+3)){
                while (file_text[i][j] != ')'){
                    tmp_str[j] = file_text[i][j];
                    file_text[i][j] = '~';
                    j++;
                }
            }
        }
        for (int j = 0; j < MAX_STR_LEN * MAX_STR_NUMBER; j++){
            if (file_text[i][j] == ';'){
                j++;
                while (file_text[i][j] == ' '){
                    j++;
                }
                if (file_text[i][j] != '\n'){
                    while (file_text[i][j-1] == ' '){
                        j--;
                    }
                    symb_insert(file_text[i], j, '\n');
                    symb_insert(tmp_str, j, '@'); // символ смещения, чтобы потом установить однозначное соответствие tmp_str и file_text
                }
            }
        }

        for (int j = 0; j < MAX_STR_LEN * MAX_STR_NUMBER; j++){
            if (file_text[i][j] == '~'){
                file_text[i][j] = tmp_str[j];
            }
        }

        /*
        int otst = 0; // отступ
        int opens = 0; // открывающие скобки
        for (int j = 0; j < MAX_STR_LEN * MAX_STR_NUMBER; j++){
            if (file_text[i][j] == '{'){
                if (!is_close_figures_next(file_text[i], j+1)) {
                    otst += 4;
                    opens++;
                }
                if (is_close_figures_next(file_text[i], j+1) && opens == 1){
                    otst += 4;
                }
            }
            else if (file_text[i][j] == '}' && file_text[i][j+1] != '\0'){
                otst -= 4;
            }
            if (file_text[i][j] == '\n'){
                int cur_otst = 0;
                int k = j+1;
                while(file_text[i][k] == ' '){
                    cur_otst++;
                    k++;
                }
                while (cur_otst < otst){
                    symb_insert(file_text[i], j, ' ');
                    cur_otst++;
                }
                while (cur_otst > otst){
                    delete_symb(file_text[i], j+1);
                    cur_otst--;
                }
            }
        } */
    }
    for (int l = 0; l < nFiles; l++){
        for (int k = 0; k < MAX_STR_NUMBER; k++){
            for (int m = 0; m < MAX_STR_LEN; m++){
                arr_filestructures[l]->filestr[k][m] = '\0';
            }
        }
    }

    int j = 0;
    int c = 0;
    int k = 0;
    char tmp_str2[MAX_STR_LEN] = {'\0'};
    for (int i = 0; i < nFiles; i++){
        while (file_text[i][j] != '\0'){
            if (file_text[i][j] != '\n'){
            arr_filestructures[i]->filestr[c][k] = file_text[i][j];
            k++;
            j++;
            }
            else{
                arr_filestructures[i]->filestr[c][k] = file_text[i][j];
                c++;
                j++;
                k = 0;
            }
        }
    }

}


