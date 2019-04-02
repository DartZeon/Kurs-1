#include <iostream>
#include <stdio.h>
// define INT_MAX
#include <bits/stdc++.h>

using namespace std;

int main()
{
    cout << "enter a number" << endl;
    // the input number, long enough to hold an int
    long long n = 0;
    // let the user enter a number
    cin >> n;
    if (n <= 0){
        cout << "error, number must be above 0";
        return -1;
    }

    if (n > INT_MAX){
        cout << "error, number is above INT_MAX = " << INT_MAX << endl;
        return -1;
    }
    cout << "your number is: " << n << endl;

    unsigned int count = 0;
    unsigned int n2 = n;
    for(unsigned int i = 1; i <= n; i++) {
        unsigned int k = n2 % i;
        if(k == 0) {
            printf("%d ", i);
            ++count;
        }
    }
    cout << endl << count << " dividers found" << endl;

    return 0;
}

