#include "header_files/global.hpp"
#include "header_files/HashMap.hpp"

using namespace std;

// Point constructor
Point::Point(int a, int b)
{
	x = a;
	y = b;
}

Point::Point()
{
	x = 0;
	y = 0;
}

HashMap::HashMap(void)
{
	this->capacity = 503;
	this->size = 0;
	this->table = new Point*[this->capacity](); // Initialize array with NULLs
}

// Destructor to free allocated memory
HashMap::~HashMap()
{
	for (int i = 0; i < this->capacity; i++)
	{
		if (this->table[i] != NULL)
			delete this->table[i]; // Free each dynamically allocated Point
	}
	delete[] this->table; // Free the table array itself
}

int HashMap::hash(Point *data)
{
	return ((data->x + 79) * (data->y + 37) * 19) + 102793;
}

int HashMap::getSize(void)
{
	return this->size;
}

int HashMap::getCapacity(void)
{
	return this->capacity;
}

// Checks if a pair of numbers is in the HashMap or not
int HashMap::contains(int a, int b)
{
	Point *temp = new Point(a, b);
	int hash = this->hash(temp);
	delete temp; // Free temporary Point after hashing

	for (int i = 0; this->table[hash % this->capacity] != NULL; i++)
	{
		temp = this->table[hash % this->capacity];
		if (temp->x == a && temp->y == b)
			return 1;
		else
			hash += 2 * i + 1;
	}

	return 0;
}

// Inserts a pair of numbers into the HashMap
void HashMap::insert(int a, int b)
{
	// Disallow duplicates
	if (this->contains(a, b))
		return;

	Point *newPoint = new Point(a, b);
	int hash = this->hash(newPoint);

	if (this->size > this->capacity / 2)
		this->expand();

	for (int i = 0; this->table[hash % this->capacity] != NULL; i++)
		hash += 2 * i + 1;

	this->table[hash % this->capacity] = newPoint;
	this->size++;

	return;
}

// Expands the table
void HashMap::expand(void)
{
	this->capacity = this->primes[++this->currentPrime];
	Point **newTable = new Point*[this->capacity](); // Initialize new array with NULLs
	Point *temp;

	for (int i = 0; i < this->primes[this->currentPrime - 1]; i++)
	{
		temp = this->table[i];
		if (temp == NULL)
			continue; 

		int hash = this->hash(temp);
		newTable[hash % this->capacity] = temp;
	}

	delete[] this->table; // Free the old table array
	this->table = newTable;
	return;
}

// I wrote this up to help debug the other functions listed above
void HashMap::printTable(void)
{
	Point *temp;

	for (int i = 0; i < this->size; i++)
	{
		temp = this->table[i];
		if (temp == NULL)
			cout << "NULL, ";
		else
			cout << "(" << temp->x << ", " << temp->y << "), ";
	}

	cout << endl << "size is : " << this->size << " and capacity: " << this->capacity << endl;
	return;
}
