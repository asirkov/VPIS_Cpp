#ifndef COMPLEX_H_INCLUDED
#define COMPLEX_H_INCLUDED

#include <iostream>
#include <string>
#include <sstream>

class Complex {
private:
    double _re;
    double _im;

public:
    Complex();
    Complex(double , double );
    Complex(Complex &);

    void set(double, double);
    double get_re();
    double get_im();

    Complex& operator+(Complex &);
    Complex& operator+(double);

    Complex& operator-(Complex &);
    Complex& operator-(double);

    Complex& operator*(Complex &);
    Complex& operator*(double);

    friend Complex& operator+(double, Complex& );
    friend Complex& operator-(double, Complex& );
    friend Complex& operator*(double, Complex& );

    //Complex& operator-(double );

    bool operator == (Complex &a);
    Complex& operator = (Complex &a);

    friend std::ostream& operator<<(std::ostream& , Complex &);
    friend std::istream& operator>>(std::istream& , Complex &);



    std::string to_string();
};


#endif // COMPLEX_H_INCLUDED
