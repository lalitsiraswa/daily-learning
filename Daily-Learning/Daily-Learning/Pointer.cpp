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
    return 0;
}
