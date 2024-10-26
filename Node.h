#pragma once

#ifndef NODE_H
#define NODE_H

struct Node {
    int data;
    Node* next;

    Node(int data) {
        this->data = data;
        this->next = nullptr;
    }

    Node() {
        this->data = 0;
        this->next = nullptr;
    }
};

struct Node16
{
	Node16* next;
	union {
		short int data;
		unsigned char digit[sizeof(data)];
	};
};

struct Node32
{
	Node32* next;
	union {
		int data;
		unsigned char digit[sizeof(data)];
	};
};

class Vertex {
public:
    int value;
    Vertex* left;
    Vertex* right;
    int balance;
    int weight;

    Vertex(int val = 0, int bal = 0, int wgh = 0) : value(val), left(nullptr), right(nullptr), balance(bal), weight(wgh) { }
};

#endif // !NODE_H