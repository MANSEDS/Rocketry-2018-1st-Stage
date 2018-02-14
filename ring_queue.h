/*
    ring_queue.h
    MANSEDS Self-Landing Rocket code
    Contributors: Alex Koch
    First-in-first-out ring queue
*/

template<typename T> class ring_queue
{
private:
    T * container_;
    uint32_t head_, tail_, length_, increment_, shift_; // Check if length can be handled by considering the difference between the head and tail
public:
    ring_queue(unsigned const bits): head_{ 0 }, tail_{ 0 }, length_{ 0 }, shift_{ uint32_t(32 - bits) }, 
                                     increment_{ uint32_t( pow(2, 32) / pow(2, bits) ) }, 
                                     container_{ new T[ uint32_t( pow(2, bits) ) ] } 
                                     {}
    // Copy and move destructors?
    bool empty() { return length_ == 0; }
    bool full() { return head_ == tail_ + 1; }
    uint32_t size() { return length_; }
    uint32_t max_size() { return pow(32 - shift_, 2); }
    T & front() { return container_[head_ >> increment_]; }
    void push(const T element) 
    {
        container_[tail_ >> shift_] = element;
        tail_ += increment_;
        length_++;
    }
    // emplace?
    void pop() 
    {
        // ~container_[head_ >> shift_]; // Call the destructor for this element
        head_ += increment_;
        length_--;
    }
    // swap??
    T * c_buf<T>::get_container() { return container_; }
    T & operator [] (size_t position)
    {
        position << shift_;
        position >> shift_;
        return container_[position];
    }
    bool operator == (const & c_buf<T> rhs_c_buf)
    {
        return (head_ == rhs_c_buf.head_) && (container_ == rhs_c_buf.container_); // Check if the containers needs to be dereferenced or not
    }
}