#include <iostream>
#include <cstring>

using namespace std;

template <typename T>
T maxn(T * array, int amount){
    T max = array[0];
    for (int i = 1; i < amount; i++)
        if (array[i] > max) max = array[i];
    return max;
}

template <>
const char * maxn(const char ** array, int amount){
    const char * max = array[0];
    for (int i = 1; i < amount; i++)
        if (strlen(array[i]) > strlen(max)) max = array[i];
    return max;
}

int main()
{
    using namespace std;
    int arri[6] = {1, 2, 5, 3, 1, -1};
    double arrd[4] = {2.3, -1.3, 8.7, 4.5};
    const char * arrc[5] = {"first", "second", "third", "long string", "another string"};

    cout << "max of integer = " << maxn(arri, 6) << endl;
    cout << "max of double = " << maxn(arrd, 4) << endl;
    cout << "max string is " << maxn(arrc, 5) << endl;

    return 0;
}