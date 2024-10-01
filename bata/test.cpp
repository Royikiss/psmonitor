/*************************************************************************
	> File Name: test.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 01 Oct 2024 04:28:13 PM CST
 ************************************************************************/

#include <iostream>
#include <unistd.h>
using namespace std;

int main() {
    srand(time(0));
    cout << "New process, process id = " << getpid() << endl;
    int n = 10;
    while (n--) {
        cout << n << endl;
        sleep(1);
        if (rand() % 100 + 1 < 20) {
            cout << "process : false" << endl;
            exit(0);
        }
    }
    return 0;
}
