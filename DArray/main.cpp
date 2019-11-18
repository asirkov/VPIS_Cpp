#include<iostream>
#include "DArray.h"

using namespace std;

int main() {
    DArray<int> arr = DArray<int>(3, 3);
    arr.fill(3);

    //cin >> arr;

    cout << arr << endl;

    //arr.delI(0);

    //cout << arr << endl;

    arr.add(4, 6, 0);

    cout << arr << endl;


    int** a = new int*[4];
    for(int i = 0; i < 4; ++i) {
        a[i] = new int[4];
        for(int j = 0; j < 4; ++j)
            a[i][j] = 8;

    }

    //arr.delJ(0);
    arr.setData(a, 4, 4);

    cout << arr << endl;

    a[1][1] = -1;

    arr.set(-2, 1, 1);
    cout << arr(1, 1) << endl << endl;

    cout << arr << endl;

    return 0;
}
