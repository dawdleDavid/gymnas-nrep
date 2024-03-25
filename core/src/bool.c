#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../head/bool.h"

char* operators[5] = {
    " ==",
    " <",
    " >",
    " <=",
    " >="
};

bool boolEval(Expression* expression){
    for(int i = 0; i <= 6; i++){
        if(strcmp(operators[i], expression->op) == 0){
            // do the stuff
            switch(i){ // ignore signed values
                case 0:
                    if(expression->a.unint == expression->b.unint){
                        return true;
                    }
                    return false;
                case 1:
                    if(expression->a.unint < expression->b.unint){
                        return true;
                    }
                    return false;
                case 2:
                    if(expression->a.unint > expression->b.unint){
                        return true;
                    }
                    return false;
                case 3:
                    if(expression->a.unint <= expression->b.unint){
                        return true;
                    }
                    return false;
                case 4:
                    if(expression->a.unint >= expression->b.unint){
                        return true;
                    }
                    return false;
            }
        }
    }
    return false;
}
