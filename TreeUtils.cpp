
#include "TreeUtils.h"

#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <iomanip>
#include <windows.h>
#include <functional>

BinaryTree::BinaryTree() : root(nullptr) {
}

BinaryTree::~BinaryTree(){
    BinaryTree::Delete();
}

void BinaryTree::PrintRootLeftRightRecursive(Vertex* node) {
    if (node != nullptr) {
        std::cout << node->value << " ";
        PrintRootLeftRightRecursive(node->left);
        PrintRootLeftRightRecursive(node->right);
    }
}

void BinaryTree::PrintLeftRootRightRecursive(Vertex* node) {
    if (node != nullptr) {
        PrintLeftRootRightRecursive(node->left);
        std::cout << node->value << " ";
        PrintLeftRootRightRecursive(node->right);
    }
}

void BinaryTree::PrintLeftRightRootRecursive(Vertex* node) {
    if (node != nullptr) {
        PrintLeftRightRootRecursive(node->left);
        PrintLeftRightRootRecursive(node->right);
        std::cout << node->value << " ";
    }
}

int BinaryTree::CalculateTreeSizeRecursive(Vertex* node) {
    if (node == nullptr) return 0;

    return 1 + CalculateTreeSizeRecursive(node->left) + CalculateTreeSizeRecursive(node->right);
}

int BinaryTree::CalculateTreeSumRecursive(Vertex* node) {
    if (node == nullptr) return 0;

    return node->value + CalculateTreeSumRecursive(node->left) + CalculateTreeSumRecursive(node->right);
}

int BinaryTree::CalculateTreeHeightRecursive(Vertex* node) {
    if (node == nullptr) return 0;

    return 1 + max(CalculateTreeHeightRecursive(node->left), CalculateTreeHeightRecursive(node->right));
}

void BinaryTree::CalculateSumOfPathRecursive(Vertex* node, int currentHeight, int& totalHeight) {
    if (node == nullptr) return;

    totalHeight += currentHeight;
    CalculateSumOfPathRecursive(node->left, currentHeight + 1, totalHeight);
    CalculateSumOfPathRecursive(node->right, currentHeight + 1, totalHeight);
}

Vertex* BinaryTree::FindVertexRecursive(Vertex* node, int value) {
    if (node == nullptr || node->value == value) {
        return node;
    }

    Vertex* leftResult = FindVertexRecursive(node->left, value);

    if (leftResult) {
        return leftResult;
    }

    return FindVertexRecursive(node->right, value);
}
Vertex** BinaryTree::FindVertexPointer(Vertex** node, int value) {
    if (*node == nullptr) {
        return node;
    }

    if ((*node)->value < value) {
        return FindVertexPointer(&((*node)->right), value);
    }
    else if ((*node)->value > value) {
        return FindVertexPointer(&((*node)->left), value);
    }
    else {
        return node;
    }
}

bool BinaryTree::DeleteVertexRecursive(Vertex* node, int value) {
    Vertex** p = &root;
    p = FindVertexPointer(p, value);

    if (*p != nullptr) {
        Vertex* q = *p;

        if (q->left == nullptr) {
            *p = q->right;
        }
        else if (q->right == nullptr) {
            *p = q->left;
        }
        else {
            Vertex* r = q->left;
            Vertex* s = q;

            while (r->right != nullptr) {
                s = r;
                r = r->right;
            }

            if (s == q) {
                r->right = q->right;
                *p = r;
            }
            else {
                s->right = r->left;
                r->left = q->left;
                r->right = q->right;
                *p = r;
            }
        }

        delete q;
    }
    else {
        return false;
    }

    return true;
}

void BinaryTree::DeleteTreeRecursive(Vertex* node) {
    if (node == nullptr) return;

    DeleteTreeRecursive(node->left);
    DeleteTreeRecursive(node->right);
    delete node;
}

void BinaryTree::PrintRootLeftRight() {
    BinaryTree::PrintRootLeftRightRecursive(root);
}

void BinaryTree::PrintLeftRootRight() {
    BinaryTree::PrintLeftRootRightRecursive(root);
}

void BinaryTree::PrintLeftRightRoot() {
    BinaryTree::PrintLeftRightRootRecursive(root);
}

void BinaryTree::PrintInfo() {
    int treeSize = this->GetSize();

    std::cout << "Size        " << treeSize << std::endl;
    std::cout << "Sum         " << this->GetSum() << std::endl;
    std::cout << "Height      " << this->GetHeight() << std::endl;
    std::cout << "Avg height  " << std::fixed << std::setprecision(2) << this->GetAvgHeight() << std::endl;
}

int BinaryTree::GetSize() {
    return BinaryTree::CalculateTreeSizeRecursive(root);
}

int BinaryTree::GetSum() {
    return BinaryTree::CalculateTreeSumRecursive(root);
}

int BinaryTree::GetHeight() {
    return BinaryTree::CalculateTreeHeightRecursive(root);
}

double BinaryTree::GetAvgHeight() {
    int totalHeight = 0;
    this->CalculateSumOfPath(1, totalHeight);
    
    return static_cast<double>(totalHeight) / this->GetSize();
}

void BinaryTree::CalculateSumOfPath(int currentHeight, int& totalHeight) {
    BinaryTree::CalculateSumOfPathRecursive(root, currentHeight, totalHeight);
}

Vertex* BinaryTree::FindVertex(int key) {
    return FindVertexRecursive(root, key);
}

bool BinaryTree::DeleteVertex(int key) {
    return DeleteVertexRecursive(root, key);
}

void BinaryTree::Delete() {
    BinaryTree::DeleteTreeRecursive(root);
}

Vertex* CreateVertex(int value) {
    return new Vertex(value);
}

PBST::PBST() : BinaryTree() { }

void PBST::Create(int* arr, int size) {
    std::function<Vertex* (int, int, int[])> CreatePBSTRecursive = [&CreatePBSTRecursive](int left, int right, int arr[]) -> Vertex* {
        if (left > right) return nullptr;

        int m = left + (right - left) / 2;
        Vertex* node = new Vertex(arr[m]);

        node->left = CreatePBSTRecursive(left, m - 1, arr);
        node->right = CreatePBSTRecursive(m + 1, right, arr);

        return node;
    };

    root = CreatePBSTRecursive(0, size - 1, arr);
}

RST::RST() : BinaryTree() { }

void RST::AddVertex(int data) {
    std::function<void(Vertex*&)> AddRecursive = [&AddRecursive, &data](Vertex*& root) {
        if (!root) {
            root = new Vertex(data);
        }
        else if (data < root->value) {
            AddRecursive(root->left);
        }
        else if (data > root->value) {
            AddRecursive(root->right);
        }
    };

    return AddRecursive(root);
}

void RST::AddVertexDoubleIndirection(int data) {
    Vertex** p = &root;

    while (*p != nullptr) {
        if (data < (*p)->value) {
            p = &((*p)->left);
        }
        else if (data > (*p)->value) {
            p = &((*p)->right);
        }
        else {
            break;
        }
    }

    if (!*p) (*p) = new Vertex(data);
}

AVL::AVL() : BinaryTree() { }

void AVL::RotateLL(Vertex*& node) {
    Vertex* q = node->left;

    if (!q) return;

    node->balance = q->balance = 0;
    node->left = q->right;
    q->right = node;
    node = q;
}

void AVL::RotateRR(Vertex*& node) {
    Vertex* q = node->right;

    if (!q) return;

    node->balance = q->balance = 0;
    node->right = q->left;
    q->left = node;
    node = q;
}

void AVL::RotateLR(Vertex*& node) {
    Vertex* q = node->left;
    Vertex* r = q->right;

    if (!q || !r) return;

    node->balance = r->balance < 0 ? 1 : 0;
    q->balance = r->balance > 0 ? -1 : 0;

    r->balance = 0;
    q->right = r->left;
    node->left = r->right;
    r->left = q;
    r->right = node;
    node = r;
}

void AVL::RotateRL(Vertex*& node) {
    Vertex* q = node->right;
    Vertex* r = q->left;

    if (!q || !r) return;

    node->balance = r->balance > 0 ? -1 : 0;
    q->balance = r->balance < 0 ? 1 : 0;

    r->balance = 0;
    q->left = r->right;
    node->right = r->left;
    r->right = q;
    r->left = node;
    node = r;
}

void AVL::AddVertex(int data) {
    bool grow = true;

    auto BalanceLeft = [&](Vertex*& p) {
        if (p->balance > 0) {
            p->balance = 0;
            grow = false;
        }
        else if (p->balance == 0) {
            p->balance = -1;
            grow = true;
        }
        else {
            p->left->balance < 0 ? RotateLL(p) : RotateLR(p);
            grow = false;
        }
    };

    auto BalanceRight = [&](Vertex*& p) {
        if (p->balance < 0) {
            p->balance = 0;
            grow = false;
        }
        else if (p->balance == 0) {
            p->balance = 1;
            grow = true;
        }
        else {
            p->right->balance > 0 ? RotateRR(p) : RotateRL(p);
            grow = false;
        }
    };

    std::function<void(Vertex*&)> AddVertexRecursive = [&](Vertex*& p) {
        if (!p) {
            p = new Vertex(data);
            grow = true;
        }

        if (p->value > data) {
            AddVertexRecursive(p->left);

            if (grow) {
                BalanceLeft(p);
            }
        }
        else if (p->value < data) {
            AddVertexRecursive(p->right);

            if (grow) {
                BalanceRight(p);
            }
        }
    };

    AddVertexRecursive(root);
}
