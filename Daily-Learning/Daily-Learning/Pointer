#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    int var = 25;
    int *ptr;
    ptr = &var;
    cout << "Vale of var: " << var << endl;
    cout << "Address of var" << &var << endl;
    cout << "Value stored in ptr (address of var): " << ptr << endl;
    cout << "Value pointed to by ptr: " << *ptr << endl;
    *ptr = 30;
    cout << "New value of var after changing through ptr: " << var << endl;
    
    int arr[3] = {10, 20, 30};
    int *arrPtr = arr;
    cout << *arrPtr << endl;
    arrPtr++;
    cout << *arrPtr << endl;
    arrPtr++;
    cout << *arrPtr << endl;
    
//    Pointer to Pointer
    int x = 100;
    int* p = &x;
    int** pp = &p;
    cout << &x << endl;
    cout << p << endl;
    
    cout << &p << endl;
    cout << pp << endl;
    
    cout << *pp << endl;
    
    cout << **pp << endl;
    
//    Pointers and Arrays
    int intArray[] = {5, 10, 15, 20};
    cout << sizeof(intArray)/sizeof(intArray[0]) << endl;
    int* aP = intArray; // same as &intArray[0];
    cout << *(aP + 2) << endl;
    return 0;
}
