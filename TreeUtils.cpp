
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

void BinaryTree::PrintRootLeftRight() {
    std::function<void(Vertex*)> Traverse = [&](Vertex* node) {
        if (node != nullptr) {
            std::cout << node->value << " ";
            Traverse(node->left);
            Traverse(node->right);
        }
    };

    Traverse(root);
}

void BinaryTree::PrintLeftRootRight() {
    std::function<void(Vertex*)> Traverse = [&](Vertex* node) {
        if (node != nullptr) {
            Traverse(node->left);
            std::cout << node->value << " ";
            Traverse(node->right);
        }
    };

    Traverse(root);
}

void BinaryTree::PrintLeftRightRoot() {
    std::function<void(Vertex*)> Traverse = [&](Vertex* node) {
        if (node != nullptr) {
            Traverse(node->left);
            Traverse(node->right);
            std::cout << node->value << " ";
        }
    };

    Traverse(root);
}

void BinaryTree::PrintInfo() {
    int treeSize = this->GetSize();

    std::cout << "Size        " << treeSize << std::endl;
    std::cout << "Sum         " << this->GetSum() << std::endl;
    std::cout << "Height      " << this->GetHeight() << std::endl;
    std::cout << "Avg height  " << std::fixed << std::setprecision(2) << this->GetAvgHeight() << std::endl;
}

int BinaryTree::GetSize() {
    std::function<int(Vertex*)> CalculateSizeRecursive = [&](Vertex* node) -> int {
        if (node == nullptr) return 0;

        return 1 + CalculateSizeRecursive(node->left) + CalculateSizeRecursive(node->right);
        };

    return CalculateSizeRecursive(root);
}

int BinaryTree::GetSum() {
    std::function<int(Vertex*)> CalculateSumRecursive = [&](Vertex* node) -> int {
        if (node == nullptr) return 0;

        return node->value + CalculateSumRecursive(node->left) + CalculateSumRecursive(node->right);
        };

    return CalculateSumRecursive(root);
}

int BinaryTree::GetHeight() {
    std::function<int(Vertex*)> CalculateHeightRecursive = [&](Vertex* node) -> int {
        if (node == nullptr) return 0;

        return 1 + max(CalculateHeightRecursive(node->left), CalculateHeightRecursive(node->right));
        };

    return CalculateHeightRecursive(root);
}

double BinaryTree::GetAvgHeight() {
    int totalHeight = 0;
    this->CalculateSumOfPath(1, totalHeight);
    
    return static_cast<double>(totalHeight) / this->GetSize();
}

void BinaryTree::CalculateSumOfPath(int currentHeight, int& totalHeight) {
    std::function<void(Vertex*, int)> CalculateSumOfPathRecursive = [&](Vertex* node, int currentHeight) {
        if (node == nullptr) return;

        totalHeight += currentHeight;

        CalculateSumOfPathRecursive(node->left, currentHeight + 1);
        CalculateSumOfPathRecursive(node->right, currentHeight + 1);
    };

    CalculateSumOfPathRecursive(root, currentHeight);
}

Vertex* BinaryTree::FindVertex(int key) {
    std::function<Vertex* (Vertex*, int)> FindVertexRecursive = [&](Vertex* node, int value) -> Vertex* {
        if (node == nullptr || node->value == value) return node;

        Vertex* leftResult = FindVertexRecursive(node->left, value);

        return leftResult ? leftResult : FindVertexRecursive(node->right, value);
    };

    return FindVertexRecursive(root, key);
}

void BinaryTree::AddVertex(int data) {
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

bool BinaryTree::DeleteVertex(int key) {
    std::function<Vertex** (Vertex**, int)> FindVertexPointerRecursive = [&](Vertex** node, int value) -> Vertex** {
        if (*node == nullptr) return node;
        if ((*node)->value < value) return FindVertexPointerRecursive(&((*node)->right), value);
        if ((*node)->value > value) return FindVertexPointerRecursive(&((*node)->left), value);

        return node;
    };

    Vertex** p = FindVertexPointerRecursive(&root, key);

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
        return true;
    }

    return false;
}

void BinaryTree::Delete() {
    std::function<void(Vertex*)> DeleteTreeRecursive= [&](Vertex* node) {
        if (node == nullptr) return;

        DeleteTreeRecursive(node->left);
        DeleteTreeRecursive(node->right);
        
        delete node;
    };
    
    DeleteTreeRecursive(root);
    
    root = nullptr;
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

void AVL::RotateLL(Vertex*& p) {
    Vertex* q = p->left;

    if (!q) return;

    p->balance = q->balance = 0;
    p->left = q->right;
    q->right = p;
    p = q;
}

void AVL::RotateRR(Vertex*& p) {
    Vertex* q = p->right;

    if (!q) return;

    p->balance = q->balance = 0;
    p->right = q->left;
    q->left = p;
    p = q;
}

void AVL::RotateLR(Vertex*& p) {
    Vertex* q = p->left;
    Vertex* r = q->right;

    if (!q || !r) return;

    p->balance = r->balance < 0 ? 1 : 0;
    q->balance = r->balance > 0 ? -1 : 0;

    r->balance = 0;
    q->right = r->left;
    p->left = r->right;
    r->left = q;
    r->right = p;
    p = r;
}

void AVL::RotateRL(Vertex*& p) {
    Vertex* q = p->right;
    Vertex* r = q->left;

    if (!q || !r) return;

    p->balance = r->balance > 0 ? -1 : 0;
    q->balance = r->balance < 0 ? 1 : 0;

    r->balance = 0;
    q->left = r->right;
    p->right = r->left;
    r->right = q;
    r->left = p;
    p = r;
}

void AVL::RotateLL1(Vertex*& p) {
    Vertex* q = p->left;

    if (!q) return;

    if (q->balance == 0) {
        q->balance = 1;
        p->balance = -1;
        _decrease = false;
    }
    else {
        p->balance = q->balance = 0;
    }

    p->left = q->right;
    q->right = p;
    p = q;
}

void AVL::RotateRR1(Vertex*& p) {
    Vertex* q = p->right;

    if (!q) return;

    if (q->balance == 0) {
        q->balance = -1;
        p->balance = 1;
        _decrease = false;
    }
    else {
        p->balance = q->balance = 0;
    }

    p->right = q->left;
    q->left = p;
    p = q;
}

void AVL::DeleteT2(Vertex*& p, Vertex*& q) {
    if (p->right) {
        DeleteT2(p->right, q);

        if (_decrease) {
            BalanceRightDelete(p);
        }
    }
    else {
        q->value = p->value;
        q = p;
        p = p->right;
        _decrease = true;
    }
}

void AVL::BalanceLeftDelete(Vertex*& p) {
    if (p->balance == -1) {
        p->balance = 0;
    }
    else if (p->balance == 0) {
        p->balance = 1;
        _decrease = false;
    }
    else if (p->balance == 1) {
        p->right->balance >= 0 ? RotateRR1(p) : RotateRL(p);
    }
}

void AVL::BalanceRightDelete(Vertex*& p) {
    if (p->balance == 1) {
        p->balance = 0;
    }
    else if (p->balance == 0) {
        p->balance = -1;
        _decrease = false;
    }
    else if (p->balance = -1) {
        p->left->balance <= 0 ? RotateLL1(p) : RotateLR(p);
    }
}

void AVL::AddVertex(int data) {
    _grow = true;

    auto BalanceLeft = [&](Vertex*& p) {
        if (p->balance > 0) {
            p->balance = 0;
            _grow = false;
        }
        else if (p->balance == 0) {
            p->balance = -1;
            _grow = true;
        }
        else {
            p->left->balance < 0 ? RotateLL(p) : RotateLR(p);
            _grow = false;
        }
    };

    auto BalanceRight = [&](Vertex*& p) {
        if (p->balance < 0) {
            p->balance = 0;
            _grow = false;
        }
        else if (p->balance == 0) {
            p->balance = 1;
            _grow = true;
        }
        else {
            p->right->balance > 0 ? RotateRR(p) : RotateRL(p);
            _grow = false;
        }
    };

    std::function<void(Vertex*&)> AddVertexRecursive = [&](Vertex*& p) {
        if (!p) {
            p = CreateVertex(data);
            _grow = true;
        }

        if (p->value > data) {
            AddVertexRecursive(p->left);

            if (_grow) {
                BalanceLeft(p);
            }
        }
        else if (p->value < data) {
            AddVertexRecursive(p->right);

            if (_grow) {
                BalanceRight(p);
            }
        }
    };

    AddVertexRecursive(root);
}

bool AVL::DeleteVertex(int key) {
    _decrease = false;
    
    std::function<bool(Vertex*&)> DeleteVertexRecursive = [&](Vertex*& p) {
        if (!p) return false;

        Vertex* q = nullptr;

        if (key < p->value) {
            DeleteVertexRecursive(p->left);

            if (_decrease) {
                BalanceLeftDelete(p);
            }
        }
        else if (key > p->value) {
            DeleteVertexRecursive(p->right);

            if (_decrease) {
                BalanceRightDelete(p);
            }
        }
        else {
            q = p;

            if (!q->left) {
                p = q->right;
                _decrease = true;
            }
            else if (!q->right) {
                p = q->left;
                _decrease = true;
            }
            else {
                DeleteT2(q->left, q);

                if (_decrease) {
                    BalanceLeftDelete(p);
                }
            }
        }

        delete(q);
        return true;
    };

    return DeleteVertexRecursive(root);
}

Vertex* CreateVertex(int value) {
    return new Vertex(value);
}
