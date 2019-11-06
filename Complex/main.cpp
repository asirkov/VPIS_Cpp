#include <iostream>
#include "Complex.h"

using namespace std;

int main() {
    Complex* foo = new Complex(1, 2);
    Complex* bar = new Complex(3, 4);

    cout << foo->to_string() << endl << endl;
    cout << bar->to_string() << endl << endl;

    cout << "+ : " << ((*foo) + (*bar)) << endl;
    cout << "- : " <<((*foo) - (*bar)) << endl;
    cout << "* : " <<((*foo) * (*bar)) << endl;

    return 0;
}
