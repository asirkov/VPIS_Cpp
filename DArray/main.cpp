#include <iostream>
#include "DArray.h"

using namespace std;

int main() {
    DArray<int> arr = DArray<int>(3, 3);
    arr.fill(3);

    cout << arr << endl;
    return 0;
}
