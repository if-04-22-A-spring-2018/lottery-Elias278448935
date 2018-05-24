#include <stdio.h>
#include "lottery.h"

static char* fileN;
static char semi;
static int* drawed;
static bool drew=false;

bool init_lottery(char* filename, char j){
    FILE* filex= fopen(filename, "r");
    semi = j;
    drew = false;
    fileN = filename;
    if(filex ==NULL)return false;
    fclose(filex);
    return true;
}



bool get_tip(int tip_number, int tip[TIP_SIZE]){
    FILE* file= fopen(fileN, "r");
    char input[MAX_LINE_LEN] = {0};
    int count = 0;
    if(tip_number < 0 || file == 0){
        fclose(file);
        return false;
    }
    char* outp = fgets(input, MAX_LINE_LEN, file);
    while(outp != NULL && count < tip_number) {
        outp = fgets(input, MAX_LINE_LEN, file);
        count++;
        if (outp != input) {
            fclose(file);
            return false;
        }
    }
    int pos = 0;
    while(input[pos] != semi && pos < UUID_LEN){
        pos++;
    }

    int insertionpos = 0;
    int number = 0;
    while(insertionpos < 6){
        pos++;
        if(input[pos]<= '9' && input[pos]>= '0'){
            number = number*10+ (input[pos] - '0');
        }
        else{
            tip[insertionpos] = number;
            number = 0;
            insertionpos++;
        }
    }
    fclose(file);
    return true;
}


bool set_drawing(int* array){
    drew = true;
    drawed = array;
    return false;
}
int get_tip_result(int tip){
    if(!drew )return -1;
    int bb[6];
    if(!get_tip(tip, bb))return -2;
    int count = 0;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            if(bb[i] == drawed[j])count++;
        }
    }
    return count;
}
int get_right_tips_count(int right_number){
    if(!drew|| right_number < 0 || right_number > TIP_SIZE)return -1;
    int zeile = 0;
    int count = 0;
    int ergebnis = 0;
    while(ergebnis != -2&& ergebnis != -1){
        ergebnis = get_tip_result(zeile);
        if(ergebnis == tip)count++;
        zeile++;
    }
    return count;
}
