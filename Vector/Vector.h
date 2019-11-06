#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <cstdlib>
#include <sstream>
#include <iostream>
#include <string>

#include "Exception.cpp"

typedef unsigned int uint;

template <typename V>
std::string TO_STRING(const V val) {
    std::ostringstream oss;
    oss << val;
    return oss.str();
}


template <typename T>
class Vector {
private:
    T* data;
    uint size;

public:
    //constructors
    Vector(uint capacity = 8);
    Vector(Vector &);           // = delete;
    Vector(Vector &&);

    //methods
    bool isEmpty();
    uint getSize();

    bool add(T);
    bool add(T, uint);
    bool addFirst(T);
    bool addLast(T);

    T removeElement(T);
    T del(uint);
    T delFirst();
    T delLast();

    //may be private
    std::string toString();
    T* toArray();

    //for test
    void fill(T);

    //operators
    T& operator[](uint);

    bool operator==(Vector& );
    void operator=(Vector& );


    friend Vector<T> operator+(Vector<T> vector1, Vector<T> vector2) {
        if(vector1.getSize() != vector2.getSize() )
            throw NotEqualsSizesException("operator+(Vector<> ,Vector<> )");
        Vector<T> result = Vector<T>(vector1.getSize() );

        for(uint i = 0; i < result.getSize(); i++)
            result[i] = vector1[i] + vector2[i];

        return result;
    }

    friend Vector<T> operator+(Vector<T> vector1, T val) {
        Vector<T> result = Vector<T>(vector1.getSize() );

        for(uint i = 0; i < result.getSize(); i++)
            result[i] = vector1[i] + val;
        return result;
    }

    friend Vector<T> operator-(Vector<T> vector1, Vector<T> vector2) {
        if(vector1.getSize() != vector2.getSize() )
            throw NotEqualsSizesException("operator-(Vector<> ,Vector<> )");
        Vector<T> result = Vector<T>(vector1.getSize() );

        for(uint i = 0; i < result.getSize(); i++)
            result[i] = vector1[i] - vector2[i];
        return result;
    }

    friend Vector<T> operator-(Vector<T> vector1, T val) {
        Vector<T> result = Vector<T>(vector1.getSize() );

        for(uint i = 0; i < result.getSize(); i++)
            result[i] = vector1[i] - val;
        return result;
    }


    friend T operator*(Vector<T> vector1, Vector<T> vector2) {
        T result = 0;
        if(vector1.getSize() != vector2.getSize() )
            throw NotEqualsSizesException();

        for(uint i = 0; i < vector1.getSize(); i++)
            result += vector1[i] * vector2[i];
        return result;
    }

    friend Vector<T> operator*(Vector<T> vector1, T val) {
        Vector<T> result = Vector<T>(vector1.getSize() );
        for(uint i = 0; i < result.getSize(); i++)
            result[i] = vector1[i] * val;
        return result;
    }

    friend Vector<T> operator*(T val, Vector<T> vector1) {
        return (vector1 * val);
    }

    friend std::ostream& operator<<(std::ostream& stream, Vector& obj) {
        stream << obj.toString();
        return stream;
    };
    friend std::istream& operator>>(std::istream& stream, Vector& obj) {
        for(uint i = 0; i < obj.getSize(); i++)
            stream >> obj[i];
        return stream;
    };
};


//constructors

template <typename T>
Vector<T>::Vector(uint capacity) {
    data = new T[capacity];
    size = capacity;
    this->fill(0);
}

template <typename T>
Vector<T>::Vector(Vector &copy) {
    T* tmp = new T[copy.getSize() ];
    for(uint i = 0; i < copy.getSize(); i++)
        tmp[i] = copy[i];

    if(data) delete data;
    data = tmp;
    this->size = copy.getSize();
}

template <typename T>
Vector<T>::Vector(Vector &&move) {
    T* tmp = new T[move.getSize() ];
    T* moveArray = move.toArray();

    for(uint i = 0; i < move.getSize(); i++)
        tmp[i] = moveArray[i];
    delete data;
    data = tmp;
    this->size = move.getSize();

    delete move.data;
    move.size = 0;
}


//methods

template <typename T>
uint Vector<T>::getSize() { return this->size; }

template <typename T>
bool Vector<T>::isEmpty() { return this->size == 0;}


/**
 * param:   newElement - element, that may be added
 *
 * returns: true, if element has been added,
 *          false, if array has not been initialized
 */
template <typename T>
bool Vector<T>::add(T newElement) {
    T* tmp = new T[this->size + 1];
    if(tmp == nullptr)
        return false;

    for(uint i = 0; i < this->size; i ++)
        tmp[i] = data[i];
    tmp[this->size] = newElement;

    delete data;
    data = tmp;
    this->size++;

    return true;
}

/**
 * param:   newElement - element, that may be added
 *          index - index, where element were added
 *
 * returns: true, if element has been added,
 *          false, if array has not been initialized, or if index out of bounds
 */
template <typename T>
bool Vector<T>::add(T newElement, uint index) {
    T* tmp = new T[this->size + 1];

    if(index > this->size)
        return false;
    if(index == this->size)
        return add(newElement);

    for(uint i = 0; i < index; i++)
        tmp[i] = data[i];
    tmp[index] = newElement;

    // may be memcpy()
    for(uint i = index; i < this->size; i++)
        tmp[i + 1] = data[i];

    delete data;
    data = tmp;
    this->size++;

    return true;
}

template <typename T>
bool Vector<T>::addFirst(T newElement) { return add(newElement, 0); }

template <typename T>
bool Vector<T>::addLast(T newElement) { return add(newElement); }

/**
 * param:   element - element that may be deleted
 *
 * returns: element, that has been delete,
 *          null, if index out of bounds, or element is not contains
 */
template <typename T>
T Vector<T>::removeElement(T element) {
    int index = -1;
    for(uint i = 0; i < this->size; i++)
        if(data[i] == element)
            index = i;
    if(index == -1)
        return 0;

    //return del(this->size - 1);
    return del(index);
}

/**
 * param:   index - index of element that may be deleted
 *
 * returns: element, that has been deleted,
 *          null, if index out of bounds, or array has not been initialized
 */
template <typename T>
T Vector<T>::del(uint index) {
    if(index >= this->size)
        return 0;
    T* tmp = new T[this->size - 1];
    T result;

    for(uint i = 0; i < index; i++)
        tmp[i] = data[i];
    result = data[index];

    // may be memcpy()
    for(uint i = index; i < this->size - 1; i++)
        tmp[i] = data[i + 1];

    delete data;
    data = tmp;
    this->size--;

    return result;
}

template <typename T>
T Vector<T>::delFirst() { return del(0); }

template <typename T>
T Vector<T>::delLast() { return del(this->size - 1); }


template <typename T>
std::string Vector<T>::toString() {
    std::string result = "[";
    for(uint i = 0; i < this->size; i++) {
        result += TO_STRING(this->data[i]);
        if(i < this->size - 1)
            result += ", ";
    }
    result += "]";
    return result;
}

template <typename T>
T* Vector<T>::toArray() { return this->data; }

/**
 * fill vector element values
 */
template <typename T>
void Vector<T>::fill(T element) {
    for(uint i = 0; i < this->size; i++)
        data[i] = element;
}


//operators

template <typename T>
T& Vector<T>::operator[](uint index) {
    if(index > this->size)
        throw IndexOutOfBoundsException("operator[]");
    return *&(this->data[index]);
}

template <typename T>
bool Vector<T>::operator==(Vector& anotherVector) {
    if(this->size != anotherVector.getSize())
        return false;
    for(uint i = 0; i < this->size; i++)
        if(data[i] != anotherVector[i])
            return false;
    return true;
}

template <typename T>
void Vector<T>::operator=(Vector& anotherVector) {
    T* tmp = new T[anotherVector.getSize() ];
    for(uint i = 0; i < anotherVector.getSize(); i++)
        tmp[i] = anotherVector[i];
    delete data;
    this->data = tmp;
    this->size = anotherVector.getSize();
}

#endif // VECTOR_H_INCLUDED

