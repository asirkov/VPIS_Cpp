#include <iostream>
#include "Vector.h"

using namespace std;

int main() {

    Vector<int> foo = Vector<int>(5);
    foo.fill(3);
    foo[3] = 5;
    cout << foo << endl;

    foo.delLast();
    foo.addFirst(28);
    foo.addFirst(22);
    foo.addLast(2);
    foo.addLast(9);

    cout << foo << endl;
    cout << "removed: " << foo.removeElement(5) << endl;
    cout << foo << endl;
    cout << "deleted: " << foo.delFirst() << endl;
    cout << foo << endl;
    cout << "deleted: " << foo.del(1) << endl;
    cout << foo << endl;

    cout << endl << "enter vector(size = " << foo.getSize() << "):" << endl;
    Vector<int> bar = Vector<int>(foo.getSize());
    cin >> bar;

    cout << endl;
    cout << "vector1   : " << foo << endl;
    cout << "vector2   : " << bar << endl;

    bar[2] = -1;

    Vector<int> add = (foo + bar);
    Vector<int> dif = (foo - bar);
    int sub1 = (foo * bar);
    Vector<int> sub2 = (foo * 2);

    cout << endl << endl;
    cout << "add       : " << add << endl;
    cout << "diff      : " << dif << endl;
    cout << "sub(vect) : " << sub1 << endl;
    cout << "sub(num)  : " << sub2 << endl;
    cout << endl;

    // for example
    try {
        cout << foo[2] << endl;
        cout << foo[19] << endl;
    } catch (IndexOutOfBoundsException ex) {
        cout << ex.getMessage() << endl;
    } catch (Exception ex ) {
        cout << "Exception occured";
        return -1;
    }

    return 0;
}
