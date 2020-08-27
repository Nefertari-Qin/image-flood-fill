#define CATCH_CONFIG_MAIN
#include <iostream>
#include "cs221util/catch.hpp"
#include "stack.h"
#include "queue.h"
#include "deque.h"
using namespace std;

TEST_CASE("GIVEN stack::add() and peek()","[weight=1][part=stack]"){
    Stack<int> intStack;
    intStack.add(1);
    REQUIRE( intStack.peek() == 1);
}

TEST_CASE("GIVEN stack::add,remove,add,peek ","[weight=1][part=stack]"){
    Stack<int> intStack;
    intStack.add(1);
    int i = intStack.remove();
    intStack.add(2);

    REQUIRE( intStack.peek() == 2);
}

TEST_CASE("GIVEN stack::basic functions","[weight=1][part=stack]"){
    Stack<int> intStack;
    vector<int> result;
    vector<int> expected;
    for (int i = 10; i > 0; i--) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intStack.push(i);
    }
    while (!intStack.isEmpty()) {
        result.push_back(intStack.pop());
    }
    REQUIRE( result == expected);
}

TEST_CASE("GIVEN queue::basic functions","[weight=1][part=queue]"){
    Queue<int> intQueue;
    vector<int> result;
    vector<int> expected;
    for (int i = 1; i <= 10; i++) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intQueue.enqueue(i);
    }
    while (!intQueue.isEmpty()) {
        result.push_back(intQueue.dequeue());
    }
    REQUIRE(result == expected);
}

TEST_CASE("GIVEN stack::big miscellaneous ops","[weight=1][part=stack]"){
    Stack<int> intStack;
    vector<int> result;
    vector<int> expected;
    for (int i = 500; i > 0; i--) {
        expected.push_back(0);
    }
    for (int i = 500; i > 0; i--) {
        expected.push_back(1);
    }
    for (int i = 500; i > 0; i--) {
        expected.push_back(2);
    }
    for (int i = 500; i > 0; i--) {
        expected.push_back(3);
    }
    for (int i = 500; i > 0; i--) {
        expected.push_back(3);
    }
    for (int i = 500; i > 0; i--) {
        expected.push_back(2);
    }
    for (int i = 500; i > 0; i--) {
        expected.push_back(1);
    }
    for (int i = 500; i > 0; i--) {
        expected.push_back(0);
    }


    for (int i = 1; i <= 500; i++) {
        intStack.push(0);
    }
    for (int i = 1; i <= 500; i++) {
        intStack.push(1);
    }
    for (int i = 1; i <= 500; i++) {
        intStack.push(2);
    }
    for (int i = 1; i <= 500; i++) {
        intStack.push(3);
    }
    for (int i = 1; i <= 500; i++) {
        intStack.push(3);
    }
    for (int i = 1; i <= 500; i++) {
        intStack.push(2);
    }
    for (int i = 1; i <= 500; i++) {
        intStack.push(1);
    }
    for (int i = 1; i <= 500; i++) {
        intStack.push(0);
    }

    while (!intStack.isEmpty()) {
        result.push_back(intStack.pop());
    }
    REQUIRE( result == expected);
}