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

// A horribly unsafe yet very fast implementation of a stack for use in the rocket code. Please understand it's limitations before using this class
template<typename T> class f_ring_stack
{
private:
	T * container_;
	uint32_t top_, shift_, increment_;
public:
	f_ring_stack() : top_{ 0 }, container_ { nullptr }, top_{ 0 }, shift_{ 0 }, increment_{ 0 } {}
	f_ring_stack(unsigned bits) : shift_{ uint32_t(32 - bits) }, increment_{ uint32_t(pow(2, 32) / pow(2, bits)) }, container_{ new T[uint32_t(pow(2, bits))] } {}
	~f_ring_stack() 
	{
		delete[] container_;
	}
	uint32_t max_size() { return pow(32 - shift_, 2); }
	T & top() { return container_[top_ >> shift_]; }
	void push(const T element)
	{
		top_ += increment_; // Must shift the top first so that it corresponds to the slot in which to place the new element
		container_[top_ >> shift_] = element;
	}
	// emplace?
	void pop()
	{
		container_[top_ >> shift_].~T(); // Call the objects destructor
		top_ -= increment_; // Deincrement as this is a LIFO queue
	}
	// Define an overload for the accessor operator []
};
