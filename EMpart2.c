/*
Scotty Fulton                            Thursday 8, 2018
Expextation Maximization part 2 for sunny and cloudy days
for continous data types, for decimal values.


*/

#include <stdio.h>
#include <math.h>

long nMkFact, nFact, kFact, nkFact, binom;
#define PI (3.1415926535897932384626433832795028841971693994L )
#define E (2.7182818284590452353602874713526624977572470937L )

int main (){


    double days[10] = {70.0,62.0,89.0,54.0,97.0,75.0,82.0,56.0,32.0,78.0};
    double sunny[10], cloudy[10], sunnyE[10], cloudyE[10];
    double stdDev = 10.0;
    double muSun = 80.0;
    double muCloud = 55.0;
    double tempD, tempN, tempS, tempC;
    double sunSum, cloudSum, wSunSum, wCloudSum, eSun, eCloud, mSun, mCloud = 0;

    // for (int j = 0; j < 10 ; j++){
    int j = 0;

    do{
        
        // print iteration number and current mu values
        printf("Iteration %d\n", j+1);
        printf("muSun = %.2lf\n", muSun);
        printf("muCloud = %.2lf\n", muCloud);
        // reset sum vars to 0
        sunSum = cloudSum = wSunSum = wCloudSum = 0;
        printf("-----------------------------\n");

        for (int i =0; i < 10 ; i++){
            // Sunny values
            // calculate the denominator for e step numerator
            tempD = 2 * stdDev * stdDev;
            // calculate the numerator for e step numerator
            tempN = ( pow( (days[i] - muSun), 2) );
            tempD = tempN / tempD;
            // calculate the numerator for e step
            tempD = pow(E, -tempD);
            sunny[i] = tempD;

            // Cloudy values
            // calculate the denominator for e step numerator
            tempD = 2 * stdDev * stdDev;
            // calculate the numerator for e step numerator
            tempN = ( pow( (days[i] - muCloud), 2) );
            tempD = tempN / tempD;
            // calculate the numerator for e step
            tempD = pow(E, -tempD);
            cloudy[i] = tempD;

            // Sunny & cloudy E step array for summation
            sunnyE[i] = sunny[i] / (sunny[i] + cloudy[i]);
            cloudyE[i] = cloudy[i] / (sunny[i] + cloudy[i]);

            // Sum sunny and cloudy arrays for m step
            sunSum += sunnyE[i];
            cloudSum += cloudyE[i];

            // calculate weighted totals 
            wSunSum += sunnyE[i] * days[i];      
            wCloudSum += cloudyE[i] * days[i];
      
        };
        
        // perform m step and save new mu values
        mSun = wSunSum / sunSum;
        tempS = fabs(mSun - muSun);
        // tempS = abs(tempS);
        printf("Difference in Sunny Mean = %lf and ", tempS);
        muSun = mSun;
        
        mCloud = wCloudSum / cloudSum;
        tempC = fabs(mCloud - muCloud);
        printf("Difference in Cloudy Mean = %lf\n", tempC);
        muCloud = mCloud;
        j++;

    }while ( (tempS > 0.1) | (tempC > 0.1) );
    printf("Halting iterations due to stop condition.\n");

    return 0;
};
