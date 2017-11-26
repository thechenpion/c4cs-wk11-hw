/**
 * In-class starter code for EECS 281 Lecture 3.
 * Originally written by James Juett for Spring 2017.
 * Updated by Dr. P for the current semester.
 * Note: This code contains an intentional bug we'll discuss in lecture!
 */

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>

using namespace std;

/**
 * A simple Timer built on the C++11 chrono library.
 * Credit: Amir Kamil
 */
class Timer {
    std::chrono::time_point<std::chrono::system_clock> cur;
    std::chrono::duration<double> elap;
public:
    Timer() : cur(), elap(std::chrono::duration<double>::zero()) {}

    void start() {
        cur = std::chrono::system_clock::now();
    } // start()

    void stop() {
        elap += std::chrono::system_clock::now() - cur;
    } // stop()

    void reset() {
        elap = std::chrono::duration<double>::zero();
    } // reset()

    double seconds() {
        return elap.count();
    } // seconds()
}; // class Timer


/**
 * Performs a straightforward linear search through the input vector
 * for the given value.
 * Should theoretically have O(n) complexity.
 *
 * Note: This code contains an intentional bug we'll discuss in lecture!
 */
int linearSearch(vector<int> vec, int val) {
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] == val) {
            return i;
        } // if
    } // for
    return -1;
} // linearSearch()


/**
 * Performs a binary search through the input vector, looking for the
 * given value. Assumes the vector is in sorted order.
 * Should theoretically have O(log n) complexity.
 *
 * Note: This code contains an intentional bug we'll discuss in lecture!
 */
int binarySearch(vector<int> vec, int val) { //OH SNAP THE VECTOR WAS PASSED BY VALUE!!!!
    int low = 0;
    int high = static_cast<int>(vec.size()) - 1; // inclusive upper bound

    while (high >= low) {
        int mid = low + (high - low) / 2;
        int midValue = vec[mid];
        if (val == midValue) {
            return mid;
        } // if
        else if (val < midValue) {
            high = mid - 1;
        } // else if
        else {
            low = mid + 1;
        } // else
    } // while
    return -1;
} // binarySearch()


void testSearch(bool doBinarySearch, const vector<int> &vec, int numSearches) {
    int numFound = 0;
    // Initialize the random number generator
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(0, 2 * vec.size());

    for (int i = 0; i < numSearches; ++i ) {
        // Pick a random element of the vector to look for, store in targetValue.
        // Don't worry about how this code works.
        int targetValue = uni(rng);

        if (doBinarySearch) {
            if (binarySearch(vec, targetValue) != -1)
                ++numFound;
        } // if
        else {
            if (linearSearch(vec, targetValue) != -1)
                ++numFound;
        } // else
    } // for

    cout << "Found " << numFound << " / " << numSearches << " items." << endl;
} // testSearch()


int main(int argc, char *argv[]) {
    Timer t;
    if (argc != 3) {
        cerr << "You must specify [b|l] for the type of search, and the number of items on the command line." << endl;
        exit(1);
    } // if

    bool doBinarySearch = (argv[1][0] == 'b');
    int numItems = atoi(argv[2]);

    // Fill the vector and track time taken
    t.start();
    vector<int> vec;
    vec.reserve(numItems);
    for (int i = 0; i < numItems; ++i) {
        vec.push_back(2 * i);
    } // for
    t.stop();
    cout << "Fill vector: " << t.seconds() << "s" << endl;

    // Test the search and track time taken
    t.reset();
    t.start();
    testSearch(doBinarySearch, vec, 100);
    t.stop();

    cout << "Searching: " << t.seconds() << "s" << endl;
	
	return 0;
} // main()
