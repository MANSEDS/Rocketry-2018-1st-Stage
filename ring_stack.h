/*
    ring_stack.h
    MANSEDS Self-Landing Rocket code
    Contributors: Alex Koch

    Last-in-first-out ring stack

    Objects can be continously pushed onto the stack with the last one always
    being on 'top'. Once more ojects than the size of the array can store are pushed 
    onto the stack then the newest elements simply overwrite the oldest.

    In order to extract all the elements in order one must loop over all the elements in order
    a number of times equal to the 'size_' of the stack.
*/

template<typename T> class ring_stack
{
private:
    T * container_;
    uint32_t top_, shift_ increment_;
public:
    ring_stack(unsigned bits) : top_{ 0 }, shift_{ uint32_t(32 - bits) }, 
                                increment_{ uint32_t( pow(2, 32) / pow(2, bits) ) }, 
                                container_{ new T[ uint32_t( pow(2, bits) ) ] } 
                                { 
                                    container_[0] = nullptr; // set the first element to nullptr so that it can be checked if the array has been filled
                                }
    bool empty() { return container_[0] == nullptr && top_ == 0; }
    bool full() { return container_[0] != nullptr; } // Container is filled only once the 0th element has been overwritten via a push() call
    uint16_t size() 
    { 
        if(container_[0] == nullptr)
        {
            return top_ >> shift_; // The shifted value of top_ corresponds to the number of elements in the stack
        }
        else{ return max_size; } // The stack has been filled and so the number of elements is always the max size as any new ones will overwrite the oldest element.
    }
    uint32_t max_size() { return pow(32 - shift_, 2); }
    T & top() { return container_[top_ >> increment_]; }
    void push(const T element) 
    {   
        top_ += increment_; // Must shift the top first so that it corresponds to the slot in which to place the new element
        container_[top_ >> shift_] = element;
    }
    // emplace?
    void pop() 
    {
        top_ -= increment_; // Deincrement as this is a LIFO queue
    }
    // swap?
}