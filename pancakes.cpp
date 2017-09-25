#include <iostream>
using namespace std;

int main() {
    const int PEOPLE = 10;
    int pancakesEaten[PEOPLE];
    int order[PEOPLE]; // 1 = the person ate the most
    int i, j;

    // load the number of pancakes each person ate
    for (i = 0; i < PEOPLE; i++) {
        cin >> pancakesEaten[i];
        order[i] = 1; // initialize the values in the array
    }

    /* for every combination of two people, if the second one ate less
    pancakes than the first one, increase their order by one
    -the person with most pancakes eaten doesn't have their order increased,
    so that they end up with value 1 (showing they are 1st)
    -if two people ate the same amount, order of neither of them is increased,
    keeping the rest of the values (1, 2, 2, 4)*/
    for (i = 0; i < PEOPLE; i++) {
        for (int j = 0; j < PEOPLE; j++) {
            if (pancakesEaten[i] > pancakesEaten[j]) {
                order[j]++;
            }
        }
    }

    /* one by one, go through the order, find the person with that value
    and print their number along with the number of pancakes eaten
    -if two people ate the same amount, they are printed in load order*/
    for (i = 1; i <= PEOPLE; i++) {
        for (j = 0; j < PEOPLE; j++) {
            if (order[j] == i) {
                cout << "Person " << j + 1 << " ate " <<
                pancakesEaten[j] << " pancakes.\n";
            }
        }
    }

    return 0;
}
