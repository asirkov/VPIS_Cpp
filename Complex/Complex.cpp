#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "Complex.h"

using namespace std;

Complex::Complex() : _re(0), _im(0) {};
Complex::Complex(double a, double b) : _re(a), _im(b) {}
Complex::Complex(Complex &copy) : _re(copy.get_re() ), _im(copy.get_im() ) {}

void Complex::set(double re, double im) {_re = re; _im = im; }
double Complex::get_re() {return _re; }
double Complex::get_im() {return _im; }

Complex& Complex::operator+(Complex &a) {
    return *(new Complex(this->get_re() + a.get_re(), this->get_im() + a.get_im()) );
}
Complex& Complex::operator+(double a) {
    return *(new Complex(this->get_re() + a, this->get_im()) );
}
Complex& operator+(double a, Complex&b) {
    return *(new Complex(a + b.get_re(), b.get_im()) );
}


Complex& Complex::operator-(Complex &a) {
    return *(new Complex(this->get_re() - a.get_re(), this->get_im() - a.get_im()) );
}
Complex& Complex::operator-(double a) {
    return *(new Complex(this->get_re() + a, this->get_im()) );
}
Complex& operator-(double a, Complex& b) {
    return *(new Complex(a + b.get_re(), b.get_im()) );
}


Complex& Complex::operator*(Complex &a) {
    return *(new Complex((this->get_re() * a.get_re() ) - (this->get_im() * a.get_im() ), (this->get_re() * a.get_im()) + (this->get_im() * a.get_re() )));
}
Complex& Complex::operator*(double a) {
    return *(new Complex(this->get_re() * a , this->get_im() * a));
}
Complex& operator*(double a, Complex& b) {
    return *(new Complex(a * b.get_re(), a * b.get_im()));
}


bool Complex::operator==(Complex &a) {
    return (this->get_re() == a.get_re()) && (this->get_im() && a.get_im());
}
Complex& Complex::operator=(Complex &a) {
    set(a.get_re(), a.get_im());
    return (*this);
}

ostream& operator<<(ostream& stream, Complex& a) {
    stream << a.to_string();
    return stream;
}

istream& operator>>(istream& stream, Complex& a){
    double re;
    double im;
    stream >> re;
    stream >> im;
    a.set(re, im);
    return stream;
}


string TO_STRING (double val) {
    std::ostringstream oss;
    oss << std::defaultfloat << val;
    return oss.str();
}

std::string Complex::to_string(){
    return "(" + TO_STRING(_re) + (_im > 0 ? "+" : "") + TO_STRING(_im) + "i)";
}

