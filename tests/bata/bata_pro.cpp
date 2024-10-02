/*************************************************************************
	> File Name: bata_pro.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 02 Oct 2024 06:12:58 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;

int main() {
    cout << "Process has stared" << endl;
    int n = 10;
    srand(time(0));
    while(n--) {
        cout << "n = " << n << endl;
        if (rand() % 100 <= 10) {
            cout << "The program encountered an error and terminated" << endl;
            return 1;
        }
    }
    return 0;
}
