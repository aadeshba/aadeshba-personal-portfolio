#include <vector>
#include <map>
#include <exception>

template<class T>

class MinHeap {

public:
    MinHeap(int d);
    /* Constructor that builds a d-ary Min Heap
       This should work for any d >= 2,
       but doesn't have to do anything for smaller d.*/

    ~MinHeap();

    void add(T item, int priority);
    /* adds the item to the heap, with the given priority. */

    const T& peek() const;
    /* returns the element with smallest priority.
       Break ties however you wish.
       Throws an exception if the heap is empty. */

    void remove();
    /* removes the element with smallest priority.
       Break ties however you wish.
       Throws an exception if the heap is empty. */

    bool isEmpty() const;
    /* returns true iff there are no elements on the heap. */

    void updatePriority(int node, int priority);//updates priorities

private:
    int d;
    int size;
    std::vector<std::pair<std::pair<T, int>, int>> v;
    int id;
    std::vector<int> mapOfIDs;//associates everything with ids
    void trickleDown(int pos);
    void bubbleUp(int pos);
    int parent(int i);
    int firstChild(int i);
    void swapInVector(int r, int s);
    // whatever you need to naturally store things.
    // You may also add helper functions here.
};


template <class T>
MinHeap<T>::MinHeap(int d) {  
    this->d = d;
    size = 0;
    id = 0;//first push will have an id of 0
}

template <class T>
MinHeap<T>::~MinHeap() {

}

template <class T>
void MinHeap<T>::add(T item, int priority) {  
    v.push_back(std::make_pair((std::make_pair(item, priority)), id));
    mapOfIDs.push_back(id);
    id++;//increment for next node
    size++;//same here
    bubbleUp(size - 1);//avoid seg fault
    return;
}

template<class T>
const T& MinHeap<T>::peek() const {
    if (isEmpty()) {
        throw std::exception();
    }
    return v[0].first.first;//first item of pair in first pair 
}

template<class T>
void MinHeap<T>::remove() {
    if (isEmpty()) {
        throw std::exception();
    }
    swapInVector(0, size - 1);
    v.erase(v.begin() + (v.size() - 1));//erases the last element in the vector
    id--;//decrements ids
    size--;
    trickleDown(0);
    return;
}

template<class T>
bool MinHeap<T>::isEmpty() const {
    if (v.empty()) {//if empty, return true
        return 1;
    } 
    else {
        return 0;//else return false
    }
}

template <class T>
void MinHeap<T>::updatePriority(int node, int priority) {
    
    int location = mapOfIDs[node];
    if (v[location].first.second < priority) {
        v[location].first.second = priority;//this function will compare the two priorites given and update the heap
        trickleDown(location);
    } 
    else {
        v[location].first.second = priority;
        bubbleUp(location);
    }
}

template<class T>
void MinHeap<T>::trickleDown(int pos) {
    long unsigned int child = firstChild(pos);
    if (child < v.size()) {
        long unsigned int checker = firstChild(pos) + 1;
            while (checker < firstChild(pos) + d) {//goes through each child node and stores 
                if (checker < v.size()) {
                    if (v[checker].first.second < v[child].first.second) {
                        child = checker;
                    } 
                    else if (v[checker].first.second == v[child].first.second) {//tiebreaker
                        if (v[checker].first.first > v[child].first.first) {
                            child = checker;
                        } 
                    }
                }    
                checker++;
            }        

        if (v[pos].first.second > v[child].first.second) {//final comparison
            swapInVector(child, pos);
            trickleDown(child);
        }
        else if (v[pos].first.second == v[child].first.second) {//tiebreaker
            if (v[pos].first.first > v[child].first.first) {
                swapInVector(child, pos);
                trickleDown(child);
            }
        }
    }
}

template<class T>
void MinHeap<T>::bubbleUp(int pos) {
    if (pos > 0 && v[pos].first.second < v[parent(pos)].first.second) {//compares priorities of each node
        swapInVector(pos, parent(pos));
        bubbleUp(parent(pos));
    } 
    else if (pos > 0 && v[pos].first.second == v[parent(pos)].first.second) {//tiebreaks
        if (v[pos].first.first < v[parent(pos)].first.first) {
            swapInVector(pos, parent(pos));
            bubbleUp(parent(pos));
        }
    }
}

template<class T>
int MinHeap<T>::parent(int i) { //returns parent
    return ((i - 1) / d); 
}

template<class T>
int MinHeap<T>::firstChild(int i) { //returns first child
    return ((d * i) + 1); 
}

template <class T>
void MinHeap<T>::swapInVector(int r, int s) {
    std::pair<std::pair<T, int>, int> temp = v[r];//temporary item to swap with item in the vector
    v[r].first = v[s].first;
    v[s].first = temp.first;
    int temp2 = mapOfIDs[v[r].second];//swaps the IDs as well
    mapOfIDs[v[r].second] = mapOfIDs[v[s].second];
    mapOfIDs[v[s].second] = temp2;
}
