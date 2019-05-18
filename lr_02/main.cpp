#include <iostream>
#include <cmath>

template <typename T>
class Array {
    T* ArrayPointer;
    int LastElement;
    size_t sizeOfArray;
public:
    ~Array() {
        delete[] ArrayPointer;
    }
    Array(): ArrayPointer(NULL), LastElement(-1), sizeOfArray(0) {}
    Array(const T &firstElement): ArrayPointer(NULL), sizeOfArray(8), LastElement(0) {
        ArrayPointer= new T[8]; 
        ArrayPointer[0]=firstElement;
    }
    Array(const Array<T> &oldArray): ArrayPointer(NULL), LastElement(-1), sizeOfArray(0) {
        reserve(oldArray.LastElement);
        cpy(oldArray.ArrayPointer,ArrayPointer,oldArray.LastElement);
        LastElement=oldArray.LastElement;
    }
private:
    void cpy(T* oldPointer, T* newPointer, const int &LastElementOffset) {
        if (LastElementOffset<0) {return;}
        if ((newPointer>oldPointer)&&(newPointer<(oldPointer+LastElementOffset))) {
            for (int i=LastElementOffset; i>=0; i--) {
                new(newPointer+i) T(*(oldPointer+i));
            }          
        } else if ((oldPointer>newPointer)&&(oldPointer<(newPointer+LastElementOffset))) {
            for (int i = 0; i<=LastElementOffset; i++) {
                new(newPointer+i) T(*(oldPointer+i));
            }
        } else {
            for (int i = 0; i<=LastElementOffset; i++) {
                new(newPointer+i) T(*(oldPointer+i));
            }
        }
    }
    void reserve(const size_t &neededSize) {
        if (!ArrayPointer) {
            ArrayPointer = new T[8];
            LastElement = -1;
            sizeOfArray = 8;
        }
        while (neededSize>=sizeOfArray) {       
            sizeOfArray=sizeOfArray<<1;
            T* newptr = new T[sizeOfArray];
            cpy(ArrayPointer,newptr,LastElement);
            delete[] ArrayPointer;
            ArrayPointer=newptr;
        }
    }
    void optimize() {
        Array buf(*this);
        (*this)=buf;
    }
public:
    void add(const T &newElement) {
        if (!ArrayPointer) {
            ArrayPointer = new T[8];
            ArrayPointer[0]=newElement;
            LastElement = 0;
            sizeOfArray=8;
        } else {
            reserve(LastElement + 1);
            LastElement++;
            new(ArrayPointer+LastElement) T(newElement);
        }
    }
    void insert(const T &newElement, const int &pos) {
        if (pos<0) {return;}
        if (pos>LastElement) {
            add(newElement);
        } else {
            reserve(LastElement+1);
            LastElement++;
            cpy(ArrayPointer+pos,ArrayPointer+pos+1,LastElement-pos);
            new(ArrayPointer+pos) T(newElement);
        }
    }
    void eraze(const int &pos) {
        if (pos<0) {return;}
        if (pos<=LastElement) {
            cpy(ArrayPointer+pos+1,ArrayPointer+pos,LastElement-pos);
            LastElement--;
        }
        optimize();
    }
    T operator[] (const int &offset) {
        return *(ArrayPointer+offset);
    }
    void operator= (const Array<T> &array) {
        if (ArrayPointer!=array.ArrayPointer) {delete[] ArrayPointer;}
        reserve(array.LastElement);
        cpy(array.ArrayPointer,ArrayPointer,array.LastElement);
        LastElement=array.LastElement;
    }
    int ioLastElement() {return LastElement;}
};

int main (void) {
    Array<int> testarray;
    testarray.add((15));
    testarray.add((14));
    testarray.add((13));
    testarray.add((12));
    testarray.add((11));
    testarray.add((10));
    testarray.add((9));
    std::cout<<"Array : ";
    for (int i = 0; i<=testarray.ioLastElement(); i++) {
        std::cout << testarray[i] << " ";
    }
    std::cout<<std::endl;
    std::cout<<"Erase №3 (#4) :";
    testarray.eraze(3);
    for (int i = 0; i<=testarray.ioLastElement(); i++) {
        std::cout << testarray[i] << " ";
    }
    std::cout<<std::endl;
    std::cout<<"Insert 5 at pos 3 :";
    testarray.insert((5),3);
    for (int i = 0; i<=testarray.ioLastElement(); i++) {
        std::cout << testarray[i] << " ";
    }
    std::cout<<std::endl;
    std::cout<<"Insert 1 at pos 100 :";
    testarray.insert((1),100); 
    for (int i = 0; i<=testarray.ioLastElement(); i++) {
        std::cout << testarray[i] << " ";
    }
    std::cout<<std::endl;
    std::cout<<"Copy to new Array :";
    Array<int> testarray2;
    testarray2=testarray;
    for (int i = 0; i<=testarray2.ioLastElement(); i++) {
        std::cout << testarray2[i] << " ";
    }
    std::cout<<std::endl;

    return 0;
}
