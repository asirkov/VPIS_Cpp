#ifndef DARRAY_H_INCLUDED
#define DARRAY_H_INCLUDED

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
class DArray {
private:
    T** data;
    uint sizeI;
    uint sizeJ;

public:
    //constructors
    DArray(uint newSizeI = 8, uint newSizeJ = 8);
    DArray(DArray &);           // = delete;
    DArray(DArray &&);

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
    T** toArray();

    //for test
    void fill(T);

    //operators
    T& operator()(uint, uint );

    bool operator==(DArray& );
    void operator=(DArray& );


    friend DArray<T> operator+(DArray<T> array1, DArray<T> array2) {
        if(array1.getSizeI() != array2.getSizeI() || array1.getSizeJ() != array2.getSizeJ())
            throw NotEqualsSizesException("operator+(DArray<> ,DArray<> )");
        DArray<T> result = DArray<T>(array1.getSizeI(), array2.getSizeJ() );

        for(uint i = 0; i < result.getSizeI(); i++)
            for(uint j = 0; j < result.getSizeJ(); j++)
                result[i][j] = array1[i][j] + array2[i][j];

        return result;
    }

    friend DArray<T> operator+(DArray<T> array1, T val) {
        DArray<T> result = DArray<T>(array1.getSizeI(), array1.getSizeJ());

        for(uint i = 0; i < result.getSizeI(); i++)
            for(uint j = 0; j < result.getSizeJ(); j++)
                result[i][j] = array1[i][j] + val;

        return result;
    }

    friend DArray<T> operator-(DArray<T> array1, DArray<T> array2) {
        if(array1.getSizeI() != array2.getSizeI() || array1.getSizeJ() != array2.getSizeJ())
            throw NotEqualsSizesException("operator+(DArray<> ,DArray<> )");
        DArray<T> result = DArray<T>(array1.getSizeI(), array2.getSizeJ() );

        for(uint i = 0; i < result.getSizeI(); i++)
            for(uint j = 0; j < result.getSizeJ(); j++)
                result[i][j] = array1[i][j] - array2[i][j];

        return result;
    }

    friend DArray<T> operator-(DArray<T> array1, T val) {
        DArray<T> result = DArray<T>(array1.getSizeI(), array1.getSizeJ() );

        for(uint i = 0; i < result.getSizeI(); i++)
            for(uint j = 0; j < result.getSizeJ(); j++)
                result[i][j] = array1[i][j] - val;

        return result;
    }

    /*

    friend T operator*(DArray<T> DArray1, DArray<T> DArray2) {
        T result = 0;
        if(DArray1.getSize() != DArray2.getSize() )
            throw NotEqualsSizesException();

        for(uint i = 0; i < DArray1.getSize(); i++)
            result += DArray1[i] * DArray2[i];
        return result;
    }

    friend DArray<T> operator*(DArray<T> DArray1, T val) {
        DArray<T> result = DArray<T>(DArray1.getSize() );
        for(uint i = 0; i < result.getSize(); i++)
            result[i] = DArray1[i] * val;
        return result;
    }

    friend DArray<T> operator*(T val, DArray<T> DArray1) {
        return (DArray1 * val);
    }

    */

    friend std::ostream& operator<<(std::ostream& stream, DArray& obj) {
        stream << obj.toString();
        return stream;
    };
    friend std::istream& operator>>(std::istream& stream, DArray& obj) {
        for(uint i = 0; i < obj.getSize(); i++)
            stream >> obj[i];
        return stream;
    };
};


//constructors

template <typename T>
DArray<T>::DArray(uint newSizeI, uint newSizeJ) {
    T** tmp = new T*[newSizeI];

    for(int i = 0; i < newSizeI; i++)
        tmp[i] = new T[newSizeJ];

    this->data = tmp;

    this->sizeI = newSizeI;
    this->sizeJ = newSizeJ;

    fill(0);
}

template <typename T>
DArray<T>::DArray(DArray &copy) {

}

template <typename T>
DArray<T>::DArray(DArray &&move) {

}


//methods

template <typename T>
uint DArray<T>::getSize() { return this->size; }

template <typename T>
bool DArray<T>::isEmpty() { return this->size == 0;}


/**
 * param:   newElement - element, that may be added
 *
 * returns: true, if element has been added,
 *          false, if array has not been initialized
 */
template <typename T>
bool DArray<T>::add(T newElement) {
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
bool DArray<T>::add(T newElement, uint index) {
    return true;
}

template <typename T>
bool DArray<T>::addFirst(T newElement) { return add(newElement, 0); }

template <typename T>
bool DArray<T>::addLast(T newElement) { return add(newElement); }

/**
 * param:   element - element that may be deleted
 *
 * returns: element, that has been delete,
 *          null, if index out of bounds, or element is not contains
 */
template <typename T>
T DArray<T>::removeElement(T element) {

}

/**
 * param:   index - index of element that may be deleted
 *
 * returns: element, that has been deleted,
 *          null, if index out of bounds, or array has not been initialized
 */
template <typename T>
T DArray<T>::del(uint index) {

}

template <typename T>
T DArray<T>::delFirst() { return del(0); }

template <typename T>
T DArray<T>::delLast() { return del(this->size - 1); }


template <typename T>
std::string DArray<T>::toString() {
    std::string result = "";

    for(uint i = 0; i < this->sizeI; i++) {
        result += "[";
        for(uint j = 0; j < this->sizeJ; j++) {
            result += TO_STRING(data[i][j]);
            if(j != this->sizeJ - 1)
                result += ", ";
        }
        result += "]\n";
    }
    //result += "]";

    return result;
}

template <typename T>
T** DArray<T>::toArray() { return this->data; }

/**
 * fill DArray element values
 */
template <typename T>
void DArray<T>::fill(T element) {
    //for(uint i = 0; i < this->size; i++)
    //    data[i] = element;
    for(uint i = 0; i < this->sizeI; i++)
        for(uint j = 0; j < this->sizeJ; j++)
            data[i][j] = element;
}


//operators

template <typename T>
T& DArray<T>::operator()(uint indexI, uint indexJ) {
    if(indexI > this->sizeI || indexJ > this->sizeJ)
        throw IndexOutOfBoundsException("operator[][]");
    return *&(this->data[indexI][indexJ]);
}

template <typename T>
bool DArray<T>::operator==(DArray& anotherDArray) {
    if(this->sizeI != anotherDArray.getSizeI() && this->sizeJ != anotherDArray.getSizeJ() )
        return false;
    for(uint i = 0; i < this->sizeI; i++)
        for(uint j = 0; i < this->sizeJ; j++)
            if(data[i][j] != anotherDArray[i][j])
                return false;
    return true;
}

template <typename T>
void DArray<T>::operator=(DArray& anotherDArray) {
    T** tmp = new T[anotherDArray.getSizeI()][anotherDArray.getSizeJ()];
    for(uint i = 0; i < anotherDArray.getSizeI(); i++)
        for(uint j = 0; j < anotherDArray.getSizeJ(); j++)
            tmp[i][j] = anotherDArray[i][j];
    delete data;
    this->data = tmp;
    this->sizeI = anotherDArray.getSizeI();
    this->sizeJ = anotherDArray.getSizeJ();
}


#endif // DARRAY_H_INCLUDED
