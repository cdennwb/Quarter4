#include <iostream>
#include <math.h>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <string>

using namespace std;

//Defines
#define popSize 50
#define maxGens 1000
#define maxDegree 7
#define geneLength 1 + 5
#define bitLength geneLength * (maxDegree + 1)
#define pMutate .001
#define pXover .7
#define rNum rand() % RAND_MAX
#define tourneySize 4

//Chromosome
struct genotype{
    //
    float fitness;
    string bits;
    genotype(): bits(""), fitness(0.0f){};
	genotype(string bts, float ftns): bits(bts), fitness(ftns){}
};

string getBits(){
    //
    string bits = '';
    for(int i = 0; i < bitLength; ++i){
        if(rNum < .5){
            bits += '0';
        }else{
            bits += '1';
        }
    }
    return bits;
}

void xOver(string  &child1, string &child2){
    //
    int index = (int) rNum * bitLength;

    string t1 = child1.substr(0, index) + child2.substr(index, bitLength);
    string t2 = child2.substr(0, index) + child1.substr(index, bitLength);

    child1 = t1; child2 = t2;
}

void mutate(string &bits){
    //
    for(int i = 0; i < bitLength; ++i){
        if(rNum < pMutate){
            if(bits[i] == '0'){
                bits.at(i) = '1';
            }else{
                bits.at(i) = '0';
            }
        }
    }
}

string tourney(vector<genotype> &pop){
    //
    vector<genotype>participants;
    for(int i = 0; i < tourneySize; ++i){
        participants.push_back(pop[rNum*popSize]);
    }
    //
    while(participants.size() > 1){
        vector<genotype>winners;
        for(int i = 0; i < participants.size()/2; ++i){
            if(participants[i].fitness > participants[participants.size() - i].fitness){
                winners.push_back(participants[i]);
            }else{
                winners.push_back(participants[participants.size() - i]);
            }
        }
        participants = winners;
    }
    return participants[0].bits;
}

float assignFitness(genotype &bobby, int (&realVals)[maxDegree + 1]){
    //
    string chromosome = bobby.bits;
    vector<int>coefficients;
    for(int i = 0; i < degree + 1; i += geneLength){
        coefficients.push_back(bin2dec(chromosome.substr(i, geneLength)));
    }
    return 1/getError(coefficients, realVals);
}

int getError(vector<int> &vars, int(&realVals)[maxDegree + 1]){
    //
    int sse = 0;
    for(int x = 0; x < 100; ++x){
        int testVal = 0;
        int actual = 0;
        for(int i = vars.length(); i > 0; --i){
            testVal += vars[i-1]*pow(x,i);
        }
        for(int i = vars.length(); i > 0; --i){
            actual += realVals[i-1]*pow(x,i);
        }
        sse += pow(actual - testVal, 2);
    }
    return sse;
}


int bin2dec(string bits){
    //
    int val = 0;
    int add = 1;
    for(int i = bits.length(); i > 0; --i){
        if(bits.at(i-1) == '1'){
            val += add;
        }
        add *= 2;
    }
    return val;
}


int main(){
    //
    srand((int)time(NULL))
    //
    while(true){
        int degree;
        cout<<"Yo, what is the degree of your polynomial? (Up to 7)\n";
        cin>>degree;
        int coefficients[degree + 1];
        cout<<"Enter in your coefficients (left to right)[ |Your Value| < " + pow(2, geneLength - 1) + " ]\n";
        for(int i = 0; i < degree + 1; ++i){
            int var;
            cin>>var;
            coefficients[i] = var;
        }

        genotype population[popSize];
        for(int i = 0; i < popSize; ++i){
            population[i].bits = getBits();
            population[i].fitness = 0.0f;
        }

        int gensNeeded = 0;
        bool found = false;

        while(!found){
            for()
        }
    }
}
