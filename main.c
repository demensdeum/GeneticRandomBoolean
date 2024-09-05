#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int randomPositiveInt(int max) {
    return rand() % max;    
}

bool randomBoolean() {
    return randomPositiveInt(100) > 49;
}

const int roundsCount = 10000;

const bool canAttackSelf = true;
const bool canAttackSameGender = false;
const bool attackEverytime = false;
const bool shuffle = true;

const int shuffleRounds = 100;
const int femaleChromosomesCount = 22;
const int maleChromosomesCount = 22;
const int chromosomesCount = femaleChromosomesCount + maleChromosomesCount;

enum Gender {
    female = 0,
    male
};

struct Chromosome {
    int id;
    int health;
    int power;
    int gender;
};


void shuffleChromosomes(struct Chromosome chromosomes[]) {
    for (int i = chromosomesCount - 1; i > 0; i--) {
        int j = randomPositiveInt(i + 1);
        struct Chromosome temp = chromosomes[i];
        chromosomes[i] = chromosomes[j];
        chromosomes[j] = temp;
    }
}

int femaleChromosomeHealth() {
    return 50 + randomPositiveInt(50);
}

int maleChromosomeHealth() {
    return 50 + randomPositiveInt(50);
}

int femaleChromosomePower() {
    return randomPositiveInt(10);
}

int maleChromosomePower() {
    return randomPositiveInt(10);
}

int simulate(int verbose) {
    struct Chromosome chromosomes[chromosomesCount];

    for (int i = 0; i < chromosomesCount; i++) {
        chromosomes[i].id = i;
        chromosomes[i].gender = i < femaleChromosomesCount ? female : male;
        chromosomes[i].health = i < femaleChromosomesCount ? femaleChromosomeHealth() : maleChromosomeHealth();
        chromosomes[i].power = i < femaleChromosomesCount ? femaleChromosomePower() : maleChromosomePower();
    }

    shuffleChromosomes(chromosomes);

    int war = true;

    int femaleChromosomesAliveCount = 0;
    int maleChromosomesAliveCount = 0;

    while (war) {
        femaleChromosomesAliveCount = 0;
        maleChromosomesAliveCount = 0;

        for (int i = 0; i < chromosomesCount; i++) {
            struct Chromosome *currentChromosome = &chromosomes[i];
            if (currentChromosome->health < 1) {
                if (verbose) {
                    printf("Dead chromosome, pass...\n");
                }
                continue;
            }

            if (attackEverytime == false && randomBoolean()) {
                if (verbose) {
                    printf("Don't want to attack, pass...\n");
                }
                continue;
            }

            struct Chromosome *randomChromosome = &chromosomes[randomPositiveInt(chromosomesCount)];
            if (randomChromosome->id == currentChromosome->id && canAttackSelf == false) {
                if (verbose) {
                    printf("Can't attack self, pass...\n");
                }
                continue;
            }
            if (randomChromosome->gender == currentChromosome->gender && canAttackSameGender == false) {
                if (verbose) {
                    printf("Can't attack same gender, pass...\n");
                }
                continue;
            }
            randomChromosome->health -= currentChromosome->power;
            if (currentChromosome->health > 0) {
                if (currentChromosome->gender == female) {
                    femaleChromosomesAliveCount++;
                }
                else if (currentChromosome->gender == male) {
                    maleChromosomesAliveCount++;
                }
            }
        }
        if (femaleChromosomesAliveCount == 0 || maleChromosomesAliveCount == 0) {
            war = false;
            break;
        }
    }

    if (femaleChromosomesAliveCount > 0) {
        if (verbose) {
            printf("Female wins the war!\n");
        }
        return female;
    } else {
        if (verbose) {
            printf("Male wins the war!\n");
        }
        return male;
    }
}

int main(int argc, char **argv) {
    printf("Genetic Random Boolean\n");

    srand(time(NULL));

    int femaleWinCount = 0;
    int maleWinCount = 0;

    for (int i = 0; i < roundsCount; i++) {
        int result = simulate(false);
        if (result == female) {
            femaleWinCount++;
        }
        else {
            maleWinCount++;
        }
    }

    float ratio = 0;
    if (femaleWinCount > 0) {
        ratio = (float)maleWinCount / (float)femaleWinCount;
    }
    printf("Female win count:%d\nMale win count: %d\nRatio: %f\n", femaleWinCount, maleWinCount, ratio);

    return 0;
}