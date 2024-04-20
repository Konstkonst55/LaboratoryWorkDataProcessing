#pragma once

#ifndef NODE_H
#define NODE_H

struct Node {
public:
    int data;
    Node* next;

    Node(int data) {
        this->data = data;
        this->next = nullptr;
    }
};

#endif // !NODE_H