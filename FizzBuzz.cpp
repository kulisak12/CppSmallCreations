#include <iostream>
using namespace std;

int main() {
    for (int i = 1; i <= 100; i++) {
        bool divBy3 = (i % 3 == 0);
        bool divBy5 = (i % 5 == 0);
        if (divBy3 || divBy5) {
            if (divBy3) {
                cout << "Fizz";
            } 
            if (divBy5) {
                cout << "Buzz";
            }
        } else {
            cout << i;
        }
        cout << ' ';
    }
    return 0;
}