#include "age.h"

float computePrice(int age, int card, int holidayTime)
{   
    int limitAge=0;
    int *plimit = &limitAge;
    recupLimitAge(plimit);
    if (age < 0)
         return -1;
    if (age>limitAge)
        return 0.0;
    else
        if (card && !holidayTime)
            return 50.0;
        else 
            return 10.0;
}
