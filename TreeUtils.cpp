
#include "TreeUtils.h"
#include "ArrayUtils.h"

#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <iomanip>
#include <windows.h>
#include <functional>
#include <algorithm>
#include <utility>

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

void BinaryTree::AddVertex(int data, int bal, int wgh) {
    std::function<void(Vertex*&)> AddRecursive = [&AddRecursive, &data, &bal, &wgh](Vertex*& root) {
        if (!root) {
            root = new Vertex(data, bal, wgh);
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

void AVL::AddVertex(int data, int bal, int wgh) {
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
            p = CreateVertex(data, bal, wgh);
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

BBT::BBT() : BinaryTree() { }

void BBT::AddVertex(int data, int bal, int wgh) {
    std::function<void(Vertex*&)> AddVertexRecursive = [&](Vertex*& p) {
        if (p == nullptr) {
            p = CreateVertex(data, bal, wgh);
            _vr = true;
            return;
        }

        if (data < p->value) {
            AddVertexRecursive(p->left);

            if (_vr) {
                if (p->balance == 0) {
                    Vertex* q = p->left;
                    p->left = q->right;
                    q->right = p;
                    p = q;
                    q->balance = 1;
                    _vr = false;
                    _hr = true;
                }
                else {
                    p->balance = 0;
                    _vr = true;
                    _hr = false;
                }
            }
        }
        else if (data > p->value) {
            AddVertexRecursive(p->right);

            if (_vr) {
                p->balance = 1;
                _hr = true;
                _vr = false;
            }
            else if (_hr) {
                if (p->balance == 1) {
                    Vertex* q = p->right;
                    p->balance = q->balance = 0;
                    p->right = q->left;
                    q->left = p;
                    p = q;
                    _vr = true;
                }

                _hr = false;
            }
        }
    };

    AddVertexRecursive(root);
}

int BBT::GetLevels() const {
    std::function<int(Vertex*)> height = [&height](Vertex* p) {
        return p ? 1 - p->balance + max(height(p->left), height(p->right)) : 0;
    };

    return height(root);
}

void OST::CalculateWeights(const std::vector<std::pair<int, int>>& keysWithWeights) {
    int n = keysWithWeights.size();
    _weights.resize(n + 1, std::vector<int>(n + 1, 0));

    for (int i = 0; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            _weights[i][j] = _weights[i][j - 1] + keysWithWeights[j - 1].second;
        }
    }
}

void OST::CalculateHeightsRoots(int n) {
    _heights.resize(n + 1, std::vector<int>(n + 1, 0));
    _roots.resize(n + 1, std::vector<int>(n + 1, 0));

    for (int i = 0; i < n; i++) {
        int j = i + 1;
        _heights[i][j] = _weights[i][j];
        _roots[i][j] = j;
    }

    for (int h = 2; h <= n; h++) {
        for (int i = 0; i + h <= n; i++) {
            int j = i + h;
            int minRoot = _roots[i][j - 1];
            int minCost = _heights[i][minRoot - 1] + _heights[minRoot][j];

            for (int k = minRoot + 1; k <= _roots[i + 1][j]; k++) {
                int cost = _heights[i][k - 1] + _heights[k][j];

                if (cost < minCost) {
                    minCost = cost;
                    minRoot = k;
                }
            }

            _heights[i][j] = minCost + _weights[i][j];
            _roots[i][j] = minRoot;
        }
    }
}

OST::OST() : BinaryTree() { }

const std::vector<std::vector<int>>& OST::GetWeights() const {
    return _weights;
}

const std::vector<std::vector<int>>& OST::GetHeights() const {
    return _heights;
}

const std::vector<std::vector<int>>& OST::GetRoots() const {
    return _roots;
}

double OST::GetWeightedAvgHeight() const {
    int totalWeightedHeight = 0, totalWeight = 0;

    std::function<void(Vertex*, int)> СalculateWeightedHeight = [&](Vertex* node, int currentHeight) {
        if (!node) return;

        totalWeightedHeight += node->weight * currentHeight;
        totalWeight += node->weight;

        СalculateWeightedHeight(node->left, currentHeight + 1);
        СalculateWeightedHeight(node->right, currentHeight + 1);
    };

    СalculateWeightedHeight(root, 1);

    return totalWeight > 0 ? static_cast<double>(totalWeightedHeight) / totalWeight : 0.0;
}

double OST::GetRatioHeightsWeights() const {
    int n = _heights[0].size() - 1;

    return (n >= 0 && _weights[0][n] != 0) ? static_cast<double>(_heights[0][n]) / _weights[0][n] : 0.0;
}

void OST::Create(std::vector<std::pair<int, int>>& keysWithWeights) {
    const int n = keysWithWeights.size();
    
    CalculateWeights(keysWithWeights);
    CalculateHeightsRoots(n);

    std::function<void(int, int)> CreateTree = [&](int left, int right) {
        if (left < right) {
            int k = _roots[left][right];

            AddVertex(keysWithWeights[k - 1].first, 0, keysWithWeights[k - 1].second);
            CreateTree(left, k - 1);
            CreateTree(k, right);
        }
    };

    CreateTree(0, n);
}

void A1::QuickSortPairs(std::vector<std::pair<int, int>>& keysWithWeights, comparatorType comp) {
    std::function<void(int, int)> QuickSortPairsRecursive;

    QuickSortPairsRecursive = [&keysWithWeights, &QuickSortPairsRecursive, &comp](int l, int r) {
        if (l >= r) return;

        std::pair<int, int> pivot = keysWithWeights[l];
        int i = l, j = r;

        while (i <= j) {
            while (comp(keysWithWeights[i], pivot)) {
                i++;
            }

            while (comp(pivot, keysWithWeights[j])) {
                j--;
            }

            if (i <= j) {
                std::swap(keysWithWeights[i++], keysWithWeights[j--]);
            }
        }

        if (l < j) QuickSortPairsRecursive(l, j);
        if (i < r) QuickSortPairsRecursive(i, r);
    };

    QuickSortPairsRecursive(0, keysWithWeights.size() - 1);
}

A1::A1() : OST() { }

void A1::Create(std::vector<std::pair<int, int>>& keysWithWeights) {
    QuickSortPairs(keysWithWeights);

    for (const auto& pair : keysWithWeights) {
        AddVertex(pair.first, 0, pair.second);
    }
}

A2::A2() : A1() { }

void A2::Create(std::vector<std::pair<int, int>>& keysWithWeights) {
    const int n = keysWithWeights.size();

    QuickSortPairs(keysWithWeights, [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return (a.first < b.first);
    });

    std::function<void(int, int)> CreateTree = [&](int left, int right) {
        if (left <= right) {
            double weight = 0.0;
            int sum = 0, i = 0;

            for (i = left; i <= right; i++) {
                weight += keysWithWeights[i].second;
            }

            for (i = left; i <= right; i++) {
                if ((sum < weight / 2.0) && (sum + keysWithWeights[i].second >= weight / 2.0)) {
                    break;
                }

                sum += keysWithWeights[i].second;
            }

            AddVertex(keysWithWeights[i].first, 0, keysWithWeights[i].second);

            CreateTree(left, i - 1);
            CreateTree(i + 1, right);
        }
    };

    CreateTree(0, n - 1);
}

Vertex* CreateVertex(int value, int balance, int weight) {
    return new Vertex(value, balance, weight);
}
