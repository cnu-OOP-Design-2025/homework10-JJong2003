#pragma once

#include <initializer_list>
#include <cstddef>


template<typename T>
class MyVector {
    T* data;            // 동적 배열을 가리키는 포인터
    size_t cap;         // 현재 할당된 배열 크기
    size_t length;      // 실제 저장된 요소 개수    
public:

    MyVector(std::initializer_list<T> init) {
        length = init.size();
        cap = length;
        data = new T[cap];
        size_t i = 0;
        for (const auto& val : init) {
            data[i++] = val;
        }
    }

    MyVector(): data(nullptr), length(0), cap(0) {}
    ~MyVector() { delete[] data; }

    // Vector 마지막에 항목을 추가하는 함수 구현, 필요시 벡터 크기 증가
    void push_back(const T& val){
        if (length+1 >= cap) {
            // 2배 증가
            T* new_datas = new T[cap*2];
            for (int i=0; i<length*2; i++) {
                new_datas[i] = data[i];
            }

            delete [] data;
            data = new_datas;
        }

        data[length] = val;
        length++;
    }   

    // Vector의 마지막 항목을 제거하는 함수 구현
    void pop_back() {
        length--;
    }

    // Vector에 있는 항목 개수(length)를 리턴하는 함수 구현
    size_t size() const {return length;}

    // [] 연산자 구현
    T& operator[](int i) {
        return data[i];
    }

    bool operator==(const MyVector& other) const {
        if (length != other.length) return false;
       
        Iterator thisIt = begin();
        Iterator otherIt = Iterator(other.data);

        for (; thisIt != end();) {
            if (*thisIt != *otherIt)
                return false;
            ++thisIt;
            ++otherIt;
        }
        
        return true;
    }

    bool operator!=(const MyVector& other) const {
        if (length != other.length) return true;
       
        Iterator thisIt = Iterator(data);
        Iterator otherIt = Iterator(other.data);

        for (; thisIt != end();) {
            if (*thisIt != *otherIt)
                return true;
            ++thisIt;
            ++otherIt;
        }
        
        return false;
    }

    bool operator<(const MyVector& other) const {
        if (length != other.length) return length < other.length;
        
        Iterator thisIt = Iterator(data);
        Iterator otherIt = Iterator(other.data);

        for (; thisIt != end();) {
            if (*thisIt < *otherIt)
                return true;
            ++thisIt;
            ++otherIt;
        }
        
        return false;
    }

    bool operator>(const MyVector& other) const {
        if (length != other.length) return length > other.length;

        Iterator thisIt = Iterator(data);
        Iterator otherIt = Iterator(other.data);

        for (; thisIt != end();) {
            if (*thisIt > *otherIt)
                return true;
            ++thisIt;
            ++otherIt;
        }
        return false;
    }

    bool operator<=(const MyVector& other) const {
        if (length != other.length) return length <= other.length;

        Iterator thisIt = Iterator(data);
        Iterator otherIt = Iterator(other.data);

        for (; thisIt != end();) {
            if (*thisIt <= *otherIt)
                return true;
            ++thisIt;
            ++otherIt;
        }
        return false;
    }

    bool operator>=(const MyVector& other) const {
        if (length != other.length) return length >= other.length;
        
        Iterator thisIt = Iterator(data);
        Iterator otherIt = Iterator(other.data);

        for (; thisIt != end();) {
            if (*thisIt >= *otherIt)
                return true;
            ++thisIt;
            ++otherIt;
        }
        return false;
    }


    // Vector에 대한 반복자
    class Iterator {
        T* ptr;         // 항목에 대한 포인터
    public:
        Iterator(T* p = nullptr): ptr(p) {}

        // 역참조 연산자 구현 
        T& operator*() {return *ptr;}

        Iterator& operator++() {
            ptr += 1;
            return *this;
        }   //전위 증가 연산자 구현  

        Iterator& operator--() {
            ptr -= 1;
            return *this;
        }   //전위 감소 연산자 구현

        Iterator operator+(int n) const {return Iterator(ptr + n);}   // 산술 연산자 구현
        Iterator operator-(int n) const {return Iterator(ptr - n);}   // 산술 연산자 구현

        bool operator==(const Iterator& other) const {return ptr == (other.ptr);}
        bool operator!=(const Iterator& other) const {return ptr != (other.ptr);}

        int operator-(const Iterator& other) const {return *ptr - *(other.ptr);}
    };

    // 첫번째 항목에 대한 iterator 리턴 함수 구현
    Iterator begin() {return Iterator(data);}

    const Iterator begin() const {return Iterator(data);}

    // 마지막 항목에 대한 iterator 리턴 함수 구현 
    Iterator end() {return Iterator(data + length);}

    const Iterator end() const {return Iterator(data + length);}


    // insert: 지정 위치에 요소 삽입 함수 구현
    Iterator insert(Iterator pos, const T& value) {
        Iterator it = begin();
        int idx = 0;
        for (; it != pos; ++it) {idx++;}
        
        if (length + 1 >= cap) {
            // 2배 증가
            T* new_datas = new T[cap*2];
            for (int i=0; i<idx; i++) {
                new_datas[i] = data[i];
            }
            new_datas[idx] = value;
            for (int i=idx+1; i<length+1; i++) {
                new_datas[i] = data[i-1];
            }
            delete [] data;
            data = new_datas;
        } else {
            for (int i=length-1; i>idx; i--) {
                data[i] = data[i+1];
            }
            data[idx] = value;
        }
        length++;
        return begin();
    }

    // erase: 지정 위치 요소 제거 함수 구현
    Iterator erase(Iterator pos) {
        Iterator it = begin();
        int idx = 0;
        for (; it != pos; ++it) {idx++;}

        for (int i=idx; i<length; i++) {
            data[i] = data[i+1];
        }

        length--;
        
        return Iterator(data);
    }

    // clear: 모든 요소 제거 함수 구현 (size = 0 초기화)
    void clear() {
        length = 0;
    }

    // at: 범위 체크 후, i번째 항목 접근 함수 구현
    T& at(size_t i) {
        // if (0<= i && i < length) return data[i];
        // return NULL;
        return data[i];
    }

    // front/back
    T& front() {
        // // 첫번째 항목 리턴 함수 구현
        // if (length > 0) return data[0];
        // return NULL;
        return data[0];
    }

    T& back() {
        // 마지막 항목 리턴 함수 구현
        // if (length <= 0) return NULL;
        return data[length-1];
    }    

    // capacity
    size_t capacity() const {return cap;}   // cap 값 리턴하는 함수 구현

    // empty
    bool empty() const {return length==0;}    // 현재 vector가 empty인지 확인하는 함수 구현

};