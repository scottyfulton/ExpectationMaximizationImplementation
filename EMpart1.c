/*
Scotty Fulton                               Thursday 8, 2018
Expextation Maximization part 1 for coin toss, binomial data.

*/

#include <stdio.h>
#include <math.h>

long nMkFact, nFact, kFact, nkFact, binom;

// factorial function
long factorialize (int n){
    long factorial = 1;
    for (int i = 1; i<=n; i++){
        factorial *= i;
    };
    return factorial;
};
// binomial function that uses factorialize
long binomalize (int n, int k){
    int nMk = (n-k);
    nMkFact = factorialize(nMk);
    nFact = factorialize(n);
    kFact = factorialize(k);
    nkFact = nMkFact * kFact;
    binom = nFact/nkFact;
};

// calcs p^k * q^n-k
double calcPxQ (double p, double n, double k){
    double q = 1.0 - p;
    double r = n-k;
    p = pow(p, k);
    q = pow( q, r );
    double result = p * q;
    return result;
};

int main (){

    double thetaA = 0.60;
    double thetaB = 0.50;
    int enn = 10;
    int kay[5] = {5, 9, 8, 4, 7};
    double CoinAvg [4];
    int tempk;
    double resultArr[4];
    float sumArr[4];
    double sumAH, sumAT, sumBH, sumBT=0;
    double coinAH, coinAT, coinBH, coinBT, binom1, binom2, binomr1, binomr2=0;

    printf("--------------------------------------------\n");
    printf("---Initial ThetaA = %.2lf, ThetaB = %.2lf----\n", thetaA, thetaB);

    // iterates through the algo 10 times
    for (int j = 0; j<10; j++){

        printf("--------------------------------------------\n");
        printf("---Iteration %d---\n", j+1);
        printf("------------------\n");

        // iterates through the number of tosses in each set
        for (int i = 0; i < 5; i++){

            // float thetaB = (1.0 - thetaA);
            tempk = kay[i];

            // A coin
            // nCk 
            long answer = binomalize(enn, tempk);
            // p^k * q^{n-k}
            double calced = calcPxQ(thetaA, (double)enn, (double)tempk);
            // = nCk * p^k * q^{n-k}
            double resultant = answer * calced;
            //binom 1
            binom1 = resultant;

            // B coin
            // p^k * q^{n-k}
            calced = calcPxQ(thetaB, (double)enn, (double)tempk);
            // = nCk * p^k * q^{n-k}
            resultant = answer * calced;
            // binom 2
            binom2 = resultant;

            // P(coin=A)
            binomr1 = binom1 / (binom1 + binom2);

            // P(coin=B) also is  (1 - P(coin = A))
            binomr2 = binom2 / (binom1 + binom2);

            // Coin A H/T knt
            coinAH = binomr1 * tempk;
            coinAT = binomr1 * (enn - tempk);
            sumAH += coinAH;
            sumAT += coinAT;

            // Coin B H/T knt
            coinBH = binomr2 * tempk;
            coinBT = binomr2 * (enn - tempk);
            sumBH += coinBH;
            sumBT += coinBT;
        };
        // calculates new thetas for M step
        thetaA = sumAH / (sumAH + sumAT);
        thetaB = sumBH / (sumBH + sumBT);
        printf("ThetaA = %lf, ThetaB = %lf\n", thetaA, thetaB);
        sumAH = sumAT = sumBH = sumBT = 0;
    };
    
    return 0;
};
