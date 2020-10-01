#include <iostream>

template <typename T> class vec
{
private:
	typedef unsigned int uint;
	uint size, maxsize;
	T* array;
	void allocNew() // allocates more space
	{
		maxsize = size * 2;
		T* tmp = new T[maxsize];

		for (uint i = 0; i < size; i++)
			tmp[i] = array[i];

		delete[] array;
		array = tmp;
	}
	void swap(T& val1, T& val2)
	{
		T temp = val1;
		val1 = val2;
		val2 = temp;
	}
	uint smallestVal(uint startIndex, uint endIndex)		// return the index of the smallest value
	{
		uint minIndex = startIndex;
		for (uint x = startIndex + 1; x < endIndex; x++)
		{
			if (array[x] < array[minIndex])
				minIndex = x;
		}
		return minIndex;
	}
public:
	vec(uint i = 20)
	{
		array = new T[i];
		maxsize = i;
		size = 0;
	}
	vec(const vec& v) // copy constructor works I think?!
	{
		maxsize = v.maxsize;
		size = v.size;
		array = new T[maxsize];
		for (int i = 0; i < v.size; i++)
			array[i] = v.array[i];
	}
	~vec()
	{
		delete[] array;
	}
	void printVector()
	{
		for (int i = 0; i < size; i++)
			std::cout << array[i] << " ";
		std::cout << "\n";
	}
	void append(T i)
	{
		if (size + 1 > maxsize)	// checks if more space needs to be allocated
			allocNew();

		array[size] = i;
		size++;
	}
	template <class U>
	void operator ()(std::initializer_list<U> list)
	{
		for (auto elem : list)
		{
			append(elem);
		}
	}
	T& operator[](uint index)
	{
		if (index > size or index < 0) { index = 0; }
		return array[index];
	}
	vec& operator = (const vec& v)		// assignment operator
	{
		if (this != &v)
		{
			maxsize = v.maxsize;
			size = v.size;
			delete[] array;
			array = new T[maxsize];
			for (int x = 0; x < v.size; x++)
				array[x] = v.array[x];
		}
		return *this;
	}
	uint Size()
	{
		return size;
	}
	T at(uint index)	// an alternative to operator overloading
	{
		if (index > size or index < 0) { index = 0; }
		return array[index];
	}
	void replace(uint toReplace, T whatToReplaceWith)
	{
		if (toReplace > size or toReplace < 0) { toReplace = 0; }
		array[toReplace] = whatToReplaceWith;
	}
	void remove(uint toRemove)
	{
		if (toRemove > size or toRemove < 0) { toRemove = 0; }
		uint x = 0;
		for (uint i = 0; i < size; i++)
		{
			if (i != toRemove)
				array[x] = array[i]; // shifts the elements backwards 
			else
				x--;
			x++;
		}
		size--;
	}
	void insert(T toInsert, uint index)	// need to optimise
	{
		if (index > size or index < 0) { index = 0; }
		if (size + 1 > maxsize) { allocNew(); }

		uint x = 0;
		T* tmp = new T[maxsize];
		for (uint i = 0; i < size; i++)
		{
			if (i == index) { tmp[index] = toInsert; x++; }
			tmp[x] = array[i];
			x++;
		}
		delete[] array;
		array = tmp;
		size++;
	}
	void pop(uint amount = 1)
	{
		if (amount > size or amount < 0) { amount = 1; }	// performs checks
		size = size - amount;
	}
	void sort()	// need to optimise
	{
		//if (std::is_same<T, int>::value or std::is_same<T, char>::value)	// for char and int
		try
		{
			uint minIndex;
			for (uint i = 0; i < size; i++)
			{
				minIndex = smallestVal(i, size);
				if (minIndex != i)
					swap(array[minIndex], array[i]);
			}
		}
		catch (T param) {
			throw"SORT WILL NOT WORK WITH TYPE SPECIFIED";
			//std::cout << "SORT WILL NOT WORK WITH TYPE SPECIFIED \n";
		}
	}
	/*Sorting Algorithm*/
	void sort(uint start, uint end)	// overloaded sort
	{
		if (end > size - 1 or end < 0) { end = size - 1; }
		if (start > size or start < 0 or start > end) { start = 0; }
		end++;
		try
		{
			uint minIndex;
			for (uint i = 0; i < size; i++)
			{
				minIndex = smallestVal(i, size);
				if (minIndex != i)
					swap(array[minIndex], array[i]);
			}
		}
		catch (T param) {
			throw"SORT WILL NOT WORK WITH TYPE SPECIFIED";
		}

	}
	void reverse()
	{
		uint end = size - 1;
		for (uint i = 0; i < end; i++)
		{
			swap(array[i], array[end]);
			end--;
		}
	}
	void reverse(uint start, uint end)	//overloaded
	{
		if (end > size - 1 or end < 0) { end = size - 1; }
		if (start > size or start < 0 or start > end) { start = 0; }
		for (start; start < end; start++)
		{
			swap(array[start], array[end]);
			end--;
		}
	}
	void erase()
	{
		size = 0;
	}
	uint count(T t)
	{
		uint amount = 0;
		for (uint x = 0; x < size; x++)
		{
			if (array[x] == t) { amount++; }
		}
		return amount;
	}
};