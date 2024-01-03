//
// Created by Rick Lattin on 3/3/21.
//

#ifndef INC_21S_PA02_LATTIRIC_DSVECTOR_H
#define INC_21S_PA02_LATTIRIC_DSVECTOR_H
#include <iostream>
#include <functional>

template <class T>

class DSVector {
    private:
        T* arVec;
        int nextOpen;
        int size;
    public:
        DSVector();                     //constructors
        DSVector(DSVector<T>&);         //copy constructor
        ~DSVector();                    //destructors

        int getNextOpen() const;        //set/get functions
        int getSize() const ;
        void setNextOpen(int);
        void setSize(int);

        DSVector& operator= (const DSVector&);     //DSVector functions
//        T& operator[](int);
        T& operator[](int) const;
        void insert(T);
        T remove(int);
        void grow();
        int find(T);
        bool isFound(T);
        void pop_last();

};

//------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------

template <class T>
DSVector<T>::DSVector() {                           //constructor
    arVec = new T[10];
    nextOpen = 0;
    size = 10;
}

template <class T>
DSVector<T>::DSVector(DSVector<T>& vec){            //copy constructor
    arVec = new T[vec.getSize()];
    nextOpen = vec.getNextOpen();
    size = vec.getSize();

    for(int i = 0; i < vec.getSize(); i++)
        arVec[i] = vec.arVec[i];
}

template <class T>
DSVector<T>::~DSVector(){                           //destructor
    delete [] arVec;
}

//------------------------------------------------------        //get/set functions
template <class T>
int DSVector<T>::getNextOpen() const{
    return nextOpen;
}

template <class T>
int DSVector<T>::getSize() const{
    return size;
}

template <class T>
void DSVector<T>::setNextOpen(int n){
    nextOpen = n;
}

template <class T>
void DSVector<T>::setSize(int n){
    size = n;
}
//--------------------------------------------------------      //DSVector functions

template <class T>
DSVector<T>& DSVector<T>::operator=(const DSVector<T>& vec){
    if(this == &vec)
        return *this;

    delete [] arVec;
    arVec = new T [vec.getSize()];
    size = vec.getSize();
    nextOpen = vec.getNextOpen();

    for(int i = 0; i<vec.getSize(); i++)
        arVec[i] = vec[i];

    return *this;
}

//template <class T>
//T& DSVector<T>::operator[](int loc){
//    return arVec[loc];
//}

template <class T>
T& DSVector<T>::operator[](int loc) const{
    return arVec[loc];
}

template <class T>
void DSVector<T>::insert(T item){           //adds one item to the back of the vector
    if(nextOpen < size){
        arVec[nextOpen] = item;
        nextOpen = nextOpen + 1;
    }
    else{
        grow();
        arVec[nextOpen] = item;
        nextOpen = nextOpen + 1;
    }
}

template <class T>
void DSVector<T>::grow(){                   //doubles the size of the vector
    T* temp = new T[2*size];

    for(int i = 0; i<size; i++)
        temp[i] = arVec[i];

    size = size*2;
    delete [] arVec;
    arVec = temp;
    //delete [] temp;
}

template <class T>
T DSVector<T>::remove(int loc){             //removes one item from the vector at a specific index
    T final = arVec[loc];

    for(int i = loc; i<nextOpen; i++)
        arVec[i] = arVec[i+1];

    nextOpen = nextOpen-1;

    return final;
}

template <class T>
int DSVector<T>::find(T item){              //finds the location of an item in the vector
    for(int i = 0; i<nextOpen; i++){
        if(item == arVec[i])
            return i;
    }

    return -1;
}

template <class T>
bool DSVector<T>::isFound(T item){          //determines whether there is a specific item in the vector
    for(int i = 0; i<nextOpen; i++){
        if(item == arVec[i])
            return true;
    }

    return false;
}

template <class T>
void DSVector<T>::pop_last(){
    //arVec[nextOpen-1] = nullptr;
    nextOpen--;
}
#endif //INC_21S_PA02_LATTIRIC_DSVECTOR_H

