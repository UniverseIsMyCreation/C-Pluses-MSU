#include <iostream>

using namespace std;

template <typename T>
class Set{
    T * elements;
    int amount_of_elements;
    bool alterations;
    void copy_set_without_elem(T *, T *,T) const;
    void copy_set_plus_elem(T *, T *,T) const;
    void copy_set(T *, T *) const;
    bool check_in_last_income_set(T *, T *, int) const;
    void add_without_checking(T);
public:
    Set();
    ~Set();
    Set(T *, int);

    bool in(T) const;
    void del(T);
    void print();
    void add(T);
    void add(T *, int);

    const Set<T> operator+ (const Set<T> &) const;
    const Set<T> operator* (const Set<T> &) const;
    const Set<T> & operator= (const Set<T> &);
};

template <typename T>
void Set<T>::add_without_checking(T new_elem){
    T * copy_elements = new T[amount_of_elements + 1];
    copy_set_plus_elem(copy_elements,elements,new_elem);
    delete[] elements;
    elements = copy_elements;
    amount_of_elements++;
}

template <typename T>
void Set<T>::copy_set_without_elem(T * dest, T * source, T del_elem) const{
    int count = 0;
    int count_copy = 0;
    while(count != amount_of_elements){
        if (source[count] == del_elem){
            count++;
            continue;
        }
        dest[count_copy] = source[count];
        count++;
        count_copy++;
    }
}

template <typename T>
void Set<T>::copy_set_plus_elem(T * dest, T * source, T new_elem) const{
    int count = 0;
    while(count != amount_of_elements){
        dest[count] = source[count];
        count++;
    }
    dest[count] = new_elem;
}

template <typename T>
void Set<T>::copy_set(T * dest, T * source) const{
    int count = 0;
    while(count != amount_of_elements){
        dest[count] = source[count];
        count++;
    }
}

template <typename T>
bool Set<T>::check_in_last_income_set(T * where, T * what, int how_many) const{
    for(int i = 0; i < how_many; i++){
        if (where[i] == *what)
            return true;
    }
    return false;
}

template <typename T>
void Set<T>::add(T * new_group_elem, int amount_of_group){
    for(int i = 0; i < amount_of_group; i++)
        add(new_group_elem[i]);
}

template <typename T>
void Set<T>::add(T new_elem){
    if (!in(new_elem)){
        alterations = true;
        T * copy_elements = new T[amount_of_elements + 1];
        copy_set_plus_elem(copy_elements,elements,new_elem);
        delete[] elements;
        elements = copy_elements;
        amount_of_elements++;
    }
}

template <typename T>
Set<T>::Set(){
    elements = nullptr;
    alterations = true;
    amount_of_elements = 0;
}

template <typename T>
Set<T>::~Set(){
    delete[] elements;
}

template <typename T>
Set<T>::Set(T * new_elements, int amount){
    alterations = true;
    int count = 0;
    T arr[amount];
    for (int i = 0; i < amount - 1; i++){
        if (!check_in_last_income_set(new_elements + i + 1,new_elements + i,amount - 1 - i)){
            arr[count] = new_elements[i];
            count++;
        }
    }
    arr[count] = new_elements[amount - 1];
    count++;
    elements = new T[count];
    amount_of_elements = count;
    copy_set(elements,arr);
}

template <typename T>
bool Set<T>::in(T check_elem) const{
    T * check_link = elements;
    int count = 0;
    while(count != amount_of_elements){
        if (*check_link == check_elem)
            return true;
        check_link++;
        count++;
    }
    return false;
}

template <typename T>
void Set<T>::del(T del_elem){
    switch(amount_of_elements){
        case 0:
            break;
        case 1:
            if (*elements == del_elem){
                alterations = true;
                delete[] elements;
                elements = nullptr;
                amount_of_elements = 0;
            }
            break;
        default:
            if (in(del_elem)){
                alterations = true;
                T * copy_elements = new T[amount_of_elements - 1];
                copy_set_without_elem(copy_elements,elements,del_elem);
                delete[] elements;
                elements = copy_elements;
                amount_of_elements--;
            }
            break;
    }
}

template <typename T>
void Set<T>::print(){
    if (elements == nullptr){
        cout << endl;
        return;
    }
    if (alterations == false){
        for (int i = 0; i < amount_of_elements; i++)
            cout << elements[i] << " ";
        cout << endl;
        return;
    }
    int count,min_count;
    T min,temp;
    for (int i = 0; i < amount_of_elements; i++) {
        count = i + 1;
        min = elements[i];
        min_count = i;
        while (count != amount_of_elements){
            if (elements[count] < min){
                min = elements[count];
                min_count = count;
            }
            count++;
        }
        temp = elements[i];
        elements[i] = min;
        elements[min_count] = temp;
        cout << min << " ";
    }
    cout << endl;
    alterations = false;
}

template <typename T>
const Set<T> Set<T>::operator+ (const Set<T> & obj_set) const {
    Set<T> new_obj_set;
    new_obj_set.add(elements,amount_of_elements);
    new_obj_set.add(obj_set.elements,obj_set.amount_of_elements);
    return new_obj_set;
}

template <typename T>
const Set<T> Set<T>::operator* (const Set<T> & obj_set) const {
    Set<T> new_obj_set;
    for (int i = 0; i < amount_of_elements; i++){
        if (obj_set.in(elements[i]))
            new_obj_set.add_without_checking(elements[i]);
    }
    return new_obj_set;
}

template <typename T>
const Set<T> & Set<T>::operator= (const Set<T> & obj_set){
    delete[] elements;
    elements = new T[obj_set.amount_of_elements];
    amount_of_elements = obj_set.amount_of_elements;
    copy_set(elements,obj_set.elements);
    alterations = true;
    return *this;
}

int main()
{
    int a[] = { 1,2,3,4,5 };
    int b[] = { 3,2,6};
    Set <int> seti1(a,5),seti2,seti3,seti4;
    seti2.add(b, 3);
    seti1.print();
    seti2.print();
    seti3 = seti1*seti2;
    cout << "Intersect: ";
    seti3.print();
    seti4 = seti1 + seti2;
    cout << "Union: ";
    seti4.print();
    seti3.add(7);
    seti4.del(3);
    seti3.print();
    seti4.print();
    return 0;
}