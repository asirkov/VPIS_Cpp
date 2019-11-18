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
    DArray(uint newSizeI = 4, uint newSizeJ = 4);
    DArray(DArray &); // = delete;
    DArray(DArray &&);

    //methods
    bool isEmpty();
    uint getSizeI();
    uint getSizeJ();

    void setSize(uint , uint );

    bool set(T , uint , uint );
    bool add(T , uint , uint );
    T* delI(uint );
    T* delJ(uint );


    void setData(T** , uint , uint );

    //may be private
    std::string toString();
    T** toArray();

    //for test
    void fill(T);

    //operators

    bool operator==(DArray& );
    void operator=(DArray& );

    T operator()(uint , uint );

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
        for(uint i = 0; i < obj.getSizeI(); i++)
            for(uint j = 0; j < obj.getSizeJ(); j++)
                stream >> obj.data[i][j];  //obj(i, j);
        return stream;
    };

    ~DArray() {
        for(uint k = 0; k < this->getSizeI(); ++k)
            delete this->data[k];
        delete this->data;
    }
};


//constructors

template <typename T>
DArray<T>::DArray(uint newSizeI, uint newSizeJ) {
    T** tmp = new T*[newSizeI];

    for(uint i = 0; i < newSizeI; i++)
        tmp[i] = new T[newSizeJ];

    this->data = tmp;

    this->sizeI = newSizeI;
    this->sizeJ = newSizeJ;

    fill(0);
}

template <typename T>
DArray<T>::DArray(DArray &copy) {
    this->setData(copy->toArray(), copy->getSizeI(), copy->getSizeJ());
}

/// don`t use it
template <typename T>
DArray<T>::DArray(DArray &&move) {
    this->data = move.toArray();
    this->sizeI = move.getSizeI();
    this->sizeJ = move.getSizeJ();
}


//methods

template <typename T>
uint DArray<T>::getSizeI() { return this->sizeI; }

template <typename T>
uint DArray<T>::getSizeJ() { return this->sizeJ; }

template <typename T>
bool DArray<T>::isEmpty() { return this->getSizeI() == 0 && this->getSizeJ() == 0;}


/// if data has no enougth capacity, throw exception
template <typename T>
bool DArray<T>::set(T element, uint i, uint j) {
    if(i > this->sizeI || j > this->sizeJ)
        throw IndexOutOfBoundsException("set(T , uint ,uint)");
    this->data[i][j] = element;
}

/// possible problem
template <typename T>
void DArray<T>::setData(T** newData, uint i, uint j) {
    /// at here
    this->sizeI = i;
    this->sizeJ = j;

    for(uint k = 0; k < this->getSizeI(); ++k)
        delete this->data[k];
    delete this->data;

    this->data = new T*[i];
    for(uint k = 0; k < i; ++k) {
        this->data[k] = new T[j];

        for(uint l = 0; l < j; ++l)
            this->data[k][l] = newData[k][l];
    }
}


template <typename T>
void DArray<T>::setSize(uint i, uint j) {
    uint newI = i;
    uint newJ = j;

    T** temp = new T*[newI];
    for(uint k = 0; k < newI; ++k) {
        temp[k] = new T[newJ];
        for(uint l = 0; l < newJ; ++l)
            temp[k][l] = 0;
    }

    uint tempI = newI <= this->getSizeI() ? newI : this->getSizeI();
    uint tempJ = newJ <= this->getSizeJ() ? newJ : this->getSizeJ();

    for(uint k = 0; k < tempI; ++k)
        for(uint l = 0; l < tempJ; ++l)
            temp[k][l] = this->data[k][l];

    this->setData(temp, i, j);
}

/// if data has not enoght capacity, create it
template <typename T>
bool DArray<T>::add(T element, uint i, uint j) {
    if((i + 1) > this->getSizeI() || (j + 1) > this->getSizeJ() ) {

        uint newI = (i + 1) > this->getSizeI() ? (i + 1) : this->getSizeI();
        uint newJ = (j + 1) > this->getSizeJ() ? (j + 1) : this->getSizeJ();

        this->setSize(newI, newJ);
        /// maybe have to return false, if capacity is not enought?
    }

    this->set(element, i, j);
    return true;
}




/// delete the row
template <typename T>
T* DArray<T>::delI(uint i) {
    if(i > this->getSizeI())
        throw IndexOutOfBoundsException("delI(uint )");
    T* result = this->data[i];

    for(uint k = i; k < this->getSizeI() - 1; ++k)
        this->data[k] = this->data[k + 1];

    delete this->data[this->getSizeI()];
    this->sizeI--;

    return result;
}


template <typename T>
T* DArray<T>::delJ(uint j) {
    if(j > this->getSizeJ())
        throw IndexOutOfBoundsException("delJ(uint )");
    T* result = new T[this->getSizeI()];

    T** newData = new T*[this->getSizeJ() - 1];

    for(uint k = 0; k < this->getSizeI(); ++k ) {
        /// return statement
        result[k] = this->data[k][j];

        /// its can be in one for, get from tail
        for(uint l = 0; l < j; ++l)
            newData[k][l] = this->data[k][l];

        for(uint l = j; l < this->getSizeJ() - 1; ++l)
            newData[k][l] = this->data[k][l + 1];
    }

    this->setData(newData, this->getSizeI(), this->getSizeJ() - 1);

    return result;
}


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

template <typename T>
void DArray<T>::fill(T element) {
    for(uint i = 0; i < this->sizeI; i++)
        for(uint j = 0; j < this->sizeJ; j++)
            data[i][j] = element;
}


//operators

template <typename T>
T DArray<T>::operator()(uint i, uint j) {
    if(i > this->sizeI || j > this->sizeJ)
        throw IndexOutOfBoundsException("operator(,)");
    return *&(this->data[i][j]);
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
    //T** tmp = new T[anotherDArray.getSizeI()][anotherDArray.getSizeJ()];
    //for(uint i = 0; i < anotherDArray.getSizeI(); i++)
    //    for(uint j = 0; j < anotherDArray.getSizeJ(); j++)
    //        tmp[i][j] = anotherDArray[i][j];
    delete data;
    this->data = copy(anotherDArray.getData());
    this->sizeI = anotherDArray.getSizeI();
    this->sizeJ = anotherDArray.getSizeJ();
}


#endif // DARRAY_H_INCLUDED
