
#include "Array.h"

#include <fstream>
#include <string>
#include <cstdlib>
#include <time.h>       /* time */

using namespace std;

//PostCondition: Array is filled with random numbers
void fillRandom(Array<int>& data, int range = 100) {
	for (int i = 0; i < data.length(); i++)
		data[i] = rand() % range;
}

//Note: Array is passed by constant reference 
//PostCondition: content of array is printed to ostream (cout)
void printArray(const Array<int>& data) {
	cout << "[ ";
	for (int i = 0; i < data.length(); i++)
		cout << data[i] << " ";
	cout << "]\n";
}

int sequentialSearch(const Array<int>& data, int key)
{
	int comps = 0;
	for (int i = 0; i < data.length(); i++) {
		comps++;
		if (data[i] == key) {
			cout << "Sequential	search took	" << comps << "	comparisons\n";
			return i;
		}
	}
	cout << "Sequential search took " << comps << " comparisons\n";
	return -1;
}

int  countOccurence(const Array<int>& data, int e)
{
	int count = 0, i;
	for (i = 0; i < data.length(); i++)
	{
		if (data[i] == e) count++;
	}
	cout << "Count took " << i << " comparisons\n";
	return count;
}

void fillOrdered(Array<int> & data, int limit) {
	int last = 1;
	for (int i = 0; i < data.length(); i++) { //fill int array
		do {
			cout << "Enter number " << (i + 1) << " of " << data.length()
				<< " between " << last << ".." << limit << ": ";
			cin >> data[i];
		} while (data[i] < last || data[i] > limit);
		last = data[i];
	}
}

//PreCondition: elements in array must be sorted
//PostCondition: returns position of element in Array or -1 if not found
int binarySearch(const Array<int>& data, int key) {
	int left = 0, right = data.length() - 1;
	int pass = 0;
	while (left <= right) {
		int pivot = (left + right) / 2;
		pass++;
		cout << "Pass " << pass << ": left " << left << " Pivot "
			<< pivot << " Right " << right << endl;
		if (data[pivot] == key) {
			return pivot;					//found
		}
		else {
			if (data[pivot] < key)
				left = pivot + 1;			// search right
			else
				right = pivot - 1;			//search left
		}
	}
	return -1;
}

//PreCondition: Array is filled ordered numbers
int countOccurenceOrdered(const Array<int>& data, int e)
{
	int i, count = 0;
	//find first occurance
	for (i = 0; i < data.length() && data[i] != e; i++);
	//count contiguous occurances
	for (; i < data.length() && data[i] == e; i++, count++);
	cout << "Count Ordered took " << i << " passes" << endl;
	return count;
}

//PostCondition:	return true if d is found in array positions s..e
//					inclusive, otherwise false
bool alreadyExists(const Array<int>& data, int s, int e, int d) {
	for (int i = s; i <= e; i++) {
		if (data[i] == d) return true;
	}
	return false;
}

//PostCondition:	Fill	array	with	one	instance	of	each	number	in	range	
//	1..data.length()
void fillPermutations(Array<int>& data)
{
	int r = rand() % data.length() + 1;
	data[0] = r;
	for (int i = 1; i < data.length(); i++)
	{
		do {
			r = rand() % data.length() + 1;
		} while (alreadyExists(data, 0, i, r));
		data[i] = r;
	}
}

//	PreCondition:	named file exists and contains integers
//	PostCondition:	array is loaded	with integers read from file	
//					and	array is resized if	necessary
void loadInts(Array<int>& data, string fname) {
	ifstream in_stream;
	in_stream.open(fname); // open file

	if (in_stream.fail())  // if file cant be opened then return
		return;

	int x, i = 0;
	// while array has room and a number can be read from the file
	while (i < data.length() && (in_stream >> x)) {
		data[i++] = x;			//put element into array
	}
	data.changeSize(i);			//resize array to i, to remove any unused elements
	in_stream.close();			// close file
}




int main() {

	/* initialize random seed: */
	srand (time(NULL));

	// code goes here
	int num, size;
	cout << "Enter size of sequence to generate: ";
	cin >> size;

	Array<int> data(size);
	char opt;
	cout << endl << "1:Fill 2:Search 3:Count 0:Quit : ";
	cin >> opt;
	while (opt != '0')
	{
		if (opt == '1') {		//fill
			cout << "Enter limit: ";
			int limit;
			cin >> limit;
			fillRandom(data, limit);
		}
		else if (opt == '2') {	//search
			cout << "Enter key: ";
			int key;
			cin >> key;
			cout << key << " found at " << sequentialSearch(data, key) << endl;
	  }
		else if (opt == '3') {	//count
			cout << "Enter key: ";
			int key;
			cin >> key;
			int occur = countOccurenceOrdered(data, key);
			cout << occur << "	occurrences	of	" << key << "	found	" << endl;
		}

		// print array and re-display menu
		cout << endl;
		printArray(data);
		cout << "1:Fill	2:Search	3:Count	0:Quit	:	";
		cin >> opt;
	}


	// ---------------------------------------------------
	cout << endl << "Press enter to quit";
	cin.get();
	return 0;
}
