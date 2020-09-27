

#ifndef ARRAY_H_
#define ARRAY_H_

#include <exception>
#include <cassert>
#include <iostream>

template <class T>
class Array
{
public:
	Array(int size=DEF_SIZE);
	~Array();
	Array(const Array<T> & ap);
	Array<T>& operator=(const Array<T>& right);
	
	T& operator[](int index);
	const T& operator[](int index) const;
	int length() const;
	
	void changeSize(int newSize);
	void initialise(T def=T());
	void print(std::ostream & os) const;

private:
	static const int DEF_SIZE=10;
	T *elements;
	int capacity;

	inline void deepCopy(const Array<T> & original);
};


// ========================= IMPLEMENTATION Array.cpp ===================================

// PreCondition: size > 0
// PostCondition: creates a dynamic array of specified size
template <class T>
Array<T>::Array(int size) 
{
	assert(size > 0);

	capacity = size;
	elements = new T[capacity];
}

// PreCondition: None
// PostCondition: returns dynamically allocated memory used for elements to the heap and elements is set to null
template <class T>
Array<T>::~Array()
{
	delete [] elements;
	elements = NULL;
	capacity = 0;
}

// PreCondition: ap is a valid Array
// PostCondition: Initalises new Array with deep copy of Array referenced by parameter ap 
template <class T>
Array<T>::Array(const Array<T> & ap)
{
	deepCopy(ap);
}


// PreCondition: None
// PostCondition: array referenced by right is copied into this
template <class T>
Array<T> & Array<T>::operator=(const Array<T> & right)
{
	if (this != &right) {
		delete [] elements;
		deepCopy(right);
	}
	return *this;
}

// PreCondition: None
// PostCondition: each position in array is initialised with def value
template <class T>
void Array<T>::initialise(T def) {
	for(int i=0; i<capacity; i++)
		elements[i] = def;
}


// PreCondition: memory allocated to elements has been released
// PostCondition: copy of original used to initialise this arrasy
template <class T>
void Array<T>::deepCopy(const Array<T> & original)
{
	capacity = original.capacity;

	elements = new T[capacity];
	for (int i=0; i<capacity; i++) {
		elements[i] = original.elements[i];
	}
}

template <class T>
T& Array<T>::operator[](int index)
{
	assert(index >=0 && index < capacity);
	return elements[index];
}

template <class T>
const T& Array<T>::operator[](int index) const
{
	assert(index >=0 && index < capacity);
	return elements[index];
}

// PreCondition: newSize is greater than 0
// PostCondition: array is resized
template <class T>
void Array<T>::changeSize(int newSize) 
{
	assert(newSize > 0);

	T *newArray = new T[newSize];
	int limit = (newSize > capacity) ? capacity : newSize;

	// copy existing elements to new array
	for(int i=0; i<limit; i++) {
		newArray[i] = elements[i];
	}

	delete [] elements;
	elements = newArray;
	capacity = newSize;
	
}

// PreCondition: None
// PostCondition: Returns length of Array
template <class T>
inline int Array<T>::length() const
{
	return capacity;
} 


// PostCondition: prints a copy of array to ostream
template <class T>
void Array<T>::print(std::ostream & os) const {
	os << "[ ";
	for(int i=0; i<length(); i++) {
		os << elements[i] << " ";
	}
	os << "]";
}

// PreCondition: None
// PostCondition: overload << operator to output array on ostream
template <class T>
std::ostream& operator <<(std::ostream& output, const Array<T>& p) {
    p.print(output);
    return output;  // for multiple << operators.
}

#endif
