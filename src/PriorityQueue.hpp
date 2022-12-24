#ifndef MAXPQHEADERDEF
#define MAXPQHEADERDEF

#include <iostream>
#include <vector>

template <typename T>
class MaxPQ{

    private:
        std::vector<T> pq;      // Vector to hold elements
        int N;                  // Number of elements
        bool less(int i, int j);// Compares elements at i and j
        void swap(int i, int j);// Swaps elements at i and j
        void swim(int k);       // Swim the child node up until priority ordered
        void sink(int k);       // Sink the parent node down until priority ordered

    public:
        MaxPQ();            // Instantiate an empty PQ
        void insert(T t);   // Insert an element into the PQ
        T delMax();         // Return the maximum priority element
        bool isEmpty();     // Checking if the PQ is empty
        void view();        // View the array
        T getMax();         // Get the number of events in current queue

};


template <typename T>
MaxPQ<T>::MaxPQ(){
    N = 0;
    T t;
    pq.push_back(t);
}


template <typename T>
bool MaxPQ<T>::less(int i, int j){
    if (pq[i] < pq[j]){
        return true;
    }
    else{
        return false;
    }
}


template <typename T>
void MaxPQ<T>::swap(int i, int j){
    T tmp = pq[i];
    pq[i] = pq[j];
    pq[j] = tmp;
}


template <typename T>
void MaxPQ<T>::swim(int k){
    while(k > 1 && less(k/2, k)){
        swap(k/2, k);
        k = k/2;
    }
}


template <typename T>
void MaxPQ<T>::sink(int k){
    while (2*k <= N){
        int j = 2*k;
        if (j<N && less(j, j+1)){
            j += 1;
        }
        if (!less(k, j)){
            break;
        }
        swap(k, j);
        k = j;
    }
}


template <typename T>
void MaxPQ<T>::insert(T t){
    N += 1;
    pq.push_back(t);
    swim(N);
}


template <typename T>
T MaxPQ<T>::delMax(){

    if (isEmpty()){
        std::cerr << "Trying Access on an Empty Priority Queue! Exiting" << std::endl;
        exit(1);
    }
    T elem = pq[1];
    swap(1, N);
    N -= 1;
    pq.pop_back();
    sink(1);
    
    return elem;
}


template <typename T>
bool MaxPQ<T>::isEmpty(){
    if (N == 0){
        return true;
    }
    else{
        return false;
    }
}


template <typename T>
void MaxPQ<T>::view(){
    for (int i=0; i<=N; i++){
        std::cout << pq[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Size: " << N << std::endl;
    std::cout << std::endl;
}


template <typename T>
T MaxPQ<T>::getMax(){
    return pq[1];
}

#endif