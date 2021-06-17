#include "file_formating.h"

bool is_captal(char symb){ // заглавная буква?
    if (symb >= 65 && symb <= 90)
        return true;
    else return false;
}

bool is_lowercase(char symb){ // строчная  буква?
    if (symb >= 97 && symb <= 122)
        return true;
    else return false;
}

bool is_same_var(LINEAR_MAP** varmap, char* name, unsigned int nVars){
    bool isSameVar = 0;
    for (int k = 0; k < nVars; ++k){
        if (strstr(varmap[k]->name, name) != NULL){
            isSameVar = 1;
        }
        else
            isSameVar = 0;
    }
    return isSameVar;
}

void map_add_variable(LINEAR_MAP** varmap, unsigned int varsize, char name[MAX_VARIABLE_SIZE]){
    int i = 0;
    while (varmap[i]->inp_size != 0){
        i++;
    }
    varmap[i]->inp_size = strlen(name);
    memcpy(varmap[i]->name, name, MAX_VARIABLE_SIZE);
}

int vars_number(LINEAR_MAP** varmap){
    int c = 0;
    while(varmap[c]->inp_size != 0){
        c++;
    }
    return c;
}

void map_rename_vars(LINEAR_MAP** varmap, int vars_number){
    bool isLowercase = 0;
    bool isPascal = 0;
    bool isCamel  = 0;
    bool isSnake  = 0;
    bool isSimple = 0;
    bool isCaps = 0;

    for (int i = 0; i < vars_number; ++i){ // удаляем пробелы перед переменными
        int j = 0;
        while (varmap[i]->name[j] == ' '){
            delete_symb(varmap[i]->name, j); // ?????????????????????????? проверить
            j++;
        }
    }

    for (int i = 0; i < vars_number; ++i){
        if (strlen(varmap[i]->name) > 1 && is_captal(varmap[i]->name[0])){ // PascalCase
            if (is_lowercase(varmap[i]->name[1])){
                isPascal = true;
            }
        }

        int k = 0;
        if (!is_captal(varmap[i]->name[0])) { // camelCase
            while (varmap[i]->name[k] != '\0') {
                if (is_captal(varmap[i]->name[k]))
                    isCamel = true;
                if (is_lowercase(varmap[i]->name[k]))
                    isLowercase = true;
                k++;
            }
            if (!isLowercase)
                isCamel = false;
        }
        k = 0;
        if (!is_captal(varmap[i]->name[0])) { // snake_case
            while (varmap[i]->name[k] != '\0') {
                if (varmap[i]->name[k] == '_')
                    isSnake = true;
                k++;
            }
        }
        k = 0;
        while (varmap[i]->name[k] != '\0'){ // CAPS
            if (is_captal(varmap[i]->name[k]))
                isCaps = true;
            else if (is_lowercase(varmap[i]->name[k])){
                isCaps = false;
                break;
            }
        }
        if (!isSnake && !isCamel && !isPascal && !isCaps)
            isSimple = true;

        if (isPascal)
            varmap[i]->type = 1;
        if (isSnake)
            varmap[i]->type = 2;
        if (isCamel)
            varmap[i]->type = 3;
        if (isSimple)
            varmap[i]->type = 4;
        if (isCaps)
            varmap[i]->type = 5;
    }
    // ФОРМАТИРОВАНИЕ
    for (int i = 0; i < vars_number; ++i){
        switch (varmap[i]->type){
            case 1:
                varmap[i]->replacement[0] = varmap[i]->name[0] + 32;
                int j = 1;
                while (varmap[i]->name[j] != '\0'){
                    varmap[i]->replacement[j] = varmap[i]->name[j];
                }
                break;
            case 2:
                strcpy(varmap[i]->replacement, varmap[i]->name);
                for (j = 0; j < strlen(varmap[i]->replacement); ++j){
                    if (varmap[i]->replacement[j] == '_'){
                        delete_symb(varmap[i]->replacement, j);
                        varmap[i]->replacement[j] = varmap[i]->replacement[j] - 32;
                    }
                }
                break;
            case 3:
                strcpy(varmap[i]->name, varmap[i]->replacement);
                break;
            case 4:
                strcpy(varmap[i]->name, varmap[i]->replacement);
                break;
            case 5:
                strcpy(varmap[i]->name, varmap[i]->replacement);
                for (j = 0; j < strlen(varmap[i]->replacement); ++j){
                    if (is_captal(varmap[i]->replacement[j])){
                        varmap[i]->replacement[j] = varmap[i]->replacement[j] + 32;
                    }
                }
                for (j = 0; j < strlen(varmap[i]->replacement); ++j){
                    if (varmap[i]->replacement[j] == '_'){
                        delete_symb(varmap[i]->replacement, j);
                        varmap[i]->replacement[j] = varmap[i]->replacement[j] - 32;
                    }
                }
                break;
        }
    }
}

void format_variables(FILE_TEXT** arr_filestructures, int n_files){
    bool isSameVar = 0;
    char varname[MAX_VARIABLE_SIZE] = {'\0'};
    unsigned int nVars = 0;

    LINEAR_MAP** varmap = (LINEAR_MAP**) malloc(MAX_VAR_NUMBER * sizeof(LINEAR_MAP));
    for (int i = 0; i < MAX_VAR_NUMBER; ++i){
        varmap[i] = (LINEAR_MAP*) malloc(sizeof(LINEAR_MAP));
    }

    for (int i = 0; i < n_files; ++i){
        for (int j = 0; j < MAX_STR_NUMBER; ++j){
            nVars = vars_number(varmap);
            isSameVar = 0;
            if (sscanf(arr_filestructures[i]->filestr[j], "int %s", varname) == 1){
                if (is_same_var(varmap, varname, nVars))
                    map_add_variable(varmap, strlen(varname), varname);
            }
            else if (sscanf(arr_filestructures[i]->filestr[j], "float %s", varname) == 1){
                if (is_same_var(varmap, varname, nVars))
                    map_add_variable(varmap, strlen(varname), varname);
            }
            else if (sscanf(arr_filestructures[i]->filestr[j], "double %s", varname) == 1){
                if (is_same_var(varmap, varname, nVars))
                    map_add_variable(varmap, strlen(varname), varname);
            }
            else if (sscanf(arr_filestructures[i]->filestr[j], "char %s", varname) == 1){
                if (is_same_var(varmap, varname, nVars))
                    map_add_variable(varmap, strlen(varname), varname);
            }
            else if (sscanf(arr_filestructures[i]->filestr[j], "bool %s", varname) == 1){
                if (is_same_var(varmap, varname, nVars))
                    map_add_variable(varmap, strlen(varname), varname);
            }
            else if (sscanf(arr_filestructures[i]->filestr[j], "unsigned int %s", varname) == 1){
                if (is_same_var(varmap, varname, nVars))
                    map_add_variable(varmap, strlen(varname), varname);
            }
            else if (sscanf(arr_filestructures[i]->filestr[j], "unsigned char %s", varname) == 1){
                if (is_same_var(varmap, varname, nVars))
                    map_add_variable(varmap, strlen(varname), varname);
            }
        }
    }

    /*
    for (int i = 0; i < n_files; ++i){
        for (int j = 0; j < MAX_STR_NUMBER; ++j){
            for (int k = 0; k < vars_number(varmap); k++)
            if (strstr(arr_filestructures[i]->filestr[j], varmap[k]->name) != NULL){
                int c = 0;
                char *istr;
                istr = strstr(arr_filestructures[i]->filestr[j], varmap[k]->name);
                int ind = istr-arr_filestructures[i]->filestr[j]+1;
                while (arr_filestructures[i]->filestr[j][ind] == varmap[k]->name);

            }
        }
    } */
}