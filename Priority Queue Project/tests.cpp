// Program: Priority Queue
// System: Vs Code on windows 10 dell
// Author: Taria Reese

/// @file tests.cpp
/// @date March 17, 2023

/// Provided testing file to implement framework based tests in. The examples
/// below demonstrates a basic empty test in each framework with a single
/// assertion. The version uses the supplied catch.hpp file in starter code.

// Catch 1.0 Framework Testing
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "priorityqueue.h"

using namespace std;

TEST_CASE("Simple enqueue size test") {
    priorityqueue<int> pq;
    REQUIRE(pq.Size() == 0);
    pq.enqueue(1, 1);
    REQUIRE(pq.Size() == 1);
}

TEST_CASE("More elements enqueue size test") {
    priorityqueue<int> pq;
    REQUIRE(pq.Size() == 0);
    pq.enqueue(1, 1);
    REQUIRE(pq.Size() == 1);
    pq.enqueue(2, 3);
    REQUIRE(pq.Size() == 2);
    pq.enqueue(3, 6);
    REQUIRE(pq.Size() == 3);
    pq.enqueue(4, 2);
    REQUIRE(pq.Size() == 4);
}

TEST_CASE("enqueue dupe size test") {
    priorityqueue<int> pq;
    REQUIRE(pq.Size() == 0);
    pq.enqueue(1, 1);
    REQUIRE(pq.Size() == 1);
    pq.enqueue(2, 3);
    REQUIRE(pq.Size() == 2);
    pq.enqueue(3, 6);
    REQUIRE(pq.Size() == 3);
    pq.enqueue(4, 2);
    REQUIRE(pq.Size() == 4);
    pq.enqueue(5, 2);
    REQUIRE(pq.Size() == 5);
}

TEST_CASE("enqueue dequeue simple test") {
    priorityqueue<int> pq;
    REQUIRE(pq.Size() == 0);
    pq.enqueue(1, 1);
    REQUIRE(pq.Size() == 1);
    REQUIRE(pq.dequeue() == 1);
    REQUIRE(pq.Size() == 0);
}

TEST_CASE("enqueue dequeue more elements test") {
    map<int, vector<int>> map;
    int n = 9;
    int vals[] = {15, 16, 17, 6, 7, 8, 9, 2, 1};
    int prs[] = {1, 2, 3, 2, 2, 2, 2, 3, 3};

    priorityqueue<int> pq;
    REQUIRE(pq.Size() == 0);
    for (int i = 0; i < n; i++) {
        pq.enqueue(vals[i], prs[i]);
        map[prs[i]].push_back(vals[i]);
        REQUIRE(pq.Size() == i + 1);
    }
    int sizeCounter = 9;
    for (auto elem : map) {
        vector<int> values = elem.second;
        for (size_t i = 0; i < values.size(); i++) {
            REQUIRE(pq.dequeue() == values[i]);
            sizeCounter--;
            REQUIRE(pq.Size() == sizeCounter);
        }
    }
}

TEST_CASE("root has dupes enqueue dequeue") {
    map<int, vector<int>> map;
    int n = 9;
    int vals[] = {15, 16, 17, 6, 7, 8, 8, 8, 1};
    int prs[] = {3, 3, 3, 2, 1, 5, 1, 1, 1};

    priorityqueue<int> pq;
    REQUIRE(pq.Size() == 0);
    for (int i = 0; i < n; i++) {
        pq.enqueue(vals[i], prs[i]);
        map[prs[i]].push_back(vals[i]);
        REQUIRE(pq.Size() == i + 1);
    }
    int sizeCounter = 9;
    for (auto elem : map) {
        vector<int> values = elem.second;
        for (size_t i = 0; i < values.size(); i++) {
            REQUIRE(pq.dequeue() == values[i]);
            sizeCounter--;
            REQUIRE(pq.Size() == sizeCounter);
        }
    }
}

TEST_CASE("enqueue dequeue dupe priorities") {
    map<int, vector<int>> map;
    int n = 9;
    int vals[] = {15, 16, 17, 6, 7, 8, 9, 2, 1};
    int prs[] = {5, 5, 5, 2, 2, 2, 2, 3, 3};
    priorityqueue<int> pq;
    for (int i = 0; i < n; i++) {
        pq.enqueue(vals[i], prs[i]);
        map[prs[i]].push_back(vals[i]);
    }
    int sizeCounter = 9;
    for (auto elem : map) {
        vector<int> values = elem.second;
        for (size_t i = 0; i < values.size(); i++) {
            REQUIRE(pq.dequeue() == values[i]);
            sizeCounter--;
            REQUIRE(pq.Size() == sizeCounter);
        }
    }
}

TEST_CASE("toString test") {
    map<int, vector<int>> map;
    int n = 9;
    int vals[] = {15, 16, 17, 6, 7, 8, 9, 2, 1};
    int prs[] = {1, 2, 3, 7, 10, 11, 6, 4, 3};
    priorityqueue<int> pq;
    for (int i = 0; i < n; i++) {
        pq.enqueue(vals[i], prs[i]);
        map[prs[i]].push_back(vals[i]);
    }
    REQUIRE(pq.Size() == 9);
    stringstream ss;
    for (auto e : map) {
        int priority = e.first;
        vector<int> values = e.second;
        for (size_t j = 0; j < values.size(); j++) {
            ss << priority << " value: " << values[j] << endl;
        }
    }
    REQUIRE(pq.toString() == ss.str());
}

TEST_CASE("toString test with dupe priorities") {
    map<int, vector<int>> map;
    int n = 9;
    int vals[] = {15, 16, 17, 6, 7, 8, 9, 2, 1};
    int prs[] = {5, 5, 5, 1, 1, 1, 9 ,9, 9, 9};
    priorityqueue<int> pq;
    for (int i = 0; i < n; i++) {
        pq.enqueue(vals[i], prs[i]);
        map[prs[i]].push_back(vals[i]);
    }
    REQUIRE(pq.Size() == 9);
    stringstream ss;
    for (auto e : map) {
        int priority = e.first;
        vector<int> values = e.second;
        for (size_t j = 0; j < values.size(); j++) {
            ss << priority << " value: " << values[j] << endl;
        }
    }
    REQUIRE(pq.toString() == ss.str());
}

TEST_CASE("toString test with dupe at root") {
    map<int, vector<int>> map;
    int n = 9;
    int vals[] = {15, 16, 17, 6, 7, 8, 9, 2, 1};
    int prs[] = {1, 1, 1, 2, 2, 2, 3, 3, 3};
    priorityqueue<int> pq;
    for (int i = 0; i < n; i++) {
        pq.enqueue(vals[i], prs[i]);
        map[prs[i]].push_back(vals[i]);
    }
    REQUIRE(pq.Size() == 9);
    stringstream ss;
    for (auto e : map) {
        int priority = e.first;
        vector<int> values = e.second;
        for (size_t j = 0; j < values.size(); j++) {
            ss << priority << " value: " << values[j] << endl;
        }
    }
    REQUIRE(pq.toString() == ss.str());
}

TEST_CASE("simple clear test")
{
    priorityqueue<int> pq;
    pq.enqueue(1, 1);
    pq.enqueue(2, 2);
    pq.enqueue(3, 3);
    pq.enqueue(4, 4);
    pq.enqueue(5, 5);
    pq.enqueue(6, 6);
    pq.enqueue(7, 7);
    pq.enqueue(8, 8);
    pq.enqueue(9, 9);
    pq.enqueue(10, 10);
    REQUIRE(pq.Size() == 10);
    pq.clear();
    REQUIRE(pq.Size() == 0);
}

TEST_CASE("clear test with dupe priorities")
{
    priorityqueue<int> pq;
    pq.enqueue(1, 5);
    pq.enqueue(9, 8);
    pq.enqueue(10, 8);
    pq.enqueue(11, 8);
    pq.enqueue(12, 2);
    pq.enqueue(13, 2);
    pq.enqueue(14, 2);
    REQUIRE(pq.Size() == 7);
    pq.clear();
    REQUIRE(pq.Size() == 0);
}

TEST_CASE("clear test with dupe at root")
{
    priorityqueue<int> pq;
    pq.enqueue(1, 5);
    pq.enqueue(9, 5);
    pq.enqueue(10, 5);
    pq.enqueue(11, 5);
    pq.enqueue(12, 2);
    pq.enqueue(13, 2);
    pq.enqueue(14, 2);
    REQUIRE(pq.Size() == 7);
    pq.clear();
    REQUIRE(pq.Size() == 0);
}

TEST_CASE("Peek Test") {
    priorityqueue<int> pq;
    pq.enqueue(1, 1);
    pq.enqueue(2, 2);
    pq.enqueue(3, 3);
    pq.enqueue(4, 4);
    pq.enqueue(5, 5);
    pq.enqueue(6, 6);
    pq.enqueue(7, 7);
    pq.enqueue(8, 8);
    pq.enqueue(9, 9);
    pq.enqueue(10, 10);
    REQUIRE(pq.Size() == 10);
    REQUIRE(pq.peek() == 1);
    REQUIRE(pq.Size() == 10);

    pq.dequeue();
    REQUIRE(pq.peek() == 2);
    REQUIRE(pq.Size() == 9);

    pq.dequeue();
    REQUIRE(pq.peek() == 3);
    REQUIRE(pq.Size() == 8);
}

TEST_CASE("peek dupe at root test") {
    priorityqueue<int> pq;
    pq.enqueue(1, 5);
    pq.enqueue(9, 5);
    pq.enqueue(12, 2);
    pq.enqueue(13, 2);
    pq.enqueue(14, 2);
    REQUIRE(pq.Size() == 5);
    REQUIRE(pq.peek() == 12);
    REQUIRE(pq.Size() == 5);

    pq.dequeue();
    REQUIRE(pq.peek() == 13);
    REQUIRE(pq.Size() == 4);

    pq.dequeue();
    REQUIRE(pq.peek() == 14);
    REQUIRE(pq.Size() == 3);

    pq.dequeue();

    REQUIRE(pq.peek() == 1);
    REQUIRE(pq.Size() == 2);

    pq.dequeue();

    REQUIRE(pq.peek() == 9);
    REQUIRE(pq.Size() == 1);

    pq.dequeue();
    REQUIRE(pq.Size() == 0);
}

TEST_CASE("peek with dupes")
{
    priorityqueue<int> pq;
    pq.enqueue(1, 5);
    pq.enqueue(9, 8);
    pq.enqueue(10, 8);
    pq.enqueue(11, 8);
    pq.enqueue(12, 2);
    pq.enqueue(13, 2);
    pq.enqueue(14, 2);
    REQUIRE(pq.Size() == 7);
    REQUIRE(pq.peek() == 12);
    REQUIRE(pq.Size() == 7);

    pq.dequeue();
    REQUIRE(pq.peek() == 13);
    REQUIRE(pq.Size() == 6);

    pq.dequeue();
    REQUIRE(pq.peek() == 14);
    REQUIRE(pq.Size() == 5);

    pq.dequeue();

    REQUIRE(pq.peek() == 1);
    REQUIRE(pq.Size() == 4);

    pq.dequeue();

    REQUIRE(pq.peek() == 9);
    REQUIRE(pq.Size() == 3);

    pq.dequeue();

    REQUIRE(pq.peek() == 10);
    REQUIRE(pq.Size() == 2);

    pq.dequeue();

    REQUIRE(pq.peek() == 11);
    REQUIRE(pq.Size() == 1);

    pq.dequeue();
    REQUIRE(pq.Size() == 0);
}

TEST_CASE("equal operator test") {
    int n = 9;
    int vals[] = {15, 16, 17, 6, 7, 8, 9, 2, 1};
    int prs[] = {5, 4, 3, 2, 7, 8, 9, 10, 11};
    priorityqueue<int> pq;
    for (int i = 0; i < n; i++) {
        pq.enqueue(vals[i], prs[i]);
    }
    REQUIRE(pq.Size() == 9);

    priorityqueue<int> pq2;
    for (int i = 0; i < 2; i++) {
        pq2.enqueue(vals[i], prs[i]);
    }

    REQUIRE(pq2.Size() == 2);
    pq2 = pq;
    REQUIRE(pq2.Size() == 9);
    REQUIRE(pq.Size() == 9);

    for (int i = 0; i < 9; i++) {
        REQUIRE(pq2.peek() == pq.peek());
        REQUIRE(pq2.dequeue() == pq.dequeue());
    }
}

TEST_CASE("equal operator test with dupes") {
    int n = 9;
    int vals[] = {15, 16, 17, 6, 7, 8, 9, 2, 1};
    int prs[] = {5, 4, 4, 4, 7, 7, 7, 10, 1};
    priorityqueue<int> pq;
    for (int i = 0; i < n; i++) {
        pq.enqueue(vals[i], prs[i]);
    }
    REQUIRE(pq.Size() == 9);

    priorityqueue<int> pq2;
    for (int i = 0; i < 2; i++) {
        pq2.enqueue(vals[i], prs[i]);
    }

    REQUIRE(pq2.Size() == 2);
    pq2 = pq;
    REQUIRE(pq2.Size() == 9);
    REQUIRE(pq.Size() == 9);

    for (int i = 0; i < 9; i++) {
        REQUIRE(pq2.peek() == pq.peek());
        REQUIRE(pq2.dequeue() == pq.dequeue());
    }
}

TEST_CASE("equal operator test with dupes at root") {
    int n = 9;
    int vals[] = {15, 16, 17, 6, 7, 8, 9, 2, 1};
    int prs[] = {5, 5, 5, 5, 7, 7, 7, 10, 1};
    priorityqueue<int> pq;
    for (int i = 0; i < n; i++) {
        pq.enqueue(vals[i], prs[i]);
    }
    REQUIRE(pq.Size() == 9);

    priorityqueue<int> pq2;
    for (int i = 0; i < 2; i++) {
        pq2.enqueue(vals[i], prs[i]);
    }

    REQUIRE(pq2.Size() == 2);
    pq2 = pq;
    REQUIRE(pq2.Size() == 9);
    REQUIRE(pq.Size() == 9);

    for (int i = 0; i < 9; i++) {
        REQUIRE(pq2.peek() == pq.peek());
        REQUIRE(pq2.dequeue() == pq.dequeue());
    }
}

TEST_CASE("equality operator test") {
        int n = 9;
    int vals[] = {15, 16, 17, 6, 7, 8, 9, 2, 1};
    int prs[] = {5, 4, 3, 2, 7, 8, 9, 10, 11};
    priorityqueue<int> pq;
    priorityqueue<int> pq2;
    for (int i = 0; i < n; i++) {
        pq.enqueue(vals[i], prs[i]);
        pq2.enqueue(vals[i], prs[i]);
    }
    REQUIRE(pq.Size() == 9);
    REQUIRE(pq2.Size() == 9);

    for (int i = 0; i < 9; i++) {
        REQUIRE(pq == pq2);
        REQUIRE(pq2.peek() == pq.peek());
        REQUIRE(pq2.dequeue() == pq.dequeue());

    }
}

TEST_CASE("equality operator test with dupes") {
    int n = 9;
    int vals[] = {15, 16, 17, 6, 7, 8, 9, 2, 1};
    int prs[] = {5, 4, 4, 4, 7, 7, 7, 10, 1};
    priorityqueue<int> pq;
    priorityqueue<int> pq2;
    for (int i = 0; i < n; i++) {
        pq.enqueue(vals[i], prs[i]);
        pq2.enqueue(vals[i], prs[i]);
    }
    REQUIRE(pq.Size() == 9);
    REQUIRE(pq2.Size() == 9);

    for (int i = 0; i < 9; i++) {
        REQUIRE(pq == pq2);
        REQUIRE(pq2.peek() == pq.peek());
        REQUIRE(pq2.dequeue() == pq.dequeue());

    }
}

TEST_CASE("equality operator test with dupes at root") {
    int n = 9;
    int vals[] = {15, 16, 17, 6, 7, 8, 9, 2, 1};
    int prs[] = {5, 5, 5, 5, 7, 7, 7, 10, 1};
    priorityqueue<int> pq;
    priorityqueue<int> pq2;
    for (int i = 0; i < n; i++) {
        pq.enqueue(vals[i], prs[i]);
        pq2.enqueue(vals[i], prs[i]);
    }
    REQUIRE(pq.Size() == 9);
    REQUIRE(pq2.Size() == 9);

    for (int i = 0; i < 9; i++) {
        REQUIRE(pq == pq2);
        REQUIRE(pq2.peek() == pq.peek());
        REQUIRE(pq2.dequeue() == pq.dequeue());

    }
}

TEST_CASE("begin and next simple test") {
    map <int, vector<int>> map;
    int n = 1;
    int vals[] = {15};
    int prs[] = {5};
    priorityqueue<int> pq;

    for (int i = 0; i < n; i++) {
        pq.enqueue(vals[i], prs[i]);
        map[prs[i]].push_back(vals[i]);
    }

    REQUIRE(pq.Size() == n);
    int value;
    int priority;
    pq.begin();
    for(int i = 0; i < n - 1; i++) {
        REQUIRE(pq.next(value, priority) == true);
        REQUIRE(map[priority].front() == value);
        map[priority].erase(map[priority].begin());
    }
    REQUIRE(pq.next(value, priority) == false);
    REQUIRE(pq.Size() == n);
    pq.clear();
    REQUIRE(pq.Size() == 0);
}

TEST_CASE("begin and next test") {
    map <int, vector<int>> map;
    int n = 9;
    int vals[] = {15, 16, 17, 6, 7, 8, 9, 2, 1};
    int prs[] = {5, 4, 3, 2, 7, 8, 9, 10, 11};
    priorityqueue<int> pq;

    for (int i = 0; i < n; i++) {
        pq.enqueue(vals[i], prs[i]);
        map[prs[i]].push_back(vals[i]);
    }

    REQUIRE(pq.Size() == n);
    int value;
    int priority;
    pq.begin();
    for(int i = 0; i < n - 1; i++) {
        REQUIRE(pq.next(value, priority) == true);
        REQUIRE(map[priority].front() == value);
        map[priority].erase(map[priority].begin());
    }

    REQUIRE(pq.next(value, priority) == false);
    REQUIRE(pq.Size() == n);
    pq.clear();
    REQUIRE(pq.Size() == 0);
}

TEST_CASE("begin and next dupes") {
    map <int, vector<int>> map1;
    int n = 9;
    int vals[] = {15, 16, 17, 6, 7, 8, 9, 2, 1};
    int prs[] = {5, 4, 4, 4, 7, 7, 7, 10, 1};
    priorityqueue<int> pq;

    for (int i = 0; i < n; i++) {
        pq.enqueue(vals[i], prs[i]);
        map1[prs[i]].push_back(vals[i]);
    }

    REQUIRE(pq.Size() == n);
    int value;
    int priority;
    
    pq.begin();
    for(int i = 0; i < n - 1; i++) {
        REQUIRE(pq.next(value, priority) == true);
        REQUIRE(map1[priority].front() == value);
        map1[priority].erase(map1[priority].begin());
    }
    REQUIRE(pq.next(value, priority) == false);
    REQUIRE(pq.Size() == n);
    REQUIRE(pq.dequeue() == 1);
    REQUIRE(pq.dequeue() == 16);
    REQUIRE(pq.dequeue() == 17);

    map <int, vector<int>> map2;
    int n2 = 6;
    int vals2[] = {15, 6, 7, 8, 9, 2};
    int prs2[] = {5, 4, 7, 7, 7, 10};
    for (int i = 0; i < n2; i++) {
        map2[prs2[i]].push_back(vals2[i]);
    }

    pq.begin();
    for (int i = 0; i < n - 3 - 1; i++) {
        REQUIRE(pq.next(value, priority) == true);
        REQUIRE(map2[priority].front() == value);
        map2[priority].erase(map2[priority].begin());
    }
    REQUIRE(pq.next(value, priority) == false);
    pq.clear();
    REQUIRE(pq.Size() == 0);
}

TEST_CASE("begin and next dupes at root") {
    map <int, vector<int>> map;
    int n = 9;
    int vals[] = {15, 16, 17, 6, 7, 8, 9, 2, 1};
    int prs[] = {5, 5, 5, 5, 7, 7, 7, 10, 1};
    priorityqueue<int> pq;

    for (int i = 0; i < n; i++) {
        pq.enqueue(vals[i], prs[i]);
        map[prs[i]].push_back(vals[i]);
    }

    REQUIRE(pq.Size() == n);
    int value;
    int priority;
    REQUIRE(pq.next(value, priority) == false);
    pq.begin();
    for(int i = 0; i < n - 1; i++) {
        REQUIRE(pq.next(value, priority) == true);
        REQUIRE(map[priority].front() == value);
        map[priority].erase(map[priority].begin());
    }

    REQUIRE(pq.next(value, priority) == false);
    pq.begin();
    REQUIRE(pq.next(value, priority) == true);
    pq.dequeue();
    REQUIRE(pq.next(value, priority) == false);
    REQUIRE(pq.Size() == n - 1);
    pq.clear();
    REQUIRE(pq.Size() == 0);
}

TEST_CASE("begin and next test with dequeue") {
    map <int, vector<int>> map;
    int n = 9;
    int vals[] = {15, 16, 17, 6, 7, 8, 9, 2, 1};
    int prs[] = {5, 4, 3, 2, 7, 8, 9, 10, 11};
    priorityqueue<int> pq;

    for (int i = 0; i < n; i++) {
        pq.enqueue(vals[i], prs[i]);
        map[prs[i]].push_back(vals[i]);
    }

    REQUIRE(pq.Size() == n);
    int value;
    int priority;
    pq.begin();
    while(pq.next(value, priority)) {
        REQUIRE(map[priority].back() == value);
        map[priority].pop_back();
        REQUIRE(pq.dequeue() == value);
    }
    REQUIRE(pq.Size() == 0);
}
